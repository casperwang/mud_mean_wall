class Seg{
  private:
    int arr[MAXN*4+5];
    int tag[MAXN*4+5];
    void pull(int now) {
      arr[now] = arr[now*2] + arr[now*2+1];
    }
    void push(int now, int len) {
      arr[now] += tag[now];
      if (len > 1) {
        tag[now*2  ] += tag[now];
        tag[now*2+1] += tag[now];
      }
      tag[now] = 0;
    }
  public:
    void build(int now=1, int l=1, int r=n) {
      if (l == r) {
        arr[now] = 0;
        return;
      }
      int mid = l + r >> 1;
      build(now*2  , l, mid);
      build(now*2+1,mid+1,r);
      pull(now);
      return;
    }
    void mdy(int ml, int mr, int k, int now=1, int l=1, int r=n) {
      push(now, r-l+1);
      if (ml <= l && r <= mr) {
        tag[now] += k;
        push(now, r-l+1);
        return;
      } else if (l > mr || r < ml) return;
      int mid = l + r >> 1;
      mdy(ml, mr, k, now*2  , l, mid);
      mdy(ml, mr, k, now*2+1,mid+1,r);
      pull(now);
      return;
    }
    int qry(int ql, int qr, int now=1, int l=1, int r=n) {
      push(now, r-l+1);
      if (ql <= l && r <= qr) {
        return arr[now];
      } else if (l > qr || r < ql) return 0;
      int mid = l + r >> 1, sum = 0;
      sum += qry(ql, qr, now*2  , l, mid);
      sum += qry(ql, qr, now*2+1,mid+1,r);
      pull(now);
      return sum;
    }
} seg;
