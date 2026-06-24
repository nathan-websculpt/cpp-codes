#include <iostream>
#include <utility>

template <typename T>
class UniquePtr {
public:
    UniquePtr() : ptr_(nullptr) {}

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
    std::cout << "Address: " << p.get() << '\n';
    std::cout << "Value: " << *p << '\n';

    *p = 99;

    std::cout << "New value: " << *p << '\n';

    UniquePtr<int> b(std::move(p));

    int stop{};
}