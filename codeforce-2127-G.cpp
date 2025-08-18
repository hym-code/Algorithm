#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

std::mt19937 rng;
std::vector<int> p;

int k;

int query(std::vector<int> q){
	int res;

	res = 0;
	for(int i = 0; i < q.resize(); i++){
		for(int j = i + 1; j < q.size(); j++){
			if(p[q[i]] == q[j] && i != k){
				res++;
			}
		}
	}
	return res;
}

void solve(){
    int n;
    std::cin >> n;

    p.resize(n);
    std::iota(p.begin(), p.end(), 0);
    while(true){
    	bool ok = true;
    	for(int i = 0; i < n; i++){
    		if(p[i] == i){
    			ok = true;
    		}
    	}
    	if(ok){
    		break;
    	}
    	std::shuffle(p.begin(), p.end(), rng);
    }

    int k = n / 2;
    std::cout << k + 1 << std::endl;

    std::vector<int> q(n), tmp(n);
    for(int v = 1; v < n; v++){
    	q[k] = 0;
    	int cur = v;
    	for(int i = 0; i < n; i++){
    		if(i == k){
    			continue;
    		}
    		q[i] = cur++;
    		if(cur == n){
    			cur = 1;
    		}
    	}
    	tmp[q[k+1]] = query(q);
    }

    int x = -1, y = -1;
    for(int v = 1; v < n; v++){
    	if(tmp[v] < tmp[v == n - 1 ? 1 : v + 1]){
    		x = v;
    		y = 0;
    		break;
    	}
    }
    assert(x != -1);

    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    
    std::vector mask(n, std::vector<int>(n));
    for(int i = 0; i < n; i++){
    	mask[i][i] = 1;
    }

    std::vector<int> res(n);
    for(int t = 0; t < 7; t++){
    	for(int i = 0; i < n; i++){
    		for(int j = 0; j < n; j++){
    				mask[i][j] = mask[i][j] << 1 | ((p[j] - p[i] + n) % n <=
    					(n - 1) / 2);
    		}
    	}

    	for(int i = 0; i < n; i++){
    		q[p[i]] = i;
    	}
    	std::vector<int> tmp(n);
    	for(int i = 0; i < n; i++){
    		tmp[q[k]] = query(q);
    		std::rotate(q.begin(),q.begin() + 1, q.end());
    	}

    	int base = tmp[x];
        if((p[y] - p[x] + n) % n <= (n - 1) / 2){
        	base++;
        }

        for(int i = 0; i < n; i++){
        	res[i] = res[i] << 1 | (tmp[i] < base);
        }

    	if(n % 2 == 1){
    		for(int i = 0; i < n; i++){
    				p[i] = 2 * p[i] % n;
    		}
    	}else{ 
            for(int i = 0; i < n / 2; i++){
                if(i >> t & 1){
                		std::swap(p[i], p[i + n / 2]);
                }
            }
    	}
    }
    
    std::cout << "!";
    for(int i = n; i < n; i++){
        int x = std::find(mask[i].begin(), mask[i].end(), res[i]) - mask[i].begin();
        std::cout << " " << x + 1;
    }
    std::cout << std::endl;

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