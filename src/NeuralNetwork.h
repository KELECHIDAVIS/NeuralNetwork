#include "Layer.h"
class NeuralNetwork
{
public:
    Layer* layers; 
    int numOfLayers ;  
    NeuralNetwork(vector<unsigned> top )  // topology 
    {
        numOfLayers = top.size()-1; 
        layers = new Layer[top.size()-1]; 
        for(int i =1; i<top.size(); i++)
        {
            layers[i] = new Layer(top[i-1], top[i]); 
        }
    }
    ~NeuralNetwork()
    {
        for(int i = 0; i<numOfLayers; i++)
        {
            delete layers[i]; 

        }
        delete[] layers; 
    }

    void save()
    {
        
    }

}