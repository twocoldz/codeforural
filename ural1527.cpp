#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define inf 0x3f3f3f3f
using namespace std;
const int N=110;
struct node{
	int u,v,nxt,c,t,h;
}edge[N*N];
struct Node{
	int u,c;
	Node(int _u,int _c):u(_u),c(_c){}
};
int head[N];
int dis[N][N];
bool inq[N][N];
int pre[N][N];
int path[N];
int d[N][N];
int n,m,e;
int Lc,Lt;

void Init(){
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,int c,int t,int h){
	edge[e].u=u;
	edge[e].v=v;
	edge[e].c=c;
	edge[e].t=t;
	edge[e].h=h;
	edge[e].nxt=head[u];
	head[u]=e++;
}

bool Bfs(int s,int e,int limit){
	//printf("s=%d e=%d mid=%d\n",s,e,limit);
	memset(dis,0x3f,sizeof(dis));
	memset(inq,0,sizeof(inq));
	memset(pre,-1,sizeof(pre));
	dis[s][0]=0;
	queue<Node> q;
	q.push(Node(s,0));
	while(!q.empty()){
		Node t=q.front();
		q.pop();
		inq[t.u][t.c]=0;
		for(int i=head[t.u];~i;i=edge[i].nxt){
			int v=edge[i].v;
			//printf("u=%d v=%d\n",t.u,v);
			if(edge[i].h>limit)
				continue;
			//printf("u=%d v=%d\n",t.u,v);
			if(edge[i].c){
				if(t.c+1<=Lc&&dis[v][t.c+1]>dis[t.u][t.c]+edge[i].t){
					dis[v][t.c+1]=dis[t.u][t.c]+edge[i].t;
					d[v][t.c+1]=d[t.u][t.c]+1;
					pre[v][t.c+1]=i;
					//printf("c=1 dis[v][t.c+1]=%d\n",dis[v][t.c+1]);
					if(v==e&&dis[v][t.c+1]<=Lt)
						return true;
					if(dis[v][t.c+1]<=Lt&&!inq[v][t.c+1]){ 
						inq[v][t.c+1]=1;
						q.push(Node(v,t.c+1));
					}
				}
			}else{
				if(t.c<=Lc&&dis[v][t.c]>dis[t.u][t.c]+edge[i].t){
					dis[v][t.c]=dis[t.u][t.c]+edge[i].t;
					d[v][t.c]=d[t.u][t.c]+1;
					pre[v][t.c]=i;
					//printf("c=0 dis[v][t.c]=%d\n",dis[v][t.c]);
					if(v==e&&dis[v][t.c]<=Lt)
						return true;
					if(dis[v][t.c]<=Lt&&!inq[v][t.c]){
						inq[v][t.c]=1;
						q.push(Node(v,t.c));
					}
				}
			}
		}
	}
	return false;
}

int main(){
	int S,T;
	while(scanf("%d %d %d %d",&n,&m,&S,&T)==4){
		Init();
		scanf("%d %d",&Lc,&Lt);
		int L=0,R=0;
		int a,b,c,t,h;
		for(int i=0;i<m;i++){
			scanf("%d %d %d %d %d",&a,&b,&c,&t,&h);
			AddEdge(b,a,c,t,h);
			R=max(R,h);
		}
		int ans=-1,dd;
		while(L<=R){
			int mid=(L+R)>>1;
			if(Bfs(T,S,mid)){
				ans=mid;
				R=mid-1;
				int x=S,i;
				for(i=0;i<=Lc;i++){
					if(dis[S][i]<=Lt&&pre[S][i]!=-1){
						c=i;
						break;
					}
				}
				dd=d[S][c];
				i=0;
				while(x!=T){
					int j=pre[x][c];
					path[i++]=j;
					x=edge[j].u;
					c-=edge[j].c;
				}
			}else{
				L=mid+1;
			}
		}
		printf("%d\n",ans);
		if(ans!=-1){
			printf("%d\n",dd);
			for(int i=0;i<dd;i++){
				printf("%d ",path[i]+1);
			}
			printf("\n");
		}
		
	}
	return 0;
}
