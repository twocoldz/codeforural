#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define inf 0x3f3f3f3f
using namespace std;
const int N=128;
struct node{
	int v,nxt;
}edge[N*N*4];
int head[N*N];
int dfn[N*N],low[N*N],stack[N*N];
int num,top,cnt;
int n,m,e,cut;
char map[N][N];
int id[N][N],deg[N*N];
bool vis[N*N*4],ins[N*N];

void Init(){
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v){
	edge[e].v=v;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void tarjan(int u,int fa){
	low[u]=dfn[u]=++num;
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v!=fa){
			if(!dfn[v]){
				tarjan(v,u);
				low[u]=min(low[u],low[v]);
				if(low[v]>dfn[u])
					cut=1;
			}else{
				low[u]=min(low[u],dfn[v]);
			}
		}
	}
}

void tarjan_cut(){
	num=top=0;
	cut=0;
	memset(dfn,0,sizeof(dfn));
	tarjan(0,-1);
	if(num<cnt)
		cut=1;
	
}

int main(){
	while(scanf("%d %d",&m,&n)==2){
		getchar();
		cnt=0;
		int flag=1;
		memset(map,0,sizeof(map));
		memset(deg,0,sizeof(deg));
		for(int i=0;i<n;i++){
			gets(map[i]);
			for(int j=0;j<m;j++){
				if(map[i][j]=='O'){
					id[i][j]=cnt++;
					if((i%2)||(j%2))
						flag=0;
				}
				
				if(map[i][j]!='O'&&map[i][j]!='-'&&map[i][j]!='|'&&
					map[i][j]!='\\'&&map[i][j]!='/'&&map[i][j]!=' ')
					flag=0;
					
			}
		}
		if(cnt==0||flag==0||n%2==0||m%2==0){
			printf("Just a picture\n");
			continue;
		}
		Init();
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				if(map[i][j]=='O'){
					if(map[i][j+1]=='-'&&map[i][j+2]=='O'){
						AddEdge(id[i][j],id[i][j+2]);
						AddEdge(id[i][j+2],id[i][j]);
						deg[id[i][j]]++;
						deg[id[i][j+2]]++;
						
					}
					if(map[i+1][j]=='|'&&map[i+2][j]=='O'){
						AddEdge(id[i][j],id[i+2][j]);
						AddEdge(id[i+2][j],id[i][j]);
						deg[id[i][j]]++;
						deg[id[i+2][j]]++;
						
					}
					if(j>1&&map[i+1][j-1]=='/'&&map[i+2][j-2]=='O'){
						AddEdge(id[i][j],id[i+2][j-2]);
						AddEdge(id[i+2][j-2],id[i][j]);
						deg[id[i][j]]++;
						deg[id[i+2][j-2]]++;
						
					}
					if(map[i+1][j+1]=='\\'&&map[i+2][j+2]=='O'){
						AddEdge(id[i][j],id[i+2][j+2]);
						AddEdge(id[i+2][j+2],id[i][j]);
						deg[id[i][j]]++;
						deg[id[i+2][j+2]]++;
						
					}
				}
			}
		}
		for(int i=0;i<cnt;i++){
			if(deg[i]!=3)
				flag=0;
		}
		if(flag==0){
			printf("Just a picture\n");
			continue;
		}
		tarjan_cut();
		if(cut==0)
			printf("Island world\n");
		else
			printf("Just a picture\n");
	}
	return 0;
}

