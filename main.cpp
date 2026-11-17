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

int next_avail_frame = 0;   /* idx in frames
                             * tracks how many frames have been used */
int wheel_start = 0;        /* index into frames, indicates starting 
                             * point of selection algorithm */


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
    
    /* convert and save args */
    num_pages = std::stoi(argv[1]);
    num_frames = std::stoi(argv[2]);
    num_cycles = std::stoi(argv[3]);
    
    if (num_pages < 1 || num_frames < 1 || num_cycles < 0 ){
        std::cout << "Usage: " << argv[0];
        std::cout << " num_pages > 0,  num_frames > 0, num_cycles >= 0\n";
        exit(1);
    }


    /* init frames array, simulating physical pages */
    frames.resize(num_frames);
    for (page& p : frames){
        p.page_num  = -1;
        p.referenced = false;
        p.modified = false;
    }

    std::uniform_int_distribution<int> gen_rand_page(0, num_pages - 1);
    std::uniform_int_distribution<int> gen_rand_write(0,1);

    /* main loop simulating a cycle of reading from or writing to a page */
    for (int i = 0; i < num_cycles; i++) {
        std::cout << "\n(cycle " << i + 1 << "):" << std::endl;

        /* get random page */
        int rand_page = gen_rand_page(gen);
        int write = gen_rand_write(gen);

        if (write){
            std::cout << "[READ] / [WRITE] page " << rand_page << std::endl;
        } else {
            std::cout << "[READ] page " << rand_page << std::endl;
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
                frames.at(next_avail_frame).modified = true;
            }
            next_avail_frame++;
        } else {
            std::cout << "Page fault. No frames available. Looking for victim...\n";
            page& victim = select_victim();
            std::cout << "Found victim: page " << victim.page_num << std::endl;
            victim.page_num = rand_page;
            victim.referenced = true;
            if (write){
                victim.modified = true;
            }
        }
    }

    std::cout << "\n*** Simulation done ***\n";
}


/* implement second chance page replacement algorithm */
page& select_victim(){
    /* iterate over all pages starting at wheel_start */

    /*
    for all pages to end
        if not ref and not mod
            save wheel_start - could wrap
            return this page
        if ref and mod
            ref to false
        if ref and not mod
            ref to false
        if not ref and mod
            "saving page to disk"
            mod to false
        
    wheel_start = 0
    */

    while (true){
        for (int i = wheel_start; i < num_frames; i++){
            page& p = frames.at(i);

            /* this page is not reference and modified, use as victim */
            if (!p.referenced && !p.modified){
                if (i + 1 < num_frames){
                    wheel_start = i + 1; 
                } else {
                    wheel_start = 0;
                }
                return p;
            }

            /* page has been reference and modified: save page to disk */
            if (p.referenced && p.modified){
                std::cout << "Saving page " << p.page_num << " to disk...";
                p.modified = false;
            }

            /* page reference but not modified: set reference to false */
            else if (p.referenced && !p.modified){
                p.referenced = false;
            }

            /* page not reference, but modified: save page to disk */
            else if (!p.referenced && p.modified){
                std::cout << "Saving page " << p.page_num << " to disk...";
                p.modified = false;
            }
        }

        /* reached the end of frames without finding victim, wrap to beginning */
        wheel_start = 0;
    }
}