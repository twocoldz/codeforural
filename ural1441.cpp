#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define inf 0x3f3f3f3f
using namespace std;
const int N=20000+10;
struct node{
	int v,nxt;
}edge[N<<2];
int head[N];
bool vis[N<<2],dfn[N];
int deg[N];
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

bool Dfs(int u,int fa){
	
	for(int i=head[u];~i;i=edge[i].nxt){
		if(!vis[i>>1]){
			vis[i>>1]=1;
			int v=edge[i].v;
			Dfs(v,u);
		}
	}
	if(u==0){
		printf("\n");
	}
	else
		printf("%d ",u);
	return false;
}

void Dfs1(int u,int fa){
	//vis[u]=1;
	
	for(int i=head[u];~i;i=edge[i].nxt){
		if(!vis[i>>1]){
			vis[i>>1]=1;
			int v=edge[i].v;
			Dfs1(v,u);
		}
	}
	printf("%d ",u);
	//vis[u]=0;
}

	
int main(){
	while(scanf("%d %d",&n,&m)==2){
		Init();
		int a,b,ans=0;
		memset(vis,0,sizeof(vis));
		memset(dfn,0,sizeof(dfn));
		memset(deg,0,sizeof(deg));
		for(int i=0;i<m;i++){
			scanf("%d %d",&a,&b);
			deg[a]++;
			deg[b]++;
			AddEdge(a,b);
			AddEdge(b,a);
		}
		for(int i=1;i<=n;i++){
			if(deg[i]&1){
				ans++;
			}
		}
		if(ans==0){
			printf("1\n");
			Dfs1(1,-1);
			printf("\n");
			continue;
		}
		printf("%d",ans/2);
		for(int i=1;i<=n;i++){
			if(deg[i]&1){
				AddEdge(0,i);
				AddEdge(i,0);
			}
		}
		Dfs(0,-1);
	}
	return 0;
}
