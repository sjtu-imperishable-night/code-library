Vec ExCenter(Vec a, Vec b, Vec c) {
    if (a == b) return (a + c) / 2;
    if (a == c) return (a + b) / 2;
    if (b == c) return (a + b) / 2;
    Vec m1 = (a + b) / 2;
    Vec m2 = (b + c) / 2;
    return Insersect(Line(m1, m1 + (b - a).turn90()), Line(m2, m2 + (c - b).turn90()));
}

Cir Solve(std::vector<Vec> p) {
    std::random_shuffle(p.begin(), p.end());
    Vec o = p[0];
    double r = 0;
    for (int i = 1; i < (int)p.size(); ++i) {
        if (sgn((p[i] - o).len() - r) <= 0) continue;
        o = (p[0] + p[i]) / 2;
        r = (o - p[i]).len();
        for (int j = 0; j < i; ++j) {
            if (sgn((p[j] - o).len() - r) <= 0) continue;
            o = (p[i] + p[j]) / 2;
            r = (o - p[i]).len();
            for (int k = 0; k < j; ++k) {
                if (sgn((p[k] - o).len() - r) <= 0) continue;
                o = ExCenter(p[i], p[j], p[k]);
                r = (o - p[i]).len();
            }
        }
    }
    return Cir(o, r);
}
