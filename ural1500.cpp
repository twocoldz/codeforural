#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define inf 0x3f3f3f3f
using namespace std;
const int N=30;
struct node{
	int v,nxt,c;
}edge[N*N*20];
int map[N][N];
int head[N];
bool vis[N];
int n,m,e,k,ans,cnt;

void Init(){
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v,int c){
	edge[e].v=v;
	edge[e].c=c;
	edge[e].nxt=head[u];
	head[u]=e++;
}

inline int num(int x){
	int c=0;
	for(int i=0;i<k;i++){
		if(x&(1<<i))
			c++;
	}
	return c;
}

void Dfs(int s,int t,int state,int fin){
	vis[s]=1;
	if(s==t){
		return ;
	}
	for(int i=0;i<n;i++){
		//int v=edge[i].v;
		if(!vis[i] && (map[s][i]&fin) ){
			Dfs(i,t,state|map[s][i],fin);
		}
	}
}

int main(){
	while(scanf("%d %d %d",&k,&n,&m)==3){
		Init();
		int a,b,c;
		memset(map,0,sizeof(map));
		for(int i=0;i<m;i++){
			scanf("%d %d %d",&a,&b,&c);
			map[a][b]=map[b][a]=(1<<c)|map[a][b];
			//AddEdge(a,b,c);
			//AddEdge(b,a,c);
		}
		cnt=k;
		ans=(1<<k)-1;
		for(int i=0;i<(1<<k);i++){
			if(num(i)>=cnt)
				continue;
			memset(vis,0,sizeof(vis));
			Dfs(0,1,0,i);
			
			if(vis[1]){
				ans=i;
				cnt=num(i);
			}
		}
		printf("%d\n",cnt);
		for(int i=0;i<k;i++){
			if(ans&(1<<i))
				printf("%d ",i);
		}
		printf("\n");
	}
	return 0;
}
