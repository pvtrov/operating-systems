//
// Created by mirabelka on 3/25/22.
//

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>


long double time_sec(clock_t time){
    return (long double)(time) / sysconf(_SC_CLK_TCK);
}


void print_res(clock_t clock_start, clock_t clock_end, struct tms start_tms, struct tms end_tms){
    printf("real %Lf\n", time_sec(clock_end - clock_start));
    printf("user %Lf\n", time_sec(end_tms.tms_utime - start_tms.tms_utime));
    printf("sys  %Lf\n\n", time_sec(end_tms.tms_stime - start_tms.tms_stime));
}


double function(double x){
    return 4/(x*x + 1);
}

double range(double from , double to){
    return function((from+to)/2.0) * (to-from);
}

void printToFile(int counter, double result){
    char* res = calloc(sizeof(char), 256);
    sprintf(res, "w%d.txt", counter);
    FILE* wantedFile = fopen(res, "wr");
    fprintf(wantedFile, "%f", result);
    free(res);
    fclose(wantedFile);
}

void countRange(int i, int numberOfProcesses, double rectangleWidth){
    double i_ = (double) i;
    double max_ = (double) numberOfProcesses;

    double left = ((i_-1)/max_);
    double right= (i_/max_);

    double result = 0.0;
    while (left + rectangleWidth <= right){
        result += range(left, left + rectangleWidth);
        right -= rectangleWidth;
    }

    result += range(left, right);
    printToFile(i, result);
}


int main(int argc, char** argv){
    char rectangleWidthInS = calloc(256, sizeof(char));
    char numProcInS = calloc(256, sizeof(char));
    double rectangleWidth;
    int numberOfProcesses;
    struct tms start_tms;
    struct tms end_tms;
    clock_t clock_start;
    clock_t clock_end;

    if (argc < 3){
        printf("too little parameters, try again\n");
        exit(-1);
    }else if (argc == 3){
        rectangleWidth = atof(argv[1]);
        numberOfProcesses = atoi(argv[2]);
    }else{
        printf("give me width of rectangle: ");
        scanf("%s", rectangleWidthInS);
        printf("give me number of processes: ");
        scanf("%s", numProcInS);
        rectangleWidth = atof(rectangleWidthInS);
        numberOfProcesses = atoi(numProcInS);
    }
    clock_start = times(&start_tms);

    int counter = 1;
    int index = 0;
    int* processPIDs = calloc(sizeof(int), numberOfProcesses);
    int processPID = 0;
    while (counter <= numberOfProcesses){
        processPID = fork();
        processPIDs[index] = processPID;
        index ++;
        if (processPID == 0){
            countRange(counter, numberOfProcesses, rectangleWidth);
            break;
        }else{
            counter ++;
        }
    }
    if (processPID != 0){
        pid_t waitPID;
        int status = 0;
        for (int i = 0; i < index; i++){
            while ((waitPID = wait(&status)) > 0);
        }
        double wholeResult = 0;
        for (int countr = 1; countr <= numberOfProcesses; countr++ ){
            char* fileName = calloc(sizeof(char), 20);
            sprintf(fileName, "w%d.txt", countr);
            FILE* file = fopen(fileName, "rw");
            char *buffer;
            size_t bufferSize = 32;
            size_t line;
            buffer = (char *) malloc(bufferSize * sizeof(char));
            line = getline(&buffer, &bufferSize, file);
            wholeResult += atof(buffer);
            free(buffer);
            fclose(file);
        }
        printf("result: %f\nrectangle width: %f\nnumber of processes: %d\n", wholeResult, rectangleWidth, numberOfProcesses);
        clock_end = times(&end_tms);
        print_res(clock_start, clock_end, start_tms, end_tms);
    }
    return 0;
}