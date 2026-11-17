#include <iostream>
#include <string>
#include <vector>
#include <random>

int num_pages;          /* number of virtual pages */
int num_frames;         /* number of physical frames */
int num_cycles;         /* number of r/w cycles the simulation runs */

int next_avail_frame;   /* tracks how many frames have been used */

struct page {
    int page_num;       /* the page being held by this physical frame */
    bool referenced;
    bool modified;
};

struct page *frames;

std::mt19937 gen(42);

int main(int argc, char *argv[]){

    /* input validation */
    if (argc != 4){
        std::cout << "Usage: " << argv[0];
        std::cout << " <num_pages>  <num_frames> <num_cycles>\n";
        exit(1);
    }

    num_pages = std::stoi(argv[1]);
    num_frames = std::stoi(argv[2]);
    num_cycles = std::stoi(argv[3]);

    /* init frames array, simulating physical pages */
    std::vector<page> frames(num_frames);
    for (page& p : frames){
        p.page_num  = -1;
        p.referenced = false;
        p.modified = false;
    }

    for (int i = 0; i < num_cycles; i++) {
        /* find random page */
        std::uniform_int_distribution<int> dist(0, num_pages - 1);
        int num = dist(gen); 
        std::cout << num << std::endl;
    }
}