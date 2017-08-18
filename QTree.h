////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple class for QuadTree.																	  //
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////
struct SQuadTreeNode
{
    SQuadTreeNode  *pParent;
    SQuadTreeNode  *pChild[4];
    void           *pData;
    float           posX;   // Position of center of QuadNode
    float           posY;
    float           dimX;   // Half size of QuadNode
    float           dimY;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
class CQuadTree
{
public:

    CQuadTree();
    void Init( const float posX, const float posY, const float dimension, const int levels );
                            // posX - position of center
                            // posY
                            // dimension - half size of quad tree
                            // levels - levels of hierarchy. 0 means only one node
                            
    // Get node pointer. If point outside any node nullptr is returned
    const SQuadTreeNode    *GetNodeAtPos( const float x, const float y ) const;

private:

    SQuadTreeNode  *CreateNode();
    void            SplitNode( SQuadTreeNode *pNode, const int level );

    std::vector< SQuadTreeNode >    m_data;
    SQuadTreeNode                  *m_pRoot;

	
};
////////////////////////////////////////////////////////////////////////////////////////////////////
