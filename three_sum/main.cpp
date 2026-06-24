#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

/*
 * Problem: 3Sum
 *
 * Given an integer array `nums`, return all the unique triplets
 * [nums[i], nums[j], nums[k]] such that:
 *
 *   i != j, i != k, and j != k
 *   nums[i] + nums[j] + nums[k] == 0
 *
 * ------------------------------------------------------------
 * Requirements:
 *
 * - The solution set must not contain duplicate triplets.
 * - You may return the triplets in any order.
 *
 * ------------------------------------------------------------
 * Examples:
 *
 * Input:  nums = [-1, 0, 1, 2, -1, -4]
 * Output: [[-1, -1, 2], [-1, 0, 1]]
 *
 * Input:  nums = [0, 1, 1]
 * Output: []
 *
 * Input:  nums = [0, 0, 0]
 * Output: [[0, 0, 0]]
 *
 * ------------------------------------------------------------
 * Constraints:
 *
 * - 3 <= nums.length <= 3000
 * - -10^5 <= nums[i] <= 10^5
 *
 * ------------------------------------------------------------
 * Key Notes:
 *
 * - Triplets must be unique
 * - Sorting is usually the key first step
 * - This is a classic "fix one value, then run two pointers" problem
 */

std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::vector<std::vector<int>> result;
    if (nums.size() < 3) {
        return result;
    }

    std::sort(nums.begin(), nums.end());

    for (size_t i = 0; i < nums.size() - 2; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }

        size_t left = i + 1;
        size_t right = nums.size() - 1;

        while (left < right) {
            const int sum = nums[i] + nums[left] + nums[right];

            if (sum < 0) {
                ++left;
            } else if (sum > 0) {
                --right;
            } else {
                result.push_back({nums[i], nums[left], nums[right]});

                while (left < right && nums[left] == nums[left + 1]) {
                    ++left;
                }
                while (left < right && nums[right] == nums[right - 1]) {
                    --right;
                }

                ++left;
                --right;
            }
        }
    }

    return result;
}

void printVector(const std::vector<int>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

void printTriplets(const std::vector<std::vector<int>>& triplets) {
    std::cout << "[";
    for (size_t i = 0; i < triplets.size(); ++i) {
        printVector(triplets[i]);
        if (i + 1 < triplets.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "]";
}

int main() {
    std::vector<std::vector<int>> tests = {
        {-1, 0, 1, 2, -1, -4}, {0, 1, 1}, {0, 0, 0}, {-2, 0, 0, 2, 2}, {-4, -2, -2, 0, 1, 2, 2, 4}};

    for (const auto& test : tests) {
        std::vector<int> nums = test;
        auto result = threeSum(nums);

        std::cout << "Input:  ";
        printVector(test);
        std::cout << "\nOutput: ";
        printTriplets(result);
        std::cout << "\n\n";
    }

    return 0;
}