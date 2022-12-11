  #include<cstdio>
  #include<algorithm>

  int a[200002];
  int b[200002];
  long long merge(int l, int h){
    if(l >= h) return 0; // 递归终点
    if(l + 1 == h) {
      if(a[l] < a[h]) {
        std::swap(a[l], a[h]); // 由于记录的是顺序对，因此我们整理为逆序.
        return 1;
      }
      return 0;
    }

    int left = l; // 左侧二分段
    int mid = ((l + h) / 2); // 中点，如果是奇数 1 2 **3** 4 5，如果是偶数则为 1 **2** 3 4
    int right = mid + 1; // 右侧分段
    long long lr = merge(l, mid); // 已经逆序
    long long rr = merge(right, h);
    int bp = l;
    long long cmpres = 0;

    // 统计两侧的顺序对个数
    while (left <= mid && right <= h){
      if(a[left] >= a[right]) {
        b[bp] = a[left]; 
        ++left;
      }
      else {
        cmpres += (mid - left + 1); //右边都比左边小
        b[bp] = a[right];
        ++right;
      }
      ++bp;
    }

    while(right <= h){
      b[bp] = a[right];
      ++bp;
      ++right;
    }
    while (left <= mid) {
      b[bp] = a[left];
      ++bp;
      ++left;
    }
    for(int i = l; i <= h; ++i) {
      a[i] = b[i];
    }
    return lr + rr + cmpres;
  }

  int main(){
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) scanf("%d", &a[i]);
    printf("%lld", merge(1, m));
    return 0;
  }