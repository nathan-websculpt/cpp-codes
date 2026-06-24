#include <iostream>
#include <string>
#include <vector>

// Given a string path, which represents an absolute path in a Unix-style file system
// Rules:
//   - The path starts with '/'
//   - Components are separated by '/'
//   - "."  means current directory  -> ignore
//   - ".." means parent directory   -> go up one level
//   - Multiple slashes "//" are treated as a single '/'
// Goal:
//   Return the simplified canonical path
//
//
// Examples
//      "/home/"                → "/home"
//      "/../"                  → "/"
//      "/home//foo/"           → "/home/foo"
//      "/a/./b/../../c/"       → "/c"
//      "/a/./b/../c/"          → "/a/c"
//
//
// Constraints(important for thinking)
//      You cannot go above root(/ )
//      Result:
//          starts with /
//          no trailing / (unless it’s just / )
//          no "." or ".." remaining

void processPart(std::vector<std::string>& dirs, const std::string& part) {
    if (part.empty() || part == ".") {
        return;
    }

    if (part == "..") {
        if (!dirs.empty()) {
            dirs.pop_back();
        }
        return;
    }

    dirs.push_back(part);
}

std::string simplifyPath(const std::string& path) {
    std::vector<std::string> dirs;
    std::string part;

    // go one step past the end and treat that position like a final '/'
    // so the last path component gets processed uniformly.
    for (size_t i = 0; i <= path.size(); ++i) {
        const char c = (i == path.size()) ? '/' : path[i];

        if (c == '/') {
            processPart(dirs, part);
            part.clear();
        } else {
            part.push_back(c);
        }
    }

    std::string result;
    for (const auto& dir : dirs) {
        result += '/';
        result += dir;
    }

    return result.empty() ? "/" : result;
}

int main() {
    std::vector<std::string> tests = {
        "/home/", "/../",   "/home//foo/",           "/a/./b/../../c/", "/a/./b/../c/",
        "/",      "/././.", "/a//b////c/d//././/..", "/abc/..."};

    for (const auto& test : tests) {
        std::cout << "Input:  " << test << '\n';
        std::cout << "Output: " << simplifyPath(test) << "\n\n";
    }
}