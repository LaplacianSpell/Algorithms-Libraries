#define TODO1 eles_on_left // <Replace with your answer for TODO1>
#define TODO2 (lvl > 0 && p->stride[lvl] + 1 > k)  // <Replace with your answer for TODO2>
#define TODO3 (p->stride[lvl] + 1) // <Replace with your answer for TODO3>

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int maxn = 100003;
const int maxh = 20;

struct Node {
Node* next[maxh];
int stride[maxh]; 
// stride[i] means the number of elements between this node and next[i]
// (does not include this node and next[i])
int val;
};

Node *nptr, *head;

void insert(Node* q) {
Node* p[maxh];
int count_lower[maxh] = {0};
int lvl;
p[lvl = maxh - 1] = head; // 最上层
while (lvl >= 0) { // 寻找
    if (p[lvl]->next[lvl] && q->val < p[lvl]->next[lvl]->val) { // 比下一个小，即应该塞到之前
        count_lower[lvl] += p[lvl]->stride[lvl] + 1; // 到next[lvl]的长度加1
        p[lvl] = p[lvl]->next[lvl]; // 将下一个节点赋予该节点
    } else { // 到该层的头了或者是比下一个大
        if (lvl) {  // 如果不是最底层
            p[lvl - 1] = p[lvl]; // 将
        }
        --lvl;
    }
}

int eles_on_left = 0;
for (lvl = 0; lvl < maxh; ++lvl) {
    q->stride[lvl] = p[lvl]->stride[lvl] - eles_on_left;
    q->next[lvl] = p[lvl]->next[lvl];
    p[lvl]->stride[lvl] = TODO1 /* What is p[lvl]'s new stride? */;
    p[lvl]->next[lvl] = q;
    eles_on_left += count_lower[lvl];
    if (rand() & 1) {
        break;
    }
}
while (++lvl < maxh) {
    p[lvl]->stride[lvl] += 1;
}
}

int getKth(int k) {
int lvl = maxh - 1;
Node* p = head;
while (k) {
    if (TODO2 /* On what condition shall we move down? */) {
        --lvl;
    } else {
        k -= TODO3 /* How to update k? */;
        p = p->next[lvl];
    }
}
return p->val;
}

int main() {
srand(1984);
int n, op, v; // n 获得操作数
scanf("%d", &n);
nptr = new Node[n + 1]; // 指向一个列表
memset(nptr, 0, sizeof(Node) * (n + 1)); // 
head = nptr++;
head->val = 0x3f3f3f3f;
while (n--) {
    scanf("%d%d", &op, &v);
    if (op == 1) {
        nptr->val = v;
        insert(nptr++);
    } else {
        v = getKth(v);
        printf("%d\n", v);
    }
}
}
