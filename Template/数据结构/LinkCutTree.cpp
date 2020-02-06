namespace LinkCutTree {
	struct Node {
		Node *ch[2], *fa;
		int sz; bool rev;
		Node() {
			ch[0] = ch[1] = fa = NULL;
			sz = 1; rev = 0;
		}
		
		void reverse() { if (this) rev ^= 1; }
		
		void down() {
			if (rev) {
				std::swap(ch[0], ch[1]);
				for (int i = 0; i < 2; i++) ch[i]->reverse();
				rev = 0;
			}
		}
		
		int size() { return this ? sz : 0; }
		
		void update() {
			sz = 1 + ch[0]->size() + ch[1]->size();
		}
		
		int which() {
			if (!fa || (this != fa->ch[0] && this != fa->ch[1])) return -1;
			return this == fa->ch[1];
		}
	} *pos[100005];
	
	void rotate(Node *k) {
		Node *p = k->fa;
		int l = k->which(), r = l ^ 1;
		k->fa = p->fa;
		if (p->which() != -1) p->fa->ch[p->which()] = k;
		p->ch[l] = k->ch[r];
		if (k->ch[r]) k->ch[r]->fa = p;
		k->ch[r] = p; p->fa = k;
		p->update(); k->update();
	}
	
	void splay(Node *k) {
		static stack<Node *> stk;
		Node *p = k;
		while (true) {
			stk.push(p);
			if (p->which() == -1) break;
			p = p->fa;
		}
		while (!stk.empty()) {
			stk.top()->down(); stk.pop();
		}
		
		while (k->which() != -1) {
			p = k->fa;
			if (p->which() != -1) {
				if (p->which() ^ k->which()) rotate(k);
				else rotate(p);
			}
			rotate(k);
		}
	}
	
	void access(Node *k) {
		Node *p = NULL;
		while (k) {
			splay(k);
			k->ch[1] = p;
			(p = k)->update();
			k = k->fa;
		}
	}
	
	void evert(Node *k) {
		access(k);
		splay(k);
		k->reverse();
	}
	
	Node *get_root(Node *k) {
		access(k);
		splay(k);
		while (k->ch[0]) k = k->ch[0];
		return k;
	}
	
	void link(Node *u, Node *v) {
		evert(u);
		u->fa = v;
	}
	
	void cut(Node *u, Node *v) {
		evert(u);
		access(v);
		splay(v);
//		if (v->ch[0] != u) return;
		v->ch[0] = u->fa = NULL;
		v->update();
	}
}
