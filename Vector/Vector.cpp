#include <iostream>
#include <initializer_list>
#include <assert.h>

template <typename T>
class vector
{
public:
    vector() : my_data(nullptr), my_size(0), my_capacity(0) {};
    vector(int size, T elem) : my_size(size), my_capacity(size*2)
                             , my_data(static_cast<T*>(::operator new(sizeof(T) * my_capacity))){
        for (int i = 0; i < size; ++i) {
            new (my_data + i) T(elem);
        }
    }            
    vector(std::initializer_list<T> list_elem) : my_size(0), my_capacity(list_elem.size()*2)
                                               , my_data(static_cast<T*>(::operator new(sizeof(T) * list_elem.size()*2))){
        for (auto& elem: list_elem){
            new (my_data + my_size) T(elem);
            my_size++; 
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
    void pop_back(){
        assert(my_size > 1);
        my_data[my_size].~T();
        --my_size;
    }
    void resize(int size){
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
    void push_back(T elem){
        if (my_size < my_capacity){
            new (my_data + my_size) T(elem);
        }
        else{
            reserve(my_capacity*2);
            new (my_data + my_size) T(elem);
        }
        my_size++;
    }
    int size() { return my_size; }
    T& operator[] (int i){
        assert (i < my_size);
        return my_data[i];
    }
    ~vector(){
        clear();
    };
private:
    void clear(){
        for (int i = 0; i < my_size; ++i)
            my_data[i].~T();
        operator delete (my_data);
        my_data = nullptr;
        my_size = 0;
        my_capacity = 0;
    }
    void reserve(int n){
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
    int my_capacity;
    int my_size;
    T* my_data;
};