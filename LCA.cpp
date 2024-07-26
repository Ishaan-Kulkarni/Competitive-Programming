#include<bits/stdc++.h>
using namespace std;

int par[100001][20];
int depth[100001];
void dfs(int node,int pp,vector<int>adj[]){
	depth[node] = depth[pp]+1;
	par[node][0] = pp;
	for(auto it:adj[node]){
		if(it != pp){
			dfs(it,node,adj);
		}
	}
}
int main()
{
	int n;
	cin>>n;
	vector<int>adj[n+1];
	for(int i = 0;i<n-1;++i){
		int u,v;
		cin>>u>>v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	int a,b;
	cin>>a>>b;
	dfs(1,0,adj);
	for(int x = 1;x<20;++x){
		for(int node = 1;node<=n;++node){
			par[node][x] = par[par[node][x-1]][x-1];
		}
	}
	if(depth[a]>depth[b]) swap(a,b);
	int k = depth[b]-depth[a];
	for(int i = 0;i<20;++i){
		if(k&(1LL<<i)){
			b = par[b][i];
		}
	}
	int lca;
	if(a==b) {lca=a;}//very imp
	else{
		for(int i = 19;i>=0;i--){
			if(par[a][i]!=par[b][i]){
				a = par[a][i];
				b = par[b][i];
			}
	    }
	    lca = par[a][0];
	}
	cout<<lca<<"\n";
}
