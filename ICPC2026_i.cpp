#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

namespace rgs = std::ranges;
std::vector<int> minp, primes;

void sieve(int n){
	minp.assign(n + 1, 0);
	primes.clear();

	for(int i = 2; i <= n; i++){
		if(minp[i] == 0){
			minp[i] = i;
			primes.push_back(i);
		}

		for(auto p : primes){
			if(i * p > n){
				break;
			}
			minp[i * p] = p;
			if(p == minp[i]){
				break;
			}
		}
	}
}

long long floor_sum(long long n, long long m, long long a, long long b){
	long long ans = 0;
	if(a >= m){
		ans += (n - 1) * n * (a / m) / 2;
		a %= m;
	}
	if(b >= m){
		ans += n * (b / m);
		b %= m;
	}

	long long y_max = (a * n + b) / m, x_max = (y_max * m - b);
	if(y_max == 0) return ans;
	ans += (n - (x_max + a - 1) / a) * y_max;
	ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
	return ans;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, T;
	std::cin >> n >> T;
    
    std::vector<int> vals;
    for(int l = 1, r; l <= n; l = r + 1){
    	r = n / (n / l);
    	vals.push_back(n / l);
    }

    const int sqrtn = std::sqrt(n);
    sieve(sqrtn);

    const int m = vals.size();

    std::vector<int> f(m);

    for(int i = 0; i < m; i++){
        f[i] = vals[i] - 1;
    }

    auto id = [&](int x){
    	if(x <= sqrtn){
    		return m - x;
    	}else{
    		return n / x - 1; 
    	}
    };

    for(int i = 0; i < primes.size(); i++){
    	const int p = primes[i];
    	for(int j = 0; j < m && vals[i] >= p * p; j++){
    		assert(id(vals[j] / p) < m);
    		f[j] -= f[id(vals[j] / p)] - i;
    	}
    }

    while(T--){
    	I64 L;
    	std::cin >> L;

    	i64 x1 = 0, y1 = 0, x2 = 0, y2 = 1;

        auto check = [&](i64 x, i64 y, int t){
        	if(x > n || y > n){
        		return false;
        	}
        	i64 tot = 0;

        	auto calc = [&](int n){
                i64 res = 0;
                int r = std::min<i64>(n, (n * x + 1) / y);
                res += i64(n - r) * n;
                res += floor_sum(r, x, y, y - 1);
                return res;
        	};

        	tot += calc(n);

        	for(int l = 1, r; l <= n; l = r + 1){
        		r = n / (n /l);
        		int ps = f[id[r]];
        		if(l > 1){
        			ps -= f[id[l - 1]];
        		}
        		tot += calc(n / l) * ps;
        	}

        	int g = std::gcd(x, y);
        	tot++;
        	for(auto p : primes){
        		if(g % p == 0){
        			tot++;
        		}
        	}

            if(tot <= L){
            	return t == -1;
            }
            return t == 1;
        };

    	while (true){
           i64 d = 1;
           bool change = false

           while(check(x1 + x2 * d, y1 + y2 * d, -1){
           	    x1 += x2 * d;
           	    y1 += y2 * d;
           	    d *= 2;
           	    change = true;
           }

           while(d != 2){
           	   if(check(x1 + x2 * d, y1 + y2 * d, -1){
           	   	  x1 += x2 * d;
           	   	  y1 += y2 * d;
           	   	  change = true;
           	   }
           }

           d = 1;

           while(check(x1 * d + x2, y1 * d + y2, 1){
           	   x2 += x1 * d;
           	   y2 += y1 * d;
           	   d *= 2;
           	   change = true;
           }

           while(d != 2){
           	   if(check(x1 * d + x2, y1 * d + y2, 1){
           	   	  x2 += x1 * d;
           	   	  y2 += y1 * d;
           	   	  change = true;
           	   }
           }

           if(!change){
           	   break;
           }
    	}

        std::cout << y1 << " " << x1 << "\n";

    }

	return 0;
}