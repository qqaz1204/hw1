#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Tree {
    int value;      // 儲存資料
    Tree* lchild;   // 左子樹
    Tree* rchild;   // 右子樹

    Tree(int v) {
        value = v;
        lchild = rchild = NULL;
    }
};

// 小於往左，大於等於往右
Tree* addNode(Tree* root, int v) {
    if (root == NULL)
        return new Tree(v);

    if (v < root->value)
        root->lchild = addNode(root->lchild, v);
    else
        root->rchild = addNode(root->rchild, v);

    return root;
}

// 空樹高度設為0（另一種常見定義）
int calcHeight(Tree* root) {
    if (root == NULL)
        return 0;

    int leftH = calcHeight(root->lchild);
    int rightH = calcHeight(root->rchild);

    // 回傳較高的那邊 +1
    return (leftH > rightH ? leftH : rightH) + 1;
}

void destroy(Tree* root) {
    if (root == NULL) return;

    destroy(root->lchild);
    destroy(root->rchild);
    delete root;
}

void experiment(int n) {
    Tree* root = NULL;

    // 插入 n 個隨機數
    for (int i = 0; i < n; i++) {
        int num = rand();
        root = addNode(root, num);
    }

    int h = calcHeight(root);              // 計算高度
    double ratio = h / log2((double)n);    // 計算 h/log2(n)

    // 印出結果
    cout << "n=" << n
         << " height=" << h
         << " ratio=" << ratio << endl;

    destroy(root); // 釋放記憶體
}

int main() {
    srand(time(NULL)); // 設定亂數種子

    // 不同 n 值測試
    int testSet[] = {100, 500, 1000, 2000, 5000, 10000};

    for (int i = 0; i < 6; i++) {
        experiment(testSet[i]);
    }

    return 0;
}
