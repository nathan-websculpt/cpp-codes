#include <iostream>
#include <vector>
#include <stack>

/*
 * Problem: Valid Parentheses (Easy)
 *
 * Given a string `s` containing only the characters '(', ')', '{', '}', '[', and ']',
 * determine if the input string is valid.
 *
 * A string is valid if:
 * - Open brackets are closed by the same type of brackets.
 * - Open brackets are closed in the correct order.
 * - Every closing bracket has a corresponding open bracket.
 *
 * Example 1:
 *   Input: s = "()"
 *   Output: true
 *
 * Example 2:
 *   Input: s = "()[]{}"
 *   Output: true
 *
 * Example 3:
 *   Input: s = "(]"
 *   Output: false
 *
 * Example 4:
 *   Input: s = "([)]"
 *   Output: false
 *
 * Constraints:
 * - 1 <= s.length <= 10^4
 * - s consists only of the characters '()[]{}'
 *
 *
 *
 * bool isValid(std::string s) {
 *
 * }
 *
 */

static bool isValid(std::string s) {
    std::stack<char> st;

    for (char c : s) {
        // if it's an opening bracket, push it
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            // if stack is empty, no matching opening bracket
            if (st.empty())
                return false;

            char top = st.top();

            // check if the top matches the closing bracket
            if ((c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '[')) {
                return false;
            }
            st.pop();
        }
    }

    // if stack is empty, all brackets were matched
    return st.empty();
}

int main() {
    std::string tst1 = "()";
    std::string tst2 = "(]";
    std::string tst3 = "()[]{]";
    std::string tst4 = "()[]{}";
    bool rslt = isValid(tst1);
    bool rslt2 = isValid(tst2);
    bool rslt3 = isValid(tst3);
    bool rslt4 = isValid(tst4);
    std::cout << std::boolalpha << rslt << "\n";
    std::cout << std::boolalpha << rslt2 << "\n";
    std::cout << std::boolalpha << rslt3 << "\n";
    std::cout << std::boolalpha << rslt4 << "\n";

    return 0;
}