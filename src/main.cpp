#include "Matrix.h"
//  REMEMBER EVERY TIME MY LIBRARY RETURNS A MATRIX FROM A STATIC FUNCTION TO DELETE IT TO AVOID MEMORY LEAK 
int main()
{
    Matrix* mat = Matrix::load("data/second.csv"); 
    mat->randomize(-1,1); 
    mat->print(); 
    mat->save("data/second.csv");    
    delete mat ; 
    return 0 ; 
}
