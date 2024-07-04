#include <iostream>
#include <queue>
#include <stack>

using namespace std;


struct vertex
{
    int edge = 0;
};

struct mark
{
    bool visited = false;
};


class Graph
{
private:

    mark* markArray = nullptr;
    vertex** matrix = nullptr;
    int* prev = nullptr;
    int mainSize = 0;
    int numEdge = 0;


    int first(int v)
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            if (matrix[v][i].edge)
            {
                return i;
            }
        }

        return mainSize;
    }


    int next(int v, int w)
    {
        for (size_t i = (w + 1); i < mainSize; i++)
        {
            if (matrix[v][i].edge)
            {
                return i;
            }
        }
        
        return mainSize;
    }


    void DFSHelper(int v)
    {
        // pre visit
        cout << v << " ";

        markArray[v].visited = true;

        int w = first(v);

        while (w < mainSize)
        {
            if (!markArray[w].visited)
            {
                DFSHelper(w);
            }
            
            w = next(v, w);
        }
        
        // post visit
    }


    void BFSHelper(int start)
    {
        queue<int> Q;
        Q.push(start);

        markArray[start].visited = true;

        while (Q.size() > 0)
        {
            int v = Q.front();
            Q.pop();

            // pre visit
            cout << v << " ";

            int w = first(v);

            while (w < mainSize)
            {
                if (!markArray[w].visited)
                {
                    markArray[w].visited = true;
                    Q.push(w);
                }
                
                w = next(v, w);
            }

            // post visit
        }
    }

    void BFSPath(int start)
    {
        queue<int> Q;
        Q.push(start);

        markArray[start].visited = true;

        // setting prev as -1 (null)
        for (size_t i = 0; i < mainSize; i++)
        {
            prev[i] = -1;
        }

        while (!Q.empty())  
        {
            int v = Q.front();
            Q.pop();

            // pre visit
            // cout << v << " ";

            int w = first(v);

            while (w < mainSize)
            {
                if (!markArray[w].visited)
                {
                    markArray[w].visited = true;
                    Q.push(w);

                    // prev changes
                    prev[w] = v;
                }
                
                w = next(v, w);
            }

            // post visit
        }
    }

    void reconstructPath(int start, int finish)
    {
        stack<int> path;

        for (size_t i = finish; i != -1; i = prev[i])
        {
            path.emplace(i);
        }
        
        if (path.top() == start)
        {
            while (!path.empty())
            {
                cout << path.top() << " ";
                path.pop();
            }
            
            cout << '\n';
        }
        
        else
        {
            cout << "Nah i'd win" << '\n';
        }
    }

    void toposortHelper(int v, stack<int>& s)
    {
        markArray[v].visited = true;

        int w = first(v);

        while (w < mainSize)
        {
            if (!markArray[w].visited)
            {
                toposortHelper(w, s);
            }
            
            w = next(v, w);
        }
        
        s.push(v);
    }

public:

    Graph(int n)
    {
        markArray = new mark[n];
        prev = new int[n];
        
        matrix = new vertex*[n];
        for (size_t i = 0; i < n; i++)
        {
            matrix[i] = new vertex[n];
        }
        
        mainSize = n;
    }

    ~Graph()
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            delete[] matrix[i];
        }
        
        delete[] matrix;
        delete[] markArray;
        delete[] prev;
    }


    void setEdge(int i, int j, int wt = 1)
    {
        if (!wt)
        {
            return;
        }

        if (!matrix[i][j].edge)
        {
            numEdge++;
            numEdge++;
        }
        
        matrix[i][j].edge = wt;
        matrix[j][i].edge = wt;
    }


    void delEdge(int i, int j)
    {
        if (matrix[i][j].edge)
        {
            numEdge--;
            numEdge--;
        }

        matrix[i][j].edge = 0;
        matrix[j][i].edge = 0;
    }


    void DFS(int start = 0)
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            markArray[i].visited = false;
        }
        
        for (size_t v = start; v < mainSize; v++)
        {
            if (!markArray[v].visited)
            {
                DFSHelper(v);
            }
        }
    }

    void BFS(int start = 0)
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            markArray[i].visited = false;
        }
        
        for (size_t v = start; v < mainSize; v++)
        {
            if (!markArray[v].visited)
            {
                BFSHelper(v);
            }
        }
    }

    void shortestPath(int start, int finish)
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            markArray[i].visited = false;
        }

        BFSPath(start);

        reconstructPath(start, finish);
    }

    void toposort(int v)
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            markArray[i].visited = false;
        }

        stack<int> s;

        toposortHelper(v, s);

        while (!s.empty())
        {
            cout << s.top() << " ";
            s.pop();
        }
        
        cout << '\n';
    }
};


int main()
{
    int n = 0;
    int q = 0;
    cin >> n >> q;

    Graph mainGraph(n);

    for (size_t i = 0; i < q; i++)
    {
        string operation = "";
        cin >> operation;

        if (operation == "add")
        {
            int u = 0;
            int v = 0;
            cin >> u >> v;

            mainGraph.setEdge(u, v);
        }

        else if (operation == "BFS")
        {
            int v = 0;
            cin >> v;

            mainGraph.BFS(v);
            cout << '\n';
        }

        else if (operation == "DFS")
        {
            int v = 0;
            cin >> v;

            mainGraph.DFS(v);
            cout << '\n';
        }

        else if (operation == "STP")
        {
            int u = 0;
            int v = 0;
            cin >> u >> v;

            mainGraph.shortestPath(u, v);
        }
        
        else if (operation == "TPS")
        {
            int v = 0;
            cin >> v;

            mainGraph.toposort(v);
        }
    }


    return 0;
}
