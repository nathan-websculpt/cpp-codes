#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>

enum class Status { Todo, InProgress, Done };

struct Task {
    unsigned int id;
    std::string title;
    Status status;
};

// for color-coded status strings
std::string status_to_string(Status status) {
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
size_t visible_length(const std::string& s) {
    size_t len = 0;
    bool in_escape = false;
    for (char c : s) {
        if (c == '\x1b') {
            in_escape = true;
            continue;
        }
        if (in_escape) {
            if (c == 'm')
                in_escape = false;
            continue;
        }
        len++;
    }
    return len;
}

class TaskManager {
private:
    std::unordered_map<unsigned int,
                       Task> tasks; // for O(1) access by task ID
    unsigned int next_id = 1;

public:
    // add task and return reference ... allow chaining
    TaskManager& add_task(const std::string& title) {
        Task task{next_id, title, Status::Todo};
        tasks[next_id++] = task;
        return *this;
    }

    // update status by ID, returns reference for chaining
    TaskManager& update_status(unsigned int id, Status status) {
        auto it = tasks.find(id);
        if (it != tasks.end()) {
            it->second.status = status;
        } else {
            std::cout << "Task with id " << id << " not found!\n";
        }
        return *this;
    }

    void list_tasks() const {
        std::cout << "\nID  | Status      | Title\n";
        std::cout << "----|------------|----------------\n";

        for (const auto& [id, task] : tasks) {
            std::string status_str = status_to_string(task.status);
            size_t padding = 12 - visible_length(status_str); // align table
            std::cout << std::setw(3) << task.id << " | " << status_str << std::string(padding, ' ')
                      << " | " << task.title << '\n';
        }
    }
};

// read a line of input
std::string read_input(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}

// convert string to lowercase
std::string to_lower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

// parse status string
Status parse_status(const std::string& status_str) {
    std::string s = to_lower(status_str);
    if (s == "inprogress")
        return Status::InProgress;
    if (s == "done")
        return Status::Done;
    return Status::Todo;
}

int main() {
    TaskManager manager;

    while (true) {
        std::cout << "\nCommands: add, list, update, quit\n";
        std::string command = read_input("> ");

        if (command == "add") {
            std::string title = read_input("Enter task title: ");
            manager.add_task(title);
        } else if (command == "list") {
            manager.list_tasks();
        } else if (command == "update") {
            try {
                // exception safe ID parsing w/ stoul
                unsigned int id = std::stoul(read_input("Enter task ID: "));
                std::string status_str = read_input("Enter status (todo, inprogress, done): ");
                Status status = parse_status(status_str);
                manager.update_status(id, status);
            } catch (...) {
                std::cout << "Invalid ID!\n";
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
