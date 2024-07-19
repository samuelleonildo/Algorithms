#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define pii pair<int, int>
#define inf 2147483647

using namespace std;


struct mark
{
    int vectorSize = 0;
    int index = 0;
};

class Graph
{
private:
    
    vector<pii>** vectorArray = nullptr;
    int** D = nullptr;
    mark* markArray = nullptr;
    int mainSize = 0;

    int weight(int v, int w)
    {
        for (size_t i = 0; i < markArray[v].vectorSize; i++)
        {
            if ((*vectorArray[v])[i].first == w)
            {
                return (*vectorArray[v])[i].second;
            }
        }

        return inf;
    }

public:

    Graph(int n)
    {
        mainSize = n;

        markArray = new mark[n];
        vectorArray = new vector<pii>*[n];
        D = new int*[n];

        for (size_t i = 0; i < n; i++)
        {
            vectorArray[i] = new vector<pii>;
            D[i] = new int[n];

            for (size_t j = 0; j < n; j++)
            {
                D[i][j] = 0;
            }
        }
    }
    ~Graph()
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            delete vectorArray[i];
            delete[] D[i];
        }
        delete[] D;
        delete[] vectorArray;
        delete[] markArray;
    }

    void setEdge(int i, int j, int wt = 1)
    {
        pii pairi = make_pair(j, wt);
        pii pairj = make_pair(i, wt);
        
        vectorArray[i]->push_back(pairi);
        markArray[i].vectorSize++;

        vectorArray[j]->push_back(pairj);
        markArray[j].vectorSize++;
    }

    void floyd(int s, int e)
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            for (size_t j = 0; j < mainSize; j++)
            {
                if (i == j)
                {
                    D[i][j] = 0;
                }
                else if (weight(i, j) != 0)
                {
                    D[i][j] = weight(i, j);
                }
                else
                {
                    D[i][j] = inf;
                }
            }
        }
        
        for (size_t k = 0; k < mainSize; k++)
        {
            for (size_t i = 0; i < mainSize; i++)
            {
                for (size_t j = 0; j < mainSize; j++)
                {
                    if ((D[i][k] != inf) && (D[k][j] != inf) && (D[i][j] > D[i][k] + D[k][j]))
                    {
                        D[i][j] = D[i][k] + D[k][j];
                    }
                }
            }
        }

        (D[s][e] == inf) ? cout << "unreachable" : cout << D[s][e];
        cout << '\n';
    }    
};


int main()
{
    int cases = 0;
    cin >> cases;

    for (size_t i = 0; i < cases; i++)
    {
        int n = 0;
        int m = 0;
        int S = 0;
        int T = 0;
        cin >> n >> m >> S >> T;

        Graph mainGraph(n);
        for (size_t j = 0; j < m; j++)
        {
            int v1 = 0;
            int v2 = 0;
            int value = 0;
            cin >> v1 >> v2 >> value;

            mainGraph.setEdge(v1, v2, value);
        }
        
        int distance = 0;
        bool reachable = false;
        cout << "Case #" << i + 1 << ": ";
        mainGraph.floyd(S, T);
    }
    

    return 0;
}
