

//problem link - https://cses.fi/problemset/task/1684

#include <bits/stdc++.h>
using namespace std;

#define ll long long;

struct two_sat{
    int n;
    vector<vector<int>>adj,radj;
    vector<int>vis,comp_no,topo_order;
    vector<int>ans;
    
    void init(int _n){
        n = _n;
        adj.assign(2 * n + 1, vector<int>());
        radj.assign(2 * n + 1, vector<int>());
        comp_no.resize(2*n+1);
        vis.resize(2*n+1,0);
        ans.resize(n+1);
    }
    
    void add_edge(int u,int v){
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
    
    void add_clause_or(int i,bool f,int j,bool g){
        add_edge(i + (f ? n : 0),j + (g ? 0 : n));
        add_edge(j + (g ? n : 0),i + (f ? 0 : n));
    }
    
    void dfs(int node){
        vis[node] = 1;
        for(auto &it : adj[node]){
            if(!vis[it]) dfs(it);
        }
        topo_order.push_back(node);
    }
    
    //SCC condensation
    //every scc will be given a number in topo ordering 
    void dfss(int node,int cnt){
        comp_no[node] = cnt;
        for(auto &it : radj[node]){
            if(comp_no[it] == 0) dfss(it,cnt);
        }
    }
    
    bool satisfiable(){
        for(int i = 1;i<=2*n;++i){
            if(!vis[i]) dfs(i);
        }
        
        int cnt = 1;
        reverse(topo_order.begin(),topo_order.end());
        for(int i = 0;i<2*n;++i){
            if(comp_no[topo_order[i]]==0) dfss(topo_order[i],cnt++);
        }
        
        for(int i = 1;i<=n;++i){
            if(comp_no[i] == comp_no[i+n]){
                return false;
            }
            else if(comp_no[i] < comp_no[i+n]){
                ans[i] = 0;
            }
            else{
                ans[i] = 1;
            }
        }
        return true;    
    }
};

int main()
{
    int n,m;
    cin >> n >> m;
    //m is number of literals (node) and n is number of clauses
    two_sat s;
    s.init(m);
    while(n--){
        int literal1,literal2;
        char c1,c2;
        cin >> c1 >> literal1 >> c2 >> literal2;
        s.add_clause_or(literal1,c1=='+',literal2,c2=='+');
    }
    
    if(s.satisfiable()){
        for(int i = 1;i<=m;++i){
            cout << (s.ans[i] ? "+" : "-") << ' ';
        }
    }
    else{
        cout << "IMPOSSIBLE\n";
    }
    
    
    
    
    return 0;
}
