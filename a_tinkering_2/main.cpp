#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

class IntArray {
public:
    IntArray() : data_(nullptr), size_(0), capacity_(0) {
        std::cout << "default constructor\n";
    }

    ~IntArray() {
        std::cout << "destructor\n";
        delete[] data_;
    }

    // copy constructor
    IntArray(const IntArray& other)
        : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
        std::cout << "copy constructor\n";

        if (capacity_ > 0) {
            data_ = new int[capacity_];

            for (std::size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    // copy assignment operator
    IntArray& operator=(const IntArray& other) {
        std::cout << "copy assignment\n";

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
        std::cout << "move constructor\n";

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // move assignment operator
    IntArray& operator=(IntArray&& other) noexcept {
        std::cout << "move assignment\n";

        // check for self-assignment
        if (this == &other) {
            return *this; // do nothing
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

    void push_back(int value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        data_[size_] = value;
        ++size_;
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

    int& operator[](std::size_t index) {
        return data_[index];
    }

    const int& operator[](std::size_t index) const {
        return data_[index];
    }

    int& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("IntArray index out of "
                                    "range");
        }

        return data_[index];
    }

    const int& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("IntArray index out of "
                                    "range");
        }

        return data_[index];
    }

    void print(const char* name) const {
        std::cout << name << ": ";

        for (std::size_t i = 0; i < size_; ++i) {
            std::cout << data_[i] << ' ';
        }

        std::cout << "(size=" << size_ << ", capacity=" << capacity_ << ")\n";
    }

private:
    int* data_;
    std::size_t size_;
    std::size_t capacity_;
};

IntArray make_array() {
    IntArray temp;
    temp.push_back(100);
    temp.push_back(200);
    temp.push_back(300);

    return temp;
}

int main() {
    std::cout << "____ create a ____\n";
    IntArray a;
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);
    a.print("a");

    std::cout << "\n____ copy constructor: "
                 "IntArray b = a ____\n";
    IntArray b = a;
    b.print("b");

    std::cout << "\n____ prove copy is "
                 "deep ____\n";
    b[0] = 999;
    a.print("a");
    b.print("b");

    std::cout << "\n____ copy assignment: c = "
                 "a ____\n";
    IntArray c;
    c.push_back(1);
    c.push_back(2);
    c.print("c before");

    c = a;
    c.print("c after");

    std::cout << "\n____ move constructor: "
                 "IntArray d = std::move(a) "
                 "____\n";
    IntArray d = std::move(a);
    d.print("d");
    a.print("a after move");

    std::cout << "\n____ move assignment: e = "
                 "std::move(b) ____\n";
    IntArray e;
    e.push_back(7);
    e.push_back(8);
    e.print("e before");

    e = std::move(b);
    e.print("e after");
    b.print("b after move");

    std::cout << "\n____ return from "
                 "function ____\n";
    IntArray f = make_array();
    f.print("f");

    std::cout << "\n____ end of main ____\n";
}