#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>

#define inf 0x3f3f3f3f
using namespace std;
const int N=1024;
struct node{
	int v,nxt;
}edge[N*N];
bool vis[N];
int deg[N];
char map[N][N];
int head[N];
unsigned int f[N][35];
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

void Bfs(int s){
	memset(vis,0,sizeof(vis));
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].v;
			if(!vis[v]){
				vis[v]=1;
				q.push(v);
				f[v][s/32]|=(1<<(s%32));
			}
		}
	}
}

int main(){
	while(scanf("%d",&n)==1){
		Init();
		memset(deg,0,sizeof(deg));
		for(int i=0;i<n;i++){
			scanf("%s",map[i]);
			for(int j=0;j<n;j++){
				if(map[i][j]=='1'){
					AddEdge(i,j);
					deg[j]++;
				}
			}
		}
		for(int i=0;i<n;i++){
			if(deg[i]==0){
				Bfs(i);
			}
		}
		scanf("%d",&m);
		int a,b;
		for(int i=0;i<m;i++){
			scanf("%d %d",&a,&b);
			a--,b--;
			if(deg[a]==0){
				printf("YES\n");
			}else{
				int flag=1;
				for(int j=0;j<=n/32;j++){
					if(f[a][j]&f[b][j]){
						flag=0;
						break;
					}
				}
				if(flag)
					printf("YES\n");
				else
					printf("No\n");
			}
		}
	}
	return 0;
}
