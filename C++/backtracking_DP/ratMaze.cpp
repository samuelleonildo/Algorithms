#include <iostream>
using namespace std;

#define pii pair<int, int>

pii steps[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct block
{
    char value = '#';
    bool visited = false;
};

bool possible(block matrix[40][40], int x, int y)
{
    bool xRow = x >= 0 && x < 40;
    bool yColumn = y >= 0 && y < 40;
    
    if (xRow && yColumn)
    {
        return ((matrix[x][y].value != '#') && (!matrix[x][y].visited) && (matrix[x][y].value != '@'));
    }

    return false;
}

bool ratMaze(block matrix[40][40], int x, int y, int j, int& spike)
{
    if (matrix[x][y].value == 's')
    {
        spike++;
    }

    if (matrix[x][y].value == 'x')
    {
        if ((j - (2 * spike)) >= 0)
        {
            return true;
        }
        
        return false;
    }

    for (pii p : steps)
    {
        int newX = x + p.first;
        int newY = y + p.second;

        if (possible(matrix, newX, newY))
        {
            matrix[newX][newY].visited = true;

            if (ratMaze(matrix, newX, newY, j, spike))
            {
                return true;
            }
            else
            {
                matrix[newX][newY].visited = false;
                spike = 0;
            }
        }   
    }

    return false;
}

int main()
{
    block matrix[40][40];
    pii start = {0, 0};
    int n = 0;
    int m = 0;
    int j = 0;
    cin >> n >> m >> j;

    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < m; k++)
        {
            cin >> matrix[i][k].value;
            if (matrix[i][k].value == '@')
            {
                start = {i, k};
            }
        }
    }
    
    int spike = 0;
    bool result = ratMaze(matrix, start.first, start.second, j, spike);

    (result) ? cout << "SUCCESS" : cout << "IMPOSSIBLE";
    cout << '\n';


    return 0;
}
