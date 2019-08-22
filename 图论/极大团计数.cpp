#include<cstdio>  
#include<cstring>  
using namespace std;  
const int N=130;  
int ans,a[N][N],R[N][N],P[N][N],X[N][N];
bool Bron_Kerbosch(int d,int nr,int np,int nx)
{  
    int i,j;  
    if(np==0&&nx==0)
    {  
        ans++;  
        if(ans>1000)//ÏÞÖÆ 
            return 1;  
        return 0;
    }  
    int u,max=0;  
    u=P[d][1];  
    for(i=1;i<=np;i++)  
    {  
        int cnt=0;  
        for(j=1;j<=np;j++)  
        {  
            if(a[P[d][i]][P[d][j]])  
                cnt++;  
        }  
        if(cnt>max)  
        {  
            max=cnt;  
            u=P[d][i];  
        }  
    }  
    for(i=1;i<=np;i++)  
    {  
        int v=P[d][i];  
        if(a[v][u]) continue;  
        for(j=1;j<=nr;j++)  
            R[d+1][j]=R[d][j];  
        R[d+1][nr+1]=v;  
        int cnt1=0;  
        for(j=1;j<=np;j++)  
            if(P[d][j]&&a[P[d][j]][v])  
                P[d+1][++cnt1]=P[d][j];  
        int cnt2=0;  
        for(j=1;j<=nx;j++)  
            if(a[X[d][j]][v])  
                X[d+1][++cnt2]=X[d][j];  
        if(Bron_Kerbosch(d+1,nr+1,cnt1,cnt2))  
            return 1;  
        P[d][i]=0;  
        X[d][++nx]=v;  
    }  
    return 0;  
}  
int main()  
{  
    int n,i,m,x,y;  
    while(scanf("%d%d",&n,&m)!=EOF)  
    {  
        memset(a,0,sizeof(a));  
        while(m--)  
        {  
            scanf("%d%d",&x,&y);  
            a[x][y]=a[y][x]=1;  
        }  
        ans=0;  
        for(i=1;i<=n;i++)  
            P[1][i]=i;  
        Bron_Kerbosch(1,0,n,0);  
        if(ans>1000)  
            printf("Too many maximal sets of friends.\n");  
        else  
            printf("%d\n",ans);
    }  
    return 0;  
}  

