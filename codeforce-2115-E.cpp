#include <bits/stdc++.h>

using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

constexpr int C = 10;

void chmax(i64 &a, i64 b){
	 if(a < b){
	 	a = b;
	 }
}

void solve(){
	int n, m;
	std::cin >> n >> m;
    
    std::vector<int> c(n), w(n);

    for(int i = 1; i <= n; i++){
    	std::cin >> c[i] >> w[i];
    }
    
    std::vector<std::vector<int>> adj(n);

    for(int i = 1; i <= m; i++){
    	int u, v;
    	std::cin >> u >> v;
    	u--;
    	v--;
    	adj[u].push_back(v);
    	adj[v].push_back(u);
    }
    
    std::vector dp1(n, std::vector<i64> C*C);

    for(int i = 1; i <= n; i++){
        for(int x = c[i]; x < C * C; x++){
        	chmax(dp1[i][x], dp1[i][x - c[i]] + w[i]);
        }

    	for(auto j : adj[i]){
    		for(int x = 0; x < C * C; x++){
    			chmax(adj[j][x],adj[i][x]);
    		}
    	}
    }
    
    std::vector dp2(n, std::vector(n, std::vector<i64>(C)));
    for(int s = 0; s < n; i++){
    	for(int i = 0; i < n; i++){
          for(int j = 0; j < 2; j++){
          	int d =  c[i] % c[s];
          	int g = std::gcd(c[s],d);
          	for(int rem = 0; rem < g; rem++){
          	    for(int j = 0; j < c[s] / g; j++){
                   int x = (j * d * rem) % c[s];
                   int y = (x - c[i] % c[s] + c[s]) % c[s];
                   int t = (y - (x - c[i])) / c[s];
                   chmax(dp2[s][i][x],dp2[s][i][y] + w[i] - i64(t)* w[s]);          
    	        }	
          	 } 	  
           }
           for(auto j : adj[i]){
           	for(int x = 0; x < c[s]; x++){
           		chmax(dp1[j][x],dp1[i][x]);
           	}
           }    	    
    	}
    }


    int q;
    std::cin >> q;

    for(int i = 0; i < q; i++){
    	int p, r;
    	std::cin >> p >> r;
    	p--;

    	if(r < C * C){
    		std::cout << dp1[p][r] << "\n";
    	}else{
    		std::cout << -1 << "\n";
    	}
    }
    

}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;

	while(t--){
		solve();
	}

	return 0;
}