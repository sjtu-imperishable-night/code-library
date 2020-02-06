#include <bits/stdc++.h>

const int MAXL = 1e5 + 5;

namespace GSAM {
    struct Node *pool_pointer;
    struct Node {
        Node *to[26], *parent;
        int step;
        
        Node(int STEP = 0): step(STEP) {
            memset(to, 0, sizeof to);
            parent = 0;
        }
        
        void *operator new (size_t) {
            return pool_pointer++;   
        }
    } pool[MAXL << 1], *root;
    
    void init() {
        pool_pointer = pool;
        root = new Node();
    }
    
    Node *Extend(Node *np, char ch) {
        static Node *last, *q, *nq;
        
        int x = ch - 'a';
        
        if (np->to[x]) {
            last = np;
            q = last->to[x];
            if (q->step == last->step + 1) np = q;
            else {
                nq = new Node(last->step + 1);
                memcpy(nq->to, q->to, sizeof q->to);
                nq->parent = q->parent;
                q->parent = np->parent = nq;
                for (; last && last->to[x] == q; last = last->parent)
                    last->to[x] = nq;
                
                np = nq;
            }
        } else {
            last = np; np = new Node(last->step + 1);
            for (; last && !last->to[x]; last = last->parent)
                last->to[x] = np;
            if (!last) np->parent = last;
            else {
                q = last->to[x];
                if (q->step == last->step + 1) np->parent = q;
                else {
                    nq = new Node(last->step + 1);
                    memcpy(nq->to, q->to, sizeof q->to);
                    nq->parent = q->parent;
                    q->parent = np->parent = nq;
                    for (; last && last->to[x] == q; last = last->parent)
                        last->to[x] = nq;
                }
            }
        }
        
        return np;
    }
}

int main() {
    
    
    return 0;
}
