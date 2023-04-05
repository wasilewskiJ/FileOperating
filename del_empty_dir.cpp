#include "headers/del_empty_dir.hpp"
#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

void del_empty_dir(const std::string& path) {
    fs::perms required_perms = fs::perms::owner_write | fs::perms::owner_read;
    try {
        for(const auto & entry : fs::directory_iterator(path)) {

            if(entry.status().permissions() >= (required_perms) && entry.is_directory() && entry.exists()) {
                if(!fs::is_empty(entry.path())) {
                    del_empty_dir(entry.path());
                } else {
                    std::cout << "DELETING DIR: " << entry.path() << std::endl;
                    fs::remove(entry.path());
                    continue;
                }
                //checks if after recursion directory is empty now
                if(fs::is_empty(entry.path()))
                 {
                    std::cout << "DELETING DIR: " << entry.path() << std::endl; 
                    fs::remove(entry.path());
                }
            }
        }
    }
    catch(std::filesystem::filesystem_error& e) {
            std::cout << "Unable to access file or path " << path << " ==> " << e.what() << std::endl;
    }
}