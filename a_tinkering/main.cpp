#include <cstddef>
#include <iostream>

class IntArray {
public:
    IntArray() : data_(nullptr), size_(0), capacity_(0) {}

    ~IntArray() {
        delete[] data_;
    }

private:
    int* data_;
    std::size_t size_;
    std::size_t capacity_;
};

int main() {
    std::cout << "y\n";
}