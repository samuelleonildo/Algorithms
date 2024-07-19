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

        return (inf - markArray[v].D);
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
            for(auto iter = vectorArray[i]->begin(); iter != vectorArray[i]->end(); ++iter)
            {
                if(iter->first == j)
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

    void dijkstra(int s, int d, int& distance, bool& reachable)
    {
        for (size_t i = 0; i < mainSize; i++)
        {
            markArray[i].D = inf;
            markArray[i].P = -1;
            markArray[i].visited = false;
        }
        
        priority_queue<pair<pii, int>, vector<pair<pii, int>>, compare> H;
        H.push({{s, s}, 0});
        markArray[s].D = 0;

        for (size_t i = 0; i < mainSize; i++)
        {
            int v = 0;
            int p = 0;
            do
            {
                if (H.empty())
                {
                    return;
                }
                
                p = H.top().first.first;
                v = H.top().first.second;
                H.pop();

            } while (markArray[v].visited);

            markArray[v].visited = true;
            markArray[v].P = p;

            int w = first(v);
            while (w < mainSize)
            {
                int mass = weight(v, w);
                if (!markArray[w].visited && (markArray[w].D > (markArray[v].D + mass)))
                {
                    markArray[w].D = markArray[v].D + mass;
                    H.push({{v, w}, markArray[w].D});
                }
                
                w = next(v, w);
            }
        }

        reachable = true;
        distance = markArray[d].D;
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
        mainGraph.dijkstra(S, T, distance, reachable);

        cout << "Case #" << (i + 1) << ": ";
        (reachable) ? cout << distance : cout << "unreachable";
        cout << '\n';
    }
    

    return 0;
}