#include<cstdio>
#include<cstring>
#include<ext/pb_ds/priority_queue.hpp>
#include<utility>
using namespace __gnu_pbds;

#define INF 0x3f3f3f3f

struct cmp {
  bool operator()(std::pair<int, int> &a, std::pair<int, int> &b) {
    return a.second > b.second;
  }
};

int main() {

  int Graph[502][502];
  int LengthList[502];
  char Visited[502];
  priority_queue<std::pair<int, int>, cmp> LengthHeap;

  memset(Graph, 0x3f, sizeof(Graph));
  memset(LengthList, 0x3f, sizeof(LengthList));

  for(int i = 0; i < sizeof(Visited); ++i) {
    Visited[i] = 'u';
  }


  int n, m, NodeA, NodeB, EdgeAB;

  scanf("%d %d", &n, &m);
  for(int i = 0; i < m; ++i) {
    scanf("%d %d %d", &NodeA, &NodeB, &EdgeAB);
    Graph[NodeA][NodeB] = EdgeAB;
  }
  
  LengthHeap.push(std::make_pair(0, INF)); // 哨兵

  for(int i = 1; i <= n; ++i) {
    Graph[i][i] = 0;
    if (Graph[1][i] != INF){
      LengthList[i] = Graph[1][i]; //填入长度表
      if(i != 1) LengthHeap.push(std::make_pair(i, Graph[1][i])); //使用小根堆维护长度, 同时不能加入自身
    }
  }
  
  Visited[1] = 'f';
  int root = 0;
  
  while(LengthHeap.top().second != INF) {
    root = LengthHeap.top().first;
    LengthHeap.pop();
    for(int i = 1; i <= n; ++i) {
      if (Graph[root][i] != INF && Visited[i] == 'u'){
        LengthList[i] = LengthList[root] + Graph[root][i]; //填入长度表
        if(i != root) LengthHeap.push(std::make_pair(i, LengthList[i])); //使用小根堆维护长度, 同时不能加入自身
      }
    }
    Visited[root] = 'f';
  }

  for(int i = 1; i <= n; ++ i){
    if(LengthList[i] != INF) printf("%d\n", LengthList[i]);
    else printf("INF\n");
  }
}
