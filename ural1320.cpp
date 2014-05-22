#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int N=1024;
int c[N],fa[N];

int find(int x){
	if(x!=fa[x]){
		fa[x]=find(fa[x]);
	}
	return fa[x];
}

int main(){
	freopen("in","r",stdin);
	int a,b;
	for(int i=1;i<=N;i++)
		fa[i]=i,c[i]=0;
	while(scanf("%d %d",&a,&b)==2){
		int fx=find(a);
		int fy=find(b);
		if(fx!=fy){
			fa[fy]=fx;
			c[fx]+=c[fy];
		}
		c[fx]++;
	}
	for(int i=1;i<=N;i++)
		if(fa[i]==i&&(c[i]&1)){
			printf("0\n");
			return 0;
		}
	printf("1\n");
	return 0;
}
