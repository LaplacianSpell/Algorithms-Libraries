#include<cstdio>
#include<cstring>
#include<ext/pb_ds/priority_queue.hpp>
#include<utility>
using namespace __gnu_pbds;

#define INF 0x7fffffff
#define LEN 502

struct cmp {
  bool operator()(std::pair<int, int> &a, std::pair<int, int> &b) {
    return a.second > b.second;
  }
};

struct Node {
  int Weight;
  int NodeName;
  Node* next;
};


int main() {

  Node* Graph[LEN];
  Node* GraphTail[LEN];
  int LengthList[LEN];
  char Visited[LEN];
  priority_queue<std::pair<int, int>, cmp> LengthHeap;
  

  for(int i = 0; i < LEN; ++i) { // Initialization
    Visited[i] = 'u';
    GraphTail[i] = nullptr; // 没有接上边，尾指针为0
    Graph[i] = nullptr; // 没有接上边，指针为空
    LengthList[i] = INF;
  }

  int n, m, NodeA, NodeB, EdgeAB;

  scanf("%d %d", &n, &m);

  for(int i = 1; i <= m; ++i) { // 访问

    scanf("%d %d %d", &NodeA, &NodeB, &EdgeAB);
    
    if(GraphTail[NodeA] == nullptr) { // 如果尾节点为空
      Graph[NodeA] = new Node(); 
      Graph[NodeA]->next = nullptr;
      Graph[NodeA]->Weight = EdgeAB;
      Graph[NodeA]->NodeName = NodeB;
      GraphTail[NodeA] = Graph[NodeA];
    }
    else {
      GraphTail[NodeA]->next = new Node(); 
      GraphTail[NodeA]->next->next = nullptr;
      GraphTail[NodeA]->next->Weight = EdgeAB;
      GraphTail[NodeA]->next->NodeName = NodeB;
      GraphTail[NodeA] = GraphTail[NodeA]->next;
    }
  }
  
  LengthHeap.push(std::make_pair(0, INF)); // 哨兵

  Node* ptr = Graph[1]; // 第一个节点
  LengthList[1] = 0; // 到自身的长度为0

  while(ptr != nullptr) {
    
    //填入长度表
    LengthList[ptr->NodeName] = ptr->Weight; 
    //使用小根堆维护长度
    LengthHeap.push(std::make_pair(ptr->NodeName, LengthList[ptr->NodeName]));
  
    ptr = ptr->next;
  }

  Visited[1] = 'f';
  ptr = Graph[LengthHeap.top().first]; // 获得当前最小的图节点(即距离1最靠近的节点指向第一条边对应节点的指针)
  Visited[LengthHeap.top().first] = 'f';

  while(LengthHeap.top().second != INF) {
    int root = LengthHeap.top().first;
    LengthHeap.pop();
    while(ptr != nullptr) {
      if (Visited[ptr->NodeName] == 'u'){
        if(LengthList[ptr->NodeName] > LengthList[root] + ptr->Weight) {
          LengthList[ptr->NodeName] = LengthList[root] + ptr->Weight;
          LengthHeap.push(std::make_pair(ptr->NodeName, LengthList[ptr->NodeName])); //使用小根堆维护长度, 同时不能加入自身
        }
      }
      ptr = ptr->next;
    }
    Visited[root] = 'f';
    ptr = Graph[LengthHeap.top().first];
  }

  for(int i = 1; i <= n; ++ i){
    if(LengthList[i] != INF) printf("%d\n", LengthList[i]);
    else printf("INF\n");
  }
}

