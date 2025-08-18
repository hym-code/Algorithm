#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

void solve(){
   int n, k;
   std::cin >> n >> k;

   std::vector<std::array<int, 2>> a(n);
   for(int i = 0; i < n; i++){
      std::cin >> a[i][0];
   }

   i64 ans = 0;
   for(int i = 0; i < n; i++){
      std::cin >> a[i][1];
      if(a[i][1] < a[i][0]){
         std::swap(a[i][1], a[i][0]);
      }
      ans += std::abs(a[i][1] - a[i][0]);
   }
   std::sort(a.begin(), a.end());

   int min = 2E9;
   for(int i = 1; i < n; i++){
      min = std::min(min, 2 * std::max(0, a[i][0] - a[i - 1][1]));
   }
   ans += min;
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