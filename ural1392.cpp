#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int N=1024;
struct node{
	int v,nxt;
}edge[N*N];
int head[N];
int x[N],y[N],z[N],r[N],vis[N];
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

inline int sqr(int x){
	return x*x;
}
void Bfs(int s,int num){
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].v;
			if(!vis[v]){
				vis[v]=num;
				q.push(v);
			}
		}
	}
}

int main(){
	while(scanf("%d",&n)==1){
		Init();
		for(int i=0;i<n;i++){
			scanf("%d %d %d %d",x+i,y+i,z+i,r+i);
			for(int j=0;j<i;j++){
				int dis=sqr(x[i]-x[j])+sqr(y[i]-y[j])+sqr(z[i]-z[j]);
				if(dis<sqr(r[i]+r[j])){
					AddEdge(i,j);
					AddEdge(j,i);
				}
			}
		}
		int cnt=1;
		memset(vis,0,sizeof(vis));
		for(int i=0;i<n;i++){
			if(!vis[i]){
				Bfs(i,cnt);
				printf("%d",i);
				for(int j=0;j<n;j++){
					if(j!=i&&vis[j]==cnt)
						printf(", %d",j);
				}
				printf("\n");
				cnt++;
			}
		}
	}
	return  0;
}
