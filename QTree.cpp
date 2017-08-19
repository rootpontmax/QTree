#include "QTree.h"
#include <cassert>

////////////////////////////////////////////////////////////////////////////////////////////////////
static int CalcTotalNodesCount( const int levels )
{
    int nodesCount = 1;
    for( int i = 1; i <= levels; ++i )
    {
        const int thisLevelCount = 1 << ( i * 2 );
        nodesCount += thisLevelCount;
    }
    return nodesCount;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
SNode::SNode() :
    pParent( nullptr ),
    pChild{ nullptr, nullptr, nullptr, nullptr },
    pData( nullptr ),
    posX( 0.0f ),
    posY( 0.0f ),
    dimX( 0.0f ),
    dimY( 0.0f ),
    dbgID( -1 )
{}
////////////////////////////////////////////////////////////////////////////////////////////////////
CTree::CTree() :
    m_pRoot( nullptr )
{}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CTree::Init( const float posX, const float posY,
                      const float dimension, const int levels )
{
    // Pre-allocate required size
    const int totalNodesCount = CalcTotalNodesCount( levels );
    m_data.reserve( totalNodesCount );
    
    // Create root node
    m_pRoot = CreateNode();
    m_pRoot->pParent = nullptr;
    m_pRoot->posX = posX;
    m_pRoot->posY = posY;
    m_pRoot->dimX = dimension;
    m_pRoot->dimY = dimension;
    
    SplitNode( m_pRoot, levels );
    
    printf( "Total nodes count: %d/%d\n", (int)m_data.size(), (int)m_data.capacity() );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
const SNode *CTree::GetNodeAtPos( const float x, const float y ) const
{
    return GetLeafRecursive( m_pRoot, x, y );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
SNode *CTree::CreateNode()
{
    assert( ( m_data.size() + 1 ) <= m_data.capacity() );
    
    const int dbgID = static_cast< int >( m_data.size() );
    SNode emptyNode;
    m_data.push_back( emptyNode );
    
    SNode *pNode = &m_data[m_data.size() - 1];
    pNode->dbgID = dbgID;
    return pNode;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CTree::SplitNode( SNode *pNode, const int level )
{
    const int childLevel = level - 1;
    if( childLevel < 0 )
        return;
    
    // Subnodes configuration
    // 0---1
    // |   |
    // 2---3
    
    pNode->pChild[0] = CreateNode();
    pNode->pChild[1] = CreateNode();
    pNode->pChild[2] = CreateNode();
    pNode->pChild[3] = CreateNode();
    
    // Assing parent node for all children
    const float childDimX = pNode->dimX / 2.0f;
    const float childDimY = pNode->dimY / 2.0f;
    for( int i = 0; i < 4; ++i )
    {
        pNode->pChild[i]->pParent = pNode;
        pNode->pChild[i]->dimX = childDimX;
        pNode->pChild[i]->dimY = childDimY;
        pNode->pChild[i]->posX = pNode->posX;
        pNode->pChild[i]->posY = pNode->posY;
    }
    
    // Move center positions
    pNode->pChild[0]->posX -= childDimX;
    pNode->pChild[0]->posY += childDimY;
    
    pNode->pChild[1]->posX += childDimX;
    pNode->pChild[1]->posY += childDimY;
    
    pNode->pChild[2]->posX -= childDimX;
    pNode->pChild[2]->posY -= childDimY;
    
    pNode->pChild[3]->posX += childDimX;
    pNode->pChild[3]->posY -= childDimY;
    
    
    for( int i = 0; i < 4; ++i )
        SplitNode( pNode->pChild[i], childLevel );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
bool CTree::IsPointInsideQuad( const SNode *pNode, const float x, const float y ) const
{
    assert( pNode );
    if( x >= ( pNode->posX - pNode->dimX ) &&
        x <= ( pNode->posX + pNode->dimX ) &&
        y >= ( pNode->posY - pNode->dimY ) &&
        y <= ( pNode->posY + pNode->dimY ) )
        return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
const SNode *CTree::GetLeafRecursive( const SNode *pNode, const float x, const float y ) const
{
    assert( pNode );
    
    if( !IsPointInsideQuad( pNode, x, y ) )
        return nullptr;
    
    for( int i = 0; i < 4; ++i )
    {
        // If this node has no child this node id leaf. Return it
        if( !pNode->pChild[i] )
            return pNode;
        
        if( IsPointInsideQuad( pNode->pChild[i], x, y ) )
            return GetLeafRecursive( pNode->pChild[i], x, y );
    }
    
    return nullptr;
    
}
////////////////////////////////////////////////////////////////////////////////////////////////////

