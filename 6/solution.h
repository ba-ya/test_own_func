#ifndef SOLUTION_H
#define SOLUTION_H

#include <algorithm>
#include <vector>
#include <QDebug>
// 题单
// https://github.com/EndlessCheng/codeforces-go/tree/master/leetcode

    using namespace std;

    ///----------------------相向双指针1, 5
    namespace TwoPointersTowards1 {
    // 15,三数之和等于0
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        // 递增
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n - 2; ++i) {
            int target = nums[i];
            // 跳过重复数字, 排过序了,只需要和上一个比较就好
            if (i > 0 && target == nums[i - 1]) {
                continue;
            }

            // 优化
            auto s = target + nums[i + 1] + nums[i + 2];
            if (s > 0) {
                break;
            }

            s = target + nums[n - 1] + nums[n - 2];
            if (s < 0) {
                continue;
            }


            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) {
                auto s = target + nums[left] + nums[right];
                if (s > 0) {
                    right--;
                } else if (s < 0) {
                    left++;
                } else {
                    res.push_back({target, nums[left], nums[right]});
                    //  for (left++; left < right && nums[left] == nums[left - 1]; left++);
                    left += 1;
                    while (left < right && nums[left] == nums[left - 1]) {
                        left += 1;
                    }
                    right -=1;
                    while (left < right && nums[right] == nums[right + 1]) {
                        right -=1;
                    }
                }
            }
        }
        return res;
    }

    // 16 给你一个长度为 n 的整数数组 nums 和 一个目标值 target。请你从 nums 中选出三个整数，使它们的和与 target 最接近。
    // 返回这三个数的和。
    // 假定每组输入只存在恰好一个解。
    int threeSumClosest(vector<int>& nums, int target) {
        int res;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int min_dis = INT_MAX;// std::numeric_limits<int>::max();
        for (int i = 0; i < n - 2; ++i) {
            int x = nums[i];
            // 优化3, nums[i - 1]和nums[i]结果一致
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }

            // 优化1, 之后所有组合都比s大,离target更远
            int s = x + nums[i + 1] + nums[i + 2];
            if (s > target) {
                if (s - target < min_dis) {
                    res = s;
                }
                break;
            }

            // 优化2, x增加,之后的组合比s大, 可能会有离target更近的情况
            s = x + nums[n - 1] + nums[n - 2];
            if (s < target) {
                if (target - s < min_dis) {
                    min_dis = target - s ;
                    res = s;
                }
                continue;
            }

            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                auto s = x + nums[left] + nums[right];
                if (s > target) {
                    if (s - target < min_dis) {
                        min_dis = s - target;
                        res = s;
                    }
                    right--;
                } else if (s < target) {
                    if (target - s < min_dis) {
                        min_dis = target - s;
                        res = s;
                    }
                    left++;
                } else {
                    return s;
                }
            }
        }
        return res;
    }

    // 2824.给你一个下标从 0 开始长度为 n 的整数数组 nums 和一个整数 target ，
    // 请你返回满足 0 <= i < j < n 且 nums[i] + nums[j] < target 的下标对 (i, j) 的数目。
    int countPairs(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int count = 0;
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            auto s = nums[left] + nums[right];
            if (s < target) {
                count += right - left;
                left++;
            } else {
                right--;
            }
            qDebug() << s
                     << "left:" <<  left << nums[left]
                     << ", right:" << right << nums[right]
                     << ", count:" << count;
        }
        return count;
    }

    // 18,4数之和等于target
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n - 3; ++i) {
            int x = nums[i];
            // 去重
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            // 优化1
            long long s = x + nums[i + 1] + nums[i + 2] + nums[i + 3];
            if (s > target) {
                break;
            }
            // 优化2
            s = x + nums[n - 1] + nums[n - 2] + nums[n - 3];
            if (s < target) {
                continue;
            }

            for (int j = i + 1; j < n - 2; ++j) {
                int y = nums[j];
                if ((j > i + 1) && nums[j] == nums[j - 1]) continue;// 去除重复数字
                if (x + y + nums[j + 1] + nums[j + 2] > target) break; // 优化1
                if (x + y + nums[n - 2] + nums[n - 1] < target) continue; // 优化2
                int left = j + 1;
                int right = n - 1;
                while (left < right) {
                    s = x + y + nums[left] + nums[right];
                    if (s > target) {
                        right--;
                    } else if (s < target) {
                        left++;
                    } else {
                        res.push_back({x, y, nums[left], nums[right]});
                        for (left++; left < right && nums[left] == nums[left - 1]; left++);
                        for (right--; left < right && nums[right] == nums[right + 1]; right--);
                    }
                }
            }
        }
        return res;
    }

    // 611三角形数量
    int triangleNumber(vector<int>& nums) {
        int count = 0;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        // 枚举最长边,
        for (int k = 2; k < n; k++) {
            int c = nums[k];
            int left = 0;
            int right = k - 1;// 关键,右边界如何限制
            while (left < right) {
                auto s = nums[left] + nums[right];
                if (s > c) {
                    count += right - left;
                    right--;
                } else {
                    left++;
                }
            }
        }
        return count;
    }
    };

    ///----------------------相向双指针2, 4
    namespace TwoPointersTowards2 {
    // 11给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
    int maxArea(vector<int>& height) {
        int ans = 0;
        int left = 0;
        int right = height.size() - 1;
        while (left < right) {
            int area = (right - left) * min(height[left], height[right]);
            ans = max(ans, area);
            height[left] < height[right] ? left++ : right--;
        }
        return ans;
    }

    // 42接雨水
    int trap(vector<int>& height) {
        // 方法1, 数组计算前后缀
        // 空间复杂度O(n)
#if 0
        int ans = 0;
        int n = height.size();
        vector<int> pre_max(n, 0);
        vector<int> suf_max(n, 0);
        // pre
        pre_max[0] = height[0];
        for (int i = 1; i < n; ++i) {
            pre_max[i] = std::max(pre_max[i - 1], height[i]);
        }
        // suf
        suf_max[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0 ; --i) {
            suf_fix[i] = max(suf_fix[i + 1], height[i]);
        }
        // 计算容量,
        for (int i = 0; i < n; i++) {
            ans += min(pre_max[i], suf_fix[i]) - height[i];
        }
        return ans;
#endif
        // 方法2,变量存储前后缀
        // 空间复杂度O(1)
        int n = height.size();
        int ans = 0;
        int left = 0;
        int right = n - 1;
        int pre_max = 0;
        int suf_max = 0;
        // 双向指针,判断条件都应该是left<right
        // < or <= 都可以, 等于的时候接不到水
        while (left < right) {
            pre_max = max(pre_max, height[left]);
            suf_max = max(suf_max, height[right]);
            if (pre_max < suf_max) {
                ans += pre_max - height[left];
                left++;
            } else {
                ans += suf_max - height[right];
                right--;
            }
        }
        return ans;
    }

    // 125验证回文串
    bool isPalindrome(string s) {
        // remove space
        auto new_end = remove_if(s.begin(), s.end(), [](unsigned char c) {
            return !isalnum(c);
        });
        s.erase(new_end, s.end());
        // to loweer
        transform(s.begin(), s.end(), s.begin(), ::tolower);

        int n = s.size();
        int left = 0;
        int right = n - 1;
        bool flag = true;
        while (left < right) {
            if (s.at(left) != s.at(right)) {
                flag = false;
                break;
            }
            left++;
            right--;
        }
        return flag;
    }

    // 1105给植物浇水
    int minimumRefill(vector<int>& plants, int capacityA, int capacityB) {
        int ans = 0;
        int n = plants.size();
        int left = 0;
        int right = n - 1;
        int left_a = capacityA;
        int left_b = capacityB;
        while(left <= right) {
            // A
            if (left_a < plants[left]) {
                left_a = capacityA;
                ans++;
            }
            left_a -= plants[left];
            left++;
            // B
            if (left_b < plants[right]) {
                left_b = capacityB;
                ans++;
            }
            left_b -= plants[right];
            right--;
        }
        if (left == right) {
            ans += plants[left] > max(left_a, left_b);
        }
        return ans;
    }

    }

    ///----------------------滑动窗口, 12
    namespace SlidingWindow {
    // 209长度最小的子数组(>=target)
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int ans = n + 1;
        int left = 0;
        int s = 0;
        for (int right = 0; right < n; ++right) {
            s += nums[right];
            // 满足条件就要更新一下ans,
            // 满足->不满足
            while (s >= target) {
                ans = min(ans, right - left + 1);
                s -= nums[left];
                left++;
            }
        }
        return ans <= n ? ans : 0;
    }

    // 3无重复字符的最长子串长度
    int lengthOfLongestSubstring(string s) {
        int ans = 0;
        int n = s.size();
        int left = 0;
        map<char, int> hash;
        for (int right = 0; right < n; ++right) {
            hash[s[right]] += 1;
            // 不满足->满足
            while (hash[s[right]] > 1) {
                hash[s[left]] -= 1;
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }

    // 713乘积小于K的子数组数目, 都是正数
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        // 或者while (prod >= k) {->while (left <= right && prod >= k)
        if (k <= 1) {
            return 0;
        }
        int n = nums.size();
        int ans = 0;
        int left = 0;
        int prod = 1;
        for (int right = 0; right < n; ++right) {
            prod *= nums[right];
            while (prod >= k) {
                prod /= nums[left];
                left++;
            }
            ans += right - left + 1;
        }
        return ans;
    }

    // 2958最多K个重复元素的最长子数组
    int maxSubarrayLength(vector<int>& nums, int k) {
        int ans = 0;
        int n = nums.size();
        // nums, count
        map<int, int> freq;
        int left = 0;
        for (int right = 0; right < n; ++right) {
            int id_r = nums[right];
            freq[id_r] += 1;
            while (freq[id_r] > k) {
                int id_l = nums[left];
                freq[id_l] -= 1;
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }

    // 2730找到最长的半重复子字符串, 参考
    int longestSemiRepetitiveSubstring(string s) {
        // 至少有一个字符
        int ans = 1;
        int same = 0;
        int left = 0;
        for (int right = 1; right < s.size(); ++right) {
            // 新加进来的判断一下
            if (s.at(right) == s.at(right - 1)) {
                same += 1;
            }
            if (same > 1) {
                left++;
                // 移除左边两个重复字符的第一个字符
                while (s[left] != s[left - 1]) {
                    left++;
                }
                same = 1;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }

    // 2779数组的最大美丽值,参考
    int maximumBeauty(vector<int>& nums, int k) {
        int ans = 0;
        sort(nums.begin(), nums.end());
        int left = 0;
        for (int right = 0; right < nums.size(); right++) {
            // while 不满足
            // 满足条件是 x+k >= y-k ->  y - x <= 2k,
            // 最左边的最大值大于最右边的最小值,即存在交集
            while (nums[right] - nums[left] > 2 * k) {
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }

    // 1004最大连续1的个数, own + 参考
    int longestOnes(vector<int>& nums, int k) {
        // 方法1, 根据翻转次数,自己写的
#if 0
        int ans = 0;
        int flip = 0;
        int left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            if (nums[right] == 0) {
                flip++;
            }
            if (flip > k) {
                while (left < right && nums[left] == 1) {
                    left++;
                }
                left++;
                flip--;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
#endif

        // 方法2, 转化为子数组内0的个数<=k, 参考
        int ans = 0;
        int cnt0 = 0;
        int left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            cnt0 += 1 - nums[right];
            while (cnt0 > k) {
                cnt0 -= 1 - nums[left];
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;

    }

    // 2962统计最大元素出现至少K次的子数组,
    // 思路有,但while和ans+的地方一开始写错了
    long long countSubarrays(vector<int>& nums, int k) {
        long long ans = 0;
        // target max elment
        auto it = max_element(nums.begin(), nums.end());
        int target = *it;
        // slide window
        long long left = 0;
        int cnt = 0;
        for (long long right = 0; right < nums.size(); ++right) {
            cnt += nums[right] == target;
            // 满足->不满足
            while (cnt == k) {
                cnt -= nums[left] == target;
                left++;
            }
            // 当前[left - 1, right]数组是满足条件的最小数组
            // 前面可以加上0,1,..., left - 2
            // 即0到left-1个
            ans += left;
        }
        return ans;
    }

    // 2302统计得分小于K的子数组数目
    long long countSubarrays(vector<int>& nums, long long k) {
        long long ans = 0;
        long long left = 0;
        long long score = 0;
        for (long long right = 0; right < nums.size(); ++right) {
            score += nums[right];
            while (score * (right - left + 1) >= k) {
                score -= nums[left];
                left++;
            }
            ans += right - left + 1;
        }
        return ans;
    }

    // 1658将x减到0的最小操作数, 参考
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        // 逆向思考,求满足 nums之和 - x 的最长子数组
        int target = reduce(nums.begin(), nums.end(), 0) - x;
        if (target < 0) {
            return -1;
        }

        int left = 0;
        int ans = -1;// 求最长,可以以-1作为起始值
        int sum = 0;
        for (int right = 0; right < n; ++right) {
            sum += nums[right];
            while (sum > target) {
                sum -= nums[left];
                left++;
            }
            if (sum == target) {
                ans = max(ans, right - left + 1);
            }
        }
        return ans < 0 ? -1 : n - ans;
    }

    // 1234最小替换子串得到平衡字符串, 参考(不太懂)
    int balancedString(string s) {
        // 记录的是待替换子串的出现次数
        int cnt['W' + 1]{};
        for (char c : s) {
            cnt[c]++;
        }

        int n = s.size();
        int target = n / 4;
        if (cnt['Q'] == target && cnt['W'] == target
            && cnt['E'] == target && cnt['R'] == target){
            return 0;
        }

        int ans = n, left = 0;
        for (int right = 0; right < n; right++) {
            cnt[s.at(right)]--;
            // 替换子串之外,即待替换子串都是正常的或者待填充的
            while (cnt['Q'] <= target && cnt['W'] <= target
                   && cnt['E'] <= target && cnt['R'] <= target) {
                ans = min(ans, right - left + 1);
                cnt[s[left]]++;
                left++;// 从替换子串挪一个字符到待替换子串
            }
        }
        return ans;

    }

    // 76最小覆盖子串,参考,
    // 写了版错误的,测试用例能通过144 / 268
    string minWindow(string s, string t) {
        auto is_covered = [](int cnt_s[], int cnt_t[]) {
            for (int i = 'a'; i <= 'z'; ++i) {
                if (cnt_s[i] < cnt_t[i]) {
                    return false;
                }
            }
            for (int i = 'A'; i <= 'Z'; ++i) {
                if (cnt_s[i] < cnt_t[i]) {
                    return false;
                }
            }
            return true;
        };
        // 128是asc码的数目
        int cnt_s[128]{0};
        int cnt_t[128]{0};
        for (char c : t) {
            cnt_t[c] += 1;
        }

        int ans_left = -1;
        int ans_right = s.size();
        int left = 0;
        for (int right = 0; right < s.size(); right++) {
            cnt_s[s.at(right)] += 1;
            // 笔误,之前两个参数都写成cnt_s了
            while (is_covered(cnt_s, cnt_t)) {
                if (right - left < ans_right - ans_left) {
                    ans_right = right;
                    ans_left = left;
                }
                cnt_s[s.at(left)] -= 1;
                left++;
            }
        }
        return ans_left < 0 ? "" : s.substr(ans_left, ans_right - ans_left + 1);
    }
    }

#endif // SOLUTION_H
