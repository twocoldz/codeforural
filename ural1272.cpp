#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=10240;
const int M=N*3;
struct node{
	int a,b,w;
	bool operator <(const node& x)const{
		return w<x.w;
	}
}e[M];
int fa[N];
int n,m,k;

int find(int x){
	if(x!=fa[x]){
		fa[x]=find(fa[x]);
	}
	return fa[x];
}

int main(){
	while(scanf("%d %d %d",&n,&m,&k)==3){
		for(int i=1;i<=n;i++)
			fa[i]=i;
		for(int i=0;i<m;i++)
			scanf("%d %d",&e[i].a,&e[i].b),e[i].w=0;
		for(int i=m;i<m+k;i++)
			scanf("%d %d",&e[i].a,&e[i].b),e[i].w=1;
		k=0;
		int num=1,ans=0;
		while(num<n){
			int fx=find(e[k].a);
			int fy=find(e[k].b);
			if(fx!=fy){
				fa[fx]=fy;
				ans+=e[k].w;
				num++;
			}
			k++;
		}
		printf("%d\n",ans);
	}
	return 0;
}

