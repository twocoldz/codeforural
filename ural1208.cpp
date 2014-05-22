#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>

const int N=20;
char name[N][3][25];
bool g[N][N];
int v[N],path[N],num[N];
int n,best;

bool hasSameOne(int a,int b){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(strcmp(name[a][i],name[b][j])==0)
				return true;
		}
	}
	return false;
}

void BuildGraph(){
	memset(g,0,sizeof(g));
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(!hasSameOne(i,j)){
				g[i][j]=g[j][i]=true;
			}
		}
	}
}

void Dfs(int *obj,int tot,int cnt){
	int x[N];
	if(tot==0){
		if(cnt>best)
			best=cnt;
		for(int i=0;i<cnt;i++)
			path[i]=obj[i];
		return ;
	}
	for(int i=0;i<tot;i++){
		if(cnt+(tot-i)<=best)
			return ;
		if(cnt+num[obj[i]]<=best)
			return ;
		int tmp=0;
		for(int j=i+1;j<tot;j++)
			if(g[obj[i]][obj[j]])
				x[tmp++]=obj[j];
		Dfs(x,tmp,cnt+1);
	}
	return ;
}

void Best(){
	best=0;
	for(int i=n-1;i>=0;i--){
		int tot=0;
		for(int j=i+1;j<n;j++)
			if(g[i][j])
				v[tot++]=j;
		//printf("u=%d tot=%d\n",i,tot);
		Dfs(v,tot,1);
		num[i]=best;
		//printf("best=%d num=%d\n",best,num[i]);
	}
}

int main(){
	while(scanf("%d",&n)==1){
		for(int i=0;i<n;i++){
			for(int j=0;j<3;j++){
				scanf("%s",name[i][j]);
			}
		}
		BuildGraph();
		/*
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)
				printf("%d ",g[i][j]);
			printf("\n");
		}
		*/
		Best();
		printf("%d\n",best);
	}
	return 0;
}
