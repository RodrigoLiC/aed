class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        int x = nums1.size();
        int y = nums2.size();
        
        int lx = 0;
        int rx = x - 1;
        int ly = 0;
        int ry = y - 1;

        while (lx + 1 < rx && ly + 1 < ry) {
            int midx = (lx + rx) / 2;
            int midy = (ly + ry) / 2;

            if (nums1[midx] == nums2[midy]) {
                if ((rx + ry - lx - ly) % 2 == 0) {
                    return (nums1[midx] + min(nums1[midx+1], nums2[midy+1])) / 2.0;
                } else {
                    return nums1[midx];
                }
            }
            if (nums1[midx] < nums2[midy]) {
                if (nums1[midx + 1] < nums2[midy + 1]) {
                    int limit = min(midx - lx, ry - midy);
                    lx += limit;
                    ry -= limit;
                }
                else {
                    int limit = min(midx - lx, rx - midx);
                    lx += limit;
                    rx -= limit;
                }
            }
            else {
                if (nums1[midx + 1] < nums2[midy + 1]) {
                    int limit = min(midy - ly, ry - midy);
                    ly += limit;
                    ry -= limit;
                }
                else {
                    int limit = min(midy - ly, rx - midx);
                    ly += limit;
                    rx -= limit;
                }
            }
        }
        vector<int> nums3;
        vector<int> nums4;

        if (nums1.size() < nums2.size()) {
            for (int i = lx; i <= rx; i++) {
                nums3.push_back(nums1[i]);
            }
            for (int i = ly; i <= ry; i++) {
                nums4.push_back(nums2[i]);
            }
        } else {
            for (int i = ly; i <= ry; i++) {
                nums3.push_back(nums2[i]);
            }
            for (int i = lx; i <= rx; i++) {
                nums4.push_back(nums1[i]);
            }
        }
        // Insertar nums4 en nums3
        for (int e : nums4) {
            for (int j = 0; j < nums3.size(); j++) {
                if (e < nums3[j]) {
                    nums3.insert(nums3.begin() + j, e);
                    break;
                }
            }
            if (nums3.size() == 0) {
                nums3.push_back(e);
            }
            else if (e >= nums3[nums3.size() - 1]) {
                nums3.push_back(e);
            }
        }

        // Calcular la mediana
        int n = nums3.size();
        if (n % 2 == 0) {
            return (nums3[n / 2 - 1] + nums3[n / 2]) / 2.0;
        } else {
            return nums3[n / 2];
        }
    }
};
