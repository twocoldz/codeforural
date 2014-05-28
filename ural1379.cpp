#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int N=512;
const int M=1441;
struct node{
	int v,nxt,t,w;
}edge[N*N];
int head[N];
int dis[N][M];
bool vis[N][M];
int n,m,e,ans;

void Init(){
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,int t,int w){
	edge[e].v=v;
	edge[e].t=t;
	edge[e].w=w;
	edge[e].nxt=head[u];
	head[u]=e++;
}


void Spfa(){
	memset(dis,-1,sizeof(dis));
	memset(vis,0,sizeof(vis));
	queue<int> q;
	dis[0][0]=10e7;
	q.push(0);
	ans=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		int t=u%1441;
		u/=1441;
		vis[u][t]=0;
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].v;
			int newt=t+edge[i].t;
			int w=min(dis[u][t],edge[i].w);
			if(newt<=1440&&w>ans&&dis[v][newt]<w){
				dis[v][newt]=w;
				if(v==n-1)
					ans=dis[v][newt];
				if(!vis[v][newt]){
					vis[v][newt]=1;
					q.push(v*1441+newt);
				}
			}
		}
	}
}

int main(){
	while(scanf("%d %d",&n,&m)==2){
		Init();
		int a,b,t,w;
		for(int i=0;i<m;i++){
			scanf("%d %d %d %d",&a,&b,&t,&w);
			w=(w-3000000)/100;
			if(w>0){
				a--,b--;
				AddEdge(a,b,t,w);
				AddEdge(b,a,t,w);
			}
		}
		if(n==1){
			printf("10000000\n");
			continue;
		}
		Spfa();
		printf("%d\n",ans);
	}
	return 0;
}

