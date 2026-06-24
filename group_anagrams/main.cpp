#include <array>
#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

/*
 * Problem: Group Anagrams (Medium)
 *
 * Given an array of strings `strs`, group the anagrams together.
 * You can return the answer in any order.
 *
 * An anagram is a word or phrase formed by rearranging the letters
 * of a different word or phrase, typically using all the original letters exactly once.
 *
 * Example 1:
 *   Input: strs = ["eat","tea","tan","ate","nat","bat"]
 *   Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 *
 * Example 2:
 *   Input: strs = [""]
 *   Output: [[""]]
 *
 * Example 3:
 *   Input: strs = ["a"]
 *   Output: [["a"]]
 *
 * Constraints:
 * - 1 <= strs.length <= 10^4
 * - 0 <= strs[i].length <= 100
 * - strs[i] consists of lowercase English letters
 *
 *
 * std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs) {
 *
 * }
 *
 */

using AnagramKey = std::array<int, 26>;

struct AnagramKeyHash {
    std::size_t operator()(const AnagramKey& key) const noexcept {
        std::size_t hash = 1469598103934665603ULL;

        for (const int count : key) {
            hash ^= static_cast<std::size_t>(count);
            hash *= 1099511628211ULL;
        }

        return hash;
    }
};

AnagramKey makeKey(std::string_view str) {
    AnagramKey key{};

    for (const char ch : str) {
        ++key[static_cast<std::size_t>(ch - 'a')];
    }

    return key;
}

std::vector<std::vector<std::string>> groupAnagrams(const std::vector<std::string>& strs) {
    std::unordered_map<AnagramKey, std::vector<std::string>, AnagramKeyHash> groups;
    groups.reserve(strs.size());

    for (const std::string& str : strs) {
        groups[makeKey(str)].push_back(str);
    }

    std::vector<std::vector<std::string>> result;
    result.reserve(groups.size());

    for (auto& [key, group] : groups) {
        result.push_back(std::move(group));
    }

    return result;
}

void printGroups(const std::vector<std::vector<std::string>>& groups) {
    std::cout << "[\n";

    for (const auto& group : groups) {
        std::cout << "  [";

        for (std::size_t i = 0; i < group.size(); ++i) {
            std::cout << '"' << group[i] << '"';

            if (i + 1 < group.size()) {
                std::cout << ", ";
            }
        }

        std::cout << "]\n";
    }

    std::cout << "]\n";
}

int main() {
    const std::vector<std::string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};

    const std::vector<std::vector<std::string>> grouped = groupAnagrams(strs);

    printGroups(grouped);

    return 0;
}