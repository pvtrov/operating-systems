#include <stdio.h>
#include "first_library.h"
#include <string.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>

// create_table rozmiar
// wc_files file1.txt file2.txt file3.txt
// remove_block index


long double time_sec(clock_t time){
    return (long double)(time) / sysconf(_SC_CLK_TCK);
}

void print_res(clock_t clock_start, clock_t clock_end, struct tms start_tms, struct tms end_tms){
    printf("real %Lf\n", time_sec(clock_end - clock_start));
    printf("user %Lf\n", time_sec(end_tms.tms_utime - start_tms.tms_utime));
    printf("sys  %Lf\n\n", time_sec(end_tms.tms_stime - start_tms.tms_stime));
}


int main(int argc, char** argv) {

    struct tms start_tms;
    struct tms end_tms;
    clock_t clock_start;
    clock_t clock_end;
    int size;

    int command_idx = 1;

    struct PointersMatrix* matrix = NULL;

    clock_start = times(&start_tms);
    while (command_idx < argc) {
        if (strcmp(argv[command_idx], "create_table") == 0) {
            size = atoi(argv[command_idx+1]);
            if (size == 0 ){
                printf("array must have more than 0 elements :(");
                exit(4);
            }
            matrix = create_table(size);
            command_idx += 2;
        }
        else if (strcmp(argv[command_idx], "wc_files") == 0) {
            int counter = 0;
            int cpy = command_idx + 1;
            char first[4000] = "wc ";
            for(;cpy < argc; cpy++){
                if(strcmp(argv[cpy], "create_table") == 0 ||
                    strcmp(argv[cpy], "wc_files") == 0 ||
                    strcmp(argv[cpy], "remove_block") == 0){
                    break;
                }
                else {
                    strcat(first, argv[cpy]);
                    strcat(first, " ");
                    counter ++;
                }
            }
            if(counter == 0){
                printf("there must be at least one file to count :)");
                exit(1);
            }
            wc_files(first, counter, matrix);
            command_idx += counter+1;
        }
        else if (strcmp(argv[command_idx], "remove_block") == 0){
            int indexToRemove = atoi(argv[command_idx+1]);
            if (indexToRemove > size-1){
                printf("block on this index do not exist");
                exit(2);
            }
            remove_block(matrix, indexToRemove);
            command_idx += 2;
        }
    }
    clock_end = times(&end_tms);
    print_res(clock_start, clock_end, start_tms, end_tms);

}



