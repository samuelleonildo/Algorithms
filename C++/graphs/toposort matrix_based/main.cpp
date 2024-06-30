#include <iostream>
#include <queue>
#include <stack>

using namespace std;


struct vertex {

    int edge = 0;
    bool visited = false;
};


class Graph {

private:

    vertex** matrix = nullptr;
    int numEdge = 0;
    int mainSize = 0;

public:

    Graph(int n) {

        numEdge = 0;
        mainSize = n;

        matrix = new vertex*[n];

        for (size_t i = 0; i < n; i++)
        {
            matrix[i] = new vertex[n];
        }
        
    }
    ~Graph() {

        for (size_t i = 0; i < mainSize; i++)
        {
            delete[] matrix[i];
        }

        delete[] matrix;
    }

    int first(int v) {

        for (size_t i = 0; i < mainSize; i++)
        {
            if (matrix[v][i].edge)
            {
                return i;
            }
        }

        return mainSize;
    }


    int next(int v, int w) {

        for (size_t i = (w + 1); i < mainSize; i++)
        {
            if (matrix[v][i].edge)
            {
                return i;
            }
        }
        
        return mainSize;
    }


    void setEdge(int i, int j) {

        if (matrix[i][j].edge == 0)
        {
            numEdge++;
        }

        matrix[i][j].edge = 1;
    }


    void delEdge(int i, int j) {

        if(matrix[i][j].edge != 0)
        {
            numEdge--;
        }

        matrix[i][j].edge = 0;
    }


    // traversals
    void graphTraverseDFS(int start) {

        for (size_t v = 0; v < mainSize; v++)
        {
            matrix[v]->visited = false;
        }
    
        for (size_t v = start; v < mainSize; v++)
        {
            if (!matrix[v]->visited)
            {
                DFS(v);
            }
        }
    }

    void DFS(int v) {

        // preVisit(v);

        matrix[v]->visited = true;

        // v was visited
        cout << v << " ";

        int w = first(v);

        while (w < mainSize)
        {
            if (!matrix[w]->visited)
            {
                DFS(w);
            }

            w = next(v, w);
        }

        // posVisit(v);
    }


    void graphTraverseBFS(int start) {

        for (size_t v = 0; v < mainSize; v++)
        {
            matrix[v]->visited = false;
        }

        for (size_t v = start; v < mainSize; v++)
        {
            if (!matrix[v]->visited)
            {
                BFS(v);
            }
        }
    }

    void BFS(int start) {

        queue<int> Q;

        Q.push(start);

        matrix[start]->visited = true;

        // start was visited
        cout << start << " ";

        while (Q.size() > 0)
        {
            int v = Q.front();
            Q.pop();

            int w = first(v);

            while (w < mainSize)
            {
                if (!matrix[w]->visited)
                {
                    matrix[w]->visited = true;
                    Q.push(w);

                    // w was visited
                    cout << w << " ";
                }
                
                w = next(v, w);
            }
        }
    }


    void toposort(int v, stack<int>& s)
    {
        matrix[v]->visited = true;

        int w = first(v);

        while (w < mainSize)
        {
            if (!matrix[w]->visited)
            {
                toposort(w, s);
            }

            w = next(v, w);
        }

        s.push(v);
    }


    void printMatrix() {

        cout << "  ";

        for (size_t i = 0; i < mainSize; i++)
        {
            cout << i << " ";
        }

        cout << '\n';

        for (size_t i = 0; i < mainSize; i++)
        {
            cout << i << " ";

            for (size_t j = 0; j < mainSize; j++)
            {
                cout << matrix[i][j].edge << " ";
            }

            cout << '\n';
        }
        
        cout << '\n';
    }
};


int main() {

    int n = 0;
    int m = 0;

    cin >> n >> m;

    Graph mainGraph(n);

    for (size_t i = 0; i < m; i++)
    {
        int u = 0;
        int v = 0;
        cin >> u >> v;

        mainGraph.setEdge(u, v);
    }

    stack<int> s;

    mainGraph.toposort(0, s);

    int loop = s.size();

    for (size_t i = 0; i < loop; i++)
    {
        cout << s.top() << " ";
        s.pop();
    }

    // mainGraph.printMatrix();


    return 0;
}
