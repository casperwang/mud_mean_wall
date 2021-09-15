size_t Rand = 7122;
inline size_t Random() {
  return Rand = Rand * 0xdefaced + 1;
}
class Treap{
  private:
    struct node{
      int l, r, pri, key, sze;
      node() {
        l = r = sze = 0;
      }
      node(int _k) {
        l = r = 0, pri = Random(), key = _k, sze = 1;
      }
    } arr[MAXN+1];
    void pull(int now) {
      if (!now) return;
      arr[now].sze = arr[arr[now].l].sze + arr[arr[now].r].sze + 1;
    }
    int cnt;
  public:
    int Merge(int a, int b) {
      if (!a || !b) return a ? a : b;
      if (arr[a].pri > arr[b].pri) {
        arr[a].r = Merge(arr[a].r, b);
        pull(a);
        return a;
      } else {
        arr[b].l = Merge(a, arr[b].l);
        pull(b);
        return b;
      }
    }
    void Split_by_key(int o, int &a, int &b, int k) {
      if (!o) a = b = 0;
      else if (arr[o].key <= k) {
        a = o;
        Split_by_key(arr[o].r, arr[a].r, b, k);
      } else {
        b = o;
        Split_by_key(arr[o].l, a, arr[b].l, k);
      }
      pull(o);
    }
    void Split_by_sze(int o, int &a, int &b, int s) {
      if (!o) a = b = 0;
      else if (arr[arr[o].l].sze + 1 <= s) {
        a = o;
        Split_by_sze(arr[o].r, arr[a].r, b, s-(arr[arr[o].l].sze+1));
      } else {
        b = o;
        Split_by_sze(arr[o].l, a, arr[b].l, s);
      }
      pull(o);
    }
    bool Insert(int x, int &root) {
      int a = 0, b = 0, c = 0;
      Split_by_key(root, b, c, x), root = b;
      Split_by_key(root, a, b, x-1);
      if (arr[b].sze) {
        root = Merge(a, Merge(b, c));
        return 0;
      }
      arr[++cnt] = node(x);
      root = Merge(Merge(a, cnt), c);
      return 1;
    }
    bool Erase(int x, int &root) {
      int a = 0, b = 0, c = 0;
      Split_by_key(root, b, c, x), root = b;
      Split_by_key(root, a, b, x-1);
      root = Merge(a, c);
      if (!arr[b].sze) return 0;
      return 1;
    }
    int kth(int k, int &root) {
      if (k < 1 || k > arr[root].sze) return -1;
      int a = 0, b = 0, c = 0;
      Split_by_sze(root, a, b, arr[root].sze - k), root = b;
      Split_by_sze(root, b, c, arr[root].sze - k + 1);
      root = Merge(a, Merge(b, c));
      return arr[b].key;
    }
} treap;
