inline char readchar() {
  static const size_t bufsize = 65536;
  static char buf[bufsize];
  static char *p = buf, *e = buf;
  if (p == e) e = buf + fread_unlocked(buf, 1, bufsize, stdin), p = buf;
  return *p++;
}
inline void const Read(int &p) {
  p = 0;
  bool tmp = 0;
  char c = readchar();
  tmp = !(c^'-');
  while (c < '0' || c > '9')
    c = readchar();
  while (c >= '0' && c <= '9')
    p = (p<<3)+(p<<1)+(c^48), c = readchar();
  p = tmp?-p:p;
}
