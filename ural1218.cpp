#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=205;
struct p{
	char name[32];
	int a,b,c;
}pe[N];
struct node{
	int u,v,nxt;
}edge[N*N];
int n,m,e;
int num,top,cnt;
int dfn[N],low[N],wh[N],head[N];
int stack[N],deg[N];
bool ins[N];

void Init(){
	e=0;
	memset(head,-1,sizeof(head));
}

void AddEdge(int u,int v){
	edge[e].u=u;
	edge[e].v=v;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void tarjan(int u){
	dfn[u]=low[u]=++num;
	stack[++top]=u;
	ins[u]=1;
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].v;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[v],low[u]);
		}else if(ins[v]&&low[u]>low[v]){
			low[u]=low[v];
		}
	}
	if(dfn[u]==low[u]){
		int j;
		cnt++;
		do{
			j=stack[top--];
			wh[j]=cnt;
			ins[j]=0;
		}while(j!=u);
	}
}

void SCC(){
	num=cnt=top=0;
	memset(ins,0,sizeof(ins));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	for(int i=1;i<=n;i++){
		if(!dfn[i])
			tarjan(i);
	}
	memset(deg,0,sizeof(deg));
	for(int i=0;i<e;i++){
		if(wh[edge[i].u]!=wh[edge[i].v]){
			deg[wh[edge[i].v]]++;
		}
	}
}

bool win(int x,int y){
	int t=0;
	if(pe[x].a>pe[y].a)
		t++;
	if(pe[x].b>pe[y].b)
		t++;
	if(pe[x].c>pe[y].c)
		t++;
	return t>=2;
}

int main(){
	while(scanf("%d",&n)!=EOF){
		Init();
		for(int i=1;i<=n;i++){
			scanf("%s %d %d %d",pe[i].name,&pe[i].a,&pe[i].b,&pe[i].c);
			for(int j=1;j<i;j++){
				if(win(i,j)){
					AddEdge(i,j);
				}else{
					AddEdge(j,i);
				}
			}
		}
		SCC();
		//printf("Over\n");
		for(int i=1;i<=n;i++){
			//printf("%d ",wh[i]);
			if(deg[wh[i]]==0){
				printf("%s\n",pe[i].name);
			}
		}
	}
	return 0;
}
