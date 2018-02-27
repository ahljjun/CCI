#include <iostream>
#include <vector>

using namespace std;

void zeroMatrix(vector<vector<int>> &matrix, int row, int col)
{
    bool *rowRecord = new bool[row];
    bool *colRecord = new bool[col];
    for(int i = 0 ; i< row; i++)
        rowRecord[i] = false;

    for(int j =0 ; j< col; j++)
        colRecord[j] = false;

    for(int i = 0 ; i< row; i++)
    {
        for(int j =0 ; j< col; j++)
        {
            if(matrix[i][j] == 0)
            {
                rowRecord[i]= true;
                colRecord[j]= true;
            }
        }
    }

    for(int i = 0 ; i< row; i++)
    {
        for(int j =0 ; j< col; j++)
        {
            if( rowRecord[i] || colRecord[j])
            {
                matrix[i][j] = 0;
            }
        }
    }

    /*
    // clear rows
    for(int i = 0 ; i< row; i++)
    {
        if(rowRecord[i])
        {
            for(int j =0 ; j< col; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }

    // clear cols 
    for(int j = 0 ; j < row; j++)
    {
        if(colRecord[j])
        {
            for(int i =0 ; i < row; i++)
            {

            }
        }
    }
    */

    delete [] rowRecord;
    delete [] colRecord;
}


int main()
{
    vector<vector<int>> arr = { {1,  2,  3,   4},
         {5,  6,  7,   8},
         {9,  0, 11, 12},
         {13, 14, 15, 16} } ;

    zeroMatrix(arr, 4, 4);

    for(int i=0; i< 4; i++)
    {
        for(int j=0; j<4; j++)
        {
            std::cout<<arr[i][j]<<'\t';
        }
        std::cout<<std::endl;
    }
}

