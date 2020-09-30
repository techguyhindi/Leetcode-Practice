There are N piles of stones arranged in a row.  The i-th pile has stones[i] stones.

A move consists of merging exactly K consecutive piles into one pile, and the cost of this move is equal to the total number of stones in these K piles.

Find the minimum cost to merge all piles of stones into one pile.  If it is impossible, return -1.


 let k = k as usize;
        if (stones.len() - 1) % (k - 1) != 0 {
            return -1;
        }
        let mut dp = vec![vec![0; stones.len()]; stones.len()];
        let sum = {
            let mut sum = Vec::with_capacity(stones.len() + 1);
            sum.push(0);
            let mut cur = 0;
            sum.extend(stones.iter().map(|n| {
                cur = cur + n;
                cur.clone()
            }));
            sum
        };
        for len in (k - 1)..stones.len() {
            for i in 0..(stones.len() - len) {
                let j = i + len;
                dp[i][j] = (i..j)
                    .step_by(k - 1)
                    .map(|l| dp[i][l] + dp[l + 1][j])
                    .min()
                    .unwrap();
                if (j - i) % (k - 1) == 0 {
                    dp[i][j] += sum[j + 1] - sum[i];
                }
            }
        }
        dp[0][stones.len() - 1]
        
        
        
        // I have added RUST Solution
        // I need C++ solution

        // here is the C++ solution
         class Solution {
public:
    int mergeStones(vector<int>& stones, int K) {
        if (((int)stones.size() - K) % (K - 1) != 0) return -1;
        
        vector<vector<int>> dp(stones.size(), vector<int>(stones.size(), 0));
        vector<int> prefix(stones.size() + 1, 0);
        for (int i = 1; i <= stones.size(); ++i) {
            prefix[i] = stones[i - 1] + prefix[i - 1];
        }
        
        for (int j = 1; j < dp.size(); j++) {
            int i = 0;
            int k = j;
            while(k < dp.size()) {
                for (int m = i, n = 1; m < k; m += (K - 1), n += (K - 1)) {
                    dp[i][k] = min(dp[i][k] == 0 ? numeric_limits<int>::max() : dp[i][k], 
                                   dp[i][m] + dp[i + n][k]);
                }

                if (j % (K - 1) == 0) {
                    dp[i][k] += prefix[k + 1] - prefix[i];
                }
                i++;
                k++;
            }
        }
        return dp[0][(int)stones.size() - 1];
    }
};
