class Per_seg{
  private:
    struct node{
      int l, r, c;
    } arr[MAXN*C];
    int cnt;
    int new_mem() {
      return ++cnt;
    }
  public:
    void build(int now=1, int l=1, int r=len) {
      if (l == r) return;
      int mid = l + r >> 1;
      arr[now].l = new_mem();
      arr[now].r = new_mem();
      build(arr[now].l, l, mid);
      build(arr[now].r,mid+1,r);
    }
    void add(int id, int k) {
      int o = root[id-1];
      root[id] = r = new_mem();
      arr[r] = arr[o];
      int L = 1, R = len, mid;
      while (L < R) {
        arr[r].c++;
        mid = L + R >> 1;
        if (k <= mid) {
          arr[r].l = new_mem();
          r = arr[r].l;
          arr[r] = arr[o = arr[o].l];
          R = mid;
        } else {
          arr[r].r = new_mem();
          r = arr[r].r;
          arr[r] = arr[o = arr[o].r];
          L = mid+1;
        }
      }
      arr[r].c++;
    }
    int kth(int l, int r, int k) {
      r = root[r], l = root[l-1];
      int L = 1, R = len, mid;
      while (L < R) {
        int t = arr[arr[r].l].c - arr[arr[l].l].c;
        mid = L + R >> 1;
        if (k <= t) {
          r = arr[r].l, l = arr[l].l;
          R = mid;
        } else {
          k -= t;
          r = arr[r].r, l = arr[l].r;
          L = mid+1;
        }
      }
      return L;
    }
} seg;
