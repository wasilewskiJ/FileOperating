#include "headers/GUI.hpp"

GUI::GUI() {
    this->exit = false;
}

void GUI::showMenu() {
    std::cout << std::endl << "==Menu==" << std::endl;
    std::cout << "0 - Recursively delete empty folders" << std::endl;
    std::cout << "1 - Print the sizes of all files in the directory tree to an external file" << std::endl;
    std::cout << "2 - Exit program" << std::endl;
    std::cout << "Choose action: ";
}

void GUI::deletion() {
    std::string path;
    std::cout << "Please enter the path to the directory tree where you want to recursively delete empty folders: \n";
    std::cin >> path;
    del_empty_dir(path);
}

void GUI::takeAction(int action) {
    switch(action) {
        case 0:
            this->deletion();
            break;
        case 1:
            this->file_sizes();
            break;
        case 2:
            this->exitProgram();
            break;
        default:
            std::cout << "Bad number" << std::endl;
            break;
    }
}

void GUI::file_sizes() {
    std::string path, output_path;
    std::cout << "Please specify the path to the directory tree where you want to check file sizes: \n";
    std::cin >> path;
    std::cout << "Please enter the path with the name of the file where the search result will be saved(for example /home/zbyszek/file.txt -> if file exists will appear empty in results): \n";
    std::cin >> output_path;
    search_file_sizes(path, output_path);
}

void GUI::exitProgram()
{
    this->exit = true;
    std::cout << "GOODBYE." << std::endl;
}

void GUI::start()
{
    int action;
    std::cout << "Welcome in File-Operating program." << std::endl;

    while (!this->exit) {
        this->showMenu();
        std::cin >> action;

        this->takeAction(action);
    }
}
