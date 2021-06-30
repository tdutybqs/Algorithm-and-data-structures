#include <iostream>

void insertionSort(int* arr, int size){
    std::cout<<"Insertion sort: "<<std::endl;
    int j;
    for (int i = 0; i < size; ++i){
        j = i - 1;
        while (j >= 0 && arr[j+1] > arr[j]){
            std::swap(arr[j+1], arr[j]);
            --j;
        }
    }
}

void bubbleSort(int* arr, int size){
    std::cout<<std::endl<<"Bubble sort: "<<std::endl;
    bool sorted = false;
    while (!sorted){
        sorted = true;
        for (int i = 0; i < size - 1; ++i){
            if (arr[i] > arr[i+1]){
                std::swap(arr[i], arr[i+1]);
                sorted = false;
            }
        }
    }
}

void printArr(int* arr, int size){
    for (int i = 0; i < size; ++i){
        std::cout<<arr[i]<<" ";
    }
}

int main(){
    int arr[10] {1,2,3,4,5,6,7,8,9,9};
    insertionSort(arr, 10);
    printArr(arr, 10);
    bubbleSort(arr, 10);
    printArr(arr, 10);
}