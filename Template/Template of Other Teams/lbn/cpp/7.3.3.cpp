#include<bits/stdc++.h>//带权费马点
using namespace std;int n;double ansx,ansy;
struct data{double x,y;int w;}p[10005];
double sqr(double x){return x*x;}
double dis(double x,double y,data p){return sqrt(sqr(x-p.x)+sqr(y-p.y));}
void hillclimb(){
     double t=1000,x,y;
     for(int i=1;i<=n;i++)ansx+=p[i].x*p[i].w,ansy+=p[i].y*p[i].w;
     ansx/=n;ansy/=n;
     while(t>0.00000001){
         x=y=0;
         for(int i=1;i<=n;i++){
             x+=(p[i].x-ansx)*p[i].w/dis(ansx,ansy,p[i]);
             y+=(p[i].y-ansy)*p[i].w/dis(ansx,ansy,p[i]);
         }
         ansx+=x*t;ansy+=y*t;
         if(t>1)t*=0.5;else t*=0.97;//一开始爬得快，最后爬得慢
     }
     printf("%.3lf %.3lf",ansx,ansy);
}
int main(){
     scanf("%d",&n);for(int i=1;i<=n;i++)scanf("%lf%lf%d",&p[i].x,&p[i].y,&p[i].w);
     hillclimb();
}
