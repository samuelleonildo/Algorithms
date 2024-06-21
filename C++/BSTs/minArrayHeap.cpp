#include <iostream>

using namespace std;


void minHeapify(int H[], int size) {

    int n = size - 1;
    int mid = n / 2;

    for (size_t i = mid; i > 0; i--){
        
        int k = i; // curr position
        int v = H[k]; // value of the curr internal node

        bool heap = false;  

        // finding proper place for the i-th internal node
        while ((!heap) && (2 * k <= n)){
            
            int j = 2 * k; // pos of the first child
            
            if (j < n){

                // has two children
                if (H[j] > H[j + 1]) // finds the smallest (< for largest)
                    j++;
            }

            if (v <= H[j]) // is a heap if v >= smallest child (>= for largest)
                heap = true;

            else {

                // places the smallest child in H[k]
                H[k] = H[j];
                k = j; // updates k
            }
        }

        H[k] = v;
    }
}


void deleteRoot(int arr[], int& n){

    // swapping
    int temp = arr[1];
    arr[1] = arr[n - 1];
    arr[n - 1] = temp; 
 
    n--;

    // heapify the root node
    minHeapify(arr, n);
}


int main() {

    int N = 0;
    cin >> N;

    while (N) {

        // doing this since we are working with a 1 based min heap
        int* mainArray = new int[++N];
        mainArray[0] = 0;

        // appending the inputs to the mainArray
        for (size_t i = 1; i < N; i++)
            cin >> mainArray[i];
        
        // heapify the mainArray
        minHeapify(mainArray, N);

        int sum = 0;
        int sumHelper = 0;

        // while there is more than 1 element in the heap
        while (N != 2){ // N == 2 means 1 element, the index 0 (null) and the index 1 (element)

            // setting the sumHelper to be the smallest number in the heap
            sumHelper = mainArray[1];
            deleteRoot(mainArray, N); // removing the root

            // adding the smallest number in the heap to the sumHelper
            sumHelper += mainArray[1];
            deleteRoot(mainArray, N); // removing the root

            // appending the sum of the smallest numbers we did
            mainArray[N] = sumHelper; 
            minHeapify(mainArray, ++N); // heapify the mainArray

            sum += sumHelper; // adding the sumHelper to the main sum
        }
        
        cout << sum << '\n';


        cin >> N;
    }


    return 0;
}
