#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define inf 0x3f3f3f3f
using namespace std;
const int N=1000;
struct node{
	int v,nxt,w;
}edge[N*30];
int head[N];
int id[40][40];
int dis[N];
bool inq[N];
int lv[N];
int n,m,e,cnt=0;

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

void Spfa(){
	queue<int> q;
	memset(dis,inf,sizeof(dis));
	memset(inq,0,sizeof(inq));
	dis[0]=0;
	q.push(0);
	inq[0]=1;
	int ans=inf;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].v;
			if(dis[v]>dis[u]+edge[i].w){
				dis[v]=dis[u]+edge[i].w;
				if(lv[v]==n&&ans>dis[v])
					ans=dis[v];
				if(!inq[v]){
					inq[v]=1,q.push(v);
				}
			}
		}
	}
	printf("%d\n",ans);
}

int main(){
	while(scanf("%d",&n)==1){
		cnt=0;
		id[0][0]=1;
		lv[cnt]=0;
		id[0][1]=cnt++;
		int x,w;
		char useless[3];
		Init();
		for(int i=1;i<=n;i++){
			scanf("%d",id[i]);
			for(int j=1;j<=id[i][0];j++){
				lv[cnt]=i;
				id[i][j]=cnt++;
				while(scanf("%d",&x)&&x){
					scanf("%d",&w);
					AddEdge(id[i-1][x],id[i][j],w);
				}
			}
			if(i!=n)
				scanf("%s",useless);
		}
		Spfa();
	}
	return 0;
}
