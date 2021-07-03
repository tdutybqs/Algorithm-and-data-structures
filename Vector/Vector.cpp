#ifndef true
#include <iostream>
#endif

template<typename T>
class vector;

template <typename T>
class my_iterator {
public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;

    reference operator+ (const int n) { return *(element + n); }
    reference operator- (const int n) { return *(element - n); }
    reference operator++ (const int) { return *element++; }
    reference operator-- (const int) { return *element--; }
    reference operator++ () { return *++element; }
    reference operator-- () { return *--element; }
    
    friend bool operator==(const my_iterator& lhs, const my_iterator& rhs){
        return lhs.element == rhs.element;
    }
    friend bool operator!=(const my_iterator& lhs, const my_iterator& rhs){
        return !(lhs == rhs);
    }

    pointer operator->() { return this->element; }
    const pointer operator->() const { return this->element; }

    reference operator[](int n) {
        return *(this->element + n);
    }
    const reference operator[](int n) const {
        return *(this->element + n);
    }

    reference operator* () { return *element; }
    const reference operator* () const { return *element; }
private:
    my_iterator() = default;
    my_iterator(T* first) : element(first) {}
    T* element{ nullptr };
    friend class vector<T>;
};

template <typename T>
class vector{
public:
    using iterator = T*;
    using const_iterator = const T*;
    vector() : my_data(nullptr), my_size(0), my_capacity(0) {};
    vector(const int size, const T elem) : my_size(size), my_capacity(size * 2)
        , my_data(static_cast<T*>(::operator new(sizeof(T)* my_capacity))) {
        for (int i = 0; i < size; ++i) {
            new (my_data + i) T(elem);
        }
    }
    vector(const vector& other) : my_size(other.my_size), my_capacity(other.my_capacity)
        , my_data(static_cast<T*>(::operator new(other.my_capacity))) {
        for (int i = 0; i < my_size; ++i) {
            new (my_data + i) T(other.my_data[i]);
        }
    }
    vector(std::initializer_list<T> list_elem) : my_size(0), my_capacity(list_elem.size() * 2)
        , my_data(static_cast<T*>(::operator new(sizeof(T)* list_elem.size() * 2))) {
        for (auto& elem : list_elem) {
            new (my_data + my_size) T(elem);
            ++my_size;
        }
    }
    vector(vector&& vec) : my_size(vec.my_size), my_capacity(vec.my_capacity), my_data(vec.my_data) {
        vec.my_data = nullptr;
    }

public:
    vector& operator=(vector&& vec) {
        if (this != &vec) {
            operator delete(my_data);
            my_size = vec.my_size;
            my_capacity = vec.my_capacity;
            my_data = vec.my_data;
            vec.my_data = nullptr;
            vec.my_capacity = 0;
            vec.my_size = 0;
        }
        return *this;
    }
    vector& operator=(const vector& vec) {
        if (this != &vec) {
            operator delete(my_data);
            my_size = vec.my_size;
            my_capacity = vec.my_capacity;
            my_data = static_cast<T*>(operator new(my_capacity));
            for (int i = 0; i < my_size; ++i) {
                new (my_data + i) T(vec.my_data[i]);
            }
        }
        return *this;
    }
    T& operator[] (const unsigned int index) const {
        return my_data[index];
    }

public:
    iterator begin() const { return my_data; }
    iterator end() const { return (my_data + my_size); }
    const_iterator cbegin() const { return my_data; };
    const_iterator cend() const { return (my_data + my_size); }

public:
    void pop_back() {
        my_data[my_size].~T();
        --my_size;
    }
    void resize(const unsigned int size) {
        if (size < my_size) {
            for (int i = my_size; i > size; --i)
                my_data[i].~T();
        }
        else if (size > my_size) {
            for (int i = my_size; i < size; ++i)
                this->push_back(0);
        }
        my_size = size;
    }
    void push_back(const T elem) {
        if (my_size < my_capacity) {
            new (my_data + my_size) T(elem);
        }
        else {
            reserve(my_capacity * 2);
            new (my_data + my_size) T(elem);
        }
        my_size++;
    }
    void reserve(const unsigned int n) noexcept {
        if (n > my_capacity) {
            my_capacity = n;
            T* tmp = static_cast<T*>(::operator new(sizeof(T) * my_capacity));
            for (int i = 0; i < my_size; ++i) {
                new (tmp + i) T(my_data[i]);
            }
            operator delete(my_data);
            my_data = tmp;
        }
    }

public:
    unsigned int capacity() const { return my_capacity; }
    unsigned int size() const { return my_size; }
    T& at(const unsigned int index) const {
        if (index >= my_size) throw std::runtime_error("Index out of range");
        else return my_data[index];
    }
    ~vector() noexcept {
        clear();
    };
    void clear() noexcept {
        for (int i = 0; i < my_size; ++i)
            my_data[i].~T();
        operator delete (my_data);
        my_data = nullptr;
        my_size = 0;
        my_capacity = 0;
    }

private:
    unsigned int my_capacity;
    unsigned int my_size;
    T* my_data;
};

// only ++
template <typename T>
void advance_impl(T& it, typename std::iterator_traits<T>::difference_type n, std::input_iterator_tag) {
    while (n > 0) {
        ++it;
        --n;
    }
}

//++ --
template <typename T>
void advance_impl(T& it, typename std::iterator_traits<T>::difference_type n, std::bidirectional_iterator_tag) {
    while (n > 0) {
        ++it;
        --n;
    }
    while (n < 0) {
        --it;
        ++n;
    }
}

// step = n
template <typename T>
void advance_impl(T& it, typename std::iterator_traits<T>::difference_type n, std::random_access_iterator_tag) {
    it += n;
}

template <typename T>
void advance(T& it, int n) {
    advance_impl(it, typename std::iterator_traits<T>::difference_type(n), typename std::iterator_traits<T>::iterator_category());
};
