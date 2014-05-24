#include <cstdio>
#include <cstring>
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <iostream>
#define next nxt
#define inf 0x3f3f3f3f
using namespace std;
const int N=100010;
int dis[2][N];
int next[2][N];
int path[2][N<<1];
int n,m;
typedef long long LL;
LL ans;
LL gcd,lcm,ca,cb,sa,sb,base,x,y;

LL exgcd(LL a,LL b,LL &x,LL &y){
	if(b==0){
		x=1,y=0;
		return a;
	}
	LL r=exgcd(b,a%b,x,y);
	LL t=x;
	x=y;
	y=t-a/b*y;
	return r;
}

int getPath(int u,int *path,int *dis,int *nxt,LL &sa,LL &ca){
	int v,len=0;;
	path[0]=u;
	dis[u]=0;
	while(true){
		v=nxt[u];
		if(dis[v]==-1){
			dis[v]=++len;
		}else{
			break;
		}
		path[len]=v;
		u=v;
	}
	sa=dis[v];
	ca=len-sa+1;
	return len;
}

void check(LL a,LL b){
	LL p;
	p=(cb*y*(a-b)/gcd+b-base)%lcm;
	//printf("a=%lld b=%lld cd=%lld lcm=%lld base=%lld t=%lld cd=%lld p=%lld\n",a,b,cb,gcd,lcm,base,t,p);
	if(p<0)
		p+=lcm;
	p+=base;
	//printf("%lld %lld\n",ans,p);
	if(ans==-1||p<ans)
		ans=p;
}

int main(){
	freopen("in","r",stdin);
	while(scanf("%d",&n)==1){
		memset(next,0,sizeof(next));
		for(int i=1;i<=n;i++){
			scanf("%d",next[0]+i);
			next[1][i]=next[0][i];
			while(scanf("%I64d",&x)&&x){
				next[1][i]=x;
			}
		}
		int S1,S2;
		scanf("%d %d",&S1,&S2);
		if(S1==S2){
			printf("0\n");
			continue;
		}
		memset(dis,-1,sizeof(dis));
		memset(path,0,sizeof(path));
		int lena=getPath(S1,path[0],dis[0],next[0],sa,ca);
		int lenb=getPath(S2,path[1],dis[1],next[1],sb,cb);
		//printf("sa=%d ca=%d lena=%d sb=%d cb=%d lenb=%d\n",sa,ca,lena,sb,cb,lenb);
		if(lena<lenb){
			for(int i=lena+1;i<=lenb;i++){
				path[0][i]=path[0][i-ca];
			}
		}else{
			for(int i=lenb+1;i<=lena;i++){
				path[1][i]=path[1][i-cb];
			}
		}
		ans=-1;
		
		int len=max(lena,lenb);
		for(int i=1;i<=len;i++){
			if(path[0][i]==path[1][i]){
				ans=i;
				break;
			}
		}
		gcd=exgcd(ca,cb,x,y);
		lcm=ca/gcd*cb;
		if(sa>sb)
			base=sa;
		else
			base=sb;
		for(int i=sa;i<=lena;i++){
			int u=path[0][i];
			if(dis[1][u]>=sb&&dis[1][u]<=lenb){
				int diff=dis[1][u]-dis[0][u];
				if(diff%gcd==0){
					check(dis[0][u],dis[1][u]);
				}
			}
		}
		printf("%I64d\n",ans); //ural int64 G++ use I64d to input and output
	}
	return 0;
}
