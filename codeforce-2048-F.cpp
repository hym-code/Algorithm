#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

constexpr int K = 61;

void solve(){
	int n;
	std::cin >> n;

	std::vector<i64> a(n), b(n);
	for(int i = 0; i < n; i++){
		std::cin >> a[i];
	}
	for(int i = 0; i < n; i++){
		std::cin >> b[i];
	}

	std::vector<int> lc(n, -1), rc(n, -1);
	std::vector<int> stk;
	for(int i = 0; i < n; i++){
		while(!stk.empty() && b[i] < b[stk.back()]){
			rc[stk.back()] = lc[i];
			lc[i] = stk.back();
			stk.pop_back();
		}
		stk.push_back(i);
	}

	while(stk.size() > 1){
		int x = stk.back();
		stk.pop_back();
		rc[stk.back()] = x;
	}

	auto dfs = [&](this auto &&self, int x, int l, int r) -> std::array<i64, K> {
          if(x == -1){
              return {};
          }
          auto L = self(lc[x], l , x);
          auto R = self(rc[x], x + 1, r);
          std::array<i64, K> f {};
          int i = 0, j = 0;
          f[0] = std::max(L[0], R[0]);
          while(i + j + 1 <  K){
          	if(L[i] > R[j]){
          			i++;
          	}else{
          		  j++;
          	}
          	f[i + j] = std::max({L[i], R[j], a[x]});
          }

          for(int i = 1; i < K; i++){
          	f[i] = std::min(f[i], f[i - 1] / b[x]);
          }
          return f;
	};
	auto f = dfs(stk[0], 0, n);

	int ans = std::find(f.begin(), f.end(), 0) - f.begin();
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