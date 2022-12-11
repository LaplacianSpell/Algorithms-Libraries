#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<ext/pb_ds/priority_queue.hpp>
#pragma warning(disable:4996)
using namespace __gnu_pbds;

struct cmp {
  bool operator()(std::pair<int, int> &a, std::pair<int, int> &b) {
    return a.first == b.first ? a.second > b.second : a.first < b.first;
  }
};

int main() {
  int p[1000000]; // 储存最新值
  memset(p, -1, sizeof(p));
  int m = 0;
  int flg = 0;
  int cnt = 0;
  priority_queue<std::pair<int, int>, cmp> q;
  // first 甜度 second 记号
  scanf("%d", &m);
  for (int i = 0; i < m; ++i)  {
    
    scanf("%d", &flg); // 读取操作

    if (flg == 1) { // 插入
      ++cnt;
      int s;
      scanf("%d", &s);
      q.push(std::make_pair(s, cnt));
      p[cnt] = s;
      do {
        if (q.empty()) {
          // printf("Res:-1\n");
          printf("-1\n");
          break;
        } // 检测到空
        else if (q.top().first == p[q.top().second]){
          printf("%d\n", q.top().first);
          // printf("Res:%d\n", q.top().first);
          break;
        } // 非空且未修改, 直接输出，对于数组不修改是因为之后只考虑是否不存在
        else {
          q.pop();
        } // 修改了，继续循环
      } while (1);
    } else if (flg == 2) { // 取最大值
      do {
        if (q.empty()) {
          // printf("Res:-1\n");
          printf("-1\n");
          break;
        } // 检测到空
        else if (q.top().first == p[q.top().second]){
          // printf("%d", q.top().first);
          q.pop();
          do {
            if (q.empty()) {
              // printf("Res:-1\n");
              printf("-1\n");
              break;
            } // 检测到空
            else if (q.top().first == p[q.top().second]){
              printf("%d\n", q.top().first);
              // printf("Res:%d\n", q.top().first);
              break;
            } // 非空且未修改, 直接输出，对于数组不修改是因为之后只考虑是否不存在
            else {
              q.pop();
            } // 修改了，继续循环
          } while (1);
          break;
        } // 非空且未修改, 直接输出，对于数组不修改是因为之后只考虑是否不存在
        else {
          q.pop();
        } // 修改了，继续循环
      } while (1);
    } else if (flg == 3) { 
      int i = 0; // 编号
      int x = 0; // 数值
      scanf("%d %d", &i, &x);
      if (p[i] == -1) {
        if(q.empty()) printf("-1\n");// printf("Res:-1");
        else{ 
          do {
            if (q.empty()) {
              // printf("Res:-1\n");
              printf("-1\n");
              break;
            } // 检测到空
            else if (q.top().first == p[q.top().second]){
              printf("%d\n", q.top().first);
              // printf("Res:%d\n", q.top().first);
              break;
            } // 非空且未修改, 直接输出，对于数组不修改是因为之后只考虑是否不存在
            else {
              q.pop();
            } // 修改了，继续循环
          } while (1);
        }
      }
      else { // 拿出去了, 则做个标记即可，将新节点压进去
        p[i] = x;
        q.push(std::make_pair(x, i));
        do {
        if (q.empty()) {
          // printf("Res:-1\n");
          printf("-1\n");
          break;
        } // 检测到空
        else if (q.top().first == p[q.top().second]){
          printf("%d\n", q.top().first);
          // printf("Res:%d\n", q.top().first);
          break;
        } // 非空且未修改, 直接输出，对于数组不修改是因为之后只考虑是否不存在
        else {
          q.pop();
        } // 修改了，继续循环
      } while (1);
      } 
    }
  }
  return 0;
}
