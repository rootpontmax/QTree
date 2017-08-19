#include "stdio.h"
#include "QTree.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
static void ReportNode( const SNode *pNode )
{
    if( pNode )
        printf( "[%03d]", pNode->dbgID );
    else
        printf( "[---]" );
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int main( int argc, const char * argv[] )
{
    printf( "Simple quad tree presentation\n" );
    
    const float posX = 0.0f;
    const float posY = 0.0f;
    const float dim = 40.0f;
    const int level = 3;
    
    CTree tree;
    tree.Init( posX, posY, dim, level );
    
    const float fieldHalfSize = 45.0f;
    const float fieldStepSize = 10.0f;
    for( int i = 0; i < 10; ++i )
    {
        for( int j = 0; j < 10; ++j )
        {
            const float x = -fieldHalfSize + j * fieldStepSize;
            const float y = -fieldHalfSize + i * fieldStepSize;
            const SNode *pNode = tree.GetNodeAtPos( x, y );
            ReportNode( pNode );
        }
        printf( "\n" );
    }
    
    
    
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
