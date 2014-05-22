#pragma GCC optimize ("O2")

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#define inf 0x3f3f3f3f
using namespace std;
const int N=250010;
int mk[N<<1],ans[N],tmp[N];
bool vis[N<<1],used[N];
int n;
int main(){
	while(scanf("%d",&n)==1){
		memset(vis,0,sizeof(vis));
		memset(ans,0,sizeof(ans));
		memset(used,0,sizeof(used));
		for(int i=1;i<=n;i++){
			scanf("%d",mk+i);
			if(mk[i])
				vis[mk[i]+n]=1;
		}
		for(int i=1+n;i<=n+n;i++){
			scanf("%d",mk+i);
			if(mk[i]){
				if(mk[mk[i]]==i){
					ans[i-n]=mk[i];
					vis[i]=0;
				}else{
					vis[mk[i]]=1;
				}
			}
		}
		queue<int> q;
		for(int i=1;i<=n;i++){
			if(!vis[i]&&mk[i]){
				//ans[mk[i]]=i;
				//vis[mk[mk[i]+n]]=0;
				q.push(i);
			}
		}
		for(int i=n+1;i<=n+n;i++){
			if(!vis[i]&&mk[i]){
				q.push(i);
				/*
				ans[i-n]=mk[i];
				if(mk[mk[i]])
					vis[mk[mk[i]]+n]=0;
					*/
			}
		}
		while(!q.empty()){
			int u=q.front();
			q.pop();
			if(u<=n){
				ans[mk[u]]=u;
				if(mk[mk[u]+n]){
					int t=mk[mk[u]+n];
					vis[t]=0;
					if(mk[t])
						q.push(t);
				}
			}else{
				ans[u-n]=mk[u];
				if(mk[mk[u]]){
					int t=mk[mk[u]]+n;
					vis[t]=0;
					if(mk[t])
						q.push(t);
				}
			}
		}
		for(int i=1;i<=n;i++){
			if(ans[i]==0&&mk[i+n]){
				ans[i]=mk[i+n];
			}
			used[ans[i]]=1;
		}
		int k=1;
		for(int i=1;i<=n;i++)
			if(ans[i]==0){
				for(;k<=n;k++)
					if(!used[k]){
						ans[i]=k,used[k]=1;
						break;
					}
			}
		for(int i=1;i<=n;i++){
			tmp[ans[i]]=i;
		}
		for(int i=1;i<=n;i++)
			printf("%d ",tmp[i]);
		printf("\n");
	}
	return 0;
}
