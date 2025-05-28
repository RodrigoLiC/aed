class Solution {
      public:
      int lengthOfLIS(vector<int>& nums) {
          int s = nums.size();
          // dp[i] : indice del ultimo elemento de la secuencia de tamaño i
          vector<int> dp(s, -1);
          int maxLength = 1;
          dp[0] = 0;
          for (int i = 1; i < nums.size(); i++) {
              if (nums[i] > nums[dp[maxLength - 1]]) {
                  dp[maxLength] = i;
                  maxLength++;
              } else {
                  int l = 0;
                  int r = maxLength - 1;
                  while (l < r) {
                      int mid = (l + r) / 2;
                      if (nums[dp[mid]] < nums[i]) {
                          l = mid + 1;
                      } else {
                          r = mid;
                      }
                  }
                  dp[l] = i;
              }
          }
          return maxLength;
      }
};
