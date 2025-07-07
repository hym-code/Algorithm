#include <bits/stdc++.h>

using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned;
using u128 = __int128;

void solve(){
	int n;
	std::cin >> n;

	std::vector<int> a(n), b(n);

	for(int i = 0; i < n; i++){
		std::cin >> a[i];
	}

    for(int i = 0; i < n; i++){
		std::cin >> b[i];
	}

	std::vector<int> prea(n + 1), preb(n + 1), sufa(n + 1), sufb(n + 1);
	for(int i = 0; i <= n; i++){
		prea[i + 1] = std::gcd(prea[i], a[i]);
		preb[i + 1] = std::gcd(preb[i], b[i]);
	}
	for(int i = 0; i <= n; i++){
		sufa[i + 1] = std::gcd(sufa[i], a[i]);
		sufb[i + 1] = std::gcd(sufb[i], b[i]);
	}

	std::vector<std::array<int, 2>> fa {{0, 0}}, fb {{0, 0}};
	std::vector<std::array<int, 2>> pa, pb;
	for(int i = 0; i <= n; ++){
		if(i == n || prea[i] != prea[i + 1]){
			pa.push_back({prea[i], i});
		}
		if(i == n || preb[i] != preb[i + 1]){
			pb.push_back({preb[i], i});
		}
	}

	for(int r = 1; r <= n; r++){
	    int t = a[r - 1];
	    for(int i = fa.size() - 1; i >= 0; i--){
	    	t = std::gcd(t, fa[i][0]);
	    	fa[i][0] = t;
	    }
	    t = b[r - 1];
	    for(int i = fb.size() - 1; i >= 0; i--){
	    	t = std::gcd(t, fb[i][0]);
	    	fb[i][0] = t;
	    }
	    fa.push_back({0, r});
	    fb.push_back({0, r});
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