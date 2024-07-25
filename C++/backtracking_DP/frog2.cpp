#include <iostream>
using namespace std;

#define inf 2147483647


int main()
{
    int* array = nullptr;
    int* pos = nullptr;

    int N = 0;
    int K = 0;
    cin >> N >> K;

    array = new int[N];
    pos = new int[N];

    for (int i = 0; i < N; i++)
    {
        cin >> array[i];
        pos[i] = inf;
    }

    pos[0] = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j <= i + K; j++)
        {
            if (j < N)
            {   
                int cost = pos[i] + abs(array[i] - array[j]);

                if(cost < pos[j])
                {
                    pos[j] = cost;
                }
            }
        }
    }

    cout << pos[N - 1];
    
    delete[] pos;
    delete[] array;
    

    return 0;
}
