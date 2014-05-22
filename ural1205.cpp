#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;
const int N=205;
const double inf=10000000000.0;
double x[N],y[N];
double dis[N][N];
bool inq[N];
double d[N];
int pre[N];
double sa,sb;
int n,s,t;

inline double sqr(double x){
	return x*x;
}

double Dis(int i,int j){
	return sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
}

void Spfa(){
	for(int i=0;i<s;i++)
		d[i]=inf;
	d[s]=0;
	memset(inq,0,sizeof(inq));
	queue<int> q;
	q.push(s);
	//printf("s=%d t=%d d[s]=%lf d[t]=%lf\n",s,t,d[s],d[t]);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int i=0;i<=s;i++){
			if(d[i]>d[u]+dis[u][i]){
				d[i]=d[u]+dis[u][i];
				pre[i]=u;
				if(!inq[i])
					q.push(i),inq[i]=1;
			}
		}
	}
	printf("%lf\n",d[t]);
	int x=t;
	int cnt=0;
	while(pre[x]!=s){
		cnt++;
		x=pre[x];
	}
	printf("%d",cnt);
	x=t;
	while(pre[x]!=s){
		printf(" %d",pre[x]);
		x=pre[x];
	}
	printf("\n");
}

int main(){
	scanf("%lf %lf",&sa,&sb);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf %lf",x+i,y+i);
	for(int i=1;i<=n;i++){
		dis[i][i]=0;
		for(int j=i+1;j<=n;j++){
			dis[i][j]=dis[j][i]=Dis(i,j)/sa;
		}
	}
	int a,b;
	while(scanf("%d %d",&a,&b)&&(a||b)){
		dis[a][b]=dis[b][a]=dis[a][b]*sa/sb;
	}
	s=0,t=n+1;
	scanf("%lf %lf",x,y);
	scanf("%lf %lf",x+t,y+t);
	for(int i=0;i<=n;i++){
		dis[s][i]=dis[i][s]=Dis(s,i)/sa;
		dis[t][i]=dis[i][t]=Dis(i,t)/sa;
	}
	swap(s,t);
	Spfa();
	return 0;
}
