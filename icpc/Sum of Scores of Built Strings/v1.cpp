class Solution {
public:
    long long sumScores(string s) {
        int n = s.size();
        vector<int> lcp(n, 0);
        int subLeft = 0;
        int subRight = 0;
        for (int i = 1; i < n; i++) {

            if (i < subRight){
                if (lcp[i - subLeft] < subRight - i) { // dentro del substring
                    lcp[i] = lcp[i - subLeft];
                } else { // al menos (subRight - i) coincidencias
                    lcp[i] = subRight - i;
                }
            }
            // avanzar mientras coincida
            while (lcp[i] < n && s[lcp[i]] == s[i + lcp[i]]) {
                lcp[i]++;
            }
            if (lcp[i] > 0) {
                subLeft = i;
                subRight = i + lcp[i];
            }
        }
        
        long long total = n; // primer caracter
        for (int i = 0; i < n; i++) {
            total += lcp[i];
        }
        return total;
    }
};
