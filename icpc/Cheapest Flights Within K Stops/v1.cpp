class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // adj list
        vector<vector<pair<int,int>>> edges(n);
        for (auto f : flights) {
            edges[f[0]].push_back({f[1],f[2]});
        }

        queue<vector<int>> q;
        for (auto e : edges[src]) {
            q.push({e.first, e.second, 0}); // ciudad, costo, stops
        }

        vector<int> best(n, -1);
        best[src] = 0;
        vector<int> curr;
        while (!q.empty()){
            curr = q.front();
            int prev = best[curr[0]];
            if (best[curr[0]] == -1) best[curr[0]] = curr[1];
            else best[curr[0]] = min(best[curr[0]], curr[1]);
            if (curr[2] < k && prev != best[curr[0]]) {
                for (auto e : edges[curr[0]]) {
                    q.push({e.first, e.second + curr[1], curr[2]+1});
                }
            }
            q.pop();
        }


        return best[dst];
    }
};
