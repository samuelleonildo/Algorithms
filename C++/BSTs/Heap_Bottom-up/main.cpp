#include <iostream>

using namespace std;


void HeapBottomUp(int H[], int size) {

    int mid = size / 2;
    int n = size;

    for (size_t i = mid; i > 0; i--){
        
        int k = i; // curr position
        int v = H[k]; // value of the curr internal node

        bool heap = false;  

        // finding proper place for the i-th internal node
        while ((!heap) && (2 * k <= n)){
            
            int j = 2 * k; // pos of the first child
            
            if (j < n){

                // has two children
                if (H[j] < H[j + 1]) // finds the largest
                    j++;
            }

            if (v >= H[j]) // is a heap if v >= largest child
                heap = true;

            else {

                // places the largest child in H[k]
                H[k] = H[j];
                k = j; // updates k
            }
        }
        
        H[k] = v;
    }
}


int main() {

    int array[12] = {9, 1, 9 ,2, 34, 61, 12, 29, 0, 25, 91, 5};
    int size = sizeof(array) / sizeof(array[0]);

    HeapBottomUp(array, size);

    for (size_t i = 0; i < 12; i++)
        cout << i << ": " << array[i] << '\n';
    

    return 0;
}
