#include <iostream>
#include <vector>
#include <unordered_set>

// check if vector 'nums' has any duplicated numbers
// write the body using:
//		unordered_set
//		a loop
//		find or equivalent

bool hasDuplicate(const std::vector<int>& nums) {
    std::unordered_set<int> uset;

    for (auto n : nums) {
        if (uset.contains(n)) {
            return true;
        } else {
            uset.insert(n);
        }
    }

    return false;
}

int main() {
    std::vector<int> nums = {3, 1, 4, 2, 5, 3};
    bool rslt = hasDuplicate(nums);
    std::cout << rslt << "\n";
}