#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Array {
public:
    Array(int k = 0, const T& t = T()) {
        if (k <= 0) {
            capacity_ = 0;
            size_ = 0;
            data_ = nullptr;
            return;
        }
        size_ = k;
        capacity_ = size_;
        data_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = t;
        }
    }

    Array(const Array& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this != &other) {
            Array tmp(other);
            std::swap(size_, tmp.size_);
            std::swap(capacity_, tmp.capacity_);
            std::swap(data_, tmp.data_);
        }
        return *this;
    }

    ~Array() {
        delete[] data_;
    }

    void pushBack(const T& element) {
        if (size_ == capacity_) {
            resize(capacity_ * 2);
        }
        data_[size_] = element;
        size_++;
    }

    T popBack() {
        if (size_ == 0) {
            throw std::out_of_range("Array is empty");
        }
        T result = data_[size_ - 1];
        size_--;
        if (size_ <= capacity_ / 4) {
            resize(capacity_ / 2);
        }
        return result;
    }

    int size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    T& operator[](int index) {
        return data_[index];
    }

    const T& operator[](int index) const {
        return data_[index];
    }
    
    bool operator==(const Array& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (int i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
    }


private:
    T* data_;
    int size_;
    int capacity_;

    void resize(int new_capacity) {
        T* new_data = new T[new_capacity];
        for (int i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        capacity_ = new_capacity;
        std::swap(data_, new_data);
        delete[] new_data;
    }
};

class Empty : public std::exception {
public:
    const char* what() const noexcept override {
        return "Array is empty";
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        os << arr[i] << " ";
    }
    return os;
}

int main() {
    return 0;
}