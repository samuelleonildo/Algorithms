#include <iostream>
using namespace std;


void knapsack(int n, int s, int size[], int value[], int* matrix[])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < s; j++)
        {
            if (!i || !j)
            {
                matrix[i][j] = 0;
            }

            else if ((size[i] <= j) && (j - size[i] >= 0))
            {
                matrix[i][j] = max(matrix[i - 1][j], value[i] + matrix[i - 1][j - size[i]]);
            }
        
            else
            {
                matrix[i][j] = matrix[i - 1][j];
            }
        }
    }
    
    cout << matrix[n - 1][s - 1] << '\n';
}


int main()
{
    int* size = nullptr;
    int* value = nullptr;
    int** matrix = nullptr;

    int N = 0;
    int S = 0;
    cin >> S >> N;

    size = new int[++N];
    value = new int[N];
    matrix = new int*[N];

    size[0] = 0;
    value[0] = 0;
    matrix[0] = new int[++S];

    for (int i = 1; i < N; i++)
    {
        cin >> size[i] >> value[i];
        matrix[i] = new int[S];
    }

    knapsack(N, S, size, value, matrix);


    return 0;
}
