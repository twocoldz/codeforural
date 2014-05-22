#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>

#define inf 0x3f3f3f3f
using namespace std;
const int N=50005;
struct node{
	int u,v,nxt;
}edge[N],qedge[N*2];
int head[N], qhead[N];
int fa[N];
int n,m,e;
int b[N],ans[N];
bool vis[N];

void Init(){
	e=0;
	memset(vis,0,sizeof(vis));
	memset(head,-1,sizeof(head));
	memset(qhead,-1,sizeof(qhead));
	for(int i=1;i<=n;i++)
		fa[i]=i;
}

void AddEdge(int u,int v){
	edge[e].u=u;
	edge[e].v=v;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void AddQuery(int u,int v){
	qedge[e].u=u;
	qedge[e].v=v;
	qedge[e].nxt=qhead[u];
	qhead[u]=e++;
}

int find(int x){
	if(x!=fa[x]){
		fa[x]=find(fa[x]);
	}
	return fa[x];
}

void tarjan(int u){
	vis[u]=1;
	for(int i=qhead[u];~i;i=qedge[i].nxt){
		int v=qedge[i].v;
		if(vis[v]){
			ans[i>>1]=find(v);
		}
	}
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].v;
		tarjan(v);
		fa[v]=u;
	}
}

int main(){
	int a,x,y,root;
	while(scanf("%d",&n)==1){
		Init();
		map<int,int> id;
		for(int i=1;i<=n;i++){
			scanf("%d %d",&a,b+i);
			id[a]=i;
		}
		//printf("read over\n");
		for(int i=1;i<=n;i++){
			if(b[i]==-1)
				root=i;
			else{
				b[i]=id[b[i]];
				AddEdge(b[i],i);
			}
		}
		int Q;
		scanf("%d",&Q);
		//printf("%d\n",Q);
		e=0;
		for(int i=0;i<Q;i++){
			scanf("%d %d",&x,&y);
			x=id[x];
			y=id[y];
			AddQuery(x,y);
			AddQuery(y,x);
		}
		//printf("read over\n");
		tarjan(root);
		for(int i=0;i<Q;i++){
			if(ans[i]==qedge[i<<1].u)
				printf("1\n");
			else if(ans[i]==qedge[i<<1].v)
				printf("2\n");
			else
				printf("0\n");
		}
	}
	return 0;
}
