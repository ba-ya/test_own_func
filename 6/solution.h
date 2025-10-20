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

    ///----------------------二分查找1, 11
    namespace BinarySearch1 {
    // 34在排序数组查找元素第一个和最后一个位置
    vector<int> searchRange(vector<int>& nums, int target) {
        // 返回 >= target的一个元素id
        auto lower_bound = [](vector<int>& nums, int target) {
            // 双开区间(left, right)
            int left = -1;
            int right = nums.size();
            while (left + 1 < right) {
                int mid = left + (right - left) / 2;
                if (nums[mid] >= target) {
                    right = mid;
                } else {
                    left = mid;
                }
            }
            return right;
        };
        // >= target
        int start = lower_bound(nums, target);
        if (start == nums.size() || nums[start] != target) {
            return {-1, -1};
        }
        // <= target 即 >target 即 >= (target + 1) 对应id的左边一个元素
        // 有start,end必存在,不用判断end == -1
        int end = lower_bound(nums, target + 1) - 1;
        return {start, end};
    }

    // 2529正整数和负整数的最大计数
    int maximumCount(vector<int>& nums) {
        // (left, right), >= target
        auto lower_bound = [](vector<int>& nums, int target) {
            int left = -1;
            int right = nums.size();
            while (left + 1 < right) {
                int mid = left + (right - left) / 2;
                if (nums[mid] >= target) {
                    right = mid;
                } else {
                    left = mid;
                }
            }
            return right;
        };

        int n = nums.size();
        int target = 0;
        // < target -> (>= target) - 1
        int start_0 = lower_bound(nums, target) - 1;
        // > target -> >= (target + 1)
        int end_0 = lower_bound(nums, target + 1);
        return max(start_0 + 1, n - end_0);
    }

    // 2300咒语和药水的成功对数
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int n = spells.size();
        int m = potions.size();
        sort(potions.begin(), potions.end());
        vector<int> ans(n, 0);
        for (int i = 0; i < n; i++) {
            int left = -1;
            int right = m;
            while (left + 1 < right) {
                int mid = left + (right - left) / 2;
                if ((long long)potions[mid] * (long long)spells[i] >= success) {
                    right = mid;
                } else {
                    left = mid;
                }
            }
            ans[i] = m - right;
        }
        return ans;
    }

    // 2563统计公平数对的数目,参考
    // 自己复制vector超时了
    long long countFairPairs(vector<int>& nums, int lower, int upper) {
        // 第一个满足>=target的位置, 这里传的参数是[left, right)
        auto lower_bound = [](vector<int> &nums, int left, int right, int target) {
            int l = left - 1;
            int r = right;
            while (l + 1 < r) {
                int mid = l + (r - l) / 2;
                if (nums[mid] >= target) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            return r;
        };
        // 第一个满足>target(等价于>= target + 1)的位置
        auto upper_bound = [lower_bound](vector<int> &nums, int left, int right, int target){
            return lower_bound(nums, left, right, target + 1);
        };

        long long ans = 0;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int start = lower_bound(nums, 0, i, lower - nums[i]);
            int end = upper_bound(nums, 0, i, upper - nums[i]);
            // [start, end - 1]区间所有位置都满足
            // cnt = end - 1 - start + 1 = end - start
            ans += end - start;
        }
        return ans;
    }

    // 2080区间查询数字的频率, 参考
    // 存每个数字出现的下标,下标数组是递增的
    class RangeFreqQuery {
    private:
        // 每个数字的下标列表
        unordered_map<int, vector<int>> pos;

    public:
        RangeFreqQuery(vector<int>& arr) {
            for (int i = 0; i < arr.size(); ++i) {
                pos[arr[i]].push_back(i);
            }
        }

        int query(int left, int right, int value) {
            auto it = pos.find(value);
            if (it == pos.end()) {
                return 0;
            }
            auto &vec = it->second;
            int start = lower_bound(vec, left);
            int end = upper_bound(vec, right);
            return end - start;
        }

    private:
        // 第一个>=target
        int lower_bound(vector<int> &nums, int target) {
            int l = - 1;
            int r = nums.size();
            while (l + 1 < r) {
                int mid = l + (r - l) / 2;
                if (nums[mid] >= target) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            return r;
        }
        // 第一个>target
        int upper_bound(vector<int> &nums, int target) {
            return lower_bound(nums, target + 1);
        }
    };

    // 275, H指数, 参考
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        // 1篇必定h值为1, 二分范围可以是[1, n]
        int ans = 0;
        // 二分答案
        // 循环不变量：
        // left - 1的回答一定为「是」
        // right + 1 的回答一定为「否」
        int left= 0;// 不满足条件
        int right = n; // 满足条件
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            // 至少有mid篇大于mid, 右边较大的mid个数需要大于mid
            if (citations[n - mid] >= mid) {
                // 此时可以判断是来,mid左边都是满足条件的,left可以更新
                left = mid;
            } else {
                right = mid;
            }
        }
        return left;
    }

    // 875爱吃香蕉的珂珂, 参考
    int minEatingSpeed(vector<int>& piles, int h) {
        // 吃完某堆香蕉用的时间, p / k 向上取整 等价于  (p - 1) / k + 1 向下取整,
        // 从 [0, n - 1]范围内, 所有的和 <= h
        auto check = [&](int k) {
            int sum = 0;
            for (auto p : piles) {
                sum += (p - 1) / k + 1;
                if (sum > h) {
                    return false;
                }
            }
            return true;
        };

        int max = *max_element(piles.begin(), piles.end());
        // 二分的是答案k(每小时吃的香蕉数), 区间是[1, max]
        int left = 0;// 循环不变量, 一定不满足条件
        int right = max;// 循环不变量, 一定满足条件
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return right;
    }

    // 2187完成旅途的最少时间
    long long minimumTime(vector<int>& time, int totalTrips) {
        // k / t 向下取整
        // 所有的和是旅程数,需要大于等于totalTrips
        auto check = [&](long long k) {
            long long sum = 0;
            for (auto &t : time) {
                sum += k / t;
            }
            return sum >= totalTrips;
        };

        long long min = *min_element(time.begin(), time.end());
        // 同样二分答案, 区间[1, 最小时间*totalTrips]
        long long left = 0; // 循环不变量, check(left)必不满足条件
        long long right = (long long)min * totalTrips;// 循环不变量, check(right)必满足条件
        while (left + 1 < right) {
            long long mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return right;
    }

    // 2861最大合金数, 参考
    int maxNumberOfAlloys(int n, int k, int budget,// n类金属,k台设备
                          vector<vector<int>>& composition, // 制造合金需要的每类金属的数目
                          vector<int>& stock, //已有的
                          vector<int>& cost) {// 每类金属的价格
        // 满足条件的最左边一个数, 一份合金也需要,必满足
        int ans = 0;
        // 满足条件的最右边一个数,
        // 假设合金只需要一份金属,价格为1,此时合金数目最多就是 min(存量) + 预算/ 1
        int max = *min_element(stock.begin(), stock.end()) + budget;
        auto check = [&](int comp_id, int cnt_rst) {
            auto &need = composition[comp_id];
            long long sum = 0;
            for (int i = 0; i < need.size(); i++) {
                long long needs = (long long)need[i] * cnt_rst;
                if (needs > stock[i]) {
                    sum += (needs - stock[i]) * cost[i];
                    if (sum > budget) {
                        return false;
                    }
                }
            }
            return true;
        };
        // 设备数目K
        for (int i = 0; i < k; i++) {
            // 0已经知道是必定满足条件的了,二分区间可以不包含了
            // 所以left = 0, 这里把left作为满足条件, right作为不满足的
            // 二分区间(0, max + 1),
            int left = ans;// 循环不变量, 必满足
            int right = max + 1; // 循环不变量, 必不满足
            while (left + 1 < right) {
                int mid = left + (right - left) / 2;
                (check(i, mid) ? left : right) = mid;
            }
            ans = left;
        }
        return ans;

    }

    // 2439最大化数组里的最小值, 参考
    // 自己写的超时了,但思路是对的,第一个数是最大值的时候就找到答案了
    int minimizeArrayValue(vector<int>& nums) {
        // 所有超过limit的部分从右向左移动,
        // 到最左边的时候能不能小于limit
        auto check = [&](int limit) ->bool {
            long long extra = 0;
            for (int i = nums.size() - 1; i > 0; i--) {
                extra = max(nums[i] + extra - limit, 0LL);
            }
            return nums[0] + extra <= limit;
        };

        int min = *min_element(nums.begin(), nums.end());
        int max = *max_element(nums.begin(), nums.end());
        int left = min - 1;// 循环不变量, left一定不大于数组内所有数, 不满足
        int right = max; // 循环不变量, right一定大于数组内所有数,满足
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (check(mid) ? right : left) = mid;
        }
        return right;

    }

    // 2517礼盒的最大甜蜜度, 参考
    int maximumTastiness(vector<int>& price, int k) {
        // 甜蜜度越大, 可选的种类k越小
        auto f = [&](int d) ->int {
            int cnt = 1, pre = price[0];
            for (auto p : price) {
                if (p - pre >= d) {
                    cnt++;
                    pre = p;
                }
            }
            return cnt;
        };

        sort(price.begin(), price.end());
        // price[0] + (k - 1) * d <= price[n - 1]
        // d <= (price[n - 1] - price[0]) / (k - 1)
        // f(d + 1) < k
        int left = 0;// f(left) >= k,
        int right = (price.back() - price[0]) / (k - 1) + 1;// f(right) < k
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (f(mid) >= k ? left : right) = mid;
        }
        return left;
    }
    }

    ///----------------------二分查找2, 6
    namespace BinarySearch2 {
    // 162寻找峰值
    int findPeakElement(vector<int>& nums) {
        // [0, n - 2]->(-1, n - 1)
        // while里面有mid + 1,所有范围限制为n-2
        int n = nums.size();
        int left = -1;
        int right = n - 1;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[mid + 1]) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return right;
    }

    // 153寻找旋转排序数组中的最小值
    int findMin(vector<int>& nums) {
        // [0, n-2]
        int n = nums.size();
        int left = -1;//不满足
        int right = n - 1;// 满足
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (nums[mid] > nums.back() ? left : right) = mid;
        }
        return nums[right];
    }

    // 33搜索旋转排序数组
    int search(vector<int>& nums, int target) {
        // [0, n - 2]
        int last = nums.back();
        auto check = [&](int i) {
            int x = nums[i];
            if (x > last) {
                return target > last && x >= target;
            }
            return target > last || x >= target;
        };

        int n = nums.size();
        int left = -1;
        int right = n - 1;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            (check(nums[mid]) ? right : left) = mid;
        }
        return nums[right] == target ? right : -1;
    }

    }
#endif // SOLUTION_H
