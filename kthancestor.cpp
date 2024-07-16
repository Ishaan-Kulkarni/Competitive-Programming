#include<bits/stdc++.h>
using namespace std;


//If we want to find the kth ancestor of any node in the tree(generic). We can simply
//perform the dfs and store the parent of each node(take a parent array). 
//After that lets say we want to find kth ancestor of any node x we can simply run a 
//while loop till k == 0 and do a backtrack like stuff with the help of parent array.
//This approach takes O(k) k can be in worst be equal to n if tree is something like skew tree.
//But if queries are given then this approach is inefficient. q<=1e5 and at every query
//we run a O(k) loop which will surely give TLE --> O(q*n).

//Lets code the brute force approach.
void helper(int root,int pp,vector<int>adj[],vector<int>&par){
	par[root] = pp;
	for(auto it:adj[root]){
		if(it!=pp){
			helper(it,root,adj,par);
		}
	}
}

//We have to reduce the TC by O(q*logn) or [O(q*1)] --> constant is not possible
//lets see if we can come up with O(q*logn) approach
//The main intuition behind the optimal approach is "every number can be
// represented in powers of 2"
//Got it? --> Yep! You are on thinking in right direction 
//instead of traversing backwards on each parent lets take a jump in terms 
//power of 2
//How can we do this? --> We have to store 2^xth parent for each node
//And if we are calculating kth ancestor of a node we can use a dp like 
//relation to calculate it.
//What could be the relation? --> I said that we have to precompute all the
//2^xth parents of each node --> We can store this in a 2d array
//Lets name it dp[node][x] --> what will it store --> it will store 2^xth parent
//of node --> oh! then can you guess what would be the space?
//--> the rows will be number of nodes which is N and what about x?
//I said 2^xth parent i.e. 2^x <= N (in worst case = N)
//--> x = logN --> oh! i.e. the space taken would be N*logN (N<=1e5)

//Ok! Now lets precompute this 2d dp
int dp[1000003][19];
void helper1(int root,int pp,vector<int>adj[]){
	dp[root][0] = pp; //2^0 = 1th parent is its immediate parent
	//You have to first compute all 2^i parents for this one and
	//only can go further because we need this info further
	for(int i = 1;i<19;++i){
		dp[root][i] = dp[dp[root][i-1]][i-1]; //this is the relation!
		//Lets elaborate
		//it tells if I want to calculate 2^ith parent first calculate 2^i-1 th
		//parent lets name it as node1, now calculate 2^i-1th parent of node1
		//for eg 2^3 == 8 parent of a node will be 2^2 == 4 parent(node1) and
		//again 2^2th == 4 parent of node1 --> if you observe we have take 8 steps 
		//overall --> go half steps up and again go half steps of that node(here node1)
	}
	for(auto it:adj[root]){
		if(it!=pp){
			helper1(it,root,adj);
		}
	}
}

int main(){
	int n,q;
	cin>>n>>q;
	vector<int>adj[n+1];
	for(int i = 0;i<n-1;++i){
		int u,v;
		cin>>u>>v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int>par(n+1);
	// helper(1,0,adj,par); //lets take 1 based indexing
	helper1(1,0,adj);
	while(q--){
		int x,k;
		cin>>x>>k;
		// while(k--){
		// 	x = par[x];
		// }

		//Now just count set bits of k and take that much jump --> which
		//is already precomputed in our black box (dp)
		for(int i = 0;i<19;++i){ //19 ~ O(log(1e5))
			if(k&(1<<i)){
				x = dp[x][i];
			}
		}
		if(x==0){}; //kth ancestor doesnt exist
		cout<<x<<"\n";
	}

	//TC --> (precomputation) O(NlogN) + O(q*logN)
}
