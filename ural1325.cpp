#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define inf 0x3f3f3f3f
using namespace std;
const int N=512;
char map[N][N];
int n,m;
const int dx[]={1,0,-1,0,1,1,-1,-1};
const int dy[]={0,1,0,-1,1,-1,1,-1};
int dis[N*N][2];
bool inq[N*N];
int q[N*N];

struct node{
	int s;
	int d1,d2;
	node(int _s,int _d1,int _d2):s(_s),d1(_d1),d2(_d2){}
	bool operator<(const node& a)const {
		if(d1==a.d1)
			return d2>a.d2;
		return d1>a.d1;
	}
};

bool Judge(int x,int y){
	if(x<0||x>=n||y<0||y>=m)
		return 0;
	return 1;
}

void Spfa(int s,int d){
	priority_queue<node> q;
	memset(dis,inf,sizeof(dis));
	q.push(node(s,0,0));
	dis[s][0]=dis[s][1]=0;
	while(!q.empty()){
		node u=q.top();
		q.pop();
		int x=u.s/m;
		int y=u.s%m;
		for(int i=0;i<8;i++){
			int tx=x+dx[i];
			int ty=y+dy[i];
			if(Judge(tx,ty)&&map[tx][ty]!='0'){
				int v=tx*m+ty;
				int f=(map[x][y]!=map[tx][ty]);
				if(dis[v][0]>dis[u.s][0]+f
					|| (dis[v][0]==dis[u.s][0]+f&&dis[v][1]>dis[u.s][1]+1)){
					dis[v][0]=dis[u.s][0]+f;
					dis[v][1]=dis[u.s][1]+1;
					q.push(node(v,dis[v][0],dis[v][1]));
				}
			}
		}
	}
	return ;
}

int main(){
	int sx,sy,dx,dy;
	while(scanf("%d %d",&n,&m)==2){
		scanf("%d %d",&sx,&sy);
		scanf("%d %d",&dx,&dy);
		for(int i=0;i<n;i++)
			scanf("%s",map[i]);
		sx--,sy--,dx--,dy--;
		Spfa(sx*m+sy,dx*m+dy);
		if(dis[dx*m+dy][0]==inf)
			printf("0 0\n");
		else
			printf("%d %d\n",dis[dx*m+dy][1]+1,dis[dx*m+dy][0]);
	}
	return 0;
}
