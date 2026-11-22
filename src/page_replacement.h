#ifndef PAGE_REPLACEMENT_H
#define PAGE_REPLACEMENT_H

#include <vector>

struct page {
    int page_num;
    bool referenced;
    bool modified;
};

page& enhanced_second_chance(std::vector<page>& frames, int& wheel_start);

#endif
