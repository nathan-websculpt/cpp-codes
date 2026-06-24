#include <iostream>
#include <unordered_map>

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
    for (int i = 0; i < nums.size(); ++i) {
        if (umap.contains(nums[i])) {
            int distance = i - umap[nums[i]];
            if (distance <= k) {
                return true;
            }
        }
        umap[nums[i]] = i;
    }

    return false;
}

int main() {
    std::cout << "...\n";
}
