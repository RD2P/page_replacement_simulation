#include <iostream>
#include <string>
#include <vector>
#include <random>

int num_pages;          /* number of virtual pages */
int num_frames;         /* number of physical frames */
int num_cycles;         /* number of r/w cycles the simulation runs */


struct page {
    int page_num;       /* the page being held by this physical frame */
    bool referenced;
    bool modified;
};

std::vector<page> frames;


page& select_victim();

/* idx in frames
 * tracks how many frames have been used */
int next_avail_frame = 0;   

// std::random_device rd;   /* use seed when testing is done */
// std::mt19937 gen(rd);


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
    frames.resize(num_frames);

    for (page& p : frames){
        p.page_num  = -1;
        p.referenced = false;
        p.modified = false;
    }

    std::uniform_int_distribution<int> gen_rand_page(0, num_pages - 1);
    std::uniform_int_distribution<int> gen_rand_write(0,1);
    for (int i = 0; i < num_cycles; i++) {
        /* get random page */
        int rand_page = gen_rand_page(gen);
        int write = gen_rand_write(gen);

        if (write){
            std::cout << "Reading/Writing page " << rand_page << std::endl;
        } else {
            std::cout << "Reading page " << rand_page << std::endl;
        }

        int curr = 0;
        
        /* check if page is already in a frame */
        while (curr < next_avail_frame){
            if (frames.at(curr).page_num == rand_page) {
                frames.at(curr).referenced = true;
                if (write){
                    frames.at(curr).modified = true;
                }
                break;
            }
            curr++;
        }
        
        /* the page is already in a frames */
        if (curr < next_avail_frame){
            continue;
        } 
        /* there is available slot */
        else if (next_avail_frame < num_frames){ 
            std::cout << "Page fault. There is a frame available.\n";
            /* use next available frame for the page */
            frames.at(next_avail_frame).page_num = rand_page;
            frames.at(next_avail_frame).referenced = true;
            if (write){
                frames.at(curr).modified = true;
            }
            next_avail_frame++;
        } else {
            std::cout << "Page fault. No frames available. Looking for victim...\n";
            page& victim = select_victim();
            std::cout << "Found victim: page " << victim.page_num << std::endl;
            victim.page_num = rand_page;
            victim.referenced = true;
            if (write){
                frames.at(curr).modified = true;
            }
        }
    }
}


/* implement second chance page replacement algorithm */
page& select_victim(){
    /*  */

    return frames.at(0);
}