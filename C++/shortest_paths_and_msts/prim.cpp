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

        return (inf);
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

        vectorArray[i]->push_back(pairi);
        markArray[i].vectorSize++;

        vectorArray[j]->push_back(pairj);
        markArray[j].vectorSize++;
    }

    void prim(int& largestDistance, bool& reachable)
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            markArray[i].D = inf;
            markArray[i].P = -1;
            markArray[i].visited = false;
        }
        
        priority_queue<pair<pii, int>, vector<pair<pii, int>>, compare> H;
        H.push({{0, 0}, 0});
        markArray[0].D = 0;

        for (size_t i = 0; i < mainSize; i++)
        {
            int v = 0;
            int p = 0;
            int num = 0;
            do
            {
                if (H.empty())
                {
                    return;
                }
                
                p = H.top().first.first;
                v = H.top().first.second;
                num = H.top().second;
                H.pop();

            } while (markArray[v].visited);

            if (largestDistance < num)
            {
                largestDistance = num;
            }

            markArray[v].visited = true;
            markArray[v].P = p;

            int w = first(v);
            while (w < mainSize)
            {
                int mass = weight(v, w);
                if (!markArray[w].visited && (markArray[w].D > mass))
                {
                    markArray[w].D = mass;
                    H.push({{v, w}, markArray[w].D});
                }
                
                w = next(v, w);
            }
        }
    
        reachable = true;
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
        bool reachable = false;
        mainGraph.prim(largestDistance, reachable);

        (reachable) ? cout << largestDistance : cout << "IMPOSSIBLE";
        cout << '\n';

        cin >> cities >> roads;
    }
    

    return 0;
}