#include <iostream>
#include <string>
#include <vector>

int num_pages;
int num_frames;

struct page {
    int page_num;
    bool referenced;
    bool modified;
};

struct page *frames;

int main(int argc, char *argv[]){

    /* input validation */
    if (argc != 3){
        std::cout << "Usage: " << argv[0] << " <num_pages>  <num_frames>\n";
        exit(1);
    }

    num_pages = std::stoi(argv[1]);
    num_frames = std::stoi(argv[2]);

    /* init frames array, simulating physical pages */
    std::vector<page> frames(num_frames);

    for (page& p : frames){
        p.page_num  = -1;
        p.referenced = false;
        p.modified = false;
    }
}