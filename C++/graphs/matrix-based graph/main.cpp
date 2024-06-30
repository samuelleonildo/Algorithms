#include <iostream>
#include <queue>

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
            if (matrix[v][i].edge != 0)
            {
                return i;
            }
        }

        return mainSize;
    }


    int next(int v, int w) {

        for (size_t i = (w + 1); i < mainSize; i++)
        {
            if (matrix[v][i].edge != 0)
            {
                return i;
            }
        }
        
        return mainSize;
    }


    void setEdge(int i, int j, int wt) {

        if (wt == 0)
        {
            return;
        }

        if (matrix[i][j].edge == 0)
        {
            numEdge++;
        }

        matrix[i][j].edge = wt;
        matrix[j][i].edge = wt;
    }


    void delEdge(int i, int j) {

        if(matrix[i][j].edge != 0)
        {
            numEdge--;
        }

        matrix[i][j].edge = 0;
        matrix[j][i].edge = 0;
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

            mainGraph.setEdge(u, v, 1);
        }

        else if (operation == "BFS")
        {
            int v = 0;
            cin >> v;

            mainGraph.graphTraverseBFS(v);
            cout << '\n';
        }

        else if (operation == "DFS")
        {
            int v = 0;
            cin >> v;

            mainGraph.graphTraverseDFS(v);
            cout << '\n';
        }
    }

    // mainGraph.printMatrix();



    return 0;
}
