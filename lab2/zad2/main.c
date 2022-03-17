//
// Created by mirabelka on 3/17/22.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/times.h>

long double time_sec(clock_t time){
    return (long double)(time) / sysconf(_SC_CLK_TCK);
}

void print_res(clock_t clock_start, clock_t clock_end, struct tms start_tms, struct tms end_tms, FILE* file){
    printf("\nEXECUTION TIME\n");
    printf("real %Lf\n", time_sec(clock_end - clock_start));
    printf("user %Lf\n", time_sec(end_tms.tms_utime - start_tms.tms_utime));
    printf("sys  %Lf\n\n", time_sec(end_tms.tms_stime - start_tms.tms_stime));
}


int libCountSign(char sign, char* file){
    FILE* fileToSearchIn = fopen(file, "r");

    if (fileToSearchIn == NULL){
        perror("Cannot open file");
        exit(1);
    }

    char c;
    int signCounter = 0;
    do{
        fread(&c, sizeof(char), 1, fileToSearchIn);
        if (c == sign){
            signCounter ++;
        }

    }while(feof(fileToSearchIn) == 0);
    fclose(fileToSearchIn);

    return signCounter;
}


int libCountLines(char sign, char* file){
    FILE* fileToSearchIn = fopen(file, "r");

    if (fileToSearchIn == NULL){
        perror("Cannot open file");
        exit(1);
    }

    char c;
    int lineCounter = 0;
    int newLineSignCounter = 0;
    do{
        fread(&c, sizeof(char), 1, fileToSearchIn);
        if((int) c == '\n'){
            if(newLineSignCounter != 0){
                lineCounter ++;
                newLineSignCounter = 0;
            }
        }
        if (c == sign){
            if (newLineSignCounter == 0){
                newLineSignCounter ++;
            }
        }

    }while(feof(fileToSearchIn) == 0);
    fclose(fileToSearchIn);

    return lineCounter;
}


int sysCountSign(char sign, char* file){
    int fileToSearchIn = open(file, O_RDONLY);

    if (fileToSearchIn < 0){
        perror("Cannot open file:");
        exit(1);
    }

    char c;
    bool end = false;
    int signCounter = 0;
    while (end == false){
        if (read(fileToSearchIn, &c, sizeof(char)) == 0){
            end = true;
            break;
        }
        if(c == sign){
            signCounter++;
        }
    }
    close(fileToSearchIn);
    return signCounter;
}

int sysCountLines(char sign, char* file){
    int fileToSearchIn = open(file, O_RDONLY);

    if (fileToSearchIn < 0){
        perror("Cannot open file:");
        exit(1);
    }

    char c;
    bool end = false;
    int lineCounter = 0;
    int newLineSignCounter = 0;
    while (end == false){
        if (read(fileToSearchIn, &c, sizeof(char)) == 0){
            end = true;
            break;
        }
        if(c == '\n'){
            if(newLineSignCounter != 0){
                lineCounter ++;
                newLineSignCounter = 0;
            }
        }
        if (c == sign){
            if(newLineSignCounter == 0){
                newLineSignCounter ++;
            }
        }
    }
    close(fileToSearchIn);
    return lineCounter;
}


int main(int argc, char** argv){
    char* sign;
    char* file;

    if (argc == 1 || argc == 0){
        sign = calloc(256, sizeof(char));
        file = calloc(256, sizeof(char));
        printf("Give me which sign you want me to count: ");
        scanf("%s", sign);
        printf("Give me file in which this sign occurs: ");
        scanf("%s", file);
    } else {
        sign = argv[1][0];
        file = argv[2];
    }

    FILE* result_file = fopen("pomiar_zad_2.txt", "w");
    struct tms start_tms;
    struct tms end_tms;
    clock_t clock_start;
    clock_t clock_end;
    struct tms start_tms2;
    struct tms end_tms2;
    clock_t clock_start2;
    clock_t clock_end2;

    clock_start = times(&start_tms);
    int libSign = libCountSign(sign, file);
    clock_end = times(&end_tms);

    clock_start2 = times(&start_tms2);
    int libLines = libCountLines(sign, file);
    clock_end2 = times(&end_tms2);

    clock_start = times(&start_tms);
    int sysSign = sysCountSign(sign, file);
    clock_end = times(&end_tms);

    clock_start2 = times(&start_tms2);
    int sysLines = sysCountLines(sign, file);
    clock_end2 = times(&end_tms2);

    printf("%s", "for a sign in poem.txt file\n");
    printf("\n sign: %d  lines: %d", libSign, libLines);
    print_res(clock_start, clock_end, start_tms, end_tms,result_file);

    printf("\n sign: %d  lines: %d", sysSign, sysLines);
    print_res(clock_start2, clock_end2, start_tms2,end_tms2, result_file);

}