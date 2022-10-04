#include "Matrix.h" 

class Layer
{
public : 
    Matrix weights; 
    Matrix biases ; // 1d for every "neuron" in the layer
    unsigned incoming , outgoing;  
    Layer(unsigned incoming , unsigned outgoing)
    {
        this->incoming = incoming; 
        this->outgoing = outgoing; 
        weights= Matrix(outgoing, incoming);
        biases = Matrix(1, outgoing); 
 
    }

    ~Layer(){}

    // feedsforward : returns an array of values 
    Matrix* feedForward(Matrix* input)    
    {
        // dot products of the weights + the biases 
    }
}; 