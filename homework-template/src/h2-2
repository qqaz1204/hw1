#include <iostream>
using namespace std;

struct Tree {
    int value;
    Tree* lchild;
    Tree* rchild;

    Tree(int v) {
        value = v;
        lchild = rchild = NULL;
    }
};

Tree* insertNode(Tree* root, int v) {
    if (root == NULL)
        return new Tree(v);

    if (v < root->value)
        root->lchild = insertNode(root->lchild, v);
    else
        root->rchild = insertNode(root->rchild, v);

    return root;
}

Tree* getMin(Tree* root) {
    while (root->lchild != NULL)
        root = root->lchild;
    return root;
}

Tree* deleteNode(Tree* root, int key) {
    if (root == NULL)
        return NULL;

    // 找目標節點
    if (key < root->value)
        root->lchild = deleteNode(root->lchild, key);
    else if (key > root->value)
        root->rchild = deleteNode(root->rchild, key);
    else {
        // ===== 找到要刪的節點 =====

        // 情況1：沒有子節點
        if (root->lchild == NULL && root->rchild == NULL) {
            delete root;
            return NULL;
        }

        // 情況2：只有右子節點
        if (root->lchild == NULL) {
            Tree* temp = root->rchild;
            delete root;
            return temp;
        }

        // 情況2：只有左子節點
        if (root->rchild == NULL) {
            Tree* temp = root->lchild;
            delete root;
            return temp;
        }

        // 情況3：有兩個子節點
        // 找右子樹最小值替代
        Tree* minNode = getMin(root->rchild);

        root->value = minNode->value;

        // 刪除那個替代節點
        root->rchild = deleteNode(root->rchild, minNode->value);
    }

    return root;
}

void inorder(Tree* root) {
    if (root == NULL) return;

    inorder(root->lchild);
    cout << root->value << " ";
    inorder(root->rchild);
}

int main() {
    Tree* root = NULL;

    int data[] = {40, 20, 60, 10, 30, 50, 70};

    // 建立 BST
    for (int i = 0; i < 7; i++) {
        root = insertNode(root, data[i]);
    }

    cout << "Before delete: ";
    inorder(root);

    // 刪除節點（測試）
    root = deleteNode(root, 40);

    cout << "\nAfter delete 40: ";
    inorder(root);

    return 0;
}
