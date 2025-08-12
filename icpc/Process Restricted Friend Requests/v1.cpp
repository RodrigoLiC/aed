class Solution {
public:
    struct Grupo {
        set<int> amigos;
        set<int> enemigos;

        void unir_con(const Grupo& otro) {
            amigos.insert(otro.amigos.begin(), otro.amigos.end());
            enemigos.insert(otro.enemigos.begin(), otro.enemigos.end());
        }

        bool fail_con(const Grupo& otro) {
            for (int enemigo : enemigos) {
                if (otro.amigos.count(enemigo)) {
                    return true;
                }
            }
            for (int enemigo : otro.enemigos) {
                if (amigos.count(enemigo)) {
                    return true;
                }
            }
            return false;
        }
    };

    struct DSU {
        vector<int> parent, rank;

        DSU(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            for (int i = 0; i < n; i++) parent[i] = i;
        }

        int find(int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        }

        int unite(int x, int y) {
            int rx = find(x);
            int ry = find(y);
            if (rx == ry) return rx;

            if (rank[rx] < rank[ry]) {
                parent[rx] = ry;
                return ry;
            } else if (rank[rx] > rank[ry]) {
                parent[ry] = rx;
                return rx;
            } else {
                parent[ry] = rx;
                rank[rx]++;
                return rx;
            }
        }
    };


    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        vector<bool> ans;
        vector<Grupo> grupos(n);
        DSU dsu(n);

        for (int i = 0; i < n; ++i) {
            grupos[i].amigos.insert(i);
        }

        for (auto enem : restrictions) {
            grupos[enem[0]].enemigos.insert(enem[1]);
            grupos[enem[1]].enemigos.insert(enem[0]);
        }

        for (auto q : requests) {
            int root1 = dsu.find(q[0]);
            int root2 = dsu.find(q[1]);
            if (grupos[root1].fail_con(grupos[root2])) {
                ans.push_back(false);
            }
            else {
                int newRoot = dsu.unite(root1, root2);
                grupos[newRoot].unir_con(grupos[root1]);
                grupos[newRoot].unir_con(grupos[root2]);
                ans.push_back(true);
            }
        }

        return ans;
    }
};
