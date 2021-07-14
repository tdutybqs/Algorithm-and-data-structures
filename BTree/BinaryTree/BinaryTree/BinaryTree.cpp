#include <iostream> 

template <typename T>
struct node {
    node() : value(T()), left(nullptr), right(nullptr) {};
    node(T v) : value(v), left(nullptr), right(nullptr) {};
    ~node() = default;
    T value;
    node<T>* left;
    node<T>* right;
};


template <typename T>
class btree {
public:
    btree() : root(static_cast<decltype(root)>(operator new(sizeof(node<T>)))) {};
    btree(T value) : root(static_cast<decltype(root)>(operator new(sizeof(node<T>(value))))) {
        root->value = value;
    };
    ~btree() = default;

    //for testing purpose only
    void insert(T value) {
        if (root->value < value) {
            root->right = new node<T>(value);
        }
    }
    T& get_root() {
        return root->value;
    }
private:
    node<T>* root;
};


int main() {
    btree<int> test;
    test.insert(4);
    std::cout << test.get_root() << std::endl;
}
