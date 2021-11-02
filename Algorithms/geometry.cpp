const double eps = 1e-9;
int sign(double x) { return (x > eps) - (x < -eps); }

struct PT {
    double x = 0, y = 0;
    PT() {};
    PT(double x, double y): x(x), y(y) {};
    PT(const PT& P) : x(P.x), y(P.y) {};
    PT operator + (const PT &a) const { return PT(x + a.x, y + a.y); }
    PT operator - (const PT &a) const { return PT(x - a.x, y - a.y); }
    PT operator * (const double a) const { return PT(x * a, y * a); }
    PT operator / (const double a) const { return PT(x / a, y / a); }
    bool operator == (PT a) const { return sign(a.x - x) == 0 && sign(a.y - y) == 0; }
    bool operator != (PT a) const { return !(*this == a); }
    void read() { cin >> x >> y; }
};
inline double dot(PT a, PT b) { return a.x * b.x + a.y * b.y; }
inline double cross(PT a, PT b) { return a.x * b.y - a.y * b.x; }