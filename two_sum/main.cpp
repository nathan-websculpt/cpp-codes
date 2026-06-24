#include <iostream>
#include <vector>
#include <unordered_map>

/*
 * Problem: Two Sum (Easy)
 *
 * Given an array of integers `nums` and an integer `target`, return the indices
 * of the two numbers such that they add up to `target`.
 *
 * Assumptions:
 * - Each input has exactly one valid solution.
 * - You may not use the same element twice.
 * - The answer can be returned in any order.
 *
 * Example:
 *   Input: nums = [2, 7, 11, 15], target = 9
 *   Output: [0, 1]
 *   Explanation: nums[0] + nums[1] == 9
 *
 * Constraints:
 * - 2 <= nums.size() <= 10^4
 * - -10^9 <= nums[i] <= 10^9
 * - -10^9 <= target <= 10^9
 *
 *
 *
 * std::vector<int> twoSum(std::vector<int>& nums, int target) {
 *
 * }
 *
 */

std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen; // value -> index

    for (int i = 0; i < nums.size(); ++i) {
        int complement = target - nums[i];

        // check if the complement exists in the map
        if (seen.find(complement) != seen.end()) {
            return {seen[complement], i};
        }

        // otherwise, store the current number and its index
        seen[nums[i]] = i;
    }

    // this should never happen if one valid answer is guaranteed
    return {};
}

int main() {
    std::vector<int> nums{2, 7, 11, 15};
    const int target = 9;

    std::vector<int> output = twoSum(nums, target);

    for (int v : output) {
        std::cout << v << "\n";
    }

    return 0;
}