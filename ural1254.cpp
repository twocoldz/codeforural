#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#define inf 0x3f3f3f3f
using namespace std;
const int dx[]={1,0,-1,0,1,-1,1,-1};
const int dy[]={0,1,0,-1,-1,1,1,-1};
const int N=80;
const double sqrt2=sqrt(2);
char map[N][N];
bool vis[N][N];
double dis[N][N];
int n,m,k;
bool flag;
struct node{
	int id;
	double dis;
	node(int x,int y,double _dis=inf):id(x*m+y),dis(_dis){};
	bool operator <(const node &b) const{
		return dis>b.dis;
	}  
};
double ans;

bool Judge(int x,int y){
	if(x<0||x>=n||y<0||y>=m)
		return false;
	return true;
}

void Dij(node s,node t){
	priority_queue<node> q;
	q.push(s);
	memset(vis,0,sizeof(vis));
	vis[s.id/m][s.id%m]=1;
	//printf("s.id=%d t.id=%d\n",s.id,t.id);
	while(!q.empty()){
		node u=q.top();
		q.pop();
		//printf("u.id=%d\n",u.id);
		int y=u.id%m;
		int x=u.id/m;
		if(u.id==t.id){
			ans+=u.dis;
			return ;
		}
		for(int i=0;i<4;i++){
			int tx=x+dx[i];
			int ty=y+dy[i];
			if(Judge(tx,ty)&&map[tx][ty]=='.'&&!vis[tx][ty])
				q.push(node(tx,ty,u.dis+1)),vis[tx][ty]=1;
		}
		for(int i=4;i<8;i++){
			int tx=x+dx[i];
			int ty=y+dy[i];
			if(Judge(tx,ty)&&map[tx][ty]=='.'&&!vis[tx][ty])
				q.push(node(tx,ty,u.dis+sqrt2)),vis[tx][ty]=1;
		}
	}
}

bool Spfa(node s,node t){
	memset(vis,0,sizeof(vis));
	for(int i=0;i<n;i++)
		for(int j=0;j<=m;j++)
			dis[i][j]=inf;
	queue<int> q;
	q.push(s.id);
	dis[s.id/m][s.id%m]=0;
	vis[s.id/m][s.id%m]=1;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		int y=x%m;
		x/=m;
		vis[x][y]=0;
		for(int i=0;i<4;i++){
			int tx=x+dx[i];
			int ty=y+dy[i];
			if(Judge(tx,ty)&&map[tx][ty]=='.'){
				if(dis[tx][ty]>dis[x][y]+1){
					dis[tx][ty]=dis[x][y]+1;
					if(!vis[tx][ty]){
						q.push(tx*m+ty),vis[tx][ty]=1;
					}
				}
			}
		}
		for(int i=4;i<8;i++){
			int tx=x+dx[i];
			int ty=y+dy[i];
			if(Judge(tx,ty)&&map[tx][ty]=='.'){
				if(dis[tx][ty]>dis[x][y]+sqrt2){
					dis[tx][ty]=dis[x][y]+sqrt2;
					if(!vis[tx][ty]){
						q.push(tx*m+ty),vis[tx][ty]=1;
					}
				}
			}
		}
	}
	//printf("%lf\n",dis[t.id/m][t.id%m]);
	if(abs(dis[t.id/m][t.id%m]-inf)<10e-6){
		return false;
	}
	ans+=dis[t.id/m][t.id%m];
	return true;
}

int main(){
	freopen("in","r",stdin);
	double speed;
	int sx,sy,tx,ty;
	while(scanf("%d %d %d %lf",&m,&n,&k,&speed)!=EOF){
		for(int i=0;i<n;i++)
			scanf("%s",map[i]);
		scanf("%d %d",&sy,&sx);
		sx--,sy--;
		ans=0;
		flag=0;
		for(int i=0;i<k;i++){
			scanf("%d %d",&ty,&tx);
			tx--,ty--;
			if(Spfa(node(sx,sy,0),node(tx,ty)))
				sx=tx,sy=ty;
		}
		printf("%.2lf\n",ans/speed);
	}
	return 0;
}
