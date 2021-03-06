#include <iostream>

template <typename T>
class List{
public:
    List(): head(nullptr), my_size(0) {}
    List(std::initializer_list<T> list_elem): my_size(0){
        for(auto& elem: list_elem){
            push_back(elem);
        }
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
    T& operator[](unsigned int index){
        Node<T>* temp = this->head;
        while (index){
            temp = temp->next;
            --index;
        }
        return temp->data;
    }
    bool empty(){return my_size == 0;}
    void pop_back(){
        Node<T> *temp = this->head;
        while (temp->next!=nullptr){
            temp = temp->next;
        }
        delete temp;
        --my_size;
    }
    T front(){
        return this->head->data;
    }
    void insert(T value, unsigned int position){
        Node<T>* temp = this->head;
        while (position){
            temp = temp->next;
            --position;
        }
        temp->data = value;
    }
    void pop_front(){
        Node<T>* temp = this->head->next;
        delete this->head;
        this->head = temp;
        --my_size;
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
    void swap(unsigned int first, unsigned int second){
        Node<T>* ftemp = this->head;
        Node<T>* stemp = this->head;
        while (first){
            ftemp = ftemp->next;
            --first;
        }
        while (second){
            stemp = stemp->next;
            --second;
        }
        T temp_data = ftemp->data;
        ftemp->data = stemp->data;
        stemp->data = temp_data;
    }
    int find(T value){
        Node<T>* temp = this->head;
        int position = 0;
        while (temp->next != nullptr){
            ++position;
            if (temp->data == value) return position;
            temp = temp->next;
        }
        return -1;
    }
private:
    template <typename U>
    struct Node{
        Node(U value, Node* pnext = nullptr): data(value), next(pnext){}
        U data;
        Node<U>* next;
    };
    unsigned int my_size;
    Node<T>* head;
};