#include<cstdio>
#include<bits/extc++.h>
using namespace __gnu_pbds;

struct Node {
  int ID;
  Node *next;
  Node *prev;
  Node(int var) {
    ID = var;
  }
};


inline int read(){
    register int x = 0, t = 1;
    register char ch=getchar(); // 读入单个字符到寄存器
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            t=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=(x<<1)+(x<<3)+(ch^48);  // 移位与异或
      	// 第十行可以换成 x = x * 10 + ch - '0'
        ch=getchar();
    }
    return x*t;
}

inline void write(int x)
{
    if(x<0){
    	putchar('-');
		x=-x;
	}
    if(x>9) 
		write(x/10);
    putchar(x%10+'0');
}

int main() {
  gp_hash_table<int, Node*> Cache;
  int n, m;
  int var;
  Node* head = nullptr;
  int CacheNumCnt = 0;
  n = read();
  m = read();
  for(int i = 0; i < n; i++){
    var = read();
    if(Cache.find(var) != Cache.end()) { // Hit
      auto ptr = Cache.find(var);
      if(ptr->second == head) {write(-1);putchar('\n');}
      else if(ptr->second == head->prev) {
        head = head->prev;
        write(-1);
        putchar('\n');
      }
      else {
        ptr->second->prev->next = ptr->second->next;
        ptr->second->next->prev = ptr->second->prev;
        
        ptr->second->prev = head->prev;
        ptr->second->next = head;
        
        head->prev->next = ptr->second;
        head->prev = ptr->second;
        head = ptr->second;
        write(-1);
        putchar('\n');
      }
    }
    else if(CacheNumCnt < m){ // Not Hit Not Full;
      Cache[var] = new Node(var);
      auto ptr = Cache.find(var);
      if(CacheNumCnt == 0){
        ptr->second->next = ptr->second;
        ptr->second->prev = ptr->second;
        head = ptr->second;
      } else {
        ptr->second->next = head;
        ptr->second->prev = head->prev;
        head->prev->next = ptr->second;
        head->prev = ptr->second;
        head = ptr->second;
      }
      ++ CacheNumCnt;
      write(-1);
      putchar('\n');
    }
    else { //Not Hit But Full
      write(head->prev->ID);
      putchar('\n');
      if(m == 1){
       delete head;
       Cache.clear();
       Cache[var] = new Node(var);
       auto ptr = Cache.find(var);
       ptr->second->next = ptr->second;
       ptr->second->prev = ptr->second;
       head = ptr->second;
      }
      else{
        int ID = head->prev->ID; // 尾节点ID
        Cache[var] = new Node(var); // 插入新节点
        auto ptr = Cache.find(var); // 新节点指针
        auto delptr = head->prev; // 删除的指针
        head->prev->prev->next = ptr->second; 
        head->prev = ptr->second;
        ptr->second->next = head;
        ptr->second->prev = delptr->prev;
        head = ptr->second;
        delete delptr;
        Cache.erase(ID);
      }
    }
  }
  return 0;
}
