#include <iostream>

using namespace std;


class Node {

public:

    int key;
    int element;
    Node* left;
    Node* right;

    Node(int k, int e) {

        key = k;
        element = e;
        left = nullptr;
        right = nullptr;
    }
    ~Node() {}
};


template <typename Key, typename E>
class BST {

private:

    int nodeCount;

    Node* getMin(Node* rt) {

        if (rt->left == nullptr)
            return rt;
        
        return getMin(rt->left);
    }

    Node* deleteMin(Node* rt) {

        if (rt->left == nullptr)
            return rt->right;
        
        rt->left = deleteMin(rt->left);

        return rt;
    }

    E* findHelper(Node* rt, Key k) {

        if (rt == nullptr)
            return nullptr;

        if (rt->key > k)
            return findHelper(rt->left, k);
        
        if (rt->key == k)
            return &rt->element;
        
        else
            return findHelper(rt->right, k);        
    }

    Node* insertHelper(Node* rt, Key k, E e) {

        if (rt == nullptr)
            return new Node(k, e);

        if (rt->key > k)
            rt->left = insertHelper(rt->left, k, e);
        
        else
            rt->right = insertHelper(rt->right, k, e);

        return rt;
    }

    Node* removeHelper(Node* rt, Key k) {

        if (rt == nullptr)
            return nullptr;

        if (rt->key > k)
            rt->left = removeHelper(rt->left, k);
        
        else if (rt->key < k)
            rt->right = removeHelper(rt->right, k);

        else {
            if (rt->left == nullptr)
                return rt->right;
            
            else if (rt->right == nullptr)
                return rt->left;
            
            else {

                Node* temp = getMin(rt->right);
                rt->element = temp->element;
                rt->key = temp->key;
                rt->right = deleteMin(rt->right);
            }
        }

        return rt;
    }

public:

    Node* root;

    BST() {

        root = nullptr;
        nodeCount = 0;
    }
    ~BST() {}

    E* find(Key k) { return findHelper(root, k); }

    void insert(Key k, E e) {

        root = insertHelper(root, k, e);
        nodeCount++;
    }

    E* remove(Key k) {

        E* temp = findHelper(root, k);

        if (temp != nullptr){

            root = removeHelper(root, k);
            nodeCount--;
        }

        return temp;
    }

    void preOrder(Node* rt) {

        if (rt != nullptr){

            cout << " " << rt->element;

            preOrder(rt->left);
            preOrder(rt->right);
        }
    }

    void inOrder(Node* rt) {

        if (rt != nullptr){

            inOrder(rt->left);

            cout << " " << rt->element;

            inOrder(rt->right);
        }
    }

    void posOrder(Node* rt) {

        if (rt != nullptr){

            posOrder(rt->left);
            posOrder(rt->right);
            
            cout << " " << rt->element;
        }
    }
};


int main() {

    auto bst = BST<int, int>();

    int n = 0;
    cin >> n;

    for (size_t i = 0; i < n; i++){
        
        int p = 0;
        cin >> p;

        bst.insert(p, p);
    }

    cout << "pre remotion: " << '\n';

    cout << "Pre order :";
    bst.preOrder(bst.root);
    cout << '\n';

    cout << "In order  :";
    bst.inOrder(bst.root);
    cout << '\n';

    cout << "Post order:";
    bst.posOrder(bst.root);
    cout << '\n';

    cout << "post remotion: " << '\n';
    
    bst.remove(bst.root->key);

    cout << "Pre order :";
    bst.preOrder(bst.root);
    cout << '\n';

    cout << "In order  :";
    bst.inOrder(bst.root);
    cout << '\n';

    cout << "Post order:";
    bst.posOrder(bst.root);
    cout << '\n';


    return 0;
}
