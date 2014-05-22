#include <cstdio>
#include <cstring>
#include <queue>
#include <assert.h>
#include <algorithm>

using namespace std;
const int N=128;
struct node{
	int v,nxt;
}edge[N*N];
int head[N];
int deg[N],ans[N],day[N];
bool need[N],have[N];
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

int main(){
	while(scanf("%d %d",&n,&m)==2){
		Init();
		int x,today;
		memset(day,-1,sizeof(day));
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			assert(day[x]==-1);
			day[x]=i;
		}
		for(int i=1;i<=n;i++){
			deg[i]=0;
			while(scanf("%d",&x)&&x){
				deg[i]++;
				AddEdge(x,i);
			}
		}
		scanf("%d",&today);
		memset(have,0,sizeof(have));
		while(scanf("%d",&x)&&x){
			have[x]=1;
			for(int i=head[x];~i;i=edge[i].nxt){
				int v=edge[i].v;
				deg[v]--;
			}
			head[x]=-1;
		}
		memset(need,0,sizeof(need));
		while(scanf("%d",&x)&&x){
			need[x]=1;
		}
		int left=0,num=0,cnt=0,no=0;
		for(int i=1;i<=n;i++)
			if(need[i]&&(!have[i]))
				left++;
		while(left&&no<=m){
			num++;
			x=day[today];
			today++;
			if(today>m)
				today=1;
			no++;
			if(x==-1||deg[x]){
				continue;
			}
			if(!have[x]){
				no=0;
				for(int i=head[x];~i;i=edge[i].nxt){
					int v=edge[i].v;
					deg[v]--;
				}
				ans[cnt++]=x;
				head[x]=-1;
				if(need[x]){
					left--;
				}
			}
			have[x]=1;
		}
		if(left==0){
			printf("%d\n",max(num-1,0));
			if(cnt){
				for(int i=0;i<cnt;i++)
					printf("%d ",ans[i]);
				printf("\n");
			}
		}else{
			printf("No Solution\n");
			/*
			for(int i=1;i<=n;i++)
				if(need[i]&&(!have[i]))
					printf("%d deg[i]=%d\n",i,deg[i]);
					*/
		}
		//printf("\n");
	}
	return 0;
}
