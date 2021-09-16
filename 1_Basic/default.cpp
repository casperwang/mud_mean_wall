#include <bits/stdc++.h>
using namespace std;
#define debug(args...) kout("[ " + string(#args) + " ]", args)
void kout() { cerr << endl; }
template <class T, class ...U> void kout(T a, U ...b) { cerr << a << ' ',kout(b...); }
template <class T> void pary(T L, T R) { while (L != R) cerr << *L << " \n"[++L==R]; }