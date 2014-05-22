#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int N=1024;
struct node{
	int v,nxt;
}edge[N*4];
int head[N];
int fa[N][2];
bool vis[N];
int n,m,e;

void Init(){
	e=0;
	memset(head,-1,sizeof(head));
	memset(fa,-1,sizeof(fa));
}

void AddEdge(int u,int v){
	edge[e].v=v;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void AddFa(int u,int v){
	if(fa[u][0]==-1)
		fa[u][0]=v;
	else
		fa[u][1]=v;
}

void Bfs(int u)
{
	queue<int> q;
	q.push(u);
	vis[u]=1;
	bool inq[N];
	memset(inq,0,sizeof(inq));
	inq[u]=1;	
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].v;
			vis[v]=1;
			if(!inq[v]){
				inq[v]=1;
				q.push(v);
			}
		}
	}
	q.push(u);
	memset(inq,0,sizeof(inq));
	inq[u]=1;
	while(!q.empty()){
		int u=q.front(),v;
		q.pop();
		if(fa[u][0]!=-1){
			v=fa[u][0];
			vis[v]=1;
			if(!inq[v])
				inq[v]=1,q.push(v);
		}
		if(fa[u][1]!=-1){
			v=fa[u][1];
			vis[v]=1;
			if(!inq[v])
				inq[v]=1,q.push(v);
		}
	}	
}

int main(){
	//freopen("in","r",stdin);
	scanf("%d",&n);
	getchar();
	Init();
	int a,b,x;
	char str[20];
	while(gets(str)){
		//printf("%s\n",str);
		if(sscanf(str,"%d %d",&a,&b)!=2)
			break;
		//printf("%d %d\n",a,b);
		AddFa(a,b);
		AddEdge(b,a);
	}
	memset(vis,0,sizeof(vis));
	//char blood[10];
	//scanf("%s",blood);
	while(scanf("%d",&x)!=EOF){
		//if(!vis[x])
			Bfs(x);
	}
	int i;
	for(i=1;i<=n;i++)
		if(!vis[i]){
			printf("%d",i);
			break;
		}
	if(i>n)
		printf("0\n");
	else{
		for(i++;i<=n;i++){
			if(!vis[i])
				printf(" %d",i);
		}
		printf("\n");
	}
	return 0;
}
