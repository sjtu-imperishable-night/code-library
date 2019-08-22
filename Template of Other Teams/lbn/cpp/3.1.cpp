LL cal(int L,int R){//一段字符串的HASH值
	return (V[R]-V[L-1]*pw[R-L+1]%M+M)%M;
}
scanf(“%s”,s+1);n=strlen(s+1);
for(pw[0]=i=1;i<=n;i++)pw[i]=pw[i-1]*S%M;
for(i=1;i<=n;i++)V[i]=(V[i-1]*S+s[i]-'a'+1)%M;
scanf(“%d%d%d%d”,&L1,&R1,&L2,&R2);
puts(cal(L1,R1)==cal(L2,R2)?“YES”:”NO”);
