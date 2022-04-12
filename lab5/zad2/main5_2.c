//
// Created by mirabelka on 4/12/22.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void print_output(FILE* file){
    char line[256];
    while (fgets(line, 256, file) != NULL){
        printf("%s\n", line);
    }
}

void mailing_sender(){
    FILE* file;
    char* command = "echo | mail -f | tail +2 | head -n -1 | tac";

    file = popen(command, "r");
    if (file == NULL){
        printf("invalid command\n");
        exit(1);
    }
    print_output(file);
}

void mailing_date(){
    FILE* file;
    char* command = "echo | mail -f | tail +2 | head -n -1 | sort -k 2";

    file = popen(command, "r");
    if (file == NULL){
        printf("invalid command\n");
        exit(1);
    }
    print_output(file);
}

void first_mail(char* argument){
    if (strcmp(argument, "sender") == 0){
        mailing_sender();
    } else if (strcmp(argument, "date") == 0){
        mailing_date();
    } else {
        printf("invalid mode, sorry\n");
        exit(1);
    }
}

void second_mail(char* argv){
    char* address = argv[1];
    char* theme = argv[2];
    char* content = argv[3];

    FILE* file;
    char command[256];

    snprintf(command, sizeof(command), "echo %s | mail -s %s %s", content, theme, address);
    file = popen(command, "r");
    if (file == NULL){
        printf("cannot open file, sorry");
        exit(1);
    }
}

int main(int argc, char* argv[]){
    if (argc == 2){
        first_mail(argv[1]);
    } else if ( argc == 4 ){
        second_mail(argv);
    } else {
        printf("wrong number of arguments, i dont get you, sory\n");
    }
}