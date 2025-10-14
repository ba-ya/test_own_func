#ifndef SOLUTION_H
#define SOLUTION_H

#include <algorithm>
#include <vector>
#include <QDebug>

using namespace std;

//----------------------相向双指针1
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

#endif // SOLUTION_H
