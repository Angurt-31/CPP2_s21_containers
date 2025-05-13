#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>
#include <initializer_list>
#include <limits>
#include <utility>

namespace s21 {

    template <typename T>
    class vector {
    public:
        // Переопределения:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = size_t;
    
        // Итератор:
        class Iterator {
        public:
            Iterator(T* ptr = nullptr) : ptr_(ptr) {}
    
            // Оператор разыменования (*iter)
            reference operator*() const {
                return *ptr_;
            }
    
            // Префиксный инкремент (++iter)
            Iterator& operator++() {
                ++ptr_;
                return *this;
            }
    
            // Постфиксный инкремент (iter++)
            Iterator operator++(int) {
                Iterator temp = *this;
                ++ptr_;
                return temp;
            }
    
            // Префиксный декремент (--iter)
            Iterator& operator--() {
                --ptr_;
                return *this;
            }
    
            // Постфиксный декремент (iter--)
            Iterator operator--(int) {
                Iterator temp = *this;
                --ptr_;
                return temp;
            }
    
            // Оператор равенства (iter1 == iter2)
            bool operator==(const Iterator& other) const {
                return ptr_ == other.ptr_;
            }
    
            // Оператор неравенства (iter1 != iter2)
            bool operator!=(const Iterator& other) const {
                return ptr_ != other.ptr_;
            }
    
        private:
            T* ptr_;
        };

            // Константный итератор:
    class ConstIterator {
        public:
            ConstIterator(const T* ptr = nullptr) : ptr_(ptr) {}
    
            const_reference operator*() const {
                return *ptr_;
            }

            ConstIterator& operator++() {
                ++ptr_;
                return *this;
            }
    
            ConstIterator operator++(int) {
                ConstIterator temp = *this;
                ++ptr_;
                return temp;
            }
    
            ConstIterator& operator--() {
                --ptr_;
                return *this;
            }
    
            ConstIterator operator--(int) {
                ConstIterator temp = *this;
                --ptr_;
                return temp;
            }
    
            bool operator==(const ConstIterator& other) const {
                return ptr_ == other.ptr_;
            }
    
            bool operator!=(const ConstIterator& other) const {
                return ptr_ != other.ptr_;
            }
    
        private:
            const T* ptr_;
        };
    
        // using iterator = T* ченьж на  Iterator
        using iterator = Iterator;
        using const_iterator = ConstIterator; // для констант
    
    private:
        value_type* arr_;
        size_type size_;
        size_type capacity_;

public:
    // Конструкторы + деструктор:
    vector() : arr_(nullptr), size_(0), capacity_(0) {}

    explicit vector(size_type n) : arr_(nullptr), size_(n), capacity_(n) {
        if (n > 0) {
            arr_ = new value_type[n]();
        }
    }

    vector(std::initializer_list<value_type> const &items)
        : arr_(nullptr), size_(items.size()), capacity_(items.size()) {
        if (size_ > 0) {
            arr_ = new value_type[capacity_];
            std::copy(items.begin(), items.end(), arr_);
        }
    }

    vector(const vector &v) : arr_(nullptr), size_(v.size_), capacity_(v.size_) {
        arr_ = new value_type[capacity_];
        for (size_type i = 0; i < size_; i++) {
            arr_[i] = v.arr_[i];
        }
    }

    vector(vector &&v) noexcept : arr_(v.arr_), size_(v.size_), capacity_(v.capacity_) {
        v.arr_ = nullptr;
        v.size_ = 0;
        v.capacity_ = 0;
    }

    ~vector() {
        if (arr_) {
            delete[] arr_;
        }
    }

    // Перегрузка:
    vector& operator=(vector &&v) noexcept {
        if (this != &v) {
            delete[] arr_;
            arr_ = v.arr_;
            size_ = v.size_;
            capacity_ = v.capacity_;
            v.arr_ = nullptr;
            v.size_ = 0;
            v.capacity_ = 0;
        }
        return *this;
    }

    // Доступ к элементам:
    reference at(size_type pos) {
        if (pos >= size_) {
            throw std::out_of_range("Position is out of range");
        }
        return arr_[pos];
    }

    const_reference at(size_type pos) const {
        if (pos >= size_) {
            throw std::out_of_range("Position is out of range");
        }
        return arr_[pos];
    }

    reference operator[](size_type pos) {
        return arr_[pos];
    }

    const_reference operator[](size_type pos) const {
        return arr_[pos];
    }

    const_reference front() const {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        return arr_[0];
    }

    reference front() {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        return arr_[0];
    }

    const_reference back() const {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        return arr_[size_ - 1];
    }

    reference back() {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        return arr_[size_ - 1];
    }

    T* data() {
        return arr_;
    }

    const T* data() const {
        return arr_;
    }

    // Итерирование:
    iterator begin() {
        return iterator(arr_);
    }

    const_iterator begin() const {
        return const_iterator(arr_);
    }

    iterator end() {
        return iterator(arr_ + size_);
    }

    const_iterator end() const {
        return const_iterator(arr_ + size_);
    }

    const_iterator cbegin() const noexcept {
         return const_iterator(arr_); 
        }

    const_iterator cend() const noexcept { 
        return const_iterator(arr_ + size_); 
    }

    // Информация о контейнере:
    bool empty() const noexcept {
        return size_ == 0;
    }

    size_type size() const noexcept {
        return size_;
    }

    size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }

    void reserve(size_type size) {
        if (size > max_size()) {
            throw std::out_of_range("Error: It doesn't fit");
        }
        if (size <= capacity_) {
            return;
        }
        value_type* new_arr = new value_type[size];
        for (size_type i = 0; i < size_; ++i) {
            new_arr[i] = arr_[i];
        }
        delete[] arr_;
        arr_ = new_arr;
        capacity_ = size;
    }

    size_type capacity() const noexcept {
        return capacity_;
    }

    void shrink_to_fit() {
        if (size_ == 0) {
            delete[] arr_;
            arr_ = nullptr;
            capacity_ = 0;
        } else if (capacity_ > size_) {
            value_type* new_arr = new value_type[size_];
            for (size_type i = 0; i < size_; ++i) {
                new_arr[i] = arr_[i];
            }
            delete[] arr_;
            arr_ = new_arr;
            capacity_ = size_;
        }
    }

    // Модификация контейнера:
    void clear() {
        size_ = 0;
    }

    iterator insert(iterator pos, const_reference value) {
        if (pos < begin() || pos > end()) {
            throw std::out_of_range("Incorrect position");
        }
        if (size_ + 1 > capacity_) {
            size_type new_capacity;
            if (capacity_ == 0) {
                new_capacity = 1;
            } else {
                new_capacity = capacity_ * 2;
            }
            reserve(new_capacity);
        }
        size_type index = pos - begin();
        for (size_type i = size_; i > index; --i) {
            arr_[i] = std::move(arr_[i - 1]);
        }
        arr_[index] = value;
        ++size_;
        return begin() + index;
    }

    void erase(iterator pos) {
        if (pos < begin() || pos >= end()) {
            throw std::out_of_range("Incorrect position");
        }
        size_type index = pos - begin();
        for (size_type i = index; i < size_ - 1; ++i) {
            arr_[i] = std::move(arr_[i + 1]);
        }
        --size_;
    }

    void push_back(const_reference value) {
        if (size_ + 1 > capacity_) {
            size_type new_capacity;
            if (capacity_ == 0) {
                new_capacity = 1;
            } else {
                new_capacity = capacity_ * 2;
            }
            reserve(new_capacity);
        }
        arr_[size_] = value;
        ++size_;
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Vector is empty");
        }
        --size_;
    }

    void swap(vector& other) {
        std::swap(arr_, other.arr_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    template <typename... Args>
    iterator insert_many(const_iterator pos, Args&&... args) {
    
    if (pos < cbegin() || pos > cend()) {
        throw std::out_of_range("Incorrect position");
    }
    
    size_type index = std::distance(cbegin(), pos);
    size_type num_el = sizeof...(args);
    
        if (size_ + num_el > capacity_) {
            size_type new_capacity;
            if (capacity_ == 0) {
                new_capacity = num_el;
            } else {
                new_capacity = std::max(capacity_ * 2, size_ + num_el);
            }
            reserve(new_capacity);
        }

        size_type index = pos - begin();
        for (size_type i = size_ + num_el - 1; i >= index + num_el; --i) {
            arr_[i] = std::move(arr_[i - num_el]);
        }
        
        size_type i = index;
        ((arr_[i++] = std::forward<Args>(args)), ...);

        size_ += num_el;
        return iterator(arr_ + index);
    }

    template <typename... Args>
    void insert_many_back(Args&&... args) {

        size_type num_el = sizeof...(args);

        if (size_ + num_el > capacity_) {
            size_type new_capacity;
            if (capacity_ == 0) {
                new_capacity = num_el;
            } else {
                new_capacity = std::max(capacity_ * 2, size_ + num_el);
            }
            reserve(new_capacity);
        }

        size_type i = size_;
        ((arr_[i++] = std::forward<Args>(args)), ...);

        size_ += num_el;
    }
};



} // namespace s21

#endif // S21_VECTOR_H