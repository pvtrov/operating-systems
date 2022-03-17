//
// Created by mirabelka on 3/16/22.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/times.h>
#include <ctype.h>

long double time_sec(clock_t time){
    return (long double)(time) / sysconf(_SC_CLK_TCK);
}

void print_res(clock_t clock_start, clock_t clock_end, struct tms start_tms, struct tms end_tms, FILE* file){
    printf("\nEXECUTION TIME\n");
    printf("real %Lf\n", time_sec(clock_end - clock_start));
    printf("user %Lf\n", time_sec(end_tms.tms_utime - start_tms.tms_utime));
    printf("sys  %Lf\n\n", time_sec(end_tms.tms_stime - start_tms.tms_stime));
    fprintf(file, "\nEXECUTION TIME\n");
    fprintf(file, "real %Lf\n", time_sec(clock_end - clock_start));
    fprintf(file, "user %Lf\n", time_sec(end_tms.tms_utime - start_tms.tms_utime));
    fprintf(file, "sys  %Lf\n\n", time_sec(end_tms.tms_stime - start_tms.tms_stime));
}


void libCopying(char* fileFromName, char* fileToName){
    FILE* firstFile = fopen(fileFromName, "r+");
    FILE* secondFile = fopen(fileToName, "w");

    if (firstFile == NULL || secondFile == NULL){
        perror("Cannot open file");
        exit(1);
    }

    char ch;
    int counter;
    do {
        fread(&ch, sizeof(char), 1, firstFile);
        if (ch != '\n'){
            counter = 0;
            fwrite(&ch, sizeof(char), 1, secondFile);
        }else {
            counter ++;
            if (counter == 1){
                fwrite(&ch, sizeof(char), 1, secondFile);
            }
        }
    }while(feof(firstFile) == 0);
    fclose(firstFile);
    fclose(secondFile);
}


void sysCopying (char* firstFileName, char* secondFileName){
    int fileFrom = open(firstFileName, O_RDONLY);
    int fileTo = open(secondFileName, O_WRONLY);

    if (fileFrom < 0 || fileTo < 0){
        perror("Cannot open file:");
        exit(1);
    }

    char ch;
    bool end = false;
    int counter = 0;
    while (end == false){
        if(read(fileFrom, &ch, sizeof(char)) == 0){
            end = true;
            break;
        }
        if (ch == '\n'){
            counter ++;
            if (counter == 1){
                write(fileTo, &ch, sizeof(char));
            }
        }else{
            counter = 0;
            write(fileTo, &ch, sizeof(char));
        }
    }
    close(fileTo);
    close(fileFrom);

}

int main(int argc, char** argv){
    char* fileFromName;
    char* fileToName;

    if (argc == 1 || argc == 0){
        fileFromName = calloc(256, sizeof(char));
        fileToName = calloc(256, sizeof(char));
        printf("Give me files names:");
        scanf("%s", fileFromName);
        scanf("%s", fileToName);
    } else {
        fileFromName = argv[1];
        fileToName = argv[2];
    }

    FILE* result_file = fopen("pomiar_zad_1.txt", "w");
    struct tms start_tms;
    struct tms end_tms;
    clock_t clock_start;
    clock_t clock_end;
    struct tms start_tms2;
    struct tms end_tms2;
    clock_t clock_start2;
    clock_t clock_end2;

    printf("\n------------LIB------------\n");
    clock_start = times(&start_tms);
    libCopying(fileFromName, fileToName);
    clock_end = times(&end_tms);

    printf("\n\n------------SYS------------\n");
    clock_start2 = times(&start_tms2);
    sysCopying(fileFromName, fileToName);
    clock_end2 = times(&end_tms2);


    fprintf(result_file, "\n------LIB-----");
    printf("\n------LIB-----");
    print_res(clock_start, clock_end, start_tms, end_tms,result_file);

    fprintf(result_file, "\n------SYS-----");
    printf("\n------SYS-----");
    print_res(clock_start2, clock_end2, start_tms2, end_tms2, result_file);
}