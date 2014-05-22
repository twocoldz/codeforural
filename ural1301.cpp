#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
const int N=128;
enum dir{U=0,D,L,R,F,B};
bool wall[N][N][4],inq[N][N][6];
int dis[N][N][6];
const int dx[]={0,0,-1,1};
const int dy[]={1,-1,0,0};
const dir ch[6][4]={
	{B,F,L,R},
	{F,B,R,L},
	{L,L,D,U},
	{R,R,U,D},
	{U,D,F,F},
	{D,U,B,B}
};
struct node{
	int x,y;
	dir d;
	node(int _x,int _y,dir _d):x(_x),y(_y),d(_d){}
};
int n,m;

bool Judge(int x,int y){
	if(x<1||x>n||y<1||y>m)
		return 0;
	return 1;
}

void Bfs(node s,node d){
	memset(dis,0x3f,sizeof(dis));
	queue<node> q;
	memset(inq,0,sizeof(inq));
	q.push(s);
	inq[s.x][s.y][s.d]=1;
	dis[s.x][s.y][s.d]=0;
	while(!q.empty()){
		node u=q.front();
		q.pop();
		inq[u.x][u.y][u.d]=0;
		//printf("ux=%d uy=%d ud=%d\n",u.x,u.y,u.d);
		//printf("-------------------\n");
		for(int i=0;i<4;i++){
			if(wall[u.x][u.y][i])
				continue;
			int tx=u.x+dx[i];
			int ty=u.y+dy[i];
			dir td=ch[u.d][i];
			//printf("tx=%d ty=%d td=%d\n",tx,ty,td);
			if(Judge(tx,ty)&&dis[tx][ty][td]>dis[u.x][u.y][u.d]+1){
				
				dis[tx][ty][td]=dis[u.x][u.y][u.d]+1;
				//printf("tx=%d ty=%d td=%d dis=%d\n",tx,ty,td,dis[tx][ty][td]);
				if(!inq[tx][ty][td]){
					inq[tx][ty][td]=1;
					q.push(node(tx,ty,td));
				}
			}
		}
	}
	return ;
}

int main(){
	freopen("in","r",stdin);
	int sx,sy,dx,dy;
	char str[100];
	scanf("%d %d",&n,&m);{
		scanf("%d %d",&sx,&sy);
		scanf("%d %d",&dx,&dy);
		while(getchar()!='v');
		getchar();
		memset(wall,0,sizeof(wall));
		while(gets(str)!=NULL){
			if(str[0]=='h')
				break;
			int x,y;
			sscanf(str,"%d %d",&x,&y);
			wall[x][y][3]=1;
			wall[x+1][y][2]=1;
		}
		while(gets(str)!=NULL){
			int x,y;
			sscanf(str,"%d %d",&x,&y);
			wall[x][y][0]=1;
			wall[x][y+1][1]=1;
		}
		//printf("read over\n");
		Bfs(node(sx,sy,U),node(dx,dy,U));
		//printf("Bfs over\n");
		if(dis[dx][dy][U]==0x3f3f3f3f){
			printf("No solution\n");
		}else
			printf("%d\n",dis[dx][dy][U]);
	}
	return 0;
}
