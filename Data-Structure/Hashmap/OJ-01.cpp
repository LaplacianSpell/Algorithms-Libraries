#include<cstdio>
#include<cstring>

inline void rd(char t[]) {
  char ch = getchar();
  long long i = 0;
  while(ch==' ' || ch == '\n' || ch == '\r') ch = getchar();

  while(ch != ' ' && ch != '\n' && ch != '\r') {
    t[i] = ch;
    i ++;
    ch = getchar();
  }
}

// 记忆每一个层级，最后会让每一个层级都达到 31^m ,这样只需要每一次乘以一个m * 31 即可。
int main() {
  long long MOD = 998244353; 
  long long m = 0; // 子串长度
  char s[200] = "";
  long long p[200]; // 计算power
  
  scanf("%lld", &m);
  rd(s);
  
  long long res = 0;
  long long n = m - 1;
  long long con = 1;
  long a = 31;

  while(n > 0){
    if(n & 1){
      con = (con * a) % MOD;
    }
    a = (a * a) % MOD;
    n >>= 1;
  }
  

  for(long long i = 0; i < strlen(s) - m + 1; ++i) { // 首先填充第一个，一直到 m - 1 次幂
    p[i] = (con * (s[i] - 'a' + 1)) % MOD;

    if(i == 0) {
      // 如果是第一列 qinjiushao
      res = (s[0] - 'a' + 1);
      for (long long j = 1; j < m; ++j) {
        res = ((res * 31) % MOD) + (s[j] - 'a' + 1);
      }
    }

    else {
      if ((res - p[i-1]) > 0) res = (res - p[i-1]);
      else res = res - p[i-1] + MOD;
      res = (res * 31) % MOD + (s[i + m - 1] - 'a' + 1);
    }
    printf("%lld\n", res);
  }
  return 0;
}
