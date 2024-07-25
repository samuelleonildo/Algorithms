#include <iostream>

using namespace std;
#define pii pair<int, int>


pii moves[8] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};


struct node
{
    bool reachable = false;
};

bool possible(int i, int j, node matrix[10][10])
{
    bool iRow = i >= 0 && i < 10;
    bool jColumn = j >= 0 && j < 10;

    return(iRow && jColumn && matrix[i][j].reachable);
}


int knightTour(node matrix[10][10], int i, int j, int& count, int& unreachable)
{
    int copy = count;

    if (count == 0)
    {
        unreachable = count;
        return 1;
    }
    
    for (pii p : moves)
    {
        int nexti = i + p.first;
        int nextj = j + p.second;

        if (possible(nexti, nextj, matrix))
        {
            matrix[nexti][nextj].reachable = false;

            if (knightTour(matrix, nexti, nextj, --count, unreachable))
            {
                return 1;
            }
            else
            {
                matrix[nexti][nextj].reachable = true;
                count++;
            }
        }    
    }

    if (count < unreachable)
    {
        unreachable = count;
    }
    
    return 0;
}


int main()
{
    int currCase = 0;

    int rows = 0;
    cin >> rows;

    while(rows)
    {
        node matrix[10][10];
        int unreachable = 0;

        for (int i = 0; i < rows; i++)
        {
            int first = 0;
            int quantity = 0;
            cin >> first >> quantity;

            for (int j = first; j < first + quantity; j++)
            {
                matrix[i][j].reachable = true;
                unreachable++;
            }
        }

        int count = unreachable;

        matrix[0][0].reachable = false;
        count--;

        knightTour(matrix, 0, 0, count, unreachable);

        cout << "Case " << ++currCase << ", " << unreachable;
        (unreachable == 1) ? cout << " square " : cout << " squares ";
        cout << "can not be reached." << '\n';

        cin >> rows;
    }


    return 0;
}
