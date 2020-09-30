/*There are N piles of stones arranged in a row.  The i-th pile has stones[i] stones.

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
        */


Say the size of stones be N, since after each merging the number of piles will subtract (K - 1), and finally we get 1 pile, so it shows that only if (N-1) mod (K-1)==0 then it's possible to merge those piles into 1.
dp[l][i] represents the minimal cost to merge the piles in interval [i,i+l), here, we merge piles as much as possible. So, when l < 1+(K-1), we don't merge any piles, so dp[i][i+l] = 0; when 1+(K-1) <= l < 1+2(K - 1), we merge once; when 1+2(K-1) <= l < 1+3(K-1), we merge twice, and so on so forth.
Let's see for a certain interval length l, how can we get dp[l][i]. After all mergings, if we consider the leftmost pile in interval [i,i+l), then the status of this pile will show as below:

No merging happens in this pile, so it contains 1 original pile, let k = 1, then the cost is dp[k][i]+dp[l-k][i+k].
One merging happens in this pile, so it contains 1+(K-1) original piles, let k = 1+(K-1), then the cost is dp[k][i]+dp[l-k][i+k].
Two mergings happen in this pile, so it contains 1+2(K-1) original piles, let k = 1+2(K-1), then the cost is dp[k][i]+dp[l-k][i+k].
.......
When (l-1) mod (K-1)==0, we can see all piles in interval [i,i+l) can be finally merged into one pile, and the cost of the last merging is sum(stones[j]) for j in [i,i+l), regardless of the merging choices before the last one. And this "last cost" happens if and only if (l-1) mod (K-1)==0
int mergeStones(vector<int>& stones, int K)
{
    int N = (int)stones.size();
    if((N - 1) % (K - 1)) return -1;
    
    vector<int> sum(N + 1, 0);
    for(int i = 0; i < N; i++) sum[i + 1] = sum[i] + stones[i];
    
    vector<vector<int> > dp(N + 1, vector<int>(N, 0));
    for(int l = K; l <= N; l++)
        for(int i = 0; i + l <= N; i++)
        {
            dp[l][i] = 10000;
            for(int k = 1; k < l; k += K - 1)
                dp[l][i] = min(dp[l][i], dp[k][i] + dp[l - k][i + k]);
            if((l - 1) % (K - 1) == 0) dp[l][i] += sum[i + l] - sum[i];
        }
    return dp[N][0];
}
