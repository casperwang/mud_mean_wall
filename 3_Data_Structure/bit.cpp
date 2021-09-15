class Bit{
  private:
    int arr[MAXN+1];
    int lb(int a) {
      return a &- a;
    }
    void mdy(int a) {
      for (int i = a; i <= n; i+=lb(i))
        arr[i]++;
    }
    int qry(int a) {
      int s = 0;
      for (int i = a; i; i-=lb(i))
        s += arr[i];
      return s;
    }
} bit;
