#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

/*
 * Problem: Container With Most Water
 *
 * Difficulty: Medium
 *
 * You are given an integer array `height` of length `n`.
 * There are `n` vertical lines drawn such that the two endpoints
 * of the i-th line are:
 *
 *   (i, 0) and (i, height[i])
 *
 * Find two lines that together with the x-axis form a container
 * such that the container contains the most water.
 *
 * Return the maximum amount of water a container can store.
 *
 * Note:
 * - You may not slant the container.
 *
 * Example 1:
 *   Input:  height = [1,8,6,2,5,4,8,3,7]
 *   Output: 49
 *   Explanation:
 *     The max area is formed by height[1] = 8 and height[8] = 7.
 *     Width = 8 - 1 = 7
 *     Height = min(8, 7) = 7
 *     Area = 7 * 7 = 49
 *
 * Example 2:
 *   Input:  height = [1,1]
 *   Output: 1
 *
 * Constraints:
 * - 2 <= height.size() <= 100000
 * - 0 <= height[i] <= 10000
 *
 * Function signature:
 *   int maxArea(std::vector<int>& height);
 *
 * Follow-up thought:
 *   Can you solve it in O(n) time?
 */

int maxArea(const std::vector<int>& height) noexcept {
    if (height.size() < 2) {
        return 0;
    }

    std::size_t left = 0;
    std::size_t right = height.size() - 1;
    std::int64_t best_area = 0;

    while (left < right) {
        const int left_height = height[left];
        const int right_height = height[right];

        const std::size_t width = right - left;
        const int container_height = std::min(left_height, right_height);

        const std::int64_t area = static_cast<std::int64_t>(width) * container_height;

        best_area = std::max(best_area, area);

        if (left_height <= right_height) {
            ++left;
        } else {
            --right;
        }
    }

    return static_cast<int>(best_area);
}

int main() {
    const std::vector<int> example_one{1, 8, 6, 2, 5, 4, 8, 3, 7};
    const std::vector<int> example_two{1, 1};
    const std::vector<int> example_three{4, 3, 2, 1, 4};
    const std::vector<int> example_four{1, 2, 1};

    assert(maxArea(example_one) == 49);
    assert(maxArea(example_two) == 1);
    assert(maxArea(example_three) == 16);
    assert(maxArea(example_four) == 2);

    std::cout << "tests passed\n";
}