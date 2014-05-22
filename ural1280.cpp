#include <cstdio>
#include <cstring>

using namespace std;
const int N=1005;
int d[N];
struct node{
	int v,nxt;
}edge[N*100];
int head[N];
int e;

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
	int n,m;
	while(scanf("%d %d",&n,&m)==2){
		memset(d,0,sizeof(d));
		Init();
		int a,b,flag=1;
		for(int i=0;i<m;i++){
			scanf("%d %d",&a,&b);
			AddEdge(a,b);
			d[b]++;
		}
		for(int i=0;i<n;i++){
			scanf("%d",&a);
			if(d[a]==0){
				for(int j=head[a];~j;j=edge[j].nxt){
					d[edge[j].v]--;
				}
			}
			else
				flag=0;
		}
		printf("%s\n",flag?"YES":"NO");
	}
	return 0;
}
