#include <iostream>
#include <assert.h>

template <typename T>
class List{
public:
    List(): head(nullptr), my_size(0), my_empty(true) {}
    List(std::initializer_list<T> list_elem): my_size(0){
        for(auto& elem: list_elem){
            push_back(elem);
        }
        check_empty();
    }
    void push_back(T elem){
        if (this->head == nullptr) this->head = new Node<T>(elem);
        else{
            Node<T> *temp = this->head;
            while (temp->next!=nullptr){
                temp = temp->next;
            }
            temp->next = new Node<T>(elem);
        }
        ++my_size;
    }
    T& operator[](int index){
        assert(index < my_size);
        Node<T>* temp = this->head;
        while (index){
            temp = temp->next;
            --index;
        }
        return temp->data;
    }
    bool empty(){return my_empty;}
    void pop_back(){
        Node<T> *temp = this->head;
        while (temp->next!=nullptr){
            temp = temp->next;
        }
        delete temp;
        --my_size;
        check_empty();
    }
    auto front(){
        return this->head->data;
    }
    void pop_front(){
        Node<T> *temp = this->head->next;
        delete this->head;
        this->head = temp;
        --my_size;
        check_empty();
    }
    int size() {return my_size;}
    ~List(){
        clear();
    }
    void clear(){
        while (my_size){
            pop_front();
        }
    }
private:
    void check_empty(){
        if (my_size > 0) my_empty = false;
        else my_empty = true;
    }
    template <typename U>
    struct Node{
        Node(U value, Node* pnext = nullptr): data(value), next(pnext){}
        U data;
        Node<U>* next;
    };
    bool my_empty;
    int my_size;
    Node<T>* head;
};