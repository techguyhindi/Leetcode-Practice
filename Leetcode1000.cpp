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
