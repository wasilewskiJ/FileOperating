#ifndef SEARCH_FILE_SIZES_HPP
#define SEARCH_FILE_SIZES_HPP

#include <filesystem>
#include <string>
#include "DoublyLinkedList.hpp"
namespace fs = std::filesystem;

bool comp(fs::directory_entry* a, fs::directory_entry* b);
void custom_print(fs::directory_entry* a);
void search_file_sizes(const std::string& path, const std::string& output_path);
#endif