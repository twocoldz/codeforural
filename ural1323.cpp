#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;
const int N=10;
struct node{
	int v,nxt;
}edge[(1<<N)*(1<<N)];
int head[1<<N];
int n,m,e,id;
bool map[N][N],vis[N];
char name[N][25];
int dp[1<<N],pre[1<<N];
int mk[N];

void Init(){
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v){
	edge[e].v=v;
	edge[e].nxt=head[u];
	head[u]=e++;
}

int find(char *s){
	for(int i=0;i<id;i++)
		if(strcmp(s,name[i])==0)
			return i;
	strcpy(name[id],s);
	return id++;
}

int count(int s){
	int c=0;
	for(int i=0;i<n;i++)
		if(s&(1<<i))
			c++;
	return c;
}

bool Hungary(int u,int now,int p){
	for(int i=0;i<n;i++){
		if(map[u][i]&&!vis[i]&&((1<<i)&now)&&(!((1<<i)&p))){
			vis[i]=1;
			if(mk[i]==-1||Hungary(mk[i],now,p)){
				mk[i]=u;
				mk[u]=i;
				return true;
			}
		}
	}
	return false;
}

void Dfs(int now,int p,int s){
	//printf("now=%d p=%d\n",now,p);
	if(s!=p)
		Dfs(p,pre[p],s);
	//printf("now=%d p=%d\n",now,p);
	int ans=count(now^p);
	printf("%d\n",ans);
	memset(mk,-1,sizeof(mk));
	int cnt=0;
	for(int i=0;i<n;i++){
		if(p&(1<<i)){
			memset(vis,0,sizeof(vis));
		//	printf("i=%d\n",i);
			if(Hungary(i,now,p)){
				cnt++;
			}
		}
	}
//	printf("%d\n",cnt);
	assert(ans==cnt);
	for(int i=0;i<n;i++){
		if(p&(1<<i)){
			if(mk[i]!=-1){
				printf("%s %s\n",name[i],name[mk[i]]);
			}
		}
	}
}

int main(){
	freopen("in","r",stdin);
	char s1[25],s2[25];
	int x,y;
	while(scanf("%d",&n)==1){
		scanf("%d",&m);
		memset(map,0,sizeof(map));
		Init();
		id=0;
		for(int i=0;i<m;i++){
			scanf("%s %s",s1,s2);
			x=find(s1);
			y=find(s2);
			map[x][y]=map[y][x]=1;
		}
		scanf("%s",s1);
		if(n==1){
			printf("0\n");
			//printf("%s\n",s1);
			continue;
		}
		x=find(s1);
		memset(dp,-1,sizeof(dp));
		queue<int> q;
		q.push((1<<x));
		dp[1<<x]=0;
		//printf("%d %d\n",x,1<<x);
		while(!q.empty()){
			int st=q.front();
			q.pop();
			bool next[2][1<<N];
			memset(next,0,sizeof(next));
			next[0][st]=1;
			int r=0;
			for(int i=0;i<n;i++){
				if(st&(1<<i)){
					for(int j=0;j<(1<<n);j++){
						if(next[r][j]){
							for(int k=0;k<n;k++){
								if(map[i][k]){
									int newst=j|(1<<k);
									next[r^1][newst]=1;
								}
							}
						}
					}
					for(int j=0;j<(1<<n);j++)
						next[r^1][j]|=next[r][j];
					r^=1;
				}
			}
			for(int i=0;i<(1<<n);i++){
				if(next[r][i]&&i!=st){
					//AddEdge(st,u);
					if(dp[i]==-1){
						dp[i]=dp[st]+1,q.push(i);
						pre[i]=st;
						//printf("%d %d\n",st,i);
					}
				}
			}
		}
		printf("%d\n",dp[(1<<n)-1]);
		Dfs((1<<n)-1,pre[(1<<n)-1],1<<x);
	}
	return 0;
}
