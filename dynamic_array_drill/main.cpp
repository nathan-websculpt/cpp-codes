#include <cassert>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

class IntArray {
public:
    IntArray() : data_(nullptr), size_(0), capacity_(0) {}

    ~IntArray() {
        delete[] data_;
    }

    // copy constructor
    IntArray(const IntArray& other)
        : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
        if (capacity_ > 0) {
            data_ = new int[capacity_];

            for (std::size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    // copy assignment operator
    IntArray& operator=(const IntArray& other) {
        // check for self-assignment
        if (this == &other) {
            return *this; // do nothing
        }

        int* new_data = nullptr;

        if (other.capacity_ > 0) {
            new_data = new int[other.capacity_];

            for (std::size_t i = 0; i < other.size_; ++i) {
                new_data[i] = other.data_[i];
            }
        }

        delete[] data_;

        data_ = new_data;
        size_ = other.size_;
        capacity_ = other.capacity_;

        return *this;
    }

    // move constructor
    IntArray(IntArray&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // move assignment operator
    IntArray& operator=(IntArray&& other) noexcept {
        // check for self-move assignment
        if (this == &other) {
            return *this;
        }

        delete[] data_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }

    std::size_t size() const {
        return size_;
    }

    std::size_t capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }

    int* data() {
        return data_;
    }

    const int* data() const {
        return data_;
    }

    int* begin() {
        return data_;
    }

    const int* begin() const {
        return data_;
    }

    const int* cbegin() const {
        return data_;
    }

    int* end() {
        return size_ == 0 ? data_ : data_ + size_;
    }

    const int* end() const {
        return size_ == 0 ? data_ : data_ + size_;
    }

    const int* cend() const {
        return size_ == 0 ? data_ : data_ + size_;
    }

    int& operator[](std::size_t index) {
        return data_[index];
    }

    const int& operator[](std::size_t index) const {
        return data_[index];
    }

    int& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("IntArray index out of range");
        }

        return data_[index];
    }

    const int& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("IntArray index out of range");
        }

        return data_[index];
    }

    int& front() {
        if (empty()) {
            throw std::out_of_range("front on empty IntArray");
        }

        return data_[0];
    }

    const int& front() const {
        if (empty()) {
            throw std::out_of_range("front on empty IntArray");
        }

        return data_[0];
    }

    int& back() {
        if (empty()) {
            throw std::out_of_range("back on empty IntArray");
        }

        return data_[size_ - 1];
    }

    const int& back() const {
        if (empty()) {
            throw std::out_of_range("back on empty IntArray");
        }

        return data_[size_ - 1];
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

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("pop_back on empty IntArray");
        }

        --size_;
    }

    void clear() {
        size_ = 0;
    }

private:
    int* data_;
    std::size_t size_;
    std::size_t capacity_;
};

int main() {
    IntArray a;

    assert(a.empty());
    assert(a.size() == 0);
    assert(a.capacity() == 0);
    assert(a.data() == nullptr);
    assert(a.begin() == a.end());

    a.push_back(10);
    a.push_back(20);
    a.push_back(30);

    assert(!a.empty());
    assert(a.size() == 3);
    assert(a.capacity() >= 3);
    assert(a[0] == 10);
    assert(a[1] == 20);
    assert(a[2] == 30);
    assert(a.at(1) == 20);
    assert(a.front() == 10);
    assert(a.back() == 30);

    a[0] = 111;
    a.at(1) = 222;
    a.front() = 333;
    a.back() = 444;

    assert(a[0] == 333);
    assert(a[1] == 222);
    assert(a[2] == 444);

    bool caught_out_of_range = false;

    try {
        a.at(99);
    } catch (const std::out_of_range&) {
        caught_out_of_range = true;
    }

    assert(caught_out_of_range);

    std::size_t old_capacity = a.capacity();
    a.reserve(old_capacity + 10);

    assert(a.capacity() == old_capacity + 10);
    assert(a.size() == 3);
    assert(a[0] == 333);
    assert(a[1] == 222);
    assert(a[2] == 444);

    a.reserve(1);

    assert(a.capacity() == old_capacity + 10);

    int iterator_sum = 0;

    for (int* it = a.begin(); it != a.end(); ++it) {
        iterator_sum += *it;
    }

    assert(iterator_sum == 999);

    int range_for_sum = 0;

    for (int value : a) {
        range_for_sum += value;
    }

    assert(range_for_sum == 999);

    const IntArray& const_a = a;

    assert(const_a.data() == a.data());
    assert(const_a.begin() == a.begin());
    assert(const_a.cbegin() == a.begin());
    assert(const_a.end() == a.end());
    assert(const_a.cend() == a.end());
    assert(const_a[0] == 333);
    assert(const_a.at(1) == 222);
    assert(const_a.front() == 333);
    assert(const_a.back() == 444);

    int const_iterator_sum = 0;

    for (const int* it = const_a.begin(); it != const_a.end(); ++it) {
        const_iterator_sum += *it;
    }

    assert(const_iterator_sum == 999);

    int citerator_sum = 0;

    for (const int* it = a.cbegin(); it != a.cend(); ++it) {
        citerator_sum += *it;
    }

    assert(citerator_sum == 999);

    IntArray b = a;

    assert(b.size() == a.size());
    assert(b.capacity() == a.capacity());
    assert(b.data() != a.data());
    assert(b[0] == 333);
    assert(b[1] == 222);
    assert(b[2] == 444);

    b[0] = 999;

    assert(b[0] == 999);
    assert(a[0] == 333);

    IntArray c;
    c.push_back(1);
    c.push_back(2);

    c = a;

    assert(c.size() == a.size());
    assert(c.capacity() == a.capacity());
    assert(c.data() != a.data());
    assert(c[0] == 333);
    assert(c[1] == 222);
    assert(c[2] == 444);

    IntArray& c_alias = c;
    c = c_alias;

    assert(c.size() == 3);
    assert(c[0] == 333);
    assert(c[1] == 222);
    assert(c[2] == 444);

    IntArray d = std::move(a);

    assert(d.size() == 3);
    assert(d[0] == 333);
    assert(d[1] == 222);
    assert(d[2] == 444);

    assert(a.empty());
    assert(a.size() == 0);
    assert(a.capacity() == 0);
    assert(a.data() == nullptr);

    IntArray e;
    e.push_back(7);
    e.push_back(8);

    e = std::move(b);

    assert(e.size() == 3);
    assert(e[0] == 999);
    assert(e[1] == 222);
    assert(e[2] == 444);

    assert(b.empty());
    assert(b.size() == 0);
    assert(b.capacity() == 0);
    assert(b.data() == nullptr);

    IntArray& e_alias = e;
    e = std::move(e_alias);

    assert(e.size() == 3);
    assert(e[0] == 999);
    assert(e[1] == 222);
    assert(e[2] == 444);

    e.pop_back();

    assert(e.size() == 2);
    assert(e[0] == 999);
    assert(e[1] == 222);

    e.clear();

    assert(e.empty());
    assert(e.size() == 0);
    assert(e.capacity() >= 2);
    assert(e.begin() == e.end());

    e.push_back(123);

    assert(e.size() == 1);
    assert(e[0] == 123);

    std::cout << "All IntArray checks passed.\n";
}