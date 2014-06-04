/*
*
*   author : twocoldz
*   date : Thu, 14 Nov 2013 16:33:27 +0800 
*   最优比例生成树  二分实现
*/
/*
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define inf 0x3f3f3f3
using namespace std;
const int N=1005;
const double eps=1e-10;
double w[N][N];
double d[N][N];
double wd[N][N];
double dis[N];
bool vis[N];
int n,m;




double Prim(double mid)
{
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
	{
		dis[i]=inf;
		wd[i][i]=0;
		for(int j=i+1;j<=n;j++)
		{
			wd[i][j]=wd[j][i]=w[i][j]-mid*d[i][j];
		}
	}
	dis[1]=0;
	double ans=0;
	for(int u=1;u<=n;u++)
	{
		int v=-1;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&(v==-1||dis[v]>dis[i]))
				v=i;
		vis[v]=1;
		ans+=dis[v];
		//printf("v=%d dis[v]=%lf\n",v,dis[v]);
		for(int i=1;i<=n;i++)
			if(!vis[i]&&dis[i]>wd[v][i])
				dis[i]=wd[v][i];
	}
	//printf("%lf %lf\n",mid,ans);
	return ans;
}

int main()
{
	while(scanf("%d",&n)==1)
	{
		scanf("%d",&m);
		double R=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				w[i][j]=1e20;
				d[i][j]=1;
			}
		}
		int a,b,tmp,cost;
		for(int i=1;i<=m;i++)
		{
			scanf("%d %d %d %d",&a,&b,&tmp,&cost);
			d[a][b]=d[b][a]=tmp;
			w[a][b]=w[b][a]=cost;
			R=max(w[a][b]/d[a][b],R);
		}
		double L=0.0;
		double ans;
		while(L<=R)
		{
			double mid=(L+R)/2;
			if(Prim(mid)>=0)
			{
				L=mid+eps;
			}
			else
			{
				R=mid-eps;
				ans=mid;
			}
		}
		printf("%.8lf\n",ans);
	}
	return 0;
}
*/

/*
*
*   author : twocoldz
*   date : Thu, 14 Nov 2013 17:42:03 +0800 
*   最优比例生成树 Dinkelbach迭代实现 
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define inf 0x3f3f3f3f
#define eps 1e-9
using namespace std;
const int N=1005;
double x[N],y[N],r[N];
double d[N][N],w[N][N];
int pre[N];
bool vis[N];
double dis[N];
int n,m;

inline double sqr(double x)
{
	return x*x;
} 

inline double Dis(int i,int j)
{
	return sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
}

double Prim(double R)
{
	memset(vis,0,sizeof(vis));
//	memset(d[0],0,sizeof(d[0]));
//	memset(w[0],0,sizeof(w[0]));
	for(int i=1;i<=n;i++)
		dis[i]=inf;
	dis[1]=0,pre[1]=0;
	double s1=0,s2=0;
	for(int u=1;u<=n;u++)
	{
		int v=-1;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&(v==-1||dis[v]>dis[i]))
				v=i;
		//printf("v=%d pre[v]=%d w=%lf d=%lf\n",v,pre[v],w[pre[v]][v],d[pre[v]][v]);
		s1+=w[pre[v]][v];
		s2+=d[pre[v]][v];
		vis[v]=1;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&(dis[i]>w[v][i]-R*d[v][i]))
				dis[i]=w[v][i]-R*d[v][i],pre[i]=v;
	}
	return s1/s2;
}

int main()
{
	while(scanf("%d",&n)!=EOF&&n)
	{
		scanf("%d",&m);
		double R=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				w[i][j]=1e20;
				d[i][j]=1;
			}
		}
		int a,b,tmp,cost;
		for(int i=1;i<=m;i++)
		{
			scanf("%d %d %d %d",&a,&b,&tmp,&cost);
			d[a][b]=d[b][a]=tmp;
			w[a][b]=w[b][a]=cost;
			R=max(w[a][b]/d[a][b],R);
		}
		double ans=0;
		while(true)
		{
			double tmp=Prim(ans);
			if(fabs(ans-tmp)<=eps)
				break;
			ans=tmp;
		}
		printf("%.8lf\n",ans);
	}
	return 0;
}
