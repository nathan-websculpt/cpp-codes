#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>

class IntArray {
public:
    IntArray() : data_(nullptr), size_(0), capacity_(0) {
        std::cout << "  [IntArray] default constructor: no heap buffer yet\n";
    }

    ~IntArray() {
        std::cout << "  [IntArray] destructor: releasing owned heap buffer\n";
        delete[] data_;
    }

    IntArray(const IntArray& other)
        : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
        std::cout << "  [IntArray] copy constructor: allocating separate heap buffer\n";

        if (capacity_ > 0) {
            data_ = new int[capacity_];

            for (std::size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    IntArray& operator=(const IntArray& other) {
        std::cout << "  [IntArray] copy assignment: replacing this buffer with a deep copy\n";

        if (this == &other) {
            std::cout << "  [IntArray] copy assignment: self-assignment, no work needed\n";
            return *this;
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

    IntArray(IntArray&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        std::cout << "  [IntArray] move constructor: stealing the source heap buffer\n";

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    IntArray& operator=(IntArray&& other) noexcept {
        std::cout
            << "  [IntArray] move assignment: releasing this buffer, then stealing source buffer\n";

        if (this == &other) {
            std::cout << "  [IntArray] move assignment: self-assignment, no work needed\n";
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

    void reserve(std::size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }

        std::cout << "  [IntArray] reserve: allocating capacity " << new_capacity << "\n";

        int* new_data = new int[new_capacity];

        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }

        delete[] data_;

        data_ = new_data;
        capacity_ = new_capacity;
    }

    void print(const char* name) const {
        std::cout << name << ": [";

        for (std::size_t i = 0; i < size_; ++i) {
            std::cout << data_[i];

            if (i + 1 < size_) {
                std::cout << ", ";
            }
        }

        std::cout << "] size=" << size_ << ", capacity=" << capacity_
                  << ", data=" << static_cast<const void*>(data_) << '\n';
    }

private:
    int* data_;
    std::size_t size_;
    std::size_t capacity_;
};

void print_section(const char* title) {
    std::cout << "\n============================================================\n";
    std::cout << title << '\n';
    std::cout << "============================================================\n";
}

void print_note(const char* text) {
    std::cout << "\n  note: " << text << "\n\n";
}

void print_array_summary(const char* name, const IntArray& array) {
    array.print(name);
}

void push_and_report(IntArray& array, int value, const char* name) {
    std::cout << "push_back(" << value << ")\n";
    array.push_back(value);
    print_array_summary(name, array);
}

void try_at(const IntArray& array, std::size_t index) {
    std::cout << "Trying at(" << index << ")... ";

    try {
        std::cout << array.at(index) << '\n';
    } catch (const std::out_of_range& error) {
        std::cout << "caught std::out_of_range: " << error.what() << '\n';
    }
}

IntArray make_array() {
    print_note(
        "make_array creates a local IntArray named temp, fills it, and returns it by value.");

    IntArray temp;
    push_and_report(temp, 100, "temp");
    push_and_report(temp, 200, "temp");
    push_and_report(temp, 300, "temp");

    std::cout << "Returning temp. Modern C++ may elide the move entirely with NRVO/copy elision.\n";
    return temp;
}

int main() {
    print_section("1. Default construction and capacity growth");
    print_note(
        "IntArray starts with data_=nullptr, size=0, and capacity=0. The first push allocates.");

    IntArray a;
    print_array_summary("a after default construction", a);

    push_and_report(a, 10, "a");
    push_and_report(a, 20, "a");
    push_and_report(a, 30, "a");

    print_note("size is the number of logical elements. capacity is the allocated heap space.");

    print_section("2. Element access: unchecked operator[] vs checked at()");
    std::cout << "a[0] uses unchecked access and returns: " << a[0] << '\n';
    try_at(a, 1);
    try_at(a, 99);

    print_section("3. front(), back(), data(), and direct mutation through references");
    std::cout << "front() returns the first live element: " << a.front() << '\n';
    std::cout << "back() returns the last live element: " << a.back() << '\n';
    std::cout << "data() exposes the owned heap address: " << static_cast<const void*>(a.data())
              << '\n';

    std::cout << "Changing a.front() to 111 through the returned int&.\n";
    a.front() = 111;
    print_array_summary("a", a);

    print_section("4. Copy construction: IntArray b = a");
    print_note("A copy must allocate its own heap buffer. b should not share a.data_.");

    IntArray b = a;
    print_array_summary("a", a);
    print_array_summary("b", b);

    std::cout << "Mutating b[0] = 999 to prove the copy is deep.\n";
    b[0] = 999;
    print_array_summary("a", a);
    print_array_summary("b", b);

    print_section("5. Copy assignment: c = a");
    print_note("c already owns a buffer. Copy assignment allocates a new copy before releasing c's "
               "old buffer.");

    IntArray c;
    push_and_report(c, 1, "c");
    push_and_report(c, 2, "c");

    std::cout << "Assigning c = a.\n";
    c = a;
    print_array_summary("a", a);
    print_array_summary("c", c);

    std::cout << "Assigning c = c to exercise the self-assignment guard.\n";
    c = c;
    print_array_summary("c", c);

    print_section("6. pop_back() and clear()");
    print_note("For int, pop_back and clear only adjust size_. A generic Vector<T> must destroy "
               "live objects.");

    c.pop_back();
    print_array_summary("c after pop_back", c);

    c.clear();
    print_array_summary("c after clear", c);
    std::cout << "capacity remains allocated after clear so the buffer can be reused.\n";
    push_and_report(c, 77, "c");

    print_section("7. Move construction: IntArray d = std::move(a)");
    print_note("A move steals the heap address. It does not copy the elements to a new address.");

    std::cout << "Before move construction:\n";
    print_array_summary("a", a);

    IntArray d = std::move(a);

    std::cout << "After move construction:\n";
    print_array_summary("d", d);
    print_array_summary("a moved-from", a);

    print_section("8. Move assignment: e = std::move(b)");
    print_note("e releases its current buffer, then takes ownership of b's buffer.");

    IntArray e;
    push_and_report(e, 7, "e");
    push_and_report(e, 8, "e");

    std::cout << "Before move assignment:\n";
    print_array_summary("b", b);
    print_array_summary("e", e);

    e = std::move(b);

    std::cout << "After move assignment:\n";
    print_array_summary("e", e);
    print_array_summary("b moved-from", b);

    print_section("9. Returning IntArray from a function");
    print_note("Depending on compiler settings, you may not see a move constructor here because "
               "copy elision can construct f directly.");

    IntArray f = make_array();
    print_array_summary("f", f);

    print_section("End of main: destructors run in reverse construction order");
}