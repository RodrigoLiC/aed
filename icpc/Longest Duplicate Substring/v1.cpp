class Solution {
public:
    int MOD = 1e9 + 7;
    int base = 26;
    long long power;

    long long calculateHash(const string& s, int start, int len) {
        long long hashValue = 0;
        power = 1;
        for (int i = 0; i < len; i++) {
            hashValue = (hashValue * base + (s[start + i] - 'a')) % MOD;
            if (i != 0) {
                power = (power * base) % MOD;
            }
        }
        return hashValue;
    }

    long long roll(long long oldHash, char oldChar, char newChar) {
        long long newHash = (oldHash - (oldChar - 'a') * power + MOD) % MOD;
        newHash = (newHash * base + (newChar - 'a')) % MOD;
        return (newHash + MOD) % MOD;
    }

    string findDupSubstringOfSize(string& s, int len, int n) {
        unordered_map<long long, int> hashMap;
        long long newHash = calculateHash(s, 0, len);
        hashMap[newHash] = 0;
        for (int i = 1; i <= n - len; i++) {
            newHash = roll(newHash, s[i - 1], s[i + len - 1]);
            if (hashMap.find(newHash) != hashMap.end()) {
                int start = hashMap[newHash];
                string candidate = s.substr(start, len);
                string current = s.substr(i, len);
                if (candidate == current) {
                    return candidate;
                }
            } else {
                hashMap[newHash] = i;
            }
        }
        return "";
    }

    string longestDupSubstring(string s) {
        int n = s.size();
        int l = 0;
        int r = n - 1;

        string currentLongest;
        int currentLongestSize = 0;

        while (l < r) {
            int mid = (l + r + 1) / 2;
            string ans = findDupSubstringOfSize(s, mid, n);
            if (!ans.empty()) {
                l = mid;
                if (ans.size() > currentLongestSize) {
                    currentLongest = ans;
                }
            } else {
                r = mid - 1;
            }
        }
        return currentLongest;
    }
};
