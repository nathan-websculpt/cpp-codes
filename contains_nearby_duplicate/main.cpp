#include <cassert>
#include <iostream>
#include <unordered_map>
#include <vector>

// return true only if distance ≤ k
// We want to check every number, then compare the computed distance to k.
// use unordered_map<int, int>
// loop with indices(not range - based)
// follow exactly :
//      check if seen
//      compute distance
//      update index

bool containsNearbyDuplicate(const std::vector<int>& nums, int k) {
    std::unordered_map<int, int> umap;

    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        if (umap.contains(nums[i])) {
            const int distance = i - umap[nums[i]];

            if (distance <= k) {
                return true;
            }
        }

        umap[nums[i]] = i;
    }

    return false;
}

int main() {
    assert(containsNearbyDuplicate({1, 2, 3, 1}, 3));
    assert(!containsNearbyDuplicate({1, 2, 3, 1}, 2));

    assert(containsNearbyDuplicate({1, 0, 1, 1}, 1));
    assert(!containsNearbyDuplicate({1, 2, 3, 4}, 3));

    assert(!containsNearbyDuplicate({}, 1));
    assert(!containsNearbyDuplicate({1}, 1));
    assert(!containsNearbyDuplicate({1, 1}, 0));

    std::cout << "tests passed...\n";
}