/* Delaunay Triangulation:
Given a sets of points on 2D plane, find a
triangulation such that no points will strictly
inside circumcircle of any triangle.
find : return a triangle contain given point
add_point : add a point into triangulation
A Triangle is in triangulation iff. its has_chd is 0.
Region of triangle u: iterate each u.edge[i].tri,
each points are u.p[(i+1)%3], u.p[(i+2)%3] 
Voronoi diagram: for each triangle in triangulation, 
the bisector of all its edges will split the region.
nearest point will belong to the triangle containing it
 */
const int N = 100000 + 5;
const long long inf = 2e6;
// return p4 is in circumcircle of tri(p1,p2,p3)
long long sqr(long long x) { return x * x; }
bool in_cc(const pll& p1, const pll& p2, const pll& p3, const pll& p4) {
    long long u11 = p1.X - p4.X; long long u12 = p1.Y - p4.Y;
    long long u21 = p2.X - p4.X; long long u22 = p2.Y - p4.Y;
    long long u31 = p3.X - p4.X; long long u32 = p3.Y - p4.Y;
    long long u13 = sqr(p1.X) - sqr(p4.X) + sqr(p1.Y) - sqr(p4.Y);
    long long u23 = sqr(p2.X) - sqr(p4.X) + sqr(p2.Y) - sqr(p4.Y);
    long long u33 = sqr(p3.X) - sqr(p4.X) + sqr(p3.Y) - sqr(p4.Y);
    __int128 det = (__int128)-u13 * u22 * u31 + (__int128)u12 * u23 * u31 + (__int128)u13 * u21 * u32 - (__int128)u11 * u23 * u32 - (__int128)u12 * u21 * u33 + (__int128)u11 * u22 * u33;
    return det > eps;
}
typedef int SdRef;
struct Tri;
typedef Tri* TriRef;
struct Edge {
    TriRef tri; SdRef side;
    Edge():tri(0), side(0){}
    Edge(TriRef _tri, SdRef _side):tri(_tri), side(_side){}
};
struct Tri {
    pll p[3];
    Edge edge[3];
    TriRef chd[3];
    Tri() {}
    Tri(const pll& p0, const pll& p1, const pll& p2) {
        p[0] = p0; p[1] = p1; p[2] = p2;
        chd[0] = chd[1] = chd[2] = 0;
    }
    bool has_chd() const { return chd[0] != 0; }
    int num_chd() const {
        return !!chd[0] + !!chd[1] + !!chd[2];
    }
    bool contains(pll const& q) const {
        for (int i = 0; i < 3; ++i)
            if (ori(p[i], p[(i + 1) % 3], q) < -eps)
                return 0;
        return 1;
    }
} pool[N * 10], *tris;
void edge(Edge a, Edge b) {
    if(a.tri) a.tri -> edge[a.side] = b;
    if(b.tri) b.tri -> edge[b.side] = a;
}
struct Trig { // Triangulation
    Trig() {
        the_root = // Tri should at least contain all points
            new(tris++) Tri(pll(-inf, -inf), pll(inf + inf, -inf), pll(-inf, inf + inf));
    }
    TriRef find(pll p) { return find(the_root, p); }
    void add_point(const pll &p) { add_point(find(the_root, p), p); }
    TriRef the_root;
    static TriRef find(TriRef root, const pll& p) {
        while (1) {
            if (!root -> has_chd())
                return root;
            for (int i = 0; i < 3 && root -> chd[i]; ++i)
                if (root -> chd[i] -> contains(p)) {
                    root = root -> chd[i];
                    break;
                }
        }
        assert(0); // "point not found"
    }
    void add_point(TriRef root, pll const& p) {
        TriRef t[3];
        /* split it into three triangles */
        for (int i = 0; i < 3; ++i)
            t[i] = new(tris++) Tri(root -> p[i], root -> p[(i + 1) % 3], p);
        for (int i = 0; i < 3; ++i)
            edge(Edge(t[i], 0), Edge(t[(i + 1) % 3], 1));
        for (int i = 0; i < 3; ++i)
            edge(Edge(t[i], 2), root -> edge[(i + 2) % 3]);
        for (int i = 0; i < 3; ++i)
            root -> chd[i] = t[i];
        for (int i = 0; i < 3; ++i)
            flip(t[i], 2);
    }
    void flip(TriRef tri, SdRef pi) {
        TriRef trj = tri -> edge[pi].tri;
        int pj = tri -> edge[pi].side;
        if (!trj) return;
        if (!in_cc(tri -> p[0], tri -> p[1], tri -> p[2], trj -> p[pj])) return;
        /* flip edge between tri,trj */
        TriRef trk = new(tris++) Tri(tri -> p[(pi + 1) % 3], trj -> p[pj], tri -> p[pi]);
        TriRef trl = new(tris++) Tri(trj -> p[(pj + 1) % 3], tri -> p[pi], trj -> p[pj]);
        edge(Edge(trk, 0), Edge(trl, 0));
        edge(Edge(trk, 1), tri->edge[(pi + 2) % 3]);
        edge(Edge(trk, 2), trj->edge[(pj + 1) % 3]);
        edge(Edge(trl, 1), trj->edge[(pj + 2) % 3]);
        edge(Edge(trl, 2), tri->edge[(pi + 1) % 3]);
        tri -> chd[0] = trk; tri -> chd[1] = trl; tri -> chd[2] = 0;
        trj -> chd[0] = trk; trj -> chd[1] = trl; trj -> chd[2] = 0;
        flip(trk, 1); flip(trk, 2);
        flip(trl, 1); flip(trl, 2);
    }
};
vector<TriRef> triang; // vector of all triangle
set<TriRef> vst;
void go(TriRef now) { // store all tri into triang
    if (vst.find(now) != vst.end())
        return;
    vst.insert(now);
    if (!now -> has_chd())
        return triang.push_back(now);
    for (int i = 0; i < now->num_chd(); ++i)
        go(now -> chd[i]);
}
void build(int n, pll* ps) { // build triangulation
    tris = pool; triang.clear(); vst.clear();
    random_shuffle(ps, ps + n);
    Trig tri; // the triangulation structure
    for (int i = 0; i < n; ++i)
        tri.add_point(ps[i]);
    go(tri.the_root);
}