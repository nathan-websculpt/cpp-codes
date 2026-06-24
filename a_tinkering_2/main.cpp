#include <cstddef>
#include <iostream>
#include <assert.h>

class IntArray {
public:
    IntArray() : data_(nullptr), size_(0), capacity_(0) {}

    ~IntArray() {
        delete[] data_;
    }

    bool empty() const {
        return size_ == 0;
    }

    int& operator[](std::size_t index) {
        return data_[index];
    }

    const int& operator[](std::size_t index) const {
        return data_[index];
    }

    void reserve(std::size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }

        int* new_data = new int[new_capacity];

        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;        
    }

    void push_back(int value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        data_[size_] = value;
        ++size_;
    }

private:
    int* data_;
    std::size_t size_;
    std::size_t capacity_;
};

int main() {
    IntArray a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);

    assert(a[3] == 4);
    std::cout << "works\n";
}