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



## 申論及開發報告

本題透過實作 Min Heap，理解優先佇列的運作原理，以及如何利用完全二元樹達到高效率的資料管理。

在實作過程中，發現透過陣列表示樹結構可以大幅簡化指標操作，並提升存取效率。同時，heapify up 與 heapify down 是維持結構正確性的核心機制。

Min Heap 在實務上應用廣泛，例如：

排程系統（Scheduling）
最短路徑演算法（Dijkstra）
優先佇列管理

本次開發也加強了對時間複雜度的理解，特別是在大量資料處理時，O(log n) 的效率優勢十分明顯。
遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。


