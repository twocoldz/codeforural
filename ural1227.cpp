#include <stdio.h>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=105;
int w[N][N];
int dis[N][2];
bool vis[N];
int n,m,S,flag;

void dfs(int u,int fa){
	vis[u]=1;
	for(int i=1;i<=n;i++){
		if(w[u][i]&&i!=fa){
			if(vis[i])
				flag=true;
			else{
				dfs(i,u);
				if(dis[i][0]+w[u][i]>dis[u][0]){
					dis[u][1]=dis[u][0];
					dis[u][0]=dis[i][0]+w[u][i];
				}else if(dis[i][0]+w[u][i]>dis[u][1]){
					dis[u][1]=dis[i][0]+w[u][i];
				}
			}
		}
	}
}

int main(){
	while(scanf("%d %d %d",&n,&m,&S)!=EOF){
		memset(w,0,sizeof(w));
		int a,b,d;
		flag=0;
		for(int i=0;i<m;i++){
			scanf("%d %d %d",&a,&b,&d);
			if(a==b||w[a][b])
				flag=true;
			w[a][b]=w[b][a]=d;
		}
		if(flag){
			printf("YES\n");
			continue;
		}
		memset(vis,0,sizeof(vis));
		memset(dis,0,sizeof(dis));
		for(int i=1;i<=n;i++){
			if(!vis[i]){
				dfs(i,-1);
			}
		}
		if(flag){
			printf("YES\n");
			continue;
		}
		for(int i=1;i<=n;i++)
			if(dis[i][0]+dis[i][1]>=S)
				flag=true;
		if(flag)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
