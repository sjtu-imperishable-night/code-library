#include<bits/stdc++.h>
#define N 30030
#define M 10007
using namespace std;bool v[N],in[N];char s[9];
int Q,n,i,x,y,o,k,f,b,F[N],sf[N],c[N][2];
struct P{int k,b;}V[N],S[N],v1,v2;
P operator+(P a,P b){return P{a.k*b.k%M,(b.k*a.b+b.b)%M};}
int pow(int a,int b,int p){int v=1;for(a%=p;b;a=a*a%p,b>>=1)if(b&1)v=v*a%p;return v;}
void dfs(int x){v[x]=in[x]=1;int y=F[x];if(in[y])F[x]=0,sf[x]=y;if(!v[y])dfs(y);in[x]=0;}
bool ir(int x){return c[F[x]][0]!=x&&c[F[x]][1]!=x;}
void ps(int x){S[x]=S[c[x][0]]+V[x]+S[c[x][1]];}
void R(int x){
    int y=F[x],k=c[y][0]==x;F[c[y][!k]=c[x][k]]=y;F[x]=F[y];
    if(!ir(y))c[F[y]][c[F[y]][1]==y]=x;F[c[x][k]=y]=x;ps(y);
}
void sy(int x){for(;!ir(x);R(x))if(!ir(F[x]))R(c[F[x]][0]==x^c[F[F[x]]][0]==F[x]?x:F[x]);ps(x);}
void acs(int x){for(o=0;x;c[x][1]=o,ps(x),o=x,x=F[x])sy(x);}
void lk(int x,int y){acs(x);sy(x);F[x]=y;}void ct(int x){acs(x);sy(x);F[c[x][0]]=0;c[x][0]=0;ps(x);}
int gf(int x){acs(x);sy(x);for(;c[x][0];x=c[x][0]);return x;}
int oc(int x,int y){int f=sf[y];if(f==x)return 1;acs(f);sy(f);sy(x);return !ir(f);}
int qu(int x){
    acs(x);sy(x);v1=S[x];y=gf(x);f=sf[y];acs(f);sy(f);v2=S[f];
    return v2.k==1?v2.b?-1:-2:v2.k==0?(v1.k*v2.b+v1.b)%M:(v1.k*(M-v2.b)%M*pow(v2.k-1+M,M-2,M)+v1.b)%M;
}
int main(){
    for(S[0].k=V[0].k=1,scanf("%d",&n),i=1;i<=n;i++)scanf("%d%d%d",&x,&F[i],&y),V[i]=S[i]=P{x,y};
    for(i=1;i<=n;i++)if(!v[i])dfs(i);
    for(scanf("%d",&Q);Q--;){
        scanf("%s%d",s,&x);
        if(s[0]=='A')printf("%d\n",qu(x));else{
            scanf("%d%d%d",&k,&f,&b);
            acs(x);sy(x);V[x]=P{k,b};ps(x);y=gf(x);
            if(x==y)if(gf(f)==y)sf[x]=f;else sf[x]=0,lk(x,f);else{
                if(oc(x,y))ct(x),lk(y,sf[y]),sf[y]=0;else ct(x);
                if(gf(f)==x)sf[x]=f;else lk(x,f);
            }
        }
    }
}
