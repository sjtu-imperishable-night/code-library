//Tsinsen A1280 最长双回文串 
#include<iostream>
#include<cstring>
using namespace std;

const int maxn = 100005;// n(空间复杂度o(n*ALP)),实际开n即可
const int ALP = 26;

struct PAM{ // 每个节点代表一个回文串
int next[maxn][ALP]; // next指针,参照Trie树
int fail[maxn]; // fail失配后缀链接
int cnt[maxn]; // 此回文串出现个数
int num[maxn];
int len[maxn]; // 回文串长度
int s[maxn]; // 存放添加的字符
int last; //指向上一个字符所在的节点，方便下一次add
int n; // 已添加字符个数
int p; // 节点个数

int newnode(int w)
{// 初始化节点，w=长度
	for(int i=0;i<ALP;i++)
	next[p][i] = 0;
	cnt[p] = 0;
	num[p] = 0;
	len[p] = w;
	return p++;
}
void init()
{
p = 0;
newnode(0);
newnode(-1);
last = 0;
n = 0;
s[n] = -1; // 开头放一个字符集中没有的字符，减少特判
fail[0] = 1;
}
int get_fail(int x)
{ // 和KMP一样，失配后找一个尽量最长的
while(s[n-len[x]-1] != s[n]) x = fail[x];
return x;
}
int add(int c)
{
c -= 'a';
s[++n] = c;
int cur = get_fail(last);
if(!next[cur][c])
{
int now = newnode(len[cur]+2);
fail[now] = next[get_fail(fail[cur])][c];
next[cur][c] = now;
num[now] = num[fail[now]] + 1;
}
last = next[cur][c];
cnt[last]++;
return len[last];
}
void count()
{
// 最后统计一遍每个节点出现个数
// 父亲累加儿子的cnt,类似SAM中parent树
// 满足parent拓扑关系
for(int i=p-1;i>=0;i--)
cnt[fail[i]] += cnt[i];
}
}pam;
char S[101010];
int l[101010],r[101010];
int main()
{
cin>>S;
int len=strlen(S);
pam.init();
for(int i=0;i<len;i++)
l[i]=pam.add(S[i]);
pam.init();
for(int i=len-1;i>=0;i--)
r[i]=pam.add(S[i]);
pam.init();
int ans=0;
for(int i=0;i<len-1;i++)
ans=max(ans,l[i]+r[i+1]);
cout<<ans<<endl;
return 0;
}