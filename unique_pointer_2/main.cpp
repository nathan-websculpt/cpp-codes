#include <iostream>
#include <utility>

template <typename T>
class UniquePtr {
public:
    // default ctor because it can be called with no args
    // this part is the member initialization list:
    //          : ptr_(nullptr)
    // important detail: the member initializer list runs before the constructor body
    UniquePtr() : ptr_(nullptr) {}

    // converting constructor candidate because it takes one argument
    // without 'explicit', C++ would allow implicit conversion from T* to UniquePtr<T>
    // without 'explicit', this would be allowed: UniquePtr<int> p = new int(42);
    // with 'explicit', that would be rejected
    // so 'explicit' means: do not use this constructor for implicit conversions
    explicit UniquePtr(T* ptr) : ptr_(ptr) {}

    ~UniquePtr() {
        delete ptr_;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;

        return *this;
    }

    T* get() const {
        return ptr_;
    }

    T& operator*() const {
        return *ptr_;
    }

    T* operator->() const {
        return ptr_;
    }

private:
    T* ptr_;
};

int main() {
    UniquePtr<int> p(new int(42));
    std::cout << "Address: " << p.get() << std::endl;
    std::cout << "Value: " << *p << std::endl;

    *p = 99;

    std::cout << "New Value: " << *p << std::endl;

    UniquePtr<int> b(std::move(p));

    int stop{};
}