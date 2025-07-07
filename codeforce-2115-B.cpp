#include <bits/stdc++.h>

using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned;
using u128 = unsigned __int128;

constexpr int inf = 1E9;

void solve(){
	int n, q;
	std::cin >> n >> q;

	std::vector<int> b(n);
	for(int i = 0; i < n; i++){
		std::cin >> b[i];
	}

	std::vector<int> p(n);
	std::iota(p.begin(),p.end(), 0);

	std::vector<std::array<int,3>> op(q);
        std::vector<int> u(n + q), v(n + q);
        for(int i = 0; i < q; i++){
        	int x, y, z;
        	std::cin >> x >> y >> z;
        	x--;
        	y--;
        	z--;
        	op[i] = {x, y, z};
        	u[n + i] = p[x];
        	v[n + i] = p[y];
        	p[z] = n + i;
        }

        std::vector<int> val(n + q);
        for(int i = 0; i < n; i++){
        	val[p[i]] = b[i];
        }

        for(int i = n + q - 1; i >= n; i--){
        	val[u[i]] = std::max(val[u[i]],val[i]);
        	val[v[i]] = std::max(val[v[i]],val[i]);
        }

        val.resize(n);
        auto a = val;

        for(auto [x, y, z] : op){
        	a[z] = std::min(a[x], a[y]);
        }
        if(a != b){
        	std::cout << -1 << "\n";
        	return;
        }

        for(int i = 0; i < n; i++){
        	std::cout << val[i] << " \n"[i == n - 1];
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

















        