#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "headers/search_file_sizes.hpp"
#include "headers/DoublyLinkedList.hpp"
namespace fs = std::filesystem;

bool comp(fs::directory_entry* a, fs::directory_entry* b) {
    bool ret;
    try {
        ret = a->file_size() >= b->file_size();
    } catch(fs::filesystem_error& e) {
             std::cout << "Unable to access file or path " << a->path() << " OR " << b->path() << " ==> " << e.what() << std::endl;
    }
        return ret;
}

void search_file_sizes(const std::string& path, const std::string& output_path) {
    fs::perms required_perms = fs::perms::owner_write | fs::perms::owner_read;
    DoublyLinkedList<fs::directory_entry *> lista;
    try {
        fs::recursive_directory_iterator it(path);
        for(const auto & entry : it) {
            if(entry.status().permissions() >= (required_perms)) {
                if(!(entry.is_directory()) && entry.is_regular_file() && entry.exists()) {
                    lista.insertAtEnd(new fs::directory_entry(entry));
                }
            } else
                it.disable_recursion_pending();
        }
    } catch(fs::filesystem_error& e) {
            std::cout << "Unable to access file or path " << path << " ==> " << e.what() << std::endl;
    }
    lista.mergeSort(lista, comp);
    lista.printToFile(output_path);
}