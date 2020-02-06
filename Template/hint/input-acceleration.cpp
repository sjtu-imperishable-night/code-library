namespace Scanner {
    const int L = (1 << 15) + 5;
    char buffer[L], *S, *T;
    
    __advance __inline char GetChar() {
        if (S == T) {
            T = (S = buffer) + fread(buffer, 1, L, stdin);
            if (S == T)
                return -1;
        }
        return *S++;
    }
    
    template <class Type>
    __advance __inline void Scan(Type &x) {
        register char ch; x = 0;
        for (ch = GetChar(); ~ch && (ch < '0' || ch > '9'); ch = GetChar());
        for (; ch >= '0' && ch <= '9'; ch = GetChar()) x = x * 10 + ch - '0';
    }
} using Scanner::Scan;
