class Solution {
private:
    vector<vector<long long>> dp;
    vector<vector<long long>> dpSum;
    vector<vector<int>> lcp;
    int MOD = 1000000007;
public:
    int numberOfCombinations(string num) {
        int n = num.size();
        dp.resize(n, vector<long long>(n + 1, 1));
        dpSum.resize(n, vector<long long>(n + 1, 1));
        lcp.resize(n, vector<int>(n, 0));

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (num[i] == num[j]) {
                    if (i + 1 < n && j + 1 < n) {
                        lcp[i][j] = 1 + lcp[i + 1][j + 1];
                    } else {
                        lcp[i][j] = 1;
                    }
                } else {
                    lcp[i][j] = 0;
                }
            }
        }
        
        if (num[0] == '0') {
            return 0;
        }

        for (int row = 1; row < n; row++) {
            for (int col = row + 1; col <= n; col++) {
                waysWhenLast(row, col, num);
            }
        }
        return dpSum[n - 1][n];
    }

    void waysWhenLast(int begin, int end, string &num) {
        if (num[begin] == '0') {
            dp[begin][end] = 0;
            if (begin > 0){
                dpSum[begin][end] = dpSum[begin-1][end];
            } else {
                dpSum[begin][end] = 0;
            }
            return;
        }

        long long total;
        int size = end - begin;
        int prevBegin = begin - size;

        if (prevBegin >= 0) {
            total = (dpSum[begin - 1][begin] - dpSum[prevBegin][begin] + MOD) % MOD;
        } else {
            total = dpSum[begin - 1][begin];
        }

        if (prevBegin >= 0){
            if (greaterEqual(begin, end, prevBegin, begin, num)){
                total += dp[prevBegin][begin];
            }
        }
        dp[begin][end] = total % MOD;
        dpSum[begin][end] = (dpSum[begin-1][end] + total) % MOD;
    }

    bool greaterEqual(int left1, int right1, int left2, int right2, string& num) {
        int skip = lcp[left1][left2];

        if (skip >= right1 - left1) {
            return true;
        } else {
            if (num[left1 + skip] > num[left2 + skip]) {
                return true;
            }
            if (num[left1 + skip] < num[left2 + skip]) {
                return false;
            }
        }
        //cout << "error";
        return true;
    }

    void PrintDP();
};
