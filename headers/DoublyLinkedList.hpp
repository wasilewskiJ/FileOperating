#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP
#include<string>
/*
DOUBLY LINKED LIST CLASS, WITH MERGE SORT, TYPE-UNIVERSAL
REQUIRES TEMPLATE INSTANTIATION
REQUIRES CUSTOM BOOL COMPARISON FUNCTION FOR MERGE SORT(A >= B) -> DESCENDING SORT
REQUIRES CUSTOM PRINT_DATA FUNCTION
*/



template <typename T>
class DoublyLinkedList;

template <typename T>
class DoublyLinkedListNode {
    public:
        friend class DoublyLinkedList<T>;
    private:
        T data;
        DoublyLinkedListNode<T>* next;
        DoublyLinkedListNode<T>* prev;
        DoublyLinkedListNode(T value) : data(value), next(nullptr), prev(nullptr) {}
};



template <typename T>
class DoublyLinkedList {
private:
    DoublyLinkedListNode<T>* head;
    DoublyLinkedListNode<T>* tail;
    int count;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    ~DoublyLinkedList();

    int getCount() const {
        return count;
    }

    bool isEmpty() const {
        return count == 0;
    }

    DoublyLinkedListNode<T>* getHead() {
        return head;
    }

    int insertAtBeginning(T value);
    int insertAtEnd(T value);
    int insertAtPosition(int position, T value);
    int removeFromBeginning();
    int removeFromEnd();
    int removeFromPosition(int position);
    int printToFile(const std::string& output_path);
    void print(void (*custom_print)(T)) const; 

    ////---------
    // MERGE SORT
    // !!!!!!!IMPORTANT!!!!!!! Requires custom bool function for data comparison ---> first_data >= second_data -> sorting in descending order 
    //------------
    // Function to merge two sorted Doubly Linked Lists
    DoublyLinkedListNode<T>* merge(DoublyLinkedListNode<T>* left, DoublyLinkedListNode<T>* right, bool (*comp)(T, T));
    // Function to divide the Doubly Linked List into two halves
    DoublyLinkedListNode<T>* getMiddle(DoublyLinkedListNode<T>* head);
    // Recursive function to sort the Doubly Linked List using Merge Sort algorithm
    DoublyLinkedListNode<T>* mergeSort(DoublyLinkedListNode<T>* head, bool (*comp)(T, T));
    // Wrapper function to sort the Doubly Linked List using Merge Sort algorithm
    void mergeSort(DoublyLinkedList<T>& list, bool (*comp)(T, T));
};
#endif