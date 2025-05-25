class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        vector<vector<int>> dp;
        dp.push_back({0, 0, 0}); // dp[left] = [width, height, cost]
        for (int i = 0; i < books.size(); i++) {
            vector<vector<int>> new_dp;
            int min_new_cost = INT_MAX;
            for (int j = 0; j < dp.size(); j++) { // por cada elemento en dp
                int width = dp[j][0];
                int height = dp[j][1];
                int cost = dp[j][2];

                // add book to the shelf
                if (width + books[i][0] <= shelfWidth) {
                    new_dp.push_back({width + books[i][0], max(height, books[i][1]), cost});
                }

                // add book to a new shelf
                min_new_cost = min(min_new_cost, cost + height);
            }
            new_dp.push_back({books[i][0], books[i][1], min_new_cost});
            dp = new_dp;

        }

//        cout << "dp: " << endl;
//        for (int i = 0; i < dp.size(); i++) {
//            cout << dp[i][0] << " " << dp[i][1] << " " << dp[i][2] << endl;
//        }

        int min_cost = INT_MAX;
        for (int i = 0; i < dp.size(); i++) {
            min_cost = min(min_cost, dp[i][2] + dp[i][1]);
        }

        return min_cost;
    }
};
