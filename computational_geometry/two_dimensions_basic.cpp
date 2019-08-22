const double INF = 1e60;
const double eps = 1e-8;
const double pi = acos(-1);

int sgn(double x) { return x < -eps ? -1 : x > eps; }
double Sqr(double x) { return x * x; }
double Sqrt(double x) { return x >= 0 ? std::sqrt(x) : 0; }

struct Vec {
    double x, y;
    
    Vec(double _x = 0, double _y = 0): x(_x), y(_y) {}
    
    Vec operator + (const Vec &oth) const { return Vec(x + oth.x, y + oth.y); }
    Vec operator - (const Vec &oth) const { return Vec(x - oth.x, y - oth.y); }
    Vec operator * (double t) const { return Vec(x * t, y * t); }
    Vec operator / (double t) const { return Vec(x / t, y / t); }
    
    double len2() const { return Sqr(x) + Sqr(y); }
    double len() const { return Sqrt(len2()); }
    
    Vec norm() const { return Vec(x / len(), y / len()); }
    Vec turn90() const { return Vec(-y, x); }
    Vec rotate(double rad) const { return Vec(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad)); }
};

double Dot(Vec a, Vec b) { return a.x * b.x + a.y * b.y; }
double Cross(Vec a, Vec b) { return a.x * b.y - a.y * b.x; }
double Det(Vec a, Vec b, Vec c) { return Cross(b - a, c - a); }

double Angle(Vec a, Vec b) { return acos(Dot(a, b) / (a.len() * b.len())); }

struct Line {
    Vec a, b;
    double theta;
    
    void GetTheta() {
        theta = atan2(b.y - a.y, b.x - a.x);
    }

    Line() = default;
    Line(Vec _a, Vec _b): a(_a), b(_b) {
        GetTheta();
    }

    bool operator < (const Line &oth) const {
        return theta < oth.theta;
    }
    
    Vec v() const { return b - a; }
    double k() const { return !sgn(b.x - a.x) ? INF : (b.y - a.y) / (b.x - a.x); }
};

bool OnLine(Vec p, Line l) {
    return sgn(Cross(l.a - p, l.b - p)) == 0;
}

bool OnSeg(Vec p, Line l) {
    return OnLine(p, l) && sgn(Dot(l.b - l.a, p - l.a)) >= 0 && sgn(Dot(l.a - l.b, p - l.b)) >= 0;
}

bool Parallel(Line l1, Line l2) {
    return sgn(Cross(l1.v(), l2.v())) == 0;
}

Vec Intersect(Line l1, Line l2) {
    double s1 = Det(l1.a, l1.b, l2.a);
    double s2 = Det(l1.a, l1.b, l2.b);
    return (l2.a * s2 - l2.b * s1) / (s2 - s1);
}

Vec Project(Vec p, Line l) {
    return l.a + l.v() * (Dot(p - l.a, l.v())) / l.v().len2();
}

double DistToLine(Vec p, Line l) {
    return std::abs(Cross(p - l.a, l.v())) / l.v().len();
}

int Dir(Vec p, Line l) {
    return sgn(Cross(p - l.b, l.v()));
}

bool SegIntersect(Line l1, Line l2) { // Strictly
    return Dir(l2.a, l1) * Dir(l2.b, l1) < 0 && Dir(l1.a, l2) * Dir(l1.b, l2) < 0;
}

bool InTriangle(Vec p, std::vector<Vec> tri) {
    if (sgn(Cross(tri[1] - tri[0], tri[2] - tri[0])) < 0)
        std::reverse(tri.begin(), tri.end());
    for (int i = 0; i < 3; ++i)
        if (Dir(p, Line(tri[i], tri[(i + 1) % 3])) == 1)
            return false;
    return true;
}

std::vector<Vec> ConvexCut(const std::vector<Vec> &ps, Line l) { // Use the counterclockwise halfplane of l to cut a convex polygon
    std::vector<Vec> qs;
    for (int i = 0; i < (int)ps.size(); ++i) {
        Vec p1 = ps[i], p2 = ps[(i + 1) % ps.size()];
        int d1 = sgn(Cross(l.v(), p1 - l.a)), d2 = sgn(Cross(l.v(), p2 - l.a));
        if (d1 >= 0) qs.push_back(p1);
        if (d1 * d2 < 0) qs.push_back(Intersect(Line(p1, p2), l));
    }
    return qs;
}

struct Cir {
    Vec o;
    double r;

    Cir() = default;
    Cir(Vec _o, double _r): o(_o), r(_r) {}

    Vec PointOnCir(double rad) const { return Vec(o.x + cos(rad) * r, o.y + sin(rad) * r); }
};

bool Intersect(Cir c, Line l, Vec &p1, Vec &p2) {
    double x = Dot(l.a - c.o, l.b - l.a);
    double y = (l.b - l.a).len2();
    double d = Sqr(x) - y * ((l.a - c.o).len2() - Sqr(c.r));
    if (sgn(d) < 0) return false;
    d = std::max(d, 0.);
    Vec p = l.a - (l.v() * (x / y));
    Vec delta = l.v() * (Sqrt(d) / y);
    p1 = p + delta; p2 = p - delta;
    return true;
}

bool Intersect(Cir a, Cir b, Vec &p1, Vec &p2) { // Not suitable for coincident circles
    double s1 = (a.o - b.o).len();
    if (sgn(s1 - a.r - b.r) > 0 || sgn(s1 - std::abs(a.r - b.r)) < 0) return false;
    double s2 = (Sqr(a.r) - Sqr(b.r)) / s1;
    double aa = (s1 + s2) * 0.5, bb = (s1 - s2) * 0.5;
    Vec o = (b.o - a.o) * (aa / (aa + bb)) + a.o;
    Vec delta = (b.o - a.o).norm().turn90() * Sqrt(a.r * a.r - aa * aa);
    p1 = o + delta; p2 = o - delta;
    return true;
}

bool Tangent(Cir c, Vec p0, Vec &p1, Vec &p2) { // In clockwise order
    double x = (p0 - c.o).len2(), d = x - Sqr(c.r);
    if (sgn(d) <= 0) return false;
    Vec p = (p0 - c.o) * (Sqr(c.r) / x);
    Vec delta = ((p0 - c.o) * (-c.r * Sqrt(d) / x)).turn90();
    p1 = c.o + p + delta; p2 = c.o + p - delta;
    return true;
}

std::vector<Line> ExTangent(Cir c1, Cir c2) { // External tangent line
    std::vector<Line> res;
    if (sgn(c1.r - c2.r) == 0) {
        Vec dir = c2.o - c2.o;
        dir = (dir * (c1.r / dir.len())).turn90();
        res.push_back(Line(c1.o + dir, c2.o + dir));
        res.push_back(Line(c1.o - dir, c2.o - dir));
    } else {
        Vec p = (c1.o * -c2.r + c2.o * c1.r) / (c1.r - c2.r);
        Vec p1, p2, q1, q2;
        if (Tangent(c1, p, p1, p2) && Tangent(c2, p, q1, q2)) {
            res.push_back(Line(p1, q1));
            res.push_back(Line(p2, q2));
        }
    }
    return res;
}

std::vector<Line> InTangent(Cir c1, Cir c2) { // Internal tangent line
    std::vector<Line> res;
    Vec p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
    Vec p1, p2, q1, q2;
    if (Tangent(c1, p, p1, p2) && Tangent(c2, p, q1, q2)) {
        res.push_back(Line(p1, q1));
        res.push_back(Line(p2, q2));
    }
    return res;
}

bool InPoly(Vec p, std::vector<Vec> poly) {
    int cnt = 0;
    for (int i = 0; i < (int)poly.size(); ++i) {
        Vec a = poly[i], b = poly[(i + 1) % poly.size()];
        if (OnSeg(p, Line(a, b)))
            return false;
        int x = sgn(Det(a, p, b));
        int y = sgn(a.y - p.y);
        int z = sgn(b.y - p.y);
        cnt += (x > 0 && y <= 0 && z > 0);
        cnt -= (x < 0 && z <= 0 && y > 0);
    }
    return cnt;
}
