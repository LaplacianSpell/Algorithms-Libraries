#include<cstdio>
using namespace std;

class Node {
 public:
  int key;
  int number;
  int child;
  Node* left;
  Node* right;  
  Node(int key) {
    this->key = key;
    number = 1; // 当且节点stack的数目
    child = 1; // 包括当前节点的子树节点数
    left = nullptr;
    right = nullptr;
  }
  ~Node() = default;
};

class BinarySearchTree {
 public:
  BinarySearchTree(){
    root_ = nullptr;
  }
  Node* root_;

  int InsertAndGetNumber(int sweet){
    Node* node = root_;
    int cnt = 0;
    // 对于根节点
    if(root_ == nullptr) {
      root_ = new Node(sweet);
      return 0;
    }
    
    // 如果根不为空，则进行遍历
    while(node != nullptr) {
      if(node->key == sweet) {
        ++ node->child;
        ++ node->number;
        return node->right == nullptr ? cnt : (cnt + node->right->child); // 注意右节点为空
      }
      else if(node->key > sweet) { // 即向左子树搜索
        ++ node->child;
        cnt += (node->number + 
            (node->right == nullptr ? 0 : (node->right->child))
            );
        // 如果左边是空，直接挂上去，反之继续循环
        if(node->left != nullptr) {
          node = node->left;
        }
        else {
          node->left = new Node(sweet);
          return cnt;
        }
      }
      else if(node->key < sweet) { // 向右子树搜索
        ++ node->child;
        if(node->right != nullptr) {
          node = node->right;
        }
        else {
          node->right = new Node(sweet);
          return cnt;
        }
      }
    }
  }

  // 寻找第k甜的节点
  int TheKthSweet(int k){
    Node* node = root_;
    int cnt = 0;
    while(node != nullptr){
      if(node->right == nullptr){ // 即右边没有节点了
        if((node->number + cnt) >= k) { // 当前节点满足要求
          --node->number;
          --node->child;
          return node->key;
        }
        else { // 当前节点不够，需要更多的节点，因此向左移动
          cnt += node->number;
          --node->child;
          node = node->left;
        }
      }
      else { // 右边存在节点
        if((node->right->child + cnt) >= k) { // 右子树太大，进入右节点
          --node->child;
          node = node->right;
        }
        else if((node->right->child + node->number + cnt) >= k) { // 右子树不够大，加上当前节点后满足要求
          --node->number;
          --node->child;
          return node->key;
        }
        else { // 右子树加上节点仍然不满，需要向左移动
          cnt += (node->number + node->right->child);
          --node->child;
          node = node->left;
        }
      }
    }
  }
};

int main() {
  BinarySearchTree tree;
  int m;
  int x, y;
  scanf("%d", &m);//输入总数
  for(int i=0; i<m; ++i){
    scanf("%d %d", &x, &y);
    switch(x){
      case 1:
        printf("%d\n", tree.InsertAndGetNumber(y));
        break;
      case 2:
        printf("%d\n", tree.TheKthSweet(y));
        break;
    }
  }
}