#pragma GCC optimize ("O2")

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#define inf 0x3f3f3f3f
using namespace std;
const int N=512;
char map[N][N];
int id[N][N];
const int dx[]={-1,1,0,0};
const int dy[]={0,0,1,-1};
int dis[N][N];
int o[N*N][2];
int dir[N][N],d[N][N],q[2*N*N];
int n,m,cnt;

inline bool Judge(int x,int y){
	if(x<0||x>=n||y<0||y>=m)
		return 0;
	return 1;
}

void Bfs(int sx,int sy){
	//queue<int> q;
	int head,rear,tx,ty,i;
	head=0,rear=0;
	memset(dis,inf,sizeof(dis));
	memset(dir,-1,sizeof(dir));
	memset(d,-1,sizeof(d));
	dis[sx][sy]=0;
	q[rear++]=sx;
	q[rear++]=sy;
	while(head<rear){
		int x=q[head++];
		int y=q[head++];
		for(i=0;i<4;i++){
			tx=x+dx[i];
			ty=y+dy[i];
			if(Judge(tx,ty)&&map[tx][ty]!='.'){
				//if(map[tx][ty]=='#'){
					if(dis[tx][ty]>dis[x][y]+1){
						dis[tx][ty]=dis[x][y]+1;
						q[rear++]=tx;
						q[rear++]=ty;
						if(x==sx&&y==sy)
							dir[tx][ty]=i;
						else
							dir[tx][ty]=dir[x][y];
						d[tx][ty]=i;
					}else if( (dis[tx][ty]==dis[x][y]+1)
								&&d[tx][ty]>i ){
						dir[tx][ty]=dir[x][y];
						d[tx][ty]=i;
					}
				/*}else{
					if(dis[tx][ty]>dis[x][y]+1){
						dis[tx][ty]=dis[x][y]+1;
						q[rear++]=tx;
						q[rear++]=ty;
						if(x==sx&&y==sy)
							dir[tx][ty]=i;
						else
							dir[tx][ty]=dir[x][y];
						d[tx][ty]=i;
					}else if( (dis[tx][ty]==dis[x][y]+1)
								&&d[tx][ty]>i ){
						dir[tx][ty]=dir[x][y];
						d[tx][ty]=i;
					}
				}*/
			}
		}
	}
}

int main(){
	freopen("in","r",stdin);
	int x,Q,i,j;
	while(scanf("%d %d",&m,&n)==2){
		//getchar();
		for(i=0;i<n;i++){
			scanf("%s",map[i]);
		}
		cnt=1;
		for(i=n-1;i>=0;i--){
			for(j=0;j<m;j++){
				if(map[i][j]=='o'){
					id[i][j]=cnt;
					o[cnt][0]=i;
					o[cnt++][1]=j;
				}
			}
		}
		scanf("%d",&Q);
		for(i=1;i<=Q;i++){
			scanf("%d",&x);
			Bfs(o[x][0],o[x][1]);
			int ans[4]={0,0,0,0};
			for(j=1;j<cnt;j++){
				if(j==x)
					continue;
				int y=dir[o[j][0]][o[j][1]];
				if(y!=-1){
					ans[y]++;
				}
			}
			printf("Experiment #%d: North: %d, South: %d, East: %d, West: %d\n",i,ans[0],ans[1],ans[2],ans[3]);
		}
	}
	return 0;
}	


