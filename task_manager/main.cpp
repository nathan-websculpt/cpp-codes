#include <algorithm>
#include <charconv>
#include <cctype>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>

enum class Status { Todo, InProgress, Done };

struct Task {
    std::string title;
    Status status;
};

// for color-coded status strings
std::string_view status_to_string(Status status) {
    switch (status) {
    case Status::Todo:
        return "\x1b[33mTodo\x1b[0m"; // Yellow
    case Status::InProgress:
        return "\x1b[34mInProgress\x1b[0m"; // Blue
    case Status::Done:
        return "\x1b[32mDone\x1b[0m"; // Green
    }

    return "Unknown";
}

// count printable characters for alignment
std::size_t visible_length(std::string_view s) {
    std::size_t len = 0;
    bool in_escape = false;

    for (char c : s) {
        if (c == '\x1b') {
            in_escape = true;
            continue;
        }

        if (in_escape) {
            if (c == 'm') {
                in_escape = false;
            }
            continue;
        }

        ++len;
    }

    return len;
}

// parse unsigned task ID from user input
unsigned int parse_task_id(std::string_view input) {
    if (input.empty()) {
        throw std::invalid_argument("Task ID is empty");
    }

    unsigned int value = 0;

    const char* first = input.data();
    const char* last = first + input.size();

    const auto result = std::from_chars(first, last, value);

    if (result.ec == std::errc::invalid_argument) {
        throw std::invalid_argument("Invalid task ID format");
    }

    if (result.ec == std::errc::result_out_of_range) {
        throw std::out_of_range("Task ID is too large");
    }

    if (result.ptr != last) {
        throw std::invalid_argument("Task ID contains trailing characters");
    }

    return value;
}

class TaskManager {
public:
    using TaskMap = std::map<unsigned int, Task>;

    // add task
    void add_task(std::string title) {
        const unsigned int current_id = next_id_;

        tasks_.try_emplace(current_id, std::move(title), Status::Todo);

        // advance only after successful insertion/construction.
        ++next_id_;
    }

    // update status by ID, returns bool for success/failure
    bool update_status(unsigned int id, Status status) {
        auto it = tasks_.find(id);

        if (it != tasks_.end()) {
            it->second.status = status;
            return true;
        }

        return false;
    }

    const TaskMap& tasks() const {
        return tasks_;
    }

private:
    // std::map keeps tasks sorted by ID
    TaskMap tasks_;
    unsigned int next_id_ = 1;
};

void print_tasks(const TaskManager& manager) {
    constexpr std::size_t status_width = 12;

    std::cout << "\nID  | Status      | Title\n";
    std::cout << "----|------------|----------------\n";

    for (const auto& [id, task] : manager.tasks()) {
        const std::string_view status_str = status_to_string(task.status);

        const std::size_t visible_status_length = visible_length(status_str);
        const std::size_t padding =
            visible_status_length < status_width ? status_width - visible_status_length : 0;

        std::cout << std::setw(3) << id << " | " << status_str << std::string(padding, ' ') << " | "
                  << task.title << '\n';
    }
}

// read a line of input
std::string read_input(std::string_view prompt) {
    std::cout << prompt << std::flush;

    std::string input;
    std::getline(std::cin, input);

    return input;
}

// convert string to lowercase
std::string to_lower(std::string_view str) {
    std::string result(str);

    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    return result;
}

// parse status string
Status parse_status(std::string_view status_str) {
    const std::string s = to_lower(status_str);

    if (s == "todo") {
        return Status::Todo;
    }

    if (s == "inprogress") {
        return Status::InProgress;
    }

    if (s == "done") {
        return Status::Done;
    }

    throw std::invalid_argument("Invalid status");
}

int main() {
    TaskManager manager;

    while (true) {
        std::cout << "\nCommands: add, list, update, quit\n";
        const std::string command = to_lower(read_input("> "));

        if (command == "add") {
            manager.add_task(read_input("Enter task title: "));
        } else if (command == "list") {
            print_tasks(manager);
        } else if (command == "update") {
            unsigned int id = 0;

            try {
                id = parse_task_id(read_input("Enter task ID: "));
            } catch (const std::invalid_argument&) {
                std::cout << "Invalid ID format!\n";
                continue;
            } catch (const std::out_of_range&) {
                std::cout << "ID is too large!\n";
                continue;
            }

            Status status = Status::Todo;

            try {
                status = parse_status(read_input("Enter status (todo, inprogress, done): "));
            } catch (const std::invalid_argument&) {
                std::cout << "Invalid status!\n";
                continue;
            }

            // handle UI logic in main(), keeping TaskManager clean.
            if (!manager.update_status(id, status)) {
                std::cout << "Task with id " << id << " not found!\n";
            }
        } else if (command == "quit") {
            break;
        } else {
            std::cout << "Unknown command!\n";
        }
    }

    std::cout << "Goodbye!\n";

    return 0;
}