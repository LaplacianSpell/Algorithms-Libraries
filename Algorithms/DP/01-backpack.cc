#include<string.h>
#include<iostream>
#include<queue>
#include<vector>
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

/*
110 8
1 11  11 21  21 31  23 33  33 43  43 53  45 55  55 65

30 10
1 4  2 6  3 12  2 7  8 2  10 18  8 2  6 7  1 9  4 10

6 4
1 4 2 6 3 12 2 7

30 15
1 4  2 6  3 12  2 7  8 2  10 18  8 2  6 7  1 9  4 10  3 28  4 12  3 7  7 2  8 17

50 20
1 4  2 6  3 12  2 7  8 2  10 18  8 2  6 7  1 9  4 10  3 28  4 12  3 7  7 2  8 17  7 4  14 17  13 4  3 8  5 9
*/

int size_[100]={0};
int value[100]={0};
bool divide_conquer_bag[100]={0};
int dynamic_bag[100]={0};
float greedy_bag[100]={0};
int backtracking_bag[100]={0};
int monte_bag[100] = {0};
int tag[100]={0};
int num;
int str[50][100]={0};

int divide_conquer(int cur_num,int capacity){
    if (cur_num <= 0 || capacity <= 0){
        divide_conquer_bag[cur_num] = 0;
        return 0;
    }
    if (capacity - size_[cur_num] < 0){
        divide_conquer_bag[cur_num] = 0;
        return divide_conquer(cur_num - 1,capacity);
    }
    if (divide_conquer(cur_num - 1,capacity - size_[cur_num])+value[cur_num] > divide_conquer(cur_num - 1,capacity)){
        divide_conquer_bag[cur_num] = 1;
        return divide_conquer(cur_num - 1,capacity - size_[cur_num])+value[cur_num];
    }
    else{
        divide_conquer_bag[cur_num] = 0;
        return divide_conquer(cur_num - 1,capacity);
    }
}

int dynamic(int cur_num,int capacity){
    if (str[cur_num][capacity] >= 0){
        return str[cur_num][capacity];
    }
    if (cur_num <= 0 || capacity <= 0){
        str[cur_num][capacity] = 0;
        return 0;
    }
    if (capacity - size_[cur_num] < 0){
        str[cur_num][capacity] = dynamic(cur_num - 1,capacity);
        return str[cur_num][capacity];
    }
    if (dynamic(cur_num - 1,capacity - size_[cur_num])+value[cur_num] > dynamic(cur_num - 1,capacity)){
        dynamic_bag[cur_num] = 1;
        str[cur_num][capacity] = dynamic(cur_num - 1,capacity - size_[cur_num])+value[cur_num];
        return str[cur_num][capacity];
    }
    else{
        //dynamic_bag[cur_num] = 0;
        str[cur_num][capacity] = dynamic(cur_num - 1,capacity);
        return str[cur_num][capacity];
    }
}

int greedy(int num,int c){
    int temp,j;
    int v = 0;
    //float c_i,c_j;
    memset(greedy_bag, 0, sizeof(greedy_bag));
    for(int i = 1;i <= num;i++){
        tag[i] = i;
    }
    
    // for(int i = 1;i <= num;i++){
    //     printf("%d:%d; ",i,value[i]/size_[i]);
    // }
    // printf("\n");
    
    for(int i = 1;i <= num;i++){
        //printf("\n%d:",tag[i]);
        for(int j = i;j <= num;j++){
            if(float(value[i])/float(size_[i]) < float(value[j])/float(size_[j])){
                temp = value[i];
                value[i] = value[j];
                value[j] = temp;
                temp = size_[i];
                size_[i] = size_[j];
                size_[j] = temp;
                temp = tag[j];
                tag[j] = tag[i];
                tag[i] = temp;
                
                //printf("%d ",tag[j]);
            }
        }
    }
    for (j = 1;j <= num;j++){
        if (size_[j] > c){
            continue;
        }
        greedy_bag[j] = 1;
        c -= size_[j];
        v += value[j];
    }
    return v;
}

float retrieve(int cur_num,int backtracking_val,int backtracking_capacity){
    float v = backtracking_val;
    for (;cur_num <= num;cur_num++){
        if (size_[cur_num] <= backtracking_capacity){
            v += value[cur_num];
            backtracking_capacity -= size_[cur_num];
        }
        else{
            backtracking_capacity = 0;
            v += ((float)value[cur_num]/(float)size_[cur_num]) * float(backtracking_capacity);
            return v;
        }
    }
    return v;
}

int backtracking(int c){
    int temp[100]={0};
    memset(temp,0,sizeof(temp));
    memset(backtracking_bag,0,sizeof(backtracking_bag));
    int maxvalue = 0;
    int i = 1;
    int v = 0;
    while(1){
        for(;i <= num && size_[i] <= c;i++){
            v += value[i];
            c -= size_[i];
            temp[i] = 1;
        }
        if (i >= num){
            for (int j = 1;j <= num;j++){
                backtracking_bag[j] = temp[j];
                //printf("%d:%d  ",j,backtracking_bag[j]);
                
            }
            //printf("\n");

            maxvalue = v;
            i = num;
        }
        else{
            temp[i] = 0;
        }
        //printf("%d\n",maxvalue);
        while (retrieve(i + 1,v,c) <= maxvalue){
            while(i > 0 && temp[i] == 0){
                i--;
            }
            if (i == 0){
                return maxvalue;
            }
            temp[i] = 0;
            v -= value[i];
            c += size_[i];
        }
        i++;
    }
}

struct Node {
    int next,s,v;
    double maxV;    // 该结点的上界
    bool operator < (const Node &x) const {
        return maxV < x.maxV;   // 优先队列内按上界从高到低排序
    }
};

priority_queue <Node> que;

int Max(int a,int b){
    if (a > b){
        return a;
    }
    else{
        return b;
    }
}

double bound_(int i, int s, int v,int capacity) {
    double res = v; 
    int c = capacity - s;
    while (i <= num && size_[i] <= c) { 
        c -= size_[i];
        v += value[i];
        i++;
    }
    if (i <= num) {
        res = v + c * (value[i] * 1.0 / size_[i]);
    }
    return res;
}

int branch_bound(int c){
    int v = 0;
    Node r = {1,0,0,bound_(1,0,0,c)};
    //printf("%f   ",r.maxV);
    que.push(r);
    //printf("push:%d \n",r.next);
    while (que.top().maxV > v){
        Node n = que.top();
        que.pop();
        //printf("pop%d \n",n.next);
        if (n.next == num){
            v = Max(v,n.v);
        }
        else{
            Node t = n;
            if (size_[n.next] + n.s <= c){
                n.maxV = bound_(n.next,n.s,n.v,c);
                //printf("%f   ",n.maxV);
                if (n.maxV > v){
                    n.s += size_[n.next];
                    n.v += value[n.next];
                    n.next++;
                    que.push(n);
                    //printf("push%d \n",n.next);
                }
            }
            t.maxV = bound_(t.next + 1,t.s,t.v,c);
            //printf("%f   ",t.maxV);
            if (n.maxV > v){
                t.next++;
                que.push(t);
                //printf("push:%d \n",t.next);
            }
        }
    }
    return v;
}

int monte(int c){
    int x[100] = {0};
    int fre,max,i,j,flag;
    memset(x,0,sizeof(x));
    memset(monte_bag,0,sizeof(monte_bag));
    fre = pow(2,num);
    srand(time(NULL));
    max = 0;
    for (i = 0;i < fre;i++){
        int s,v,a;
        s = 0;
        v = 0;
        flag = 0;
        a = rand();
        for(j = 1;j <= num;j++){
            x[j] = a%2;//x[j]则为随机的0或者1
            a = a>>1;//随机数a除以2仍然是随机数
            if ((j + 1)%15 == 0){//由于随机数范围有限，每隔一段就要重新赋随机数
                a = rand();
            }
        } 
        for (j = 1;j <= num;j++){
            s += x[j]*size_[j];
            v += x[j]*value[j];
            if (s <= c){
                if (max < v){
                    max = v;
                    if (flag == 0){
                        for (int k = j;k > 0;k--){
                            monte_bag[k] = x[k];
                        }
                        flag = 1;
                    }
                    monte_bag[j] = x[j];
                }
            }
            else{
                s -= x[j]*size_[j];
                v -= x[j]*value[j];
                x[j] = 0;
                if (flag == 1){
                    monte_bag[j] = x[j];
                }
            }
        }
        for(j = 1;j <= num;j++){
            x[j] = 0;
        }
    }
    return max;
}

int main(){
    int capacity;
    clock_t start, end;
    printf("请输入背包容量：\n");
    scanf("%d",&capacity);
    printf("\n请输入总物品个数:\n");
    scanf("%d",&num);
    printf("\n请输入物品大小和价值:\n");
    for (int i = 1;i <= num;i++){
        scanf("%d%d",&size_[i],&value[i]);
    }

    int res;
    memset(divide_conquer_bag, 0, sizeof(divide_conquer_bag));
    start = clock();
    res = divide_conquer(num,capacity);
    end = clock();
    printf("分治法得出最大价值为%d,要放入背包的物品序号为：\n",res);
    for (int i = 1;i <= num;i++){
        if (divide_conquer_bag[i]){
            printf("%d ",i);
        }
    }
    printf("\n");
    
    printf("time=%f\n", (double)(end - start) / CLOCKS_PER_SEC);

    memset(str, -1, sizeof(str));
    start = clock();
    res = dynamic(num,capacity);
    end = clock();
    printf("动态规划法得出最大价值为%d,要放入背包的物品序号为：\n",res);
    for (int i = 1;i <= num;i++){
        if (divide_conquer_bag[i]){
            printf("%d ",i);
        }
    }
    
    printf("\n");
    
    printf("time=%f\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    start = clock();
    res = greedy(num,capacity);
    end = clock();
        printf("贪心算法得出最大价值为%d,要放入背包的物品序号为：\n",res);

    // for (int i = 1;i <= num;i++){
    //     printf("%d ",tag[i]);
    // }
    //printf("\n");
    for (int i = 1;i <= num;i++){
        for (int j = 1;j <= num;j++){
            if (greedy_bag[j] > 0 && tag[j] == i){
                printf("%d ",tag[j]);
                break;
            }
        }
    }
    printf("\n");
    
    printf("time=%f\n", (double)(end - start) / CLOCKS_PER_SEC);
    start = clock();
    res = backtracking(capacity);
    end = clock();
    printf("回溯法得出最大价值为%d,要放入背包的物品序号为：\n", res);
    for (int i = 1;i <= num;i++){
        for (int j = 1;j <= num;j++){
            if (backtracking_bag[j] > 0 && tag[j] == i){
                printf("%d ",tag[j]);
                break;
            }
        }
    }
    printf("\n");
    
    printf("time=%f\n", (double)(end - start) / CLOCKS_PER_SEC);
    start = clock();
    res = branch_bound(capacity);
    end = clock();
    printf("分支界限法得出最大价值为%d,要放入背包的物品序号为：\n",res);

    for (int i = 1;i <= num;i++){
        for (int j = 1;j <= num;j++){
            if (backtracking_bag[j] > 0 && tag[j] == i){
                printf("%d ",tag[j]);
                break;
            }
        }
    }
    printf("\n");
    
    printf("time=%f\n", (double)(end - start) / CLOCKS_PER_SEC);
    start = clock();
    res = monte(capacity);
    end = clock();
    printf("蒙特卡洛法得出最大价值为%d,要放入背包的物品序号为：\n",res);
    for (int i = 1;i <= num;i++){
        for (int j = 1;j <= num;j++){
            if (monte_bag[j] > 0 && tag[j] == i){
                printf("%d ",tag[j]);
                break;
            }
        }
    }
    printf("\n");
    
    printf("time=%f\n", (double)(end - start) / CLOCKS_PER_SEC);
    
    return 0;
}

/*
71 26
34 59
82 30
23 19
1 66
88 85
12 94
57 8
10 3
68 44
5 5
33 1
37 41
69 82
98 76
24 1
26 12
83 81
16 73
26 32
18 74
43 54
52 62
71 41
22 19
65 10
68 65
8 53
40 56
40 53
24 70
72 66
16 58
34 22
10 72
19 33
28 96
13 88
34 68
98 45
29 44
31 61
79 78
33 78
60 6
74 66
44 11
56 59
54 83
17 48
63 52
83 7
100 51
54 37
10 89
5 72
79 23
42 52
65 55
93 44
52 57
64 45
85 11
68 90
54 31
62 38
29 48
40 75
35 56
90 64
47 73
77 66
87 35
75 50
39 16
18 51
38 33
25 58
61 85
13 77
36 71
53 87
46 69
28 52
44 10
34 13
39 39
69 75
42 38
97 13
34 90
83 35
8 83
74 93
38 61
74 62
22 95
40 73
7 26
94 85
*/