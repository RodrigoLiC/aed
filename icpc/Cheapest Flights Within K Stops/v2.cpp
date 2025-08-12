class Solution {
public:
    struct Estado {
        int ciudad;
        int costo;
        int stops;

        Estado(int ciudad_, int costo_, int stops_) : ciudad(ciudad_), costo(costo_), stops(stops_) {}
    };

    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // adj list
        vector<vector<pair<int,int>>> edges(n);
        for (auto f : flights) {
            edges[f[0]].push_back({f[1],f[2]});
        }

        queue<Estado> q;
        vector<int> best(n, -1);
        best[src] = 0;
        for (auto e : edges[src]) {
            q.emplace(e.first, e.second, 0); // ciudad, costo, stops
        }

        while (!q.empty()){
            Estado curr = q.front();
            int& b = best[curr.ciudad];
            int prev = b;
            if (b == -1 || curr.costo < b) {
                b = curr.costo;
                if (curr.stops < k) {
                    for (auto e : edges[curr.ciudad]) {
                        q.emplace(e.first, e.second + curr.costo, curr.stops+1);
                    }
                }
            }
            q.pop();
        }

        return best[dst];
    }
};
