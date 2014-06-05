#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int N=512;
struct node{
	int v,nxt,w;
}edge[N*N];
int head[N];
int inq[N];
int dis[N];
int n,m,e;

void Init(){
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,int w){
	edge[e].v=v;
	edge[e].w=w;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void Bfs(int s,int t){
	memset(dis,-1,sizeof(dis));
	memset(inq,0,sizeof(inq));
	dis[s]=0;
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].v;
			if(dis[u]+edge[i].w>dis[v]){
				dis[v]=dis[u]+edge[i].w;
				if(!inq[v]){
					inq[v]=1;
					q.push(v);
				}
			}
		}
	}
	return ;
}

int main(){
	while(scanf("%d %d",&n,&m)==2){
		Init();
		int a,b,w,s,t;
		for(int i=0;i<m;i++){
			scanf("%d %d %d",&a,&b,&w);
			AddEdge(a,b,w);
		}
		scanf("%d %d",&s,&t);
		Bfs(s,t);
		if(dis[t]!=-1){
			printf("%d\n",dis[t]);
		}else{
			printf("No solution\n");
		}
	}
	return 0;
}
