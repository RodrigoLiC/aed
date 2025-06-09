class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;

        int rows = matrix.size();
        int cols = matrix[0].size();
        vector<vector<int>> dp(rows, vector<int>(cols, -1));

        int maxLength = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                maxLength = max(maxLength, aux(matrix, dp, i, j));
            }
        }
        return maxLength;
    }

    int aux(vector<vector<int>>& matrix, vector<vector<int>>& dp, int i, int j) {
        if (dp[i][j] != -1) return dp[i][j]; // memoizacion

        int rows = matrix.size();
        int cols = matrix[0].size();
        int maxLength = 1;

        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (auto& dir : directions) {
            int newRow = i + dir.first;
            int newCol = j + dir.second;

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                matrix[newRow][newCol] > matrix[i][j]) { // si es creciente
                maxLength = max(maxLength, 1 + aux(matrix, dp, newRow, newCol));
            }
        }

        dp[i][j] = maxLength;
        return maxLength;
    }
};
