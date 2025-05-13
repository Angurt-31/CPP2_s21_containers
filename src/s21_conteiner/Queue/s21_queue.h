#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <initializer_list>
#include <cstddef>
#include <utility>
#include <stdexcept>

namespace s21 {

template <typename T>
class queue {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;

    // Конструктор + деструкторы + 
    queue() : head_(nullptr), tail_(nullptr), size_(0) {}

    queue(std::initializer_list<value_type> const &items) : queue() {
        for (const auto& item : items) {
            push(item);
        }
    }

    queue(const queue &q) : queue() {
        Node* current = q.head_;
        while (current != nullptr) {
            push(current->data_);
            current = current->next_;
        }
    }

    queue(queue&& q) noexcept : head_(q.head_), tail_(q.tail_), size_(q.size_) {
        q.head_ = nullptr;
        q.tail_ = nullptr;
        q.size_ = 0;
    }

    ~queue() {
        while (head_ != nullptr) {
            Node* temp = head_;
            head_ = head_->next_;
            delete temp;
        }
    }

    // Перегрузка присваивания копирования + перемещениия
    queue& operator=(const queue &q) {
        if (this != &q) {
            // Очищаем
            while (head_ != nullptr) {
                Node* temp = head_;
                head_ = head_->next_;
                delete temp;
            }
            tail_ = nullptr;
            size_ = 0;
            // Копируем
            Node* current = q.head_;
            while (current != nullptr) {
                push(current->data_);
                current = current->next_;
            }
        }
        return *this;
    }

    queue& operator=(queue&& q) noexcept {
        if (this != &q) {
            // Очищаем 
            while (head_ != nullptr) {
                Node* temp = head_;
                head_ = head_->next_;
                delete temp;
            }
            // из q
            head_ = q.head_;
            tail_ = q.tail_;
            size_ = q.size_;
            // Обнуляем q
            q.head_ = nullptr;
            q.tail_ = nullptr;
            q.size_ = 0;
        }
        return *this;
    }

    // Доступ к голове + хвосту
    const_reference front() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return head_->data_;
    }

    const_reference back() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return tail_->data_;
    }

    // Capacity
    bool empty() const {           // | или ||
        return head_ == nullptr;
    }

    size_type size() const {
        return size_;
    }

    // чёто туда сюда
    // + к хвоту
    void push(const_reference value) {
        Node* new_node = new Node(value, nullptr, tail_);
        if (tail_ != nullptr) {
            tail_->next_ = new_node;
        } else {
            head_ = new_node;
        }
        tail_ = new_node;
        size_++;
    }

        // +++++ к хвосту
        template <typename... Args>
        void insert_many_back(Args&&... args) {
            (push(std::forward<Args>(args)), ...);
        }

    // - башка 
    void pop() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        Node* temp = head_;
        head_ = head_->next_;
        if (head_ != nullptr) {
            head_->prev_ = nullptr;
        } else {
            tail_ = nullptr;
        }
        delete temp;
        size_--;
    }

    // ченж
    void swap(queue& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }

     // смотреть можно , трогать нельзя
     class const_iterator {
        public:
            const_iterator() : current_(nullptr) {}
            const_iterator(const Node* node) : current_(node) {}
    
            const_reference operator*() const {
                return current_->data_;
            }
    
            const T* operator->() const {
                return &current_->data_;
            }
    
            const_iterator& operator++() {
                current_ = current_->next_;
                return *this;
            }
    
            const_iterator operator++(int) {
                const_iterator tmp = *this;
                ++(*this);
                return tmp;
            }
    
            const_iterator& operator--() {
                current_ = current_->prev_;
                return *this;
            }
    
            const_iterator operator--(int) {
                const_iterator tmp = *this;
                --(*this);
                return tmp;
            }
    
            bool operator==(const const_iterator& other) const {
                return current_ == other.current_;
            }
    
            bool operator!=(const const_iterator& other) const {
                return current_ != other.current_;
            }
    
        private:
            const Node* current_;
        };
    
        const_iterator begin() const {
            return const_iterator(head_);
        }
    
        const_iterator end() const {
            return const_iterator(nullptr);
        }

private:
    // Структура Node | юзать чужой лист контрпродуктивно |
    struct Node {
        value_type data_;
        Node* next_;
        Node* prev_;
        //Ноду както так соберём
        Node(const_reference value, Node* next = nullptr, Node* prev = nullptr)
            : data_(value), next_(next), prev_(prev) {}
    };

    Node* head_;
    Node* tail_;
    size_type size_;
};

} // namespace s21
// я художник не местный попишу и уеду

#endif // S21_QUEUE_H