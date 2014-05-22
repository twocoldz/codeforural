#include <cstdio>
#include <cstring>
using namespace std;
const int N=1024;
struct node{
	int v,nxt;
}edge[N<<2];
int head[N],x[N],y[N];
int n,m,e;

void Init(){
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v){
	edge[e].v=v;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void dfs(int u,int dep,int fa){
	x[u]=dep,y[u]=m;
	m+=2;
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v!=fa){
			dfs(v,dep+2,u);
		}
	}
}

int main(){
	while(scanf("%d",&n)==1){
		m=-1000;
		Init();
		int a,b;
		for(int i=0;i<n-1;i++){
			scanf("%d %d",&a,&b);
			AddEdge(a,b);
			AddEdge(b,a);
		}
		dfs(1,m,-1);
		for(int i=1;i<=n;i++)
			printf("%d %d\n",x[i],y[i]);
	}
	return 0;
}
