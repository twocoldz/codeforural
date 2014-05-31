#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cassert>

#define inf 0x3f3f3f3f
using namespace std;
const int N=256;
struct node{
	int v,nxt,f;
}edge[N*N*2];
int head[N];
int n,m,e;
int dis[N];

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
	memset(dis,-1,sizeof(dis));
	dis[s]=0;
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].v;
			if(edge[i].f>0&&dis[v]==-1){
				dis[v]=dis[u]+1;
				if(v==t)
					return true;
				q.push(v);
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
			int tmp=Dfs(v,t,min(limit-cost,edge[i].f));
			if(tmp){
				cost+=tmp;
				edge[i].f-=tmp;
				edge[i^1].f+=tmp;
			}
			if(limit==cost)
				break;
		}
	}
	if(cost==0)
		dis[s]=-1;
	return cost;
}

int  Dinic(int s,int t){
	int ans=0;
	while(Bfs(s,t))
		ans+=Dfs(s,t,inf);
	return ans;
}
int a[N],b[N];

int main(){
	while(scanf("%d",&n)==1){
		int flag=1;
		int suma=0,sumb=0;
		for(int i=1;i<=n;i++){
			scanf("%d",a+i);
			if(a[i]>n*100)
				flag=0;
			suma+=a[i];
		}
		for(int i=1;i<=n;i++){
			scanf("%d",b+i);
			if(b[i]>n*100)
				flag=0;
			sumb+=b[i];
		}
		if(flag==0){
			printf("NO\n");
			continue;
		}
		assert(suma==sumb);
		Init();
		int s=0,t=n+n+1;
		for(int i=1;i<=n;i++){
			AddEdge(s,i,a[i]);
			AddEdge(i,s,0);
			AddEdge(i+n,t,b[i]);
			AddEdge(t,i+n,0);
			for(int j=n;j>=1;j--){
				AddEdge(i,j+n,100);
				AddEdge(j+n,i,0);
			}
		}
		int ans=Dinic(s,t);
		if(ans==suma){
			printf("YES\n");
			for(int i=1;i<=n;i++){
				for(int j=head[i];~j&&edge[j].v!=0;j=edge[j].nxt){
					printf("%d ",100-edge[j].f);
				}
				printf("\n");
			}
		}
		else
			printf("NO\n");
	}
	return 0;
}
