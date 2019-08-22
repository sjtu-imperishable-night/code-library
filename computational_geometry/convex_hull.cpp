std::vector<Vec> ConvexHull(std::vector<Vec> p) {
    std::sort(p.begin(), p.end());
    std::vector<Vec> ans, S;
    for (int i = 0; i < (int)p.size(); ++i) {
        while (S.size() >= 2 && sgn(Det(S[S.size() - 2], S.back(), p[i])) <= 0)
            S.pop_back();
        S.push_back(p[i]);
    }
    ans = S;
    S.clear();
    for (int i = p.size() - 1; i >= 0; --i) {
        while (S.size() >= 2 && sgn(Det(S[S.size() - 2], S.back(), p[i])) <= 0)
            S.pop_back();
        S.push_back(p[i]);
    }
    for (int i = 1; i + 1 < (int)S.size(); ++i)
        ans.push_back(S[i]);
    return ans;
}
