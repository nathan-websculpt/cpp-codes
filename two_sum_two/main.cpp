#include <iostream>
#include <vector>

/*
 * Problem: Two Sum II - Input Array Is Sorted
 *
 * Given a 1-indexed array of integers `numbers` that is already sorted
 * in non-decreasing order, find two numbers such that they add up to
 * a specific target number.
 *
 * Let these two numbers be numbers[index1] and numbers[index2] where:
 *
 *   1 <= index1 < index2 <= numbers.length
 *
 * Return the indices of the two numbers, index1 and index2,
 * added by one as an integer array [index1, index2].
 *
 * ------------------------------------------------------------
 * Constraints:
 *
 * - 2 <= numbers.length <= 3 * 10^4
 * - -1000 <= numbers[i] <= 1000
 * - numbers is sorted in non-decreasing order
 * - -1000 <= target <= 1000
 * - Exactly one solution exists
 *
 * ------------------------------------------------------------
 * Examples:
 *
 * Input:  numbers = [2, 7, 11, 15], target = 9
 * Output: [1, 2]
 * Explanation: 2 + 7 = 9
 *
 * Input:  numbers = [2, 3, 4], target = 6
 * Output: [1, 3]
 *
 * Input:  numbers = [-1, 0], target = -1
 * Output: [1, 2]
 *
 * ------------------------------------------------------------
 * Key Notes:
 *
 * - The array is sorted → this is the critical hint
 * - You must return 1-based indices
 * - Exactly one solution exists
 */

std::vector<int> twoSum(const std::vector<int>& numbers, int target) {
    int left = 0;
    int right = numbers.size() - 1;

    while (left < right) {
        int sum = numbers[left] + numbers[right];

        if (sum < target) {
            ++left;
        } else if (sum > target) {
            --right;
        } else {
            return {left + 1, right + 1};
        }
    }
}

int main() {
    std::vector<std::pair<std::vector<int>, int>> tests = {
        {{2, 7, 11, 15}, 9}, {{2, 3, 4}, 6}, {{-1, 0}, -1}};

    for (const auto& [numbers, target] : tests) {
        auto result = twoSum(numbers, target);

        std::cout << "Input: [";
        for (size_t i = 0; i < numbers.size(); ++i) {
            std::cout << numbers[i];
            if (i + 1 < numbers.size())
                std::cout << ", ";
        }
        std::cout << "], target = " << target << "\n";

        std::cout << "Output: [" << result[0] << ", " << result[1] << "]\n\n";
    }
}