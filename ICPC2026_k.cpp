#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

namespace rgs = std::ranges;


void solve(){
	int n;
	std::cin >> n;

	std::string s;
	std::cin >> s;

	s = 'L' + s + 'R';

	std::vector<int> a(n + 2);
	for(int i = 1; i <= n; i++){
		std::cin >> a[i];
	}

	std::set<int> f0, f1, f01;
	for(int i = 0; i <= n; i++){
		f1.insert(i);
	}
	for(int i = 1; i <= n + 1; i++){
		int t0 = -2, t1 = -2;

		for(auto j : {i - 1, i - 2}){
			if(j < 0){
				continue;
			}

			int v = -2;
			if(s[j] == 'L'){
				if(s[i] == 'L'){
					if(a[i] - a[j] == i - j - 1){
					   v = -1;
					}
				} else {
					v = a[i] + a[j] + i - j - 1;
					if(v < 0){
						v = -2;
					}
				}
			} else {
                  if(s[i] == 'L'){
                  	 v = a[i] + a[j] + (i - j - 1);
                  	 if(v < 0){
                  	 	v = -2;
                  	 }
                  } else{
                  	  if(a[j] - a[i] == i - j - 1){
                  	  	v = -1
                  	  }
                  }
 			}

 			if(j == i - 2){
 				t0 = v;
 			} else{
 				t1 = v;
 			}
		}

		std::vector<std::pair<int, int>> spe;;
		for(auto c : {t0, t1}){
			if(c < 0){
				continue;
			}
			int mask = 0;
			if(f01.contains(c) || f1.contains(c)){
				mask |= 1;
			}
			if((f01.contains(c) || f0.contains(c)) && (t0 == c || t0 == -1)) ||
			    (f01.contains(c) || f1.contains(c)) && (t1 == c || t1 == -1) {
				mask |= 2;
			}
			spe.emplace_back(c, mask);
		}

		if(t0 == -1){
			if(t1 == -1){
				if(f1.size() > f01.size()){
					std::swap(f1, f01);
				}
				f01.merge(f1);
				f1 = std::move(f0);
			} else {
				std::swap(f0, f1);
			}
		} else {
			if(t1 == -1){
				if(f1.size() > f01.size()){
					std::swap(f1, f01);
				}
				f01.merge(f1);
				f0.clear();
			} else {
				f0 = std::move(f01);
	            if(f1.size() > f0.size()){
					std::swap(f1, f0);
				}
				f0.merge(f1);
			}
		}

		for(auto [c, mask] : spe){
			f0.erase(c);
			f1.erase(c);
			f01.erase(c);

			if(mask == 1){
				f0.insert(c);
			}else if (mask == 2){
				f1.insert(c);
			} else if(mask == 3){
				f01.insert(c);
			}
		}
	}

	if(f1.empty() && f01.empty()){
		std::cout << -1 << "\n";
		return;
	}

	int c;
	if(!f1.empty()){
		c = *f1.begin();
	} else {
		c = *f01.begin();
	}
    
    std::vector<int> dp(n + 2, -1);
    dp[0] = 0;
	for(int i = 1; i <= n + 1; i++){

		for(auto j : {i - 1, i - 2}){
			if(j < 0){
				continue;
			}

			int v = -2;
			if(s[j] == 'L'){
				if(s[i] == 'L'){
					if(a[i] - a[j] == i - j - 1){
					   v = -1;
					}
				} else {
					v = a[i] + a[j] + i - j - 1;
					if(v < 0){
						v = -2;
					}
				}
			} else {
                  if(s[i] == 'L'){
                  	 v = a[i] + a[j] + (i - j - 1);
	                 if(v < 0){
	                  	 v = -2;
	                  }
                  } else{
                  	  if(a[j] - a[i] == i - j - 1){
                  	  	v = -1
                  	  }
                  }
 			}

 			if((v == c || v == -1) && dp[j] != -1){
 				dp[i] = j;
 			}
		}
    }

    std::string ans(n, '1');
    for(int i = dp[n + 1]; i > 0; i = dp[i]){
    	ans[i - 1] = '0';
    }

    std::cout << ans << "\n";

}

int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int T;
	std::cin >> T;

	while(T--){
		solve();
	}

	return 0;
}