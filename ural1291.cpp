#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N=1024;
int sp[N][3];
struct node{
	int v,nxt;
}edge[N*2];
int head[N];
int sz[N];
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

int gcd(int a,int b){
	return b==0?a:gcd(b,a%b);
}

void Dfs(int u,int fa){
	for(int i=head[u];~i;i=edge[i].nxt){
		int v=edge[i].v;
		if(v!=fa){
			sp[v][0]=!sp[u][0];
			sp[v][1]=sp[u][1]*sz[u];
			sp[v][2]=sp[u][2]*sz[v];
			int tmp=gcd(sp[v][1],sp[v][2]);
			sp[v][1]/=tmp;
			sp[v][2]/=tmp;
			Dfs(v,u);
		}
	}
}

int main(){
	freopen("in","r",stdin);
	int a,st;
	while(scanf("%d",&n)==1){
		Init();
		for(int i=1;i<=n;i++){
			scanf("%d",sz+i);
			while(scanf("%d",&a)&&a){
				AddEdge(i,a);
				//AddEdge(a,i);
			}
		}
		for(int i=1;i<=n;i++){
			sp[i][0]=1;
			sp[i][1]=0;
			sp[i][2]=1;
		}
		scanf("%d %d",&a,&st);
		sp[a][0]=1;
		sp[a][1]=st;
		sp[a][2]=1;
		Dfs(a,-1);
		for(int i=1;i<=n;i++){
			if(!sp[i][0])
				printf("-");
			printf("%d/%d\n",sp[i][1],sp[i][2]);
		}
	}
	return 0;
}
