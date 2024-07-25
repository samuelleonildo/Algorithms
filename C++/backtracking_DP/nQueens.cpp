#include <iostream>
using namespace std;

struct block
{
    bool queen = 0;
};

bool possible(block** matrix, int row, int col, int n)
{
    int i = 0;
    int j = 0;

    for (i = 0; i < col; i++)
    {
        if (matrix[row][i].queen)
        {
            return 0;
        }
    }

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (matrix[i][j].queen)
        {
            return 0;
        }
    }

    for (i = row, j = col; j >= 0 && i < n; i++, j--)
    {
        if (matrix[i][j].queen)
        {
            return 0;
        }
    }
    
    return 1;
}

bool nQueens(block** matrix, int n, int col)
{
    if (col >= n)
    {
        return 1;
    }

    for (size_t i = 0; i < n; i++)
    {
        if (possible(matrix, i, col, n))
        {
            matrix[i][col].queen = 1;

            if (nQueens(matrix, n, col + 1))
            {
                return 1;
            }
            
            matrix[i][col].queen = 0;
        }
    }
    

    return 0;
}

int main()
{
    block** matrix = nullptr;
    int n = 0;
    cin >> n;

    matrix = new block*[n];
    for (size_t i = 0; i < n; i++)
    {
        matrix[i] = new block[n];
    }
    
    if(nQueens(matrix, n, 0))
    {
        cout << "sim" << '\n';
    }
    else
    {
        cout << "nao ne mano" << '\n';
    }
    

    return 0;
}
