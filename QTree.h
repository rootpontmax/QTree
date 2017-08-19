////////////////////////////////////////////////////////////////////////////////////////////////////
// Simple class for QuadTree.																	  //
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////
struct SNode
{
    SNode();
    
    SNode  *pParent;
    SNode  *pChild[4];
    void   *pData;
    float   posX;   // Position of center of QuadNode
    float   posY;
    float   dimX;   // Half size of QuadNode
    float   dimY;
    
    int     dbgID;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
class CTree
{
public:

    CTree();
    void Init( const float posX, const float posY, const float dimension, const int levels );
                            // posX - position of center
                            // posY
                            // dimension - half size of quad tree
                            // levels - levels of hierarchy. 0 means only one node
                            
    // Get node pointer. If point outside any node nullptr is returned
    const SNode    *GetNodeAtPos( const float x, const float y ) const;

private:

    SNode          *CreateNode();
    void            SplitNode( SNode *pNode, const int level );
    bool            IsPointInsideQuad( const SNode *pNode, const float x, const float y ) const;
    const SNode    *GetLeafRecursive( const SNode *pNode, const float x, const float y ) const;

    std::vector< SNode >    m_data;
    SNode                  *m_pRoot;

	
};
////////////////////////////////////////////////////////////////////////////////////////////////////
