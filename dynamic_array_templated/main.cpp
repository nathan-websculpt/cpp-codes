#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

template <typename T>
class SimpleVector {
public:
    SimpleVector() : data_(nullptr), size_(0), capacity_(0) {
        std::cout << "default constructor\n";
    }

    ~SimpleVector() {
        std::cout << "destructor\n";
        clear();
        deallocate_storage();
    }

    // Copy constructor
    SimpleVector(const SimpleVector& other) : data_(nullptr), size_(0), capacity_(0) {
        std::cout << "copy constructor\n";

        if (other.capacity_ > 0) {
            data_ = allocate_storage(other.capacity_);
            capacity_ = other.capacity_;

            try {
                for (; size_ < other.size_; ++size_) {
                    std::construct_at(data_ + size_, other.data_[size_]);
                }
            } catch (...) {
                clear();
                deallocate_storage();
                throw;
            }
        }
    }

    // Copy assignment operator
    SimpleVector& operator=(const SimpleVector& other) {
        std::cout << "copy assignment\n";

        if (this == &other) {
            return *this;
        }

        SimpleVector temp(other);
        swap(temp);

        return *this;
    }

    // Move constructor
    SimpleVector(SimpleVector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        std::cout << "move constructor\n";

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // Move assignment operator
    SimpleVector& operator=(SimpleVector&& other) noexcept {
        std::cout << "move assignment\n";

        if (this == &other) {
            return *this;
        }

        clear();
        deallocate_storage();

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

    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(next_capacity());
        }

        std::construct_at(data_ + size_, value);
        ++size_;
    }

    void push_back(T&& value) {
        if (size_ == capacity_) {
            reserve(next_capacity());
        }

        std::construct_at(data_ + size_, std::move(value));
        ++size_;
    }

    template <typename... Args>
    T& emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            reserve(next_capacity());
        }

        std::construct_at(data_ + size_, std::forward<Args>(args)...);
        ++size_;

        return data_[size_ - 1];
    }

    void pop_back() {
        if (empty()) {
            throw std::out_of_range("pop_back on empty SimpleVector");
        }

        --size_;
        std::destroy_at(data_ + size_);
    }

    void clear() {
        for (std::size_t i = 0; i < size_; ++i) {
            std::destroy_at(data_ + i);
        }

        size_ = 0;
    }

    void reserve(std::size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }

        T* new_data = allocate_storage(new_capacity);
        std::size_t constructed = 0;

        try {
            for (; constructed < size_; ++constructed) {
                std::construct_at(new_data + constructed,
                                  std::move_if_noexcept(data_[constructed]));
            }
        } catch (...) {
            for (std::size_t i = 0; i < constructed; ++i) {
                std::destroy_at(new_data + i);
            }

            deallocate_storage(new_data, new_capacity);
            throw;
        }

        clear();
        deallocate_storage();

        data_ = new_data;
        size_ = constructed;
        capacity_ = new_capacity;
    }

    void resize(std::size_t new_size) {
        if (new_size < size_) {
            while (size_ > new_size) {
                pop_back();
            }

            return;
        }

        if (new_size > capacity_) {
            reserve(new_size);
        }

        while (size_ < new_size) {
            std::construct_at(data_ + size_);
            ++size_;
        }
    }

    void resize(std::size_t new_size, const T& value) {
        if (new_size < size_) {
            while (size_ > new_size) {
                pop_back();
            }

            return;
        }

        if (new_size > capacity_) {
            reserve(new_size);
        }

        while (size_ < new_size) {
            std::construct_at(data_ + size_, value);
            ++size_;
        }
    }

    T& operator[](std::size_t index) {
        return data_[index];
    }

    const T& operator[](std::size_t index) const {
        return data_[index];
    }

    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("SimpleVector index out of range");
        }

        return data_[index];
    }

    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("SimpleVector index out of range");
        }

        return data_[index];
    }

    T& front() {
        if (empty()) {
            throw std::out_of_range("front on empty SimpleVector");
        }

        return data_[0];
    }

    const T& front() const {
        if (empty()) {
            throw std::out_of_range("front on empty SimpleVector");
        }

        return data_[0];
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("back on empty SimpleVector");
        }

        return data_[size_ - 1];
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("back on empty SimpleVector");
        }

        return data_[size_ - 1];
    }

    T* data() {
        return data_;
    }

    const T* data() const {
        return data_;
    }

    void swap(SimpleVector& other) noexcept {
        using std::swap;

        swap(data_, other.data_);
        swap(size_, other.size_);
        swap(capacity_, other.capacity_);
    }

    void print(const char* name) const {
        std::cout << name << ": ";

        for (std::size_t i = 0; i < size_; ++i) {
            std::cout << data_[i] << ' ';
        }

        std::cout << "(size=" << size_ << ", capacity=" << capacity_ << ")\n";
    }

private:
    static T* allocate_storage(std::size_t capacity) {
        if (capacity == 0) {
            return nullptr;
        }

        return static_cast<T*>(::operator new(sizeof(T) * capacity));
    }

    static void deallocate_storage(T* pointer, std::size_t /*capacity*/) {
        ::operator delete(pointer);
    }

    void deallocate_storage() {
        deallocate_storage(data_, capacity_);
        data_ = nullptr;
        capacity_ = 0;
    }

    std::size_t next_capacity() const {
        return capacity_ == 0 ? 1 : capacity_ * 2;
    }

private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;
};

template <typename T>
void swap(SimpleVector<T>& lhs, SimpleVector<T>& rhs) noexcept {
    lhs.swap(rhs);
}

SimpleVector<int> make_int_vector() {
    SimpleVector<int> temp;
    temp.push_back(100);
    temp.push_back(200);
    temp.push_back(300);

    return temp;
}

SimpleVector<std::string> make_string_vector() {
    SimpleVector<std::string> temp;
    temp.emplace_back("alpha");
    temp.emplace_back("beta");
    temp.emplace_back("gamma");

    return temp;
}

int main() {
    std::cout << "____ SimpleVector<int> ____\n";

    std::cout << "\n____ create a ____\n";
    SimpleVector<int> a;
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);
    a.print("a");

    std::cout << "\n____ copy constructor: SimpleVector<int> b = a ____\n";
    SimpleVector<int> b = a;
    b.print("b");

    std::cout << "\n____ prove copy is deep ____\n";
    b[0] = 999;
    a.print("a");
    b.print("b");

    std::cout << "\n____ copy assignment: c = a ____\n";
    SimpleVector<int> c;
    c.push_back(1);
    c.push_back(2);
    c.print("c before");

    c = a;
    c.print("c after");

    std::cout << "\n____ move constructor: SimpleVector<int> d = std::move(a) ____\n";
    SimpleVector<int> d = std::move(a);
    d.print("d");
    a.print("a after move");

    std::cout << "\n____ move assignment: e = std::move(b) ____\n";
    SimpleVector<int> e;
    e.push_back(7);
    e.push_back(8);
    e.print("e before");

    e = std::move(b);
    e.print("e after");
    b.print("b after move");

    std::cout << "\n____ return from function ____\n";
    SimpleVector<int> f = make_int_vector();
    f.print("f");

    std::cout << "\n____ pop_back ____\n";
    f.pop_back();
    f.print("f after pop_back");

    std::cout << "\n____ resize larger ____\n";
    f.resize(5, 42);
    f.print("f after resize");

    std::cout << "\n____ resize smaller ____\n";
    f.resize(2);
    f.print("f after resize smaller");

    std::cout << "\n\n____ SimpleVector<std::string> ____\n";

    SimpleVector<std::string> words;
    words.push_back("hello");
    words.push_back("world");
    words.emplace_back("from emplace_back");

    words.print("words");

    std::cout << "\n____ copy string vector ____\n";
    SimpleVector<std::string> words_copy = words;
    words_copy[0] = "changed";
    words.print("words");
    words_copy.print("words_copy");

    std::cout << "\n____ move string vector ____\n";
    SimpleVector<std::string> moved_words = std::move(words_copy);
    moved_words.print("moved_words");
    words_copy.print("words_copy after move");

    std::cout << "\n____ return string vector from function ____\n";
    SimpleVector<std::string> returned_words = make_string_vector();
    returned_words.print("returned_words");

    std::cout << "\n____ end of main ____\n";
}