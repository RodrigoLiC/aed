class Solution {
public:
    struct Estado {
        int ciudad;
        int costo;
        int stops;

        Estado(int ciudad_, int costo_, int stops_) : ciudad(ciudad_), costo(costo_), stops(stops_) {}

        bool operator<(const Estado& otro) const {
            // menor cantidad de paradas tiene más prioridad
            if (stops != otro.stops) return stops > otro.stops;
            return costo > otro.costo;  // menor costo tiene mayor prioridad
        }
    };

    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // adj list
        vector<vector<pair<int,int>>> edges(n);
        for (auto f : flights) {
            edges[f[0]].push_back({f[1],f[2]});
        }

        priority_queue<Estado> pq;
        vector<int> best(n, -1);
        best[src] = 0;
        for (auto e : edges[src]) {
            pq.emplace(e.first, e.second, 0); // ciudad, costo, stops
        }

        while (!pq.empty()){
            Estado curr = pq.top();
            int& b = best[curr.ciudad];
            int prev = b;
            if (b == -1 || curr.costo < b) {
                b = curr.costo;
                if (curr.stops < k) {
                    for (auto e : edges[curr.ciudad]) {
                        pq.emplace(e.first, e.second + curr.costo, curr.stops+1);
                    }
                }
            }
            pq.pop();
        }
        
        return best[dst];
    }
};
