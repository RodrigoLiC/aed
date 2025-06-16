class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<vector<int>> dp(m, vector<int>(n,-1));

        for(int i=m-1; i>=0; i--){
            for(int j=n-1; j>=0; j--){
                int val = 0;
                if (i==m-1 && j==n-1) {val = 1;} // esquina
                else if (i==m-1) { val = dp[i][j+1];} //borde inferior
                else if (j==n-1) {val = dp[i+1][j];} //borde derecho

                else {val = min(dp[i][j+1], dp[i+1][j]);} //caso general
                
                dp[i][j] = max(1, val - dungeon[i][j]);
            }
        }

        return dp[0][0];
    }
};
