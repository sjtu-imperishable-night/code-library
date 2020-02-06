srand(time(0));
for(i=1;i<=n;i++)b[i]=i;
random_shuffle(b+1,b+n+1);
for(i=2;i<=n;i++)swap(b[i],b[rand()%(i-1)+1]);
