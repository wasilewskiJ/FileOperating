#ifndef GUI_H_
#define GUI_H_
#include "DoublyLinkedList.hpp"
#include "del_empty_dir.hpp"
#include "search_file_sizes.hpp"
#include <iostream>
#include <string>

class GUI {
private:
    std::string path;
    std::string output_path;
    bool exit;
    void exitProgram();
    void takeAction(int action);
    void showMenu();
    void deletion();
    void file_sizes();
public:
    GUI();
    void start();
};

#endif