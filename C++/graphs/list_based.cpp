#include <iostream>
#include <list>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;


struct mark
{
    bool visited = false;
};



class Graph
{
private:
    
    list<int>** ListArray = nullptr;
    mark* markArray = nullptr;
    int* prev = nullptr;
    int mainSize = 0;
    int numEdge = 0;

    int first(int v)
    {
        if (!ListArray[v]->empty())
        {
            return ListArray[v]->front();
        }

        return mainSize;
    }

    int next(int v, int w)
    {
        if(!ListArray[v]->empty())
        {
            list<int>::iterator successor = find(ListArray[v]->begin(), ListArray[v]->end(), w);

            if(successor != ListArray[v]->end())
            {
                ++successor;
                if(successor != ListArray[v]->end())
                {
                    return *successor;
                }
            }
        }

        return mainSize;
    }

    void DSFHelper(int start)
    {
        // pre visit
        cout << start << " ";

        markArray[start].visited = true;
        int w = first(start);

        while (w < mainSize)
        {
            if (!markArray[w].visited)
            {
                DSFHelper(w);
            }
            
            w = next(start, w);
        }
        
        // post visit
    }

    void BFSHelper(int start)
    {
        queue<int> q;
        q.push(start);
        markArray[start].visited = true;

        while (!q.empty())
        {
            int v = q.front();
            q.pop();

            // pre visit
            cout << v << " ";

            int w = first(v);

            while (w < mainSize)
            {
                if (!markArray[w].visited)
                {
                    markArray[w].visited = true;
                    q.push(w);
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
        mainSize = n;

        markArray = new mark[n];
        ListArray = new list<int>*[n];
        prev = new int[n];

        for (size_t i = 0; i < n; i++)
        {
            ListArray[i] = new list<int>;
        }
        
    }
    ~Graph()
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            delete ListArray[i];
        }
        delete[] ListArray;
        delete[] markArray;
        delete[] prev;
    }

    void setEdge(int i, int j)
    {
        if(!ListArray[i]->empty())
        {
            for(list<int>::iterator iter = ListArray[i]->begin(); iter != ListArray[i]->end(); ++iter)
            {
                if(*iter == j)
                {
                    return;
                }
            }

            ListArray[i]->push_back(j);
            ListArray[i]->sort();
            numEdge++;

            ListArray[j]->push_back(i);
            ListArray[j]->sort();
            numEdge++;
        }
        
        else
        {
            ListArray[i]->push_back(j);
            numEdge++;

            ListArray[j]->push_back(i);
            numEdge++;
        }
    }

    void delEdge(int i, int j)
    {
        if(!ListArray[i]->empty())
        {
            list<int>::iterator iter = find(ListArray[i]->begin(), ListArray[i]->end(), j);

            if(iter != ListArray[i]->end())
            {
                numEdge--;
                ListArray[i]->erase(iter);
            }

            iter = find(ListArray[j]->begin(), ListArray[j]->end(), i);

            if(iter != ListArray[j]->end())
            {
                numEdge--;
                ListArray[j]->erase(iter);
            }
        }
    }

    void DFS(int start = 0)
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            markArray[i].visited = false;
        }
        
        for (size_t i = start; i < mainSize; i++)
        {
            if (!markArray[i].visited)
            {
                DSFHelper(i);
            }
        }
    }

    void BFS(int start = 0)
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            markArray[i].visited = false;
        }
        
        for (size_t i = start; i < mainSize; i++)
        {
            if (!markArray[i].visited)
            {
                BFSHelper(i);
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
