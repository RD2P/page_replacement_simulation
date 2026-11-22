#include "page_replacement.h"

#include <iostream>

page& enhanced_second_chance(std::vector<page>& frames, int& wheel_start){
    while (true){
        for (std::size_t i = static_cast<std::size_t>(wheel_start);
             i < frames.size(); i++){
            page& p = frames.at(i);

            if (!p.referenced && !p.modified){
                if (i + 1 < frames.size()){
                    wheel_start = static_cast<int>(i + 1);
                } else {
                    wheel_start = 0;
                }
                return p;
            }

            if (p.referenced && p.modified){
                std::cout << "Saving page " << p.page_num << " to disk...";
                p.modified = false;
            } else if (p.referenced && !p.modified){
                p.referenced = false;
            } else if (!p.referenced && p.modified){
                std::cout << "Saving page " << p.page_num << " to disk...";
                p.modified = false;
            }
        }

        wheel_start = 0;
    }
}
