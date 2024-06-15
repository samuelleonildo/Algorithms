#include <iostream>
#include <vector> 

using namespace std;


class Heap {

private:

    vector<int>& heap; // Pointer to the heap array
    int maxsize; // Maximum size of the heap 
    int n; // Number of elements now in the heap

    void swap(int first, int second) {

        int temp = heap[first];
        heap[first] = heap[second];
        heap[second] = temp;
    }

    void siftdown(int pos) {

        while (!isLeaf(pos)){ // Stop if pos is a leaf
            
            int j = leftChild(pos);
            int rc = rightChild(pos);

            if ((rc < n) && heap[rc] >= heap[j])
                j = rc; // Set j to greater child’s value
            
            if (heap[pos] >= heap[j])
                return;
            
            swap(pos, j);
            pos = j; // move down
        }
        
    }

    /* void buildHeap() {

        for (int i = n / 2; i > 0; i--) {

            int k = i;
            int v = heap[k];
            int is_heap = false;

            while (!is_heap && leftChild(k) <= n) {

                int j = leftChild(k);

                if (j < n) {

                    if (heap[j] < heap[j + 1])  // right child is greater
                        j = rightChild(k);
                }

                if (v >= heap[j])  // heap property ok
                    is_heap = true;

                else {
                    heap[k] = heap[j];
                    k = j;
                }
            }

            heap[k] = v;
        }
    } */
    
    void buildHeap() { // Heapify contents of Heap

        for (int i = ((n / 2) - 1); i >= 0; i--)
            siftdown(i); 
    }

public:

    Heap(vector<int>& h, int num, int max) : heap(h) {

        n = num;
        maxsize = max;
        buildHeap();
    }

    int rightChild(int pos) { return 2*pos + 2; }

    int leftChild(int pos) { return 2*pos + 1; }

    bool isLeaf(int pos) {

        return ((pos >= n / 2) && (pos < n));
    }

    int parent(int pos) {

        return (pos - 1) / 2;
    }

    void insert(const int& it) {

        if (n < maxsize){

            int curr = n++;
            heap[curr] = it;

            while ((curr != 1) && (heap[curr] >= heap[parent(curr)])) {
                
                swap(curr, parent(curr));
                curr = parent(curr);
            }
        }
    }
};


int main(){

    vector<int> array = {0, 71, 2, 10, 63, 15, 52, 28, 71, 12, 3, 12};

    auto heap = new Heap(array, array.size(), array.size());

    for (int i = 0; i < array.size(); i++)
        cout << i << ": " << array[i] << '\n';

    return 0;
}
