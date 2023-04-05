#include "headers/DoublyLinkedList.hpp"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;


/*
DOUBLY LINKED LIST CLASS, WITH MERGE SORT, TYPE-UNIVERSAL
REQUIRES TEMPLATE INSTANTIATION
REQUIRES CUSTOM BOOL COMPARISON FUNCTION FOR MERGE SORT(A >= B) -> DESCENDING SORT
REQUIRES CUSTOM PRINT_DATA FUNCTION
*/



template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    DoublyLinkedListNode<T> *current = head;
    while (current != nullptr) {
        DoublyLinkedListNode<T> *next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    count = 0;
}

template <typename T>
int DoublyLinkedList<T>::insertAtBeginning(T value) {
    DoublyLinkedListNode<T> *newNode = nullptr;
    try {
        newNode = new DoublyLinkedListNode<T>(value);
    }
    catch (const std::bad_alloc &ex) {
        std::cout << "Error: Failed to allocate memory for new node: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }

    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    count++;
    return EXIT_SUCCESS;
}

template <typename T>
int DoublyLinkedList<T>::insertAtEnd(T value) {
        DoublyLinkedListNode<T>* newNode = nullptr;
        try {
            newNode = new DoublyLinkedListNode<T>(value);
        } catch(const std::bad_alloc& ex) {
            std::cout << "Error: Failed to allocate memory for new node: " << ex.what() << '\n';
            return EXIT_FAILURE;
        }

        if (isEmpty()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
        return EXIT_SUCCESS;
}

template <typename T>
int DoublyLinkedList<T>::insertAtPosition(int position, T value) {
        if (position < 0 || position > count) {
            std::cout << "Error: Invalid position: " << position << '\n';
            return EXIT_FAILURE;
        }

        if (position == 0) {
            return insertAtBeginning(value);
        } else if (position == count) {
            return insertAtEnd(value);
        } else {
            DoublyLinkedListNode<T>* current = head;
            DoublyLinkedListNode<T>* newNode = nullptr;
            try {
                newNode = new DoublyLinkedListNode<T>(value);
            } catch(const std::bad_alloc& ex) {
                std::cout << "Error: Failed to allocate memory for new node: " << ex.what() << '\n';
                return EXIT_FAILURE;
            }

            for (int i = 0; i < position; i++) {
                current = current->next;
            }

            current->prev->next = newNode;
            newNode->prev = current->prev;
            newNode->next = current;
            current->prev = newNode;
            count++;
            return EXIT_SUCCESS;
        }
}

template <typename T>
int DoublyLinkedList<T>::removeFromBeginning() {
        if (isEmpty()) {
            std::cout << "Error: List is empty\n";
            return EXIT_FAILURE;
        }

        DoublyLinkedListNode<T>* temp = head;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr;
        } else {
            head->prev = nullptr;
        }

        delete temp;
        count--;
        return EXIT_SUCCESS;
}

template <typename T>
int DoublyLinkedList<T>::removeFromEnd() {
        if (isEmpty()) {
            std::cout << "Error: List is empty\n";
            return EXIT_FAILURE;
        }

        DoublyLinkedListNode<T>* temp = tail;
        tail = tail->prev;

        if (tail == nullptr) {
            head = nullptr;
        } else {
            tail->next = nullptr;
        }

        delete temp;
        count--;
        return EXIT_SUCCESS;
}

template <typename T>
int DoublyLinkedList<T>::removeFromPosition(int position) {
        if (isEmpty()) {
            std::cout << "Error: List is empty\n";
            return EXIT_FAILURE;
        }

        if (position < 0 || position >= count) {
            std::cout << "Error: Invalid position: " << position << '\n';
            return EXIT_FAILURE;
        }

        if (position == 0) {
            return removeFromBeginning();
        } else if (position == count - 1) {
            return removeFromEnd();
        } else {
            DoublyLinkedListNode<T>* current = head;

            for (int i = 0; i < position; i++) {
                current = current->next;
            }

            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            count--;
            return EXIT_SUCCESS;
        }
}

template <typename T>
void DoublyLinkedList<T>::print(void (*custom_print)(T)) const {
        DoublyLinkedListNode<T>* current = head;
        while (current != nullptr) {
            custom_print(current->data);
            std::cout << '\n';
            current = current->next;
        }
        std::cout << '\n';
}

//-----------
// MERGE SORT
// !!!!!!!IMPORTANT!!!!!!! Requires custom bool function for data comparison ---> first_data >= second_data -> sorting in descending order 
//------------

// Function to divide the Doubly Linked List into two halves
template <typename T>
DoublyLinkedListNode<T>* DoublyLinkedList<T>::getMiddle(DoublyLinkedListNode<T>* head) {
    DoublyLinkedListNode<T>* slow = head;
    DoublyLinkedListNode<T>* fast = head->next;

    while (fast != nullptr) {
        fast = fast->next;

        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    return slow;
}

// Function to merge two sorted Doubly Linked Lists
template <typename T>
DoublyLinkedListNode<T>* DoublyLinkedList<T>::merge(DoublyLinkedListNode<T>* left, DoublyLinkedListNode<T>* right, bool (*comp)(T, T)) {
    if (left == nullptr) {
        return right;
    }

    if (right == nullptr) {
        return left;
    }

    DoublyLinkedListNode<T>* merged = nullptr;

    if (comp(left->data, right->data)) {
        merged = left;
        merged->next = merge(left->next, right, comp);
        merged->next->prev = merged;
    }
    else {
        merged = right;
        merged->next = merge(left, right->next, comp);
        merged->next->prev = merged;
    }

    return merged;
}

// Recursive function to sort the Doubly Linked List using Merge Sort algorithm
template <typename T>
DoublyLinkedListNode<T>* DoublyLinkedList<T>::mergeSort(DoublyLinkedListNode<T>* head, bool (*comp)(T, T)) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    DoublyLinkedListNode<T>* middle = getMiddle(head);
    DoublyLinkedListNode<T>* nextOfMiddle = middle->next;

    middle->next = nullptr;

    DoublyLinkedListNode<T>* left = mergeSort(head, comp);

    DoublyLinkedListNode<T>* right = mergeSort(nextOfMiddle, comp);

    DoublyLinkedListNode<T>* sortedList = merge(left, right, comp);

    return sortedList;
}

template <typename T>
void DoublyLinkedList<T>::mergeSort(DoublyLinkedList<T>& list, bool (*comp)(T, T)) {
    if (list.isEmpty() || list.getCount() == 1) {
        return;
    }

    list.head = mergeSort(list.head, comp);
    DoublyLinkedListNode<T>* temp = list.head;

    while (temp->next != nullptr) {
        temp = temp->next;
    }

    list.tail = temp;
}

//function operating on fs::directory_entry *, that printToFile at output_path
template<>
int DoublyLinkedList<fs::directory_entry *>::printToFile(const std::string& output_path) {
    try {
        // Open the file in output mode and create it if it doesn't exist
        std::ofstream outfile(output_path);
        DoublyLinkedListNode<fs::directory_entry *>* current = head;
        while (current != nullptr) {
            if(current->data->file_size() >= 1000000000)
                outfile << current->data->path() << " SIZE: " << current->data->file_size() / 1000000000.0 << " GB\n";
            else if(current->data->file_size() >= 1000000)
                outfile << current->data->path() << " SIZE: " << current->data->file_size() / 1000000.0 << " MB\n";
            else if(current->data->file_size() >= 1000)
                outfile << current->data->path() << " SIZE: " << current->data->file_size() / 1000.0 << " KB\n";
            else
                outfile << current->data->path() << " SIZE: " << current->data->file_size() << " B\n";
            current = current->next;
        }
        std::cout << '\n';
    outfile.close();
  }
  catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
return EXIT_SUCCESS;
}

//EXPLICIT TEMPLATE INSTANTIATIONS
template class DoublyLinkedList<fs::directory_entry *>;
template class DoublyLinkedListNode<fs::directory_entry *>;




