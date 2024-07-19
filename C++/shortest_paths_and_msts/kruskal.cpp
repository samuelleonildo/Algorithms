#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define pii pair<int, int>
#define inf 2147483647

using namespace std;


struct mark
{
    bool visited = false;
    int vectorSize = 0;
    int D = inf;
    int P = -1;
    int index = 0;
};

struct compare
{
    bool operator()(pair<pii, int>& x, pair<pii, int>& y)
    {
        return x.second > y.second;
    }
};


class DSqu
{
private:

    int* A = nullptr;

public:

    DSqu(int n)
    {
        A = new int[n];
        for (size_t i = 0; i < n; i++)
        {
            A[i] = -1;
        }
    }
    ~DSqu()
    {
        delete[] A;
    }

    int find(int curr)
    {
        if (A[curr] == -1)
        {
            return curr;
        }

        A[curr] = find(A[curr]);
        return A[curr];
    }

    void unite(int a, int b)
    {
        int root1 = find(a);
        int root2 = find(b);
        
        if (root1 != root2)
        {
            A[root2] = root1;
        }
    }
};


class Graph
{
private:
    
    vector<pii>** vectorArray = nullptr;
    mark* markArray = nullptr;
    int mainSize = 0;

    int first(int v)
    {
        markArray[v].index = 0;

        if (!vectorArray[v]->empty())
        {
            return vectorArray[v]->front().first;
        }

        return mainSize;
    }

    int next(int v, int w)
    {
        int& i = markArray[v].index;
        if((i + 1) < markArray[v].vectorSize)
        {
            return (*vectorArray[v])[++i].first;
        }

        return mainSize;
    }

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

        for (size_t i = 0; i < n; i++)
        {
            vectorArray[i] = new vector<pii>;
        }
        
    }
    ~Graph()
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            delete vectorArray[i];
        }
        delete[] vectorArray;
        delete[] markArray;
    }

    void setEdge(int i, int j, int wt = 1)
    {
        pii pairi = make_pair(j, wt);
        pii pairj = make_pair(i, wt);

        if(!vectorArray[i]->empty())
        {
            for(auto iter : *vectorArray[i])
            {
                if(iter.first == j)
                {
                    return;
                }
            }
        }
        
        vectorArray[i]->push_back(pairi);
        markArray[i].vectorSize++;

        vectorArray[j]->push_back(pairj);
        markArray[j].vectorSize++;
    }

    void kruskal(int& largestDistance, bool& reachable)
    {
        int cost = 0;
        int edgecent = 1;
        priority_queue<pair<pii, int>, vector<pair<pii, int>>, compare> H;
        for (int i = 0; i < mainSize; i++)
        {
            int w = first(i);
            while(w < mainSize)
            {
                edgecent++;
                H.push({{i, w}, weight(i, w)});
                w = next(i, w);
            }
        }
        DSqu ds(mainSize);
        int numMST = mainSize;

        while (numMST > 1)
        {
            if (H.empty())
            {
                reachable = false;
                return;
            }

            pair<pii, int> top = H.top();
            int v = top.first.first;
            int u = top.first.second;
            int wt = top.second;
            H.pop();

            if (ds.find(v) != ds.find(u))
            {
                ds.unite(v, u);
                cost += wt;
                if (wt > largestDistance)
                {
                    largestDistance = wt;
                }
                numMST--;
            }
        }
    }
};


int main()
{
    int cities = 0;
    int roads = 0;
    cin >> cities >> roads;

    while (cities || roads)
    {
        Graph mainGraph(cities);

        for (size_t i = 0; i < roads; i++)
        {
            int v1 = 0;
            int v2 = 0;
            int d = 0;
            cin >> v1 >> v2 >> d;
        
            mainGraph.setEdge(v1, v2, d);
        }

        int largestDistance = 0;
        bool reachable = true;
        mainGraph.kruskal(largestDistance, reachable);

        (reachable) ? cout << largestDistance : cout << "IMPOSSIBLE";
        cout << '\n';

        cin >> cities >> roads;
    }
    

    return 0;
}
