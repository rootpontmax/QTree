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
CQuadTree::CQuadTree() :
    m_pRoot( nullptr )
{}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CQuadTree::Init( const float posX, const float posY,
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
    
    printf( "Total nodes count: %d\n", totalNodesCount );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
const SQuadTreeNode *CQuadTree::GetNodeAtPos( const float x, const float y ) const
{
    return nullptr;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
SQuadTreeNode *CQuadTree::CreateNode()
{
    assert( ( m_data.size() + 1 ) <= m_data.capacity() );
    SQuadTreeNode emptyNode;
    m_data.push_back( emptyNode );
    
    return &m_data[m_data.size() - 1];
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void CQuadTree::SplitNode( SQuadTreeNode *pNode, const int level )
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

