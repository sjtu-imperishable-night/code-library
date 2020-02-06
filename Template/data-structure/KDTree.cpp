namespace KDTree {
    struct Vec {
        int d[2];
        
        Vec() = default;
        Vec(int x, int y) {
            d[0] = x; d[1] = y;
        }
        
        bool operator == (const Vec &oth) const {
            for (int i = 0; i < 2; ++i)
                if (d[i] != oth.d[i]) return false;
            return true;
        }
    };
    
    struct Rec {
        int mn[2], mx[2];
        
        Rec() = default;
        Rec(const Vec &p) {
            for (int i = 0; i < 2; ++i)
                mn[i] = mx[i] = p.d[i];
        }
        
        static Rec Merge(const Rec &a, const Rec &b) {
            Rec res;
            for (int i = 0; i < 2; ++i) {
                res.mn[i] = std::min(a.mn[i], b.mn[i]);
                res.mx[i] = std::max(a.mx[i], b.mx[i]);
            }
            return res;
        }
        
        static bool In(const Rec &a, const Rec &b) { // a in b
            for (int i = 0; i < 2; ++i)
                if (a.mn[i] < b.mn[i] || a.mx[i] > b.mx[i]) return false;
            return true;
        }
        
        static bool Out(const Rec &a, const Rec &b) {
            for (int i = 0; i < 2; ++i)
                if (a.mx[i] < b.mn[i] || a.mn[i] > b.mx[i]) return true;
            return false;
        }
    };
    
    struct Node *pool_pointer;
    struct Node {
        Node *ch[2];
        Vec p;
        Rec rec;
        int sum, val;
        int size;
        
        Node() = default;
        Node(const Vec &_p, int _v): p(_p), rec(_p), sum(_v), val(_v) {
            ch[0] = ch[1] = 0;
            size = 1;
        }
        
        bool Bad() {
            const double alpha = 0.75;
            
            for (int i = 0; i < 2; ++i)
                if (ch[i] && ch[i]->size > size * alpha) return true;
            return false;
        }
        
        void Update() {
            sum = val;
            size = 1;
            rec = Rec(p);
            for (int i = 0; i < 2; ++i) if (ch[i]) {
                sum += ch[i]->sum;
                size += ch[i]->size;
                rec = Rec::Merge(rec, ch[i]->rec);
            }
        }
        
        void *operator new (size_t) {
            return pool_pointer++;
        }
    } pool[MAXN], *root;
    
    Node *null = 0;
    
    std::pair<Node *&, int> Insert(Node *&k, const Vec &p, int val, int dim) {
        if (!k) {
            k = new Node(p, val);
            return std::pair<Node *&, int>(null, -1);
        }
        if (k->p == p) {
            k->sum += val;
            k->val += val;
            return std::pair<Node *&, int>(null, -1);
        }
        std::pair<Node *&, int> res = Insert(k->ch[p.d[dim] >= k->p.d[dim]], p, val, dim ^ 1);
        k->Update();
        if (k->Bad()) return std::pair<Node *&, int>(k, dim);
        return res;
    }
    
    Node *nodes[MAXN];
    int node_cnt;
    
    void Traverse(Node *k) {
        if (!k) return;
        Traverse(k->ch[0]);
        nodes[++node_cnt] = k;
        Traverse(k->ch[1]);
    }
    
    int _dim;
    
    bool cmp(Node *a, Node *b) {
        return a->p.d[_dim] < b->p.d[_dim];
    }
    
    void Build(Node *&k, int l, int r, int dim) {
        if (l > r) return;
        int mid = (l + r) >> 1;
        _dim = dim;
        std::nth_element(nodes + l, nodes + mid, nodes + r + 1, cmp);
        
        k = nodes[mid]; k->ch[0] = k->ch[1] = 0;
        Build(k->ch[0], l, mid - 1, dim ^ 1);
        Build(k->ch[1], mid + 1, r, dim ^ 1);
        k->Update();
    }
    
    void Rebuild(Node *&k, int dim) {
        node_cnt = 0;
        Traverse(k);
        Build(k, 1, node_cnt, dim);
    }
    
    int Query(Node *k, const Rec &rec) {
        if (!k) return 0;
        if (Rec::Out(k->rec, rec)) return 0;
        if (Rec::In(k->rec, rec)) return k->sum;
        int res = 0;
        if (Rec::In(k->p, rec)) res += k->val;
        for (int i = 0; i < 2; ++i)
            res += Query(k->ch[i], rec);
        return res;
    }
    
    // --------
    
    void Init() {
        pool_pointer = pool;
        root = 0;
    }
    
    void Insert(int x, int y, int val) {
        std::pair<Node *&, int> p = Insert(root, Vec(x, y), val, 0);
        if (p.first != null) Rebuild(p.first, p.second);
    }
    
    int Query(int x1, int y1, int x2, int y2) {
        Rec rec = Rec::Merge(Vec(x1, y1), Vec(x2, y2));
        return Query(root, rec);
    }
}
