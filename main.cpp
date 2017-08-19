#include "stdio.h"
#include "QTree.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
int main( int argc, const char * argv[] )
{
    printf( "Simple quad tree presentation\n" );
    
    const float posX = 0.0f;
    const float posY = 0.0f;
    const float dim = 40.0f;
    const int level = 4;
    const float cellSize = dim / 4.0;
    
    CTree tree;
    tree.Init( posX, posY, dim, level );
    
    const int fieldSize = 10;
    const int halfFiedSize = fieldSize / 2;
    const float halfFieldStep = halfFiedSize * cellSize;
    
    for( int i = 0; i < fieldSize; ++i )
    {
        for( int j = 0; j < fieldSize; ++j )
        {
            const float x = ( j * cellSize ) - halfFieldStep;
            const float y = ( i * cellSize ) - halfFieldStep;
            
            const SNode *pNode = tree.GetNodeAtPos( x, y );
            if( pNode )
            {
                printf( "[%03d]", pNode->dbgID );
            }
            else
            {
                printf( "[---]" );
            }
            
            
        }
        printf( "\n" );
    }
    
    
    
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
