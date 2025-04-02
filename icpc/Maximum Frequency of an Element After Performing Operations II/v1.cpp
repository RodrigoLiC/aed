class Solution {
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        sort(nums.begin(), nums.end());
        int ans1 = numIsInArray(nums, k, numOperations);
        int ans2 = numIsNotInArray(nums, k, numOperations);
        return max(ans1,ans2);
    }

    int numIsNotInArray(vector<int>& nums, int k, int numOperations){
        int best = 0;
        for (int left = 0; left < nums.size(); left++) {
            int l = left;
            int r = nums.size() - 1;
            while (l < r) {
                int mid = (l + r + 1) / 2;
                if (nums[mid] - nums[left] > 2 * k || mid - left + 1 > numOperations) {
                    r = mid - 1;
                } else {
                    l = mid;
                }
            }
            int right = r;
            best = max(best, right - left + 1);
        }
        return best;
    }

    int numIsInArray(vector<int>& nums, int k, int numOperations){
        unordered_set<int> valoresUnicos;
        int best = 0;
        for (int i = 0; i < nums.size(); i++) {
            valoresUnicos.insert(nums[i]);
        }
        for (int valor : valoresUnicos) {
            int l = 0;
            int r = nums.size() - 1;
            while (l < r) {
                int mid = (l + r) / 2;
                if (nums[mid] < valor - k) {
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
            int left = l;
            l = 0;
            r = nums.size() - 1;
            while (l < r) {
                int mid = (l + r + 1) / 2;
                if (nums[mid] > valor + k) {
                    r = mid - 1;

                } else {
                    l = mid;
                }
            }
            int right = r;
            int equals = findLastOccurrence(valor, nums) - findFirstOccurrence(valor, nums) + 1;

            best = max(best, min(equals + numOperations, right - left + 1));
        }
        return best;
    }

    int findFirstOccurrence(int num, vector<int>& nums){
        int l = 0;
        int r = nums.size() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (nums[mid] < num) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return l;
    }

    int findLastOccurrence(int num, vector<int>& nums){
        int l = 0;
        int r = nums.size() - 1;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (nums[mid] > num) {
                r = mid - 1;
            } else {
                l = mid;
            }
        }
        return r;
    }
};
