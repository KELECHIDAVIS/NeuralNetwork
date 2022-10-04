#include "Layer.h"
//  REMEMBER EVERY TIME MY LIBRARY RETURNS A MATRIX FROM A STATIC FUNCTION TO DELETE IT TO AVOID MEMORY LEAK 
int main()
{
    Matrix *input = new Matrix(10, 3 );
    input->randomize(0,1); 
     
    Layer layer(3,2);
    
    Matrix * output =  layer.feedForward(input);    
    output -> print(); 
    delete input; 
    delete output ; 
    return 0 ; 
}  