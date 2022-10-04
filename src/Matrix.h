#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector> 
#include <random>
using namespace std; 
class Matrix
{
    public: 
    unsigned rows, cols; 
    float** arr; 
    Matrix(){}; 
    Matrix(unsigned row, unsigned cols )
    {
        rows = row; 
        this->cols = cols; 
        arr= new float*[rows]; // allocates the row arrays 
        for(int i = 0 ; i<rows; i++)
            arr[i] = new float[cols];  
        for(int i = 0 ; i< rows ; i++)
        {
            for(int j = 0 ; j<cols; j++)
            {
                arr[i][j]    = 0; 
            }
        } 
        
    }
    ~Matrix() // frees up memory 
    {
        for(int i =0; i<rows; i++)
            delete[] arr[i]; 
        delete[] arr; 

    }

    void randomize(float min , float max) // fills the matrix with numbers between the range 
    {
        srand(time(NULL)); 
        for(int i = 0; i<rows; i++)
        {
            for(int j = 0; j<cols; j++)
            {
                arr[i][j] =  min + (float)(rand()) /( (float) (RAND_MAX/(max-min))); ; 
            }
        }
    }

    // takes a function address at the parameter 
    void applyFunc(float(*func)(float)) // applys a function to every element in the matrix 
    {
        for(int i = 0 ; i<rows ; i++)
        {
            for(int j = 0 ; j<cols ; j++)
            {
                arr[i][j] = func(arr[i][j]); 
            }
        }
    }

    void print()
    {
        for(int i = 0 ; i<rows ; i++)
        {
            for(int j = 0 ; j<cols;  j++)
            {
                std::cout<<arr[i][j]; 
                if(j!=cols-1)
                    cout<<" | ";  
            }
            cout<<endl; 
        }
        cout<<endl; 
    }  

    void save(string filename) // saves to a file 
    {
         
        ofstream strm(filename)    ;
        for(int i = 0 ; i<rows ; i++)
        {
            for(int j = 0 ; j<cols;  j++)
            {
                strm<<arr[i][j]; 
                if(j!=cols-1)
                    strm<<",";  
            }
            if(i!=rows-1)
                strm<<endl; 
        }
        if(!strm.fail()){
            cout<<"Successfully Saved Matrix to "<<filename<<endl; 
        }else{
            cout<<"Matrix Saving Failed" <<endl; 
        }
        strm.close(); 
    }

    // function is a unefficient because it does have to go over the file twice 
    static Matrix* load(string filename) // loads the given file ; ONLY CSV (for now )
    {
        ifstream file(filename); 
        string line;
        if(!file.fail()){
            cout<<"Successfully Loaded Matrix : "<< filename<<endl; 
        }else{
            cout<<"Matrix Loading Failed" <<endl; 
        }
        vector<vector<float>> temp; 
        unsigned row =0 ; 
        while(getline(file , line))
        {
            istringstream lineStream(line);
            string num;  
            temp.push_back(vector<float>());// row 
            while(getline(lineStream,num,','))
            {
                temp[row].push_back(stof(num)); 
                 
            }
            row++; 
            
        }
        Matrix *mat = new Matrix(temp.size(), temp[0].size());
        int i =0, j =0;  
        for(int i =0; i<temp.size(); i++)
        {
            for(int j = 0; j<temp[i].size(); j++)   
            {
                mat->arr[i][j] = temp[i][j]; 
            }
            
        }
        
        file.close(); 
        return mat; 
    }

    static bool sameDim(Matrix *first ,Matrix *second)
    {
        if(first->rows == second->rows)
        {
            if(first->cols == second->cols)
            {
                return true; 
            }
        }
        return false ; 
    }
    // for all in place transformations they have to be the same dimensions 
    void add(Matrix *other) // adds this mat with another mat
    {
        if(!sameDim(this , other))
        {
            cout<<"Cannot add because the dimensions were conflicting "<<endl; 
            exit(1); 
        }
        for(int i = 0; i<rows ; i++)
        {
            for(int j = 0; j<cols; j++)
            {
                this->arr[i][j]+=other->arr[i][j]; 
            }
        }
    } 
    void subtract(Matrix *other )
    {
        if(!sameDim(this , other))
        {
            cout<<"Cannot subtract because the dimensions were conflicting "<<endl; 
            exit(1); 
        }
        for(int i = 0; i<rows ; i++)
        {
            for(int j = 0; j<cols; j++)
            {
                this->arr[i][j]-=other->arr[i][j]; 
            }
        }
    }
    void divideInPlace(Matrix *other)
    {
        if(!sameDim(this , other))
        {
            cout<<"Cannot divide because the dimensions were conflicting "<<endl; 
            exit(1); 
        }
        for(int i = 0; i<rows ; i++)
        {
            for(int j = 0; j<cols; j++)
            {
                this->arr[i][j]/=other->arr[i][j];
            }
        }    
    }
    void multiplyInPlace(Matrix *other )
    {
        if(!sameDim(this , other))
        {
            cout<<"Cannot multiply because the dimensions were conflicting "<<endl; 
            exit(1); 
        }
        for(int i = 0; i<rows ; i++)
        {
            for(int j = 0; j<cols; j++)
            {
                this->arr[i][j]*=other->arr[i][j]; 
            }
        }
    }

    void scale(float num) // multiplies the elements by the scalar
    {
        for(int i = 0; i<rows ; i++)
        {
            for(int j = 0; j<cols; j++)
            {
                this->arr[i][j]*=num; 
            }
        }
    }

    void addScalar(float num) // adds the elements by the scalar
    {
        for(int i = 0; i<rows ; i++)
        {
            for(int j = 0; j<cols; j++)
            {
                this->arr[i][j]+=num; 
            }
        }
    }

    static Matrix* dotProduct(Matrix *first , Matrix *second)
    {
        if(first->cols == second->rows)
        {
            Matrix *mat = new Matrix(first->rows, second->cols); 
            for(int i=0; i<mat->rows ; i++)
            {
                for(int j =0; j<mat->cols; j++)
                {
                    // dot product
                    float sum = 0;  
                    for(int k = 0 ; k<first->cols; k++)
                    {
                        sum+= first->arr[i][k] * second->arr[k][j]; 
                    }
                    mat->arr[i][j] = sum; 
                }
            }
            return mat; 
        }else{
            cout<<"Cannot Dot The Matrices due to a dimension conflict (first cols have to equal second rows )"<<endl; 
            exit(1); 
             
        }
    }

    Matrix* transpose() // transposes current matrix 
    {
        Matrix* mat = new Matrix(this->cols, this->rows); 
        for(int i = 0; i<mat->rows; i++)
        {
            for(int j = 0; j<mat->cols; j++)
            {
                mat->arr[i][j]=this->arr[j][i]; 
            }
        }
        return mat; 
    }

}; 