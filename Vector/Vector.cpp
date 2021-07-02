#include <iostream>

template <typename T>
class vector
{
public:
    vector() : my_data(nullptr), my_size(0), my_capacity(0) {};
    vector(int const size, T const elem) : my_size(size), my_capacity(size*2)
                                         , my_data(static_cast<T*>(::operator new(sizeof(T) * my_capacity))){
        for (int i = 0; i < size; ++i) {
            new (my_data + i) T(elem);
        }
    }            
    vector(const vector& other) : my_size(other.my_size), my_capacity(other.my_capacity)
                                   , my_data(static_cast<T*>(::operator new(other.my_capacity))){
        for (int i = 0; i < my_size; ++i){
            new (my_data + i) T(other.my_data[i]);
        }
    }
    vector(std::initializer_list<T> list_elem) : my_size(0), my_capacity(list_elem.size()*2)
                                               , my_data(static_cast<T*>(::operator new(sizeof(T) * list_elem.size()*2))){
        for (auto& elem: list_elem){
            new (my_data + my_size) T(elem);
            ++my_size; 
        }
    }
    vector(vector&& vec) : my_size(vec.my_size), my_capacity(vec.my_capacity), my_data(vec.my_data){
        vec.my_data = nullptr;
    }
    vector& operator=(vector&& vec){
        if (this != &vec){
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
    vector& operator=(const vector& vec){
        if (this != &vec){
            operator delete(my_data);
            my_size = vec.my_size;
            my_capacity = vec.my_capacity;
            my_data = static_cast<T*>(operator new(my_capacity));
            for (int i = 0; i < my_size; ++i){
                new (my_data + i) T(vec.my_data[i]);
            }
        }
        return *this;
    }
    void pop_back(){
        my_data[my_size].~T();
        --my_size;
    }
    void resize(unsigned int const size){
        if (size < my_size){
            for (int i = my_size; i > size; --i)
                my_data[i].~T();
        }
        else if (size > my_size){
            for (int i = my_size; i < size; ++i)
                this->push_back(0);
        }
        my_size = size;
    }
    void push_back(T const elem){
        if (my_size < my_capacity){
            new (my_data + my_size) T(elem);
        }
        else{
            reserve(my_capacity*2);
            new (my_data + my_size) T(elem);
        }
        my_size++;
    }
    unsigned int capacity(){return my_capacity;}
    unsigned int size() { return my_size; }
    T& operator[] (unsigned int index){
        return my_data[index];
    }
    T& at(unsigned int const index){
        if (index>=my_size) throw std::runtime_error("Index out of range");
        else return my_data[index];
    }
    ~vector(){
        clear();
    };
    void reserve(unsigned int const n){
        if (n > my_capacity){
            my_capacity = n;
            T* tmp = static_cast<T*>(::operator new(sizeof(T) * my_capacity));
            for (int i = 0; i < my_size; ++i){
                new (tmp + i) T(my_data[i]);
            }
            operator delete(my_data);
            my_data = tmp;
        }
    }
    void clear(){
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