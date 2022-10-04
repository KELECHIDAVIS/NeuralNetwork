#include "Matrix.h" 

struct Layer {
    Matrix* weights; 
    Matrix* biases ; // 1d for every "neuron" in the layer
    unsigned incoming , outgoing;  
    Layer(unsigned incoming , unsigned outgoing)
    {
        this->incoming = incoming; 
        this->outgoing = outgoing; 
        weights = new Matrix(outgoing, incoming);
        biases = new Matrix(1, outgoing); 
        weights->randomize(-1,1);
         
        biases->randomize(0,1); 
 
    };

    ~Layer(){
        delete weights; 
        delete biases; 
    }

    // feedsforward : returns an array of values 
    // the rows of the input can be for the batches of data; for now ill just test it with one 
    // so basically each row equals one piece of data
    // FOR NOW THE ACTIVATION IS GOING TO BE IN THIS FUNCTION FOR EFFICIENCY REASON: RELU FOR NOW 
    Matrix*  feedForward(Matrix* input)     
    {
      
       
        if(incoming == input->cols)
        {
             // xN * weightN  +bias
           Matrix  *outputs = new Matrix (input->rows, outgoing); 
           for(int i =0; i<input->rows; i++)
           {
                for(int  j = 0; j<weights->rows; j++)
                {
                    float weightSum=0; 
                    for(int k = 0; k<weights->cols ; k++)
                    {
                        weightSum += weights->arr[j][k]*input->arr[i][k] ; 
                    }              
                    // now we have the weighted sum  
                    weightSum += biases->arr[0][j]; // adds the biases 
                   
                    //then add to outputs 
                    outputs->arr[i][j] = relu( weightSum);  // uses activation function  RELU FOR NOW COULD IMPLEMENT A SYSTEM FOR CHANGING IT LATE R


                }
           }
           
           
           return outputs; // return a pointer matrix of the output to the input 
        }else{
            cout<<"Wrong Dimensions in feed forward"<<endl; 
            exit(1);  

        }
    }; 

    void backProp(Matrix* input , Matrix* target) // back props and tweaks the gradients based on the error of the outputs 
    {
        if(input->rows != target->rowds) // they should have the same size 
        { 
            cout<<"Input and target matrices should have the same number of rows when calculating backprop"<<endl; 
            exit(1); // throws error
        }

    }
    float relu (float val )
    {
        if(val>0)
            return val; 

        return 0;  
    }; 

}; 