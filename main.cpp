#include <iostream>
#include <string.h>

int num_pages;
int num_slots;

struct page {
    int page_num;
    bool referenced;
    bool modified;
};


int main(int argc, char *argv[]){

    /* input validation */
    if (argc != 3){
        std::cout << "Usage: " << argv[0] << " <num_pages>  <num_slots>\n";
    }

    num_pages = std::stoi(argv[1]);
    num_slots = std::stoi(argv[2]);

}