class Solution {
public:
    int MOD = 1e9 + 7;
    int base1 = 100003;
    int base2 = 100019;
    vector<long long> powers1 = {1};
    vector<long long> powers2 = {1};

    bool check3(int len, const vector<vector<int>>& paths) { // O(lgn)
        unordered_set<long long> set1;
        unordered_set<long long> set2;
        long long hashValue1 = 0;
        long long hashValue2 = 0;
        int exp = len - 1;
        while (powers1.size() < len) {
            powers1.push_back((powers1.back() * base1) % MOD);
            powers2.push_back((powers2.back() * base2) % MOD);
        }
        for (int j = 0; j < len; j++) {
            hashValue1 = (hashValue1 * base1 + paths[0][j]) % MOD;
            hashValue2 = (hashValue2 * base2 + paths[0][j]) % MOD;
        }
        set1.insert(hashValue1);
        set2.insert(hashValue2);
        for (int j = 0; j < paths[0].size() - len; j++) { // O(n)
            long long newHash1 = ((hashValue1 - paths[0][j] * powers1[exp])%MOD + MOD) % MOD;
            long long newHash2 = ((hashValue2 - paths[0][j] * powers2[exp])%MOD + MOD) % MOD;
            hashValue1 = (newHash1 * base1 + paths[0][j + len] + MOD) % MOD;
            hashValue2 = (newHash2 * base2 + paths[0][j + len] + MOD) % MOD;
            set1.insert(hashValue1);
            set2.insert(hashValue2);
        }

        for (int i = 1; i < paths.size(); i++) { // O(m)
            hashValue1 = 0;
            hashValue2 = 0;
            for (int j = 0; j < len; j++) {
                hashValue1 = (hashValue1 * base1 + paths[i][j]) % MOD;
                hashValue2 = (hashValue2 * base2 + paths[i][j]) % MOD;
            }

            unordered_set<long long> current1;
            unordered_set<long long> current2;
            for (int j = 0; j < paths[i].size() - len + 1; j++) { // O(n)
                if (set1.find(hashValue1) != set1.end() && set2.find(hashValue2) != set2.end()) {
                    current1.insert(hashValue1);
                    current2.insert(hashValue2);
                }
                if (j + len < paths[i].size()) {
                    long long newHash1 = ((hashValue1 - paths[i][j] * powers1[exp])%MOD + MOD) % MOD;
                    long long newHash2 = ((hashValue2 - paths[i][j] * powers2[exp])%MOD + MOD) % MOD;
                    hashValue1 = (newHash1 * base1 + paths[i][j + len] + MOD) % MOD;
                    hashValue2 = (newHash2 * base2 + paths[i][j + len] + MOD) % MOD;
                }
            }
            if (current1.empty()){return false;}
            if (current2.empty()){return false;}
            swap(set1, current1);
            swap(set2, current2);
        }
        return true;
    }

    int longestCommonSubpath(int n, vector<vector<int>>& paths) {
        int l = 0;
        int r = INT_MAX;
        for (const auto& path : paths) {
            r = min(r, static_cast<int>(path.size()));
        }
        int currentLongest = 0;

        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (check3(mid, paths)) {
                l = mid;
                currentLongest = mid;
            } else {
                r = mid - 1;
            }
        }

        return currentLongest;
    }
};
