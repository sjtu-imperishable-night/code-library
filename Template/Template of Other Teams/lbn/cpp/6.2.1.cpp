#define D double
#define eps 1e-8
#define pi acos(-1)
using namespace std;
int sgn(D x){return x<-eps?-1:x>eps;}//x>0-->1 x=0-->0 x<0-->-1
int cmp(D x,D y){return sgn(x-y);}//x>y-->1 x=0-->0 x<y-->-1
D sqr(D x){return x*x;}
