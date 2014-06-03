#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define inf 0x3f3f3f3f
using namespace std;
const int N=10e5+10;
//vector<int> route[1000];
//vector<int> station[N];
struct node{
	int v,nxt;
}redge[N<<1],sedge[N<<1];
int rhead[1024],shead[N];
int dis[N],pre[N];
int q[N];
int n,m,re,se;

void Init(){
	re=se=0;
	memset(rhead,-1,sizeof(rhead));
	memset(shead,-1,sizeof(shead));
}

void rAddEdge(int u,int v){
	redge[re].v=v;
	redge[re].nxt=rhead[u];
	rhead[u]=re++;
}

void sAddEdge(int u,int v){
	sedge[se].v=v;
	sedge[se].nxt=shead[u];
	shead[u]=se++;
}

void Bfs(int s,int t){
	memset(dis,0x3f,sizeof(dis));
	memset(pre,-1,sizeof(pre));
	//queue<int> q;
	int hea=0,rear=0;
	q[rear++]=s;
	dis[s]=0;
	while(hea<=rear){
		int u=q[hea++];
		//q.pop();
		//set<int>::iterator it=map[u].begin();
		for(int i=shead[u];~i;i=sedge[i].nxt){
			int x=sedge[i].v;
			for(int j=rhead[x];~j;j=redge[j].nxt){
				int v=redge[j].v;
				if(dis[v]==inf){
					dis[v]=dis[u]+1;
					pre[v]=u;
					if(v==t)
						return ;
					q[rear++]=(v);
				}
			}
		}
	}
	return ;
}
int a[N];
int main(){
	while(scanf("%d %d",&m,&n)==2){
		Init();
		int k,s,t;
		for(int i=0;i<m;i++){
			scanf("%d",&k);
			for(int j=0;j<k;j++){
				scanf("%d",&t);
				rAddEdge(i,t);
				sAddEdge(t,i);
				//station[t].push_back(i);
				//route[i].push_back(t);
			}
		}
		scanf("%d %d",&s,&t);
		Bfs(t,s);
		if(dis[s]==inf){
			printf("-1\n");
		}else{
			printf("%d\n",dis[s]);
			while(s!=t){
				printf("%d ",s);
				s=pre[s];
			}
			printf("%d\n",t);
		}
	}
	return 0;
}
