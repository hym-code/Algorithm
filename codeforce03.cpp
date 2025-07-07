#include <bits/stdc++.h>

using u64 = unsigned long long;
using i64 = long long;
using u32 = unsigned;
using u128 = __int128;

template <typename T>
struct Fenwick{
	int n;
	std::vector<T> a;

	Fenwick(int n_ = 0){
		init(n_);
	}

	void init(int n_){
		n = n_;
		a.assign(n,T{});
	}

	void add(int x, const T &v){
		for(int i = x + 1; i <= n; i += i & - i){
			a[i - 1] = a[i - 1] + v;
		}
	}

	T sum (int x){
		T ans{};
		for(int i = x; i > 0; i -= i & - i){
			ans = ans + a[i - 1];
		}
		return ans;
	}

	T rangSum(int l, int r){
		return sum(r) - sum(l);
	}

	int select(const T &k){
		int x = 0;
		T cur{};
		for(int i = 1 << std::__lg(n); i; i /= 2){
			if(x + i <= n && cur + a[x + i - 1] <= k){
				x += 1;
				cur = cur + a[x - 1];
			}
		}
		return x;
	}
}



















void solve(){
	i64 n;
	std::cin >> n;
    
    std::vector<int> a(n), b(n)

    for(int i = 1; i <= n; i++){
    	std::cin >> a[i];
    }

    for(int i = 1; i <= n; i++){
    	std::cin >> b[i];
    }

    std::vector<int> L(n, -1), R(n, -1);
    //笛卡尔树
    std::vector<int> stack;
    std::deque<int> queue;

    for(int i = 1; i <= n; i++){
    	while(!queue.Empty() && a[i] < stack.back()){

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