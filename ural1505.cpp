#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
const int N=10005;
struct node{
	int u,v,nxt,w,c,f;
}edge[N*20];
int head[N],pre[N];
int in[N],out[N];
long long dis[N];
bool inq[N];
int n,m,e;

void Init(){
	e=0;
	memset(head,-1,sizeof(head));
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
}

void AddEdge(int u,int v,int w,int c,int f){
	edge[e].u=u;
	edge[e].v=v;
	edge[e].w=w;
	edge[e].c=c;
	edge[e].f=f;
	edge[e].nxt=head[u];
	head[u]=e++;
}

void Bfs(int t){
	memset(dis,0x3f,sizeof(dis));
	memset(inq,0,sizeof(inq));
	memset(pre,-1,sizeof(pre));
	queue<int> q;
	for(int i=1;i<=n;i++){
		if(in[i]<out[i]){
			dis[i]=0;
			inq[i]=1;
			q.push(i);
			//printf("in<out %d\n",i);
		}
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		inq[u]=0;
		//printf("%d\n",u);
		for(int i=head[u];~i;i=edge[i].nxt){
			int v=edge[i].v;
			//rintf("u=%d v=%d\n",u,v);
			if(edge[i].f<edge[i].c){
				if(dis[v]>dis[u]){
					dis[v]=dis[u];
					pre[v]=i;
					if(!inq[v]){
						inq[v]=1;
						q.push(v);
					}
				}
			}else{
				if(i%2==0&&dis[v]>dis[u]+edge[i].w){
					dis[v]=dis[u]+edge[i].w;
					pre[v]=i;
					if(!inq[v]){
						inq[v]=1;
						q.push(v);
					}
				}
			}
		}
	}
	return ;
}

char str[204800];

int main(){
	while(scanf("%d",&n)==1){
		Init();
		getchar();
		int a,f,c,w;
		for(int i=1;i<=n;i++){
			gets(str);
			char s[1024];
			int k=0;
			for(int j=0;str[j]!='\0';j++){
				if(str[j]=='.'||str[j]==','){
					if(k==0)
						continue;
					s[k]='\0';
					sscanf(s,"%d %d %d %d",&a,&c,&f,&w);
					AddEdge(i,a,w,c,f);
					AddEdge(a,i,w,f,0);
					out[i]+=f;
					in[a]+=f;
					k=0;
				}else{
					s[k++]=str[j];
				}
			}
		}
		Bfs(n);
		if(dis[n]==inf){
			printf("Impossible\n");
		}else{
			printf("%I64d\n",dis[n]);    //timue use I64d for int64 input and output
			int t=n;
			while(pre[t]!=-1){
				int i=pre[t];
				//printf("i=%d u=%d\n",i,edge[i].u);
				if(i%2){
					edge[i^1].f--;
				}else{
					edge[i].f++;
				}
				t=edge[i].u;
			}
			for(int i=1;i<=n;i++){
				f=0;
				for(int j=head[i];~j;j=edge[j].nxt){
					if(j%2)
						continue;
					if(f)
						printf(", %d %d",edge[j].v,edge[j].f);
					else
						printf("%d %d",edge[j].v,edge[j].f);
					f=1;
				}
				printf(".\n");
			}
		}
	}
	return 0;
}
