#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

/*
 * Problem: Longest Substring Without Repeating Characters (Medium)
 *
 * Given a string `s`, find the length of the longest substring
 * without repeating characters.
 *
 * A substring is a contiguous sequence of characters within the string.
 *
 * Example 1:
 *   Input: s = "abcabcbb"
 *   Output: 3
 *   Explanation: The answer is "abc", with length 3.
 *
 * Example 2:
 *   Input: s = "bbbbb"
 *   Output: 1
 *   Explanation: The answer is "b", with length 1.
 *
 * Example 3:
 *   Input: s = "pwwkew"
 *   Output: 3
 *   Explanation: The answer is "wke", with length 3.
 *                Note that the answer must be a substring, not a subsequence.
 *
 * Constraints:
 * - 0 <= s.length <= 5 * 10^4
 * - s consists of English letters, digits, symbols, and spaces.
 *
 *
 * int lengthOfLongestSubstring(std::string s) {
 *
 * }
 *
 */

int lengthOfLongestSubstring(const std::string& s) {
    std::vector<int> lastSeen(256, -1);
    int left = 0;
    int best = 0;

    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        unsigned char c = static_cast<unsigned char>(s[right]);

        if (lastSeen[c] >= left) {
            left = lastSeen[c] + 1;
        }

        lastSeen[c] = right;
        best = std::max(best, right - left + 1);
    }

    return best;
}

int main() {
    std::string tst1 = "abcabcbb";
    std::string tst2 = "pwwkew";
    std::string tst3 = "bbbbbb";
    int res = lengthOfLongestSubstring(tst1);
    int res2 = lengthOfLongestSubstring(tst2);
    int res3 = lengthOfLongestSubstring(tst3);
    std::cout << "Input: " << tst1 << " -> longest substring length = " << res << "\n";
    std::cout << "Input: " << tst2 << " -> longest substring length = " << res2 << "\n";
    std::cout << "Input: " << tst3 << " -> longest substring length = " << res3 << "\n";
}