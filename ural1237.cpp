#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#define inf 0x3f3f3f3f
using namespace std;
const int N=205;
struct node{
	int v,nxt,f,w;
}edge[N*N+N];
int head[N];
int dis[N];
bool inq[N],vis[N];
int a[N][N];
int d[N][N];
int n,m,e;

void Init(){
	e=0;
	memset(vis,0,sizeof(vis));
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,int f,int w){
	edge[e].v=v;
	edge[e].f=f;
	edge[e].w=w;
	edge[e].nxt=head[u];
	head[u]=e++;
}

bool Spfa(int s,int t){
	memset(dis,inf,sizeof(dis));
	memset(inq,0,sizeof(inq));
	dis[s]=0;
	inq[s]=1;
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].v;
			if(edge[i].f>0&&dis[v]>dis[u]+edge[i].w){
				dis[v]=edge[i].w+dis[u];
				if(!inq[v]){
					q.push(v);
					inq[v]=1;
				}
			}
		}
	}
	//printf("dis[t]=%d\n",dis[t]);
	return dis[t]!=inf;
}

int Dfs(int s,int t,int limit,int dep,int fa){
	if(s==t)
		return limit;
	int cost=0;
	vis[s]=1;
	//printf("s=%d t=%d dep=%d\n",s,t,dep);
	//getchar();
	for(int i=head[s];~i;i=edge[i].nxt){
		int v=edge[i].v;
		if(vis[v])
			continue;
		if(dis[s]+edge[i].w==dis[v]&&edge[i].f>0){
			int tmp=Dfs(v,t,min(limit-cost,edge[i].f),dep+1,s);
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
		dis[s]=inf;
	vis[s]=0;
	return cost;
}

int Dinic(int s,int t){
	int ans=0;
	while(Spfa(s,t)){
		int tmp=Dfs(s,t,inf,0,-1);
		//printf("num=%d\n",tmp);
		ans+=tmp*dis[t];
	}
	return ans;
}
int ax[N],ay[N],bx[N],by[N];
int B[N],C[N];

int main(){
	while(scanf("%d %d",&n,&m)!=EOF){
		Init();
		for(int i=1;i<=n;i++){
			scanf("%d %d %d",ax+i,ay+i,B+i);
		}
		for(int i=1;i<=m;i++){
			scanf("%d %d %d",bx+i,by+i,C+i);
		}
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				d[i][j]=abs(ax[i]-bx[j])+abs(ay[i]-by[j])+1;
			}
		}
		int s=0,t=1+n+m;
		for(int i=1;i<=n;i++){
			AddEdge(s,i,B[i],0);
			AddEdge(i,s,0,0);
			for(int j=1;j<=m;j++){
				AddEdge(i,j+n,B[i],d[i][j]);
				AddEdge(j+n,i,0,-d[i][j]);
			}
		}
		for(int i=1;i<=m;i++){
			AddEdge(i+n,t,C[i],0);
			AddEdge(t,i+n,0,0);
		}
		int ans1=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				scanf("%d",a[i]+j);
				ans1+=a[i][j]*d[i][j];
			}
		}
		//printf("%d\n",ans1);
		int ans2=Dinic(s,t);
		//printf("%d %d\n",ans1,ans2);
		if(ans1==ans2)
			printf("OPTIMAL\n");
		else{
			printf("SUBOPTIMAL\n");
			for(int u=1;u<=n;u++){
				for(int i=head[u];~i;i=edge[i].nxt){
					int v=edge[i].v;
					if(v>n)
						a[u][v-n]=B[u]-edge[i].f;
				}
			}
			for(int i=1;i<=n;i++)
				for(int j=1;j<=m;j++)
					j==m?printf("%d\n",a[i][j]):printf("%d ",a[i][j]);
		}
	}
	return 0;
}
