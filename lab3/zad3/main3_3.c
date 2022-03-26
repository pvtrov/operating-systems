//
// Created by mirabelka on 3/25/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int goInside(char* path, char* wordToFind, char* dirName){
    FILE* file = fopen(path, "rw");
    if (file == NULL){
        return -1;
    }
    char* buffer;
    size_t bufferSize;
    size_t line;
    buffer = (char *) malloc(bufferSize * sizeof(char));
    line = getline(&buffer, &bufferSize, file);
    if (strstr(buffer, wordToFind) != NULL){
        printf("PID: %d, path: %s\n", getpid(), dirName);
    }
    fclose(file);
    free(buffer);
    return 0;
}


void ransackFile(char* dirName, char* wordToFind, int depth, int currentDepth){
    char* path = calloc(sizeof(char), 1000);
    int directories = 0;
    struct dirent *dirent;
    DIR *dir = opendir(dirName);
    int type;

    if (dir == NULL){
        return;
    }

    while((dirent = readdir(dir)) != NULL){
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0){
            type = dirent->d_type;
            char buf[PATH_MAX];
            if (type == DT_DIR){
                directories ++;
            }
            if (type == DT_REG){
                sprintf(path, "%s/%s", dirName, dirent->d_name);
                char* result = realpath(path, NULL);

                goInside(path, wordToFind, path);
                free(result);
            }
        }
    }
    free(path);
    closedir(dir);

    if (currentDepth < depth){
        pid_t* kids = calloc(sizeof(pid_t), directories);
        int index = 0;
        pid_t kid;
        dir = opendir(dirName);
        if (dir == NULL){
            return;
        }
        struct dirent *dirent2;
        while((dirent2 = readdir(dir) != NULL)){
            if (strcmp(dirent2->d_name, ".") != 0 && strcmp(dirent2->d_name, "..") != 0){
                if (dirent2->d_type == DT_DIR){
                    kid = fork();
                    if (kid != 0){
                        kids[index] = kid;
                    }
                    else{
                        char* pathSnd = calloc(sizeof(char), strlen(dirent->d_name)+2 + strlen(dirName));
                        sprintf(pathSnd, "%s/%s", dirName, dirent->d_name);
                        ransackFile(pathSnd, wordToFind, depth, currentDepth++);
                        free(pathSnd);
                        break;
                    }
                }
            }
        }
        if (kid != 0){
            closedir(dir);
            pid_t waitPID;
            int status = 0;
            for (int i = 0; i < index; i++){
                while ((waitPID = wait(&status)) > 0);
            }
        }
    }
}

int main(int argc, char** argv){
    char* dirName = calloc(256, sizeof(char));
    char* wordToFind = calloc(256, sizeof(char));
    int depth;

    if (argc < 4){
        printf("too little parameters, try again\n");
        exit(-1);
    }else if (argc == 4){
        dirName = argv[1];
        wordToFind = argv[2];
        depth = argv[3];
    }else{
        printf("Give me directory: ");
        scanf("%s", dirName);
        printf("Give me word:  ");
        scanf("%s", wordToFind);
        printf("How deep should I look?: ");
        scanf("%d", depth);
    }

    ransackFile(dirName, wordToFind, depth, 0);
}