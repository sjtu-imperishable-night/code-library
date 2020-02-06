bool HalfPlaneIntersect(std::vector<Line> L, std::vector<Vec> &ch) {
	std::sort(L.begin(), L.end());
	int head = 0, tail = 0;
	Vec *p = new Vec[L.size()];
	Line *q = new Line[L.size()];
	q[0] = L[0];
	for (int i = 1; i < (int)L.size(); i++) {
		while (head < tail && Dir(p[tail - 1], L[i]) != 1) tail--;
		while (head < tail && Dir(p[head], L[i]) != 1) head++;
		q[++tail] = L[i];
		if (!sgn(Cross(q[tail].b - q[tail].a, q[tail - 1].b - q[tail - 1].a))) {
			tail--;
			if (Dir(L[i].a, q[tail]) == 1) q[tail] = L[i];
		}
		if (head < tail) p[tail - 1] = Intersect(q[tail - 1], q[tail]);
	}
	while (head < tail && Dir(p[tail - 1], q[head]) != 1) tail--;
	if (tail - head <= 1) return false;
	p[tail] = Intersect(q[head], q[tail]);
	for (int i = head; i <= tail; i++) ch.push_back(p[i]);
	delete[] p; delete[] q;
	return true;
}
