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
    const int newLevel = level - 1;
    if( newLevel < 0 )
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
    for( int i = 0; i < 4; ++i )
        pNode->pChild[i]->pParent = pNode;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

