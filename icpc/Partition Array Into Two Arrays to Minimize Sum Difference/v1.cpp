class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        int nn = nums.size();
        int n = nn / 2;

        int doubleSumNums = 0;
        for (int i = 0; i < nums.size(); i++) {
            nums[i] *= 2;
            doubleSumNums += nums[i];
        }

        vector<vector<int>> left(n + 1, vector<int>());
        vector<vector<int>> right(n + 1, vector<int>());

        left[0].push_back(0);
        right[0].push_back(0);

        for (int num = 0; num < n; num++) {
            for (int row = n+1; row > 0; row--) {
                for (auto ele : left[row - 1]) {
                    left[row].push_back(ele + nums[num]);
                }
            }
        }

        for (int num = n; num < nn; num++) {
            for (int row = n+1; row > 0; row--) {
                for (auto ele : right[row - 1]) {
                    right[row].push_back(ele + nums[num]);
                }
            }
        }

        for (int row = 0; row <= n; row++) {
            sort(left[row].begin(), left[row].end());
            sort(right[row].begin(), right[row].end());
        }

//        cout << "Left: " << endl;
//        for (int row = 0; row <= n; row++) {
//            cout << "Row: " << row << " ";
//            for (auto ele : left[row]) {
//                cout << ele << " ";
//            }
//            cout << endl;
//        }
//        cout << "Right: " << endl;
//        for (int row = 0; row <= n; row++) {
//            cout << "Row: " << row << " ";
//            for (auto ele : right[row]) {
//                cout << ele << " ";
//            }
//            cout << endl;
//        }

        int ans = INT_MAX;
        for(int i = 0; i < n; i++){
            for (auto num : left[i]) {
                int target = doubleSumNums/2 - num;
                int low = 0;
                int high = right[n - i].size() - 1;
                while (low < high) { // find >=
                    int mid = (low + high) / 2;
                    if (right[n - i][mid] < target) {
                        low = mid + 1;
                    }
                    else {
                        high = mid;
                    }
                }
                if (abs(right[n - i][low] - target) < ans) {
                    ans = abs(right[n - i][low] - target);
                }
            }
        }

        return ans;
    }
};
