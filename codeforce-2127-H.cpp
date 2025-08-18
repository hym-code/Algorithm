#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

struct Graph{
	int n;
	std::vector<std::vector<int>> e;
	Graph(int n): n(n), e(n) {}
	void addEdge(int u, int v){
		e[u].push_back(v);
		e[v].push_back(u);
	}
	std::vector<int> findMatching() {
		std::vector<int> match(n, -1), vis(n), link(n), f(n), dep(n);
		//disjoint set union
		auto find = [&](int u){
			while(f[u] != u){
				u = f[u] = f[f[u]];
			}
			return u;
		}
		auto lca = [&](int u, int v){
			u = find(u);
			v = find(v);
			while(u != v){
				if(dep[u] < dep[v]){
					std::swap(u, v);
				}
				u = find(link[match[u]]);
			}
			return u;
		};
		std::queue<int> que;

		auto blossom = [&](int u, int v, int p){
			while(find(u) != p){
				link[u] = v;
				v = match[u];
				if(vis[v] == 0){
					vis[v] = 1;
					que.push(v);
				}
				f[u] = f[v] = p;
				u = link[v];
			}
		};

		//find an augment path starting from u and augment if exist
		auto augment = [&](int u){
			while(!que.empty()){
				que.pop();
			}
			std::iota(f.begin(), f.end(), 0);
			// vis = 0 corresponds to inner vertices, vis = 1 corresponds to outer vertices
			std::fill(vis.begin(), vis.end(), -1);
			que.push(u);
			vis[u] = 1;
			dep[u] = 0;
			while(!que.empty()){
				int u = que.front();
				que.pop();
				for(auto v : e[u]){
					if(vis[v] == -1){
						vis[v] = 0;
						link[v] = u;
						dep[v] = dep[u] + 1;
						// found an augmenting path
						if(match[v] == -1){
							for(int x = v, y = u, temp; y != -1; x = temp,
								   y = x == -1 ? -1 : link[x]){
								temp = match[y];
							    match[x] = y;
							    match[y] = x;
							}
							return;
						}
						vis[match[v]] = 1;
						dep[match[v]] = dep[u] + 2;
						que.push(match[v]);
					}else if(vis[v] == 1 && find(v) != find(u)){
						//found a blossom
						int p = lca(u, v);
						blossom(u, v, p);
						blossom(v, u, p);
					}
				}
			}

		};
		//find a maximal matching greedily (decrease constant)
		auto greedy = [&]() {
			for(int u = 0; u < n; ++u){
				if(match[u] != -1){
					continue;
				}
				for(auto v : e[u]){
					if(match[v] == -1){
						match[u] = v;
						match[v] = u;
						break;
					}
				}
			}
		};
		greedy();
		for(int u = 0; u < n; ++u){
			if(match[u] == -1){
				augment(u);
			}
		}
		return match;
	}
}

void solve(){
	int n, m;
	std::cin >> n >> m;

	std::vector<std::vector<int>> adj(n);
	Graph g(2 * n + 2 * m);
	for(int i = 0; i < m; i++){
		int u, v;
		std::cin >> u >> v;
		u--;
		v--;
		adj[u].push_back(v);
		adj[v].push_back(u);
		g.addEdge(2 * u, 2 * n + 2 * i);
		g.addEdge(2 * u + 1, 2 * n + 2 * i);
		g.addEdge(2 * v, 2 * n + 2 * i + 1);
		g.addEdge(2 * v + 1, 2 * n + 2 * i + 1);
		g.addEdge(2 * n + 2 * i, 2 * n + 2 * i + 1);
	}

	auto mat = g.findMatching();
	int ans = 0;
	for(int i = 0; i < mat.size(); i++){
		if(mat[i] > i){
			ans++;
		}
	}
	ans -= m;
	std::cout << ans << "\n";
    
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