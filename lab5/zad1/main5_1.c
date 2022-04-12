//
// Created by mirabelka on 4/11/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define MAX_ARGS 20  // in line
#define MAX_LINES 10
#define READ 0
#define WRITE 1

int which_number_is_it(char line[], int i){
    if (i == 0) return line[8] - '0';
    else return line[9] - '0';
}

int* get_lines(char* line){
    char** lines = calloc(MAX_ARGS, sizeof(char*));
    char* argument = strtok(line, "|");
    int counter = 0;
    lines[counter++] = argument;

    while((argument = strtok(NULL, "|")) != NULL){
        lines[counter++] = argument;
    }
    static int lines_num[MAX_ARGS];
    int i = 0;
    while(lines[i] != NULL){
        lines_num[i] = which_number_is_it(lines[i], i);
        i++;
    }
    lines_num[i] = -1;
    return lines_num;
}

char** give_me_arguments(char* command, char* path){
    char** args = calloc(256, sizeof(char));
    char* arg = strtok(command, " ");
    strcpy(path, arg);

    int counter = 0;
    args[counter++] = arg;
    while (arg != NULL){
        args[counter++] = arg;
        arg = strtok(NULL, " ");
    }
    args[counter] = NULL;
    return args;
}

char** separate(char* line){
    char** commands = calloc(MAX_ARGS, sizeof(char*));
    int counter = 0;
    char* arg = strtok(line, "|");
    while (arg != NULL){
        commands[counter++] = arg;
        arg = strtok(NULL, "|");
    }
    return commands;
}

void create_commands(FILE* file){
    char* line = calloc(256, sizeof(char));
    char* lines[10];
    char* commands_for_pot[10];
    int* lines_wanted_to_do;
    char one_line = calloc(256, sizeof(char ));
    char** arguments;

    int counter = 0;
    int pot_counter = 0;
    while (fgets(line, 256* sizeof(char), file)){
        if (strstr(line, "=")){
            char* better_line = calloc(256, sizeof(char));
            char* even_better_line = calloc(256, sizeof(char));
            char* token = strtok(line, "=");
            token = strtok(NULL,"=");
            better_line = strncpy(better_line, token, strlen(token)-1);
            even_better_line = separate(better_line);
            lines[counter] = even_better_line;
            counter ++;
        } else {
            lines_wanted_to_do = get_lines(line);
            int i = 0;
            while (lines_wanted_to_do[i] != -1){
                int num = lines_wanted_to_do[i];
                char* this_one_line = lines[num];
                commands_for_pot[pot_counter] = this_one_line;
                pot_counter++;
                i++;
            }
            int pipe_in[2];
            int pipe_out[2];

            if (pipe(pipe_out) != 0){
                printf("error, sorry\n");
                exit(1);
            }
            for (i = 0; i < pot_counter; i++){
                pid_t pid = fork();

                if (pid == 0){
                    if (i == 0){
                        close(pipe_out[READ]);
                        dup2(pipe_out[WRITE], STDOUT_FILENO);
                    } else if (i == pot_counter - 1){
                        close(pipe_out[READ]);
                        close(pipe_out[WRITE]);
                        close(pipe_in[WRITE]);
                        dup2(pipe_in[READ], STDIN_FILENO);
                    } else {
                        close(pipe_in[WRITE]);
                        close(pipe_out[READ]);
                        dup2(pipe_in[READ], STDIN_FILENO);
                        dup2(pipe_out[WRITE], STDOUT_FILENO);
                    }
                    char path[256];
                    arguments = give_me_arguments(commands_for_pot[i], path);

                    if (execvp(path, arguments) == -1){
//                        printf("error, cant piping, sorry\n");
                        exit(1);
                    }
                } else {
                    close(pipe_in[WRITE]);
                    pipe_in[READ] = pipe_out[READ];
                    pipe_in[WRITE] = pipe_out[WRITE];
                    if (pipe(pipe_out) != 0){
                        printf("cannot move pipe sory\n");
                        exit(1);
                    }
                }
            }
        }
    }
    int status = 0;
    pid_t wpid;
    while ((wpid = wait(&status)) != -1);
}

int main(int argc, char* argv[]){
    if (argc != 2){
        printf("wrong number of arguments!\n");
        exit(1);
    }
    FILE* file_to_read_from = fopen(argv[1], "r");
    if (file_to_read_from == NULL){
        printf("something not working :(");
        exit(1);
    }
    create_commands(file_to_read_from);
}