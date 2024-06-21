#include <iostream>

using namespace std;


int max(int a, int b){

    if (a > b)
        return a;

    return b;
}


struct BstNode {

    int data;
    int height;
    BstNode* left;
    BstNode* right;

    BstNode(int param_data) {

        data = param_data;
        left = right = nullptr;
    }
    ~BstNode() {}
};


int h(BstNode* rt) {    

    if (rt == nullptr)
        return -1;

    return rt->height;
}


int getBalance(BstNode* rt) {

    if (rt == nullptr)
        return 0;

    return h(rt->left) - h(rt->right);
}


class BST {

private:

    BstNode* root;
    int nodeCount;

    int* findHelper(BstNode* rt, int k) {

        if (rt == nullptr)
            return nullptr;

        if (k > rt->data)
            return findHelper(rt->right, k);
        
        if (k == rt->data)
            return &rt->data;
        
        else
            return findHelper(rt->left, k);
    }


    BstNode* getMin(BstNode* rt) {

        if (rt->left == nullptr)
            return rt;
        
        return getMin(rt->left);
    }

    BstNode* deleteMin(BstNode* rt) {

        if (rt->left == nullptr)
            return rt->right;
        
        rt->left = deleteMin(rt->left);

        return rt;
    }


    BstNode* removeHelper(BstNode* rt, int k) {

        if (rt == nullptr)
            return nullptr;

        if (rt->data > k)
            rt->left = removeHelper(rt->left, k);
        
        else if (rt->data < k)
            rt->right = removeHelper(rt->right, k);

        else {
            if (rt->left == nullptr)
                return rt->right;
            
            else if (rt->right == nullptr)
                return rt->left;
            
            else {

                BstNode* temp = getMin(rt->right);
                rt->data = temp->data;
                rt->height = temp->height;
                rt->right = deleteMin(rt->right);
            }
        }


        return rt;
    }


    BstNode* leftRotate(BstNode* rt) {

        BstNode* r = rt->right;
        BstNode* rl = r->left;

        r->left = rt;
        rt->right = rl;

        rt->height = max(h(rt->left), h(rt->right)) + 1;

        r->height = max(h(r->left), h(r->right)) + 1;

        return r;
    }


    BstNode* rightRotate(BstNode* rt) {

        BstNode* l = rt->left;
        BstNode* lr = l->right;

        l->right = rt;
        rt->left = lr;

        rt->height = max(h(rt->left), h(rt->right)) + 1;

        l->height = max(h(l->left), h(l->right)) + 1;

        return l;
    }


    BstNode* insertHelper(BstNode* rt, int k) {

        if (rt == nullptr)
            return new BstNode(k);

        if (rt->data > k)
            rt->left = insertHelper(rt->left, k);

        else
            rt->right = insertHelper(rt->right, k);

        rt->height = max(h(rt->left), h(rt->right)) + 1;

        int balance = getBalance(rt);

        if (balance > 1) {

            if (k < rt->left->data)
                return rightRotate(rt);

            rt->left = leftRotate(rt->left);
            return rightRotate(rt);
        }

        if (balance < -1) {

            if (k >= rt->right->data)
                return leftRotate(rt);

            rt->right = rightRotate(rt->right);
            return leftRotate(rt);
        }

        /*

        if (balance < -1 && k >= rt->right->data)
            return leftRotate(rt);

        if (balance > 1 && k < rt->left->data) // > 1
            return rightRotate(rt);

        if (balance > 1 && k >= rt->left->data) { // > 1

            rt->left = leftRotate(rt->left);
            return rightRotate(rt);
        }

        if (balance < -1 && k < rt->right->data) {

            rt->right = rightRotate(rt->right);
            return leftRotate(rt);
        }

        */

        return rt;
    }

    void preOrderHelper(BstNode* rt = nullptr) {

        if (rt != nullptr) {

            cout << rt->data << ": " << rt->height << '\n';

            preOrderHelper(rt->left);
            preOrderHelper(rt->right);
        }
    }

public:

    BST() {

        root = nullptr;
        nodeCount = 0;
    }

    ~BST() {}

    bool find(int k) { return findHelper(root, k); }

    void insert(int k) {
    
        root = insertHelper(root, k);
        nodeCount++;
    }

    int* remove(int k) {

        int* temp = findHelper(root, k);

        if (temp != nullptr){

            root = removeHelper(root, k);
            nodeCount--;
        }

        return temp;
    }

    void preOrder() { return preOrderHelper(root); }

};


int main() {

    auto* mainBST = new BST();

    for (size_t i = 0; i < 7; i++){

        int test = 0;
        cin >> test;

        mainBST->insert(test);
    }

    mainBST->preOrder();
    mainBST->remove(2);
    cout << '\n';
    mainBST->preOrder();
    

    return 0;
}
