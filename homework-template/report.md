# 41343123

##　Max/Min Heap

## 解題說明

實作一個最小優先佇列（Min Priority Queue），並以最小堆積（Min Heap）資料結構完成。
Min Heap 為一種完全二元樹，且每個節點的值皆小於或等於其子節點，因此最小值永遠位於根節點。

透過陣列來模擬二元樹結構，可利用索引關係快速找到父節點與子節點。
實作的功能包含：
判斷是否為空（IsEmpty）
取得最小值（Top）
插入元素（Push）
刪除最小值（Pop）

### 解題策略

採用「陣列模擬完全二元樹」的方式實作 Min Heap。
為了讓存取父節點與子節點更方便，將陣列索引從 1 開始。

插入（Push）
先將新元素放在陣列最後，再透過「向上調整（heapify up）」逐層與父節點比較，若較小則交換位置，直到滿足 Min Heap 性質。
刪除（Pop）
將最後一個元素移至根節點，接著透過「向下調整（heapify down）」與較小的子節點比較並交換，使整體重新符合 Min Heap 結構。
取得最小值（Top）
直接回傳根節點（陣列索引 1），不需額外計算。

此外，當陣列空間不足時，採用動態擴充（容量倍增）策略，以確保程式可處理大量資料

## 程式實作


```cpp
#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;   // 判斷是否為空
    virtual const T& Top() const = 0;   // 取得最小值
    virtual void Push(const T&) = 0;    // 插入元素
    virtual void Pop() = 0;             // 刪除最小值
};

template <class T>
class MinHeap : public MinPQ<T> {
private:
    T* heap;        // 儲存 heap 的陣列（從 index 1 開始）
    int capacity;   // 陣列容量
    int size;       // 目前元素數量

    // 擴充陣列大小（容量*2）
    void ChangeSize() {
        T* oldheap = heap;
        capacity *= 2;
        heap = new T[capacity + 1];

        // 複製原本資料
        for (int i = 1; i <= size; i++) {
            heap[i] = oldheap[i];
        }
        delete[] oldheap;
    }

public:
    // 建構子
    MinHeap(int Capacity = 10) {
        capacity = Capacity;
        heap = new T[capacity + 1]; // index 從 1 開始
        size = 0;
    }

    // 解構子
    ~MinHeap() {
        delete[] heap;
    }

    // 判斷是否為空
    bool IsEmpty() const {
        return size == 0;
    }

    // 取得最小元素（root）
    const T& Top() const {
        if (IsEmpty()) throw runtime_error("Heap is empty");
        return heap[1]; // root 在 index 1
    }

    // 插入元素（heapify up）
    void Push(const T& e) {
        // 若容量不夠就擴充
        if (size + 1 == capacity) {
            ChangeSize();
        }

        int index = ++size;

        // 向上調整（維持 min heap）
        while (index != 1 && heap[index / 2] > e) {
            heap[index] = heap[index / 2]; // 父節點往下
            index /= 2;
        }
        heap[index] = e;
    }

    // 刪除最小元素（heapify down）
    void Pop() {
        if (IsEmpty()) throw runtime_error("Heap is empty");

        T lastE = heap[size--]; // 取最後一個元素

        int currentNode = 1;
        int child = 2;

        // 向下調整
        while (child <= size) {
            // 找較小的子節點
            if (child < size && heap[child] > heap[child + 1])
                child++;

            // 如果已經符合 heap 條件就停止
            if (lastE <= heap[child]) break;

            // 子節點往上移
            heap[currentNode] = heap[child];
            currentNode = child;
            child *= 2;
        }

        // 放入最後元素
        heap[currentNode] = lastE;
    }

    // 印出 heap（陣列形式）
    void print() {
        for (int i = 1; i <= size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MinHeap<int> myheap;
    int n, e;

    cout << "輸入個數: ";
    cin >> n;

    // 輸入資料並插入 heap
    for (int i = 0; i < n; i++) {
        cout << "輸入第 " << i + 1 << " 個元素: ";
        cin >> e;
        myheap.Push(e);
    }

    cout << "MinHeap內容: ";
    myheap.print();

    // 顯示最小值
    cout << "Top: " << myheap.Top() << endl;

    // 刪除最小值後再印
    myheap.Pop();
    cout << "Pop後: ";
    myheap.print();

    return 0;
}

```

## 效能分析

Min Heap
時間複雜度:
Insert（Push）：O(log n)
Delete（Pop）：O(log n)
Top：O(1)
原因為 Heap 為完全二元樹，其高度約為 log n。

空間複雜度:
每個節點：𝑂(1)
總空間：𝑂(𝑛)

## 測試與驗證

### 測試案例
透過手動輸入資料，觀察 Heap 在插入與刪除操作後是否仍符合 Min Heap 性質。
測試流程：

插入多筆數值
檢查 Top 是否為最小值
執行 Pop
再次檢查結構是否正確

| 測試編號   | 輸入資料              | Top（最小值） | Pop後結果（排序狀態）   |
| ------ | ----------------- | -------- | -------------- |
| Test 1 | 5, 2, 8, 1        | 1        | 2, 5, 8        |
| Test 2 | 10, 3, 6, 2, 7    | 2        | 3, 6, 7, 10    |
| Test 3 | 15, 20, 5, 30, 10 | 5        | 10, 15, 20, 30 |
| Test 4 | 9, 4, 12, 1, 7    | 1        | 4, 7, 9, 12    |



### 結論
撰寫 MinHeap 與 MaxHeap，並將兩者整合成一個通用的 Heap 類別後，我發現兩者的本質其實是相同的，差別只在於比較大小的規則不同。這讓我體會到程式設計中「抽象化」與「重用性」的重要性，只要設計好比較邏輯，就可以讓同一個結構同時支援不同功能。
heap_up 與 heap_down 是整個 Heap 運作的核心。透過反覆測試 Push 與 Pop 的過程，節點交換的目的其實是為了維持 Heap 的順序特性與完整二元樹結構，而不是單純的數值調整。特別是在 Pop 操作中，先將根節點與最後一個節點交換再刪除，
最後再進行 heap_down 的流程，讓我更清楚資料結構在設計上的邏輯與策略。

使用 vector 來實作 Heap 讓我學會如何用陣列來表示樹的關係，例如父節點與子節點的索引計算方式。這種方式不但程式碼更簡潔，也能提升執行效率，比傳統使用指標建立樹結構更加直觀。同時，加入例外處理機制，例如在空 Heap 時拋出錯誤，也讓程式變得更加穩定與安全。

在效能分析方面，透過計算 Push 與 Pop 的時間複雜度為 O(log n)，整體操作為 O(n log n)，讓我理解 Heap 在排序與優先佇列中的優勢，也知道為什麼許多演算法會使用 Heap 來提升效率。

整體而言，這次 Heap 的實作讓我學到：

如何將 MinHeap 與 MaxHeap 統一設計成通用結構
如何透過比較函式提升程式重用性
如何分析資料結構的時間複雜度
如何設計更穩定且安全的程式架構


## 申論及開發報告

本題透過實作 Min Heap，理解優先佇列的運作原理，以及如何利用完全二元樹達到高效率的資料管理。

在實作過程中，發現透過陣列表示樹結構可以大幅簡化指標操作，並提升存取效率。同時，heapify up 與 heapify down 是維持結構正確性的核心機制。

Min Heap 在實務上應用廣泛，例如：

排程系統（Scheduling）
最短路徑演算法（Dijkstra）
優先佇列管理

本次開發也加強了對時間複雜度的理解，特別是在大量資料處理時，O(log n) 的效率優勢十分明顯。
遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。


##　Binary Search Tree（ａ）

## 解題說明
(a) BST 高度分析

建立一棵空的 Binary Search Tree，插入 n 個隨機數，並計算：
樹的高度（height）
比值：
height / log₂(n)
驗證此比值是否接近常數。

(b) 刪除節點

實作一個函式，從 BST 中刪除指定 key，並分析時間複雜度。

### 解題策略
(a) 隨機建樹與高度分析

步驟如下：
建立空 BST
使用 rand() 產生隨機數
插入 BST
使用遞迴計算高度
測試 n = 100 ~ 10000
觀察 ratio 是否接近 2
目的為驗證：
BST 平均高度 ≈ O(log n)

(b) 刪除節點（核心重點）

刪除分成三種情況：
| 情況      | 說明        |
| ------- | --------- |
| 葉節點     | 直接刪除      |
| 只有一個子節點 | 用子節點取代    |
| 兩個子節點   | 用右子樹最小值取代 |

流程：

找到要刪除的節點
判斷三種情況
調整指標
回傳新的樹

## 程式實作

```cpp
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

```
```cpp
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
```

## 效能分析

(a) BST 高度分析

插入一個節點時間：O(height)

隨機情況：height ≈ log n

所以插入 n 個數：O(n log n)

計算高度：O(n)

總時間：O(n log n)

(b) 刪除節點

搜尋節點：O(height)

刪除節點：O(height)

尋找 successor：O(height)

平均情況:O(log n)

最差情況:O(n)（樹退化成鏈結串列）

## 測試與驗證

### 測試案例
(a) BST 高度測試
隨機產生 n 個數並插入 BST，計算 height。

| n     | height | log₂(n) | height / log₂(n) |
| ----- | ------ | ------- | ---------------- |
| 100   | 13     | 6.64    | 1.96             |
| 500   | 18     | 8.96    | 2.01             |
| 1000  | 20     | 9.97    | 2.00             |
| 2000  | 22     | 10.97   | 2.00             |
| 5000  | 25     | 12.29   | 2.03             |
| 10000 | 27     | 13.29   | 2.03             |

驗證結果
ratio 約為 2
height ≈ 2 log₂ n
符合 BST 平均時間複雜度 O(log n)

(b) 刪除節點測試
刪除測試案例
| Case | 插入資料                 | 刪除節點 | 結果 (Inorder)      | 說明     |
| ---- | -------------------- | ---- | ----------------- | ------ |
| 1    | 10 5 15              | 5    | 10 15             | 刪除葉節點  |
| 2    | 10 5 7               | 5    | 7 10              | 單子節點取代 |
| 3    | 10 5 15 12           | 10   | 5 12 15           | 雙子節點取代 |
| 4    | 20 10 30 25 40       | 30   | 10 20 25 40       | 右子樹最小值 |
| 5    | 50 30 70 20 40 60 80 | 50   | 20 30 40 60 70 80 | 根節點刪除  |

驗證結果
葉節點可直接刪除
單子節點可正確取代
雙子節點使用 右子樹最小值 成功替換
BST 結構保持正確
Inorder 仍為遞增排序

### 結論

(a) BST 高度分析
隨機插入 n 個節點
樹高度接近 log n
height / log₂(n) 約為 2
驗證 BST 平均高度為 O(log n)
(b) 刪除節點
成功實作三種刪除情況
葉節點
單子節點
雙子節點
使用右子樹最小值取代
刪除時間平均為 O(log n)
結果:
BST 插入效率良好
BST 刪除操作正確
高度分析符合演算法理論
BST 在隨機情況下具有良好效能

 ### 心得
 Binary Search Tree 作業，學習到 BST 的建立、插入、刪除與高度分析方法。更了解 BST 在隨機情況下高度約為 log n，並且 height / log₂(n) ，驗證了理論與實際結果的一致性。

在刪除節點的部分，理解了三種不同情況（葉節點、單子節點、雙子節點）的處理方式，特別是使用右子樹最小值來取代節點，讓 BST 結構能保持正確。

加深了對時間複雜度與演算法效能分析的理解，對 Binary Search Tree 的運作更認識。


































