#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <algorithm>  // Для std::copy
#include <stdexcept>  // Для std::out_of_range

namespace s21{


    template<typename T, size_t N>

    class array{

public:
    // Переопределения:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;

private:
    value_type data_[N];

public:
        // строим  да ломаем
            //обычный
    array() = default; 

        // если надо из листа
    array(std::initializer_list<value_type> const &items){
        if(items.size() > N){
           throw std::out_of_range("Many elements");
        }
        std::copy(items.begin(), items.end(), data_);
        for (size_t i = items.size(); i < N; i++){ // косяк, заполним нулями
            data_[i] = T{};
        }
    }

    // отксерим
    array(const array &a){
        std::copy(std::begin(a.data_), std::end(a.data_), std::begin(data_));
    }

    //переносим
    array(array &&a) noexcept{
        for(size_t i = 0; i < N; i++){
            data_[i] = std::move(a.data_[i]);
        }
    }    // array(array &&a) noexcept = default;  интерессно так сработает ? поидее должно

    // разберём
    ~array() = default;

    // перегрузим

    array& operator=(array&& a) noexcept {
        if (this != &a) {
            for (size_t i = 0; i < N; ++i) {
                data_[i] = std::move(a.data_[i]);
                a.data_[i]= T{}; // вожможно обнулять не надо если по тестам не попадём, тогда эту строку нафиг потереть надо
            }
        }
        return *this;
    }

    // access is allowed, or maybe not ;)

    reference at(size_type pos){
        if(pos >= N){
            throw std::out_of_range("Position is out of range");
            /* throw std::out_of_range("Index " + std::to_string(pos) + 
               " is out of range for array size " + 
               std::to_string(N));  это варик о нейронки, хз стоит так делать , а то сильно замудрёно хоть и понятно нафига. */
        }
        return data_[pos];
    }

    const_reference at(size_type pos) const {  // Для const объектов
        if (pos >= N) {
            throw std::out_of_range("Position is out of range");
        }
        return data_[pos];
    }

    reference operator[](size_type pos){
        return data_[pos];
    }

    const_reference operator[](size_type pos) const {
        return data_[pos];
    }
    
    reference front() {
        return data_[0];
    }

    const_reference front() const {
        return data_[0];
    }

    reference back(){
        return data_[N - 1];
    }

    const_reference back() const {
        return data_[N - 1];
    }

    iterator data(){
        return data_;
    }

    const_iterator data() const{
        return data_;
    }

    // итераторы :(

    iterator begin() noexcept {
        return data_;
    }

    const_iterator begin() const noexcept {
        return data_;
    }

    const_iterator cbegin() const noexcept {
        return begin(); // возможно это лишнии понты, в задании не прося посему шоб тесты допом не писать можно это грохнуть
    }

    iterator end() noexcept {
        return data_ + N;
    }

    const_iterator end() const noexcept {
        return data_ + N;
    }

    const_iterator cend() const noexcept {
        return end(); // аналогичноь cbegin, думаю тоже лишнии понты
    }

    //Капасити 

    constexpr bool empty() const noexcept {    //проверяет | или ||
        return N ==0;
    }

    size_type size() const noexcept{
        return N;
    }

    size_type max_size() const noexcept{
        return N;                               //  теже яйца только max
    }

    void swap(array& other) noexcept {
        std::swap_ranges(data_, data_ + N, other.data_);
    }


    void fill(const_reference value) noexcept {
        for (size_t i = 0; i < N; i++){
            data_[i]= value;
        }
    }
    
    };
    
  
    
   

} // namespace s21


#endif // S21_ARRAY_H