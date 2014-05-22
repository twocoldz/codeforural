#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define inf 0x3f3f3f3f
using namespace std;
const int N=128;
struct node{
	int v,nxt,f;
}edge[N*N*4];
int head[N*2];
int dis[N*2];
bool inq[N*2];
int n,m,e;

void Init(){
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,int f){
	edge[e].v=v;
	edge[e].f=f;
	edge[e].nxt=head[u];
	head[u]=e++;
}

bool Bfs(int s,int t){
	queue<int> q;
	memset(dis,-1,sizeof(dis));
	memset(inq,0,sizeof(inq));
	dis[s]=0;
	inq[s]=1;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		//printf("u=%d\n",u);
		q.pop();
		inq[u]=0;
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].v;
			if(edge[i].f>0&&dis[v]==-1){
				dis[v]=dis[u]+1;
				if(v==t)
					return true;
				if(!inq[v]){
					q.push(v);
					inq[v]=1;
				}
			}
		}
	}
	return false;
}

int Dfs(int s,int t,int limit){
	if(s==t)
		return limit;
	int cost=0;
	for(int i=head[s];~i;i=edge[i].nxt){
		int v=edge[i].v;
		if(dis[s]+1==dis[v]&&edge[i].f>0){
			int tmp=Dfs(v,t,min(edge[i].f,limit-cost));
			if(tmp){
				cost+=tmp;
				edge[i].f-=tmp;
				edge[i^1].f+=tmp;
			}
			if(cost==limit)
				break;
		}
	}
	if(cost==0)
		dis[s]=-1;
	return cost;
}

int Dinic(int s,int t){
	int ans=0;
	while(Bfs(s,t)){
		ans+=Dfs(s,t,inf);
	}
	return ans;
}

int main(){
	freopen("in","r",stdin);
	int tot;
	while(scanf("%d",&tot)==1){
		Init();
		int n,m,s,t,w,a,b;
		scanf("%d %d %d %d",&n,&m,&s,&t);
		for(int i=1;i<=n;i++){
			scanf("%d",&w);
			AddEdge(i,i+n,w);
			AddEdge(i+n,i,0);
		}
		for(int i=1;i<=m;i++){
			scanf("%d %d",&a,&b);
			AddEdge(a+n,b,inf);
			AddEdge(b,a+n,0);
			AddEdge(b+n,a,inf);
			AddEdge(a,b+n,0);
		}
		if(s==t){
			printf("NO\n");
			continue;
		}
		int ans=Dinic(s+n,t);
		//printf("%d\n",ans);
		printf("%s\n",ans<=tot?"YES":"NO");
	}
	return 0;
}
