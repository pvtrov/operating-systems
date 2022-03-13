//
// Created by mirabelka on 3/10/22.
//

#ifndef OPERATING_SYSTEMS_COURSE_FIRST_LIBRARY_H
#define OPERATING_SYSTEMS_COURSE_FIRST_LIBRARY_H

#include <stdio.h>

struct PointersMatrix{
    int lastAddedIndex;
    int size;
    struct MemoryBlock** blocks;
};

struct MemoryBlock{
    char content;
};


struct PointersMatrix* create_table(int size);
int wc_files(char* first, int numberOfFiles, struct PointersMatrix* matrix);
void remove_block(struct PointersMatrix* matrix, int indexToRemove);
void removingMatrix(struct PointersMatrix* matrix);


#endif //OPERATING_SYSTEMS_COURSE_FIRST_LIBRARY_H

