#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;
const int N=1<<16;
struct node{
	int v,nxt;
}edge[N*10];
int head[N];
bool vis[N];
int dis[2][N];
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

void Dfs(int u,int fa,int d,int *dis){
	dis[u]=d;
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v!=fa&&dis[v]>dis[u]+1){
			Dfs(v,u,d+1,dis);
		}
	}
	return ;
}

int main(){
	freopen("in","r",stdin);
	while(scanf("%d",&n)==1){
		Init();
		int x,pre,now;
		memset(vis,0,sizeof(vis));
		for(int i=0;i<n;i++){
			scanf("%d %d",&x,&pre);
			x--;
			vis[pre]=1;
			while(x--){
				scanf("%d",&now);
				AddEdge(pre,now);
				AddEdge(now,pre);
				pre=now;
				vis[pre]=1;
			}
		}
		int fir;
		scanf("%d",&x);
		now=pre=-1;
		while(x--){
			pre=now;
			scanf("%d",&now);
			if(pre==-1)
				fir=now;
		}
		memset(dis,0x3f,sizeof(dis));
		Dfs(fir,-1,0,dis[0]);
		Dfs(now,pre,0,dis[1]);
		for(int i=1;i<=32767;i++){
			if(vis[i]&&dis[1][i]+dis[0][now]==dis[0][i])
				printf("%d\n",i);
		}
	}
	return 0;
}	

