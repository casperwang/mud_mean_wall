struct line{
  double a, b;
  int l, r;
};
class LiChao_Seg{
  private:
    int arr[MAXN*4+5];
    double calc(int id, int x) {
      return p[id].a * x + p[id].b;
    }
  public:
    void mdy(int ml, int mr, int v, int now=1, int l=1, int r=MAXN) {
      int mid = l + r >> 1;
      if (ml <= l && r <= mr) {
        int o = arr[now];
        double reso = calc(o, mid), resv = calc(v, mid);
        if (resv > reso) arr[now] = v;
        if (l == r) return;
        if (p[v].a < p[o].a) {
          if (reso >= resv)
            mdy(ml    , mr    , v, now*2  , l, mid);
          else
            mdy(p[o].l, p[o].r, o, now*2+1,mid+1,r);
        } else if (p[v].a > p[o].a) {
          if (resv >= reso) 
            mdy(p[o].l, p[o].r, o, now*2  , l, mid);
          else
            mdy(ml    , mr    , v, now*2+1,mid+1,r);
        }
        return;
      } else if (l > mr || r < ml) return;
      mdy(ml, mr, v, now*2  , l, mid);
      mdy(ml, mr, v, now*2+1,mid+1,r);
    }
    pdi qry(int d, int now=1, int l=1, int r=MAXN) {
      pdi res = pdi(calc(arr[now], d), arr[now]);
      if (l == d && r == d) {
        return res;
      } else if (l > d || r < d) return pdi(-INF, 0);
      int mid = l + r >> 1;
      res = max(res, qry(d, now*2  , l, mid));
      res = max(res, qry(d, now*2+1,mid+1,r));
      return res;
    }
} seg;
