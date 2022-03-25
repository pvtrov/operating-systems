//
// Created by mirabelka on 3/18/22.
//

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <ftw.h>
#include <time.h>
#include <dirent.h>

struct stat sb;
int normalFiles = 0, directories = 0, characters = 0, blocks = 0, fifo = 0, links = 0, sockets = 0;

char* better_ctime(const __time_t* tuturutu){
    char *buff = calloc(sizeof(char), 20);
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(tuturutu));
    return buff;
}

#ifdef NFTW
char* defineTypeForNFTW(const struct stat* something){
    if(S_ISREG(something->st_mode)){
        normalFiles++;
    }
    if (S_ISDIR(something->st_mode)){
        directories ++;
        return "directory";
    }
    if (S_ISCHR(something->st_mode)){
        characters ++;
        return "characters";
    }
    if (S_ISBLK(something->st_mode)){
        blocks ++;
        return "blocks";
    }
    if (S_ISFIFO(something->st_mode)){
        fifo ++;
        return "fifo";
    }
    if (S_ISLNK(something->st_mode)){
        links ++;
        return "links";
    }
    if (S_ISSOCK(something->st_mode)){
        sockets ++;
        return "sock";
    }
    return "nothing";
}

void printing(const char* fpath, const struct stat* something, int tflag, struct FTW* ftwbuf){
    char * result = realpath(fpath, NULL);

    printf("At: %s", result);
    printf(",%lu", sb.st_nlink);
    char* type = defineTypeForNFTW(something);
    printf(", %s", type);
    printf(", %ld", sb.st_size);
    printf(", File access time %s", better_ctime(&sb.st_atime));
    printf(", File modify time %s\n", better_ctime(&sb.st_mtime));
}
#endif

#ifdef READDIR
char* defineType(unsigned char something){
    if (something == DT_REG){
        normalFiles ++;
        return "normal file";
    }if (something == DT_DIR){
        directories ++;
        return "directory";
    }if (something == DT_CHR){
        characters ++;
        return "characters";
    }
    if (something == DT_BLK){
        blocks ++;
        return "blocks";
    }
    if (something == DT_FIFO){
        fifo ++;
        return "fifo";
    }
    if (something == DT_LNK){
        links ++;
        return "links";
    }
    if (something == DT_SOCK){
        sockets ++;
        return "sock";
    }
    return "nothing";
}

void ransack(char* directoryName) {
    char path[1000];
    struct dirent *insideDirectory;
    DIR *directory = opendir(directoryName);

    if (directory == NULL) {
        return;
    }


    while ((insideDirectory = readdir(directory)) != NULL) {
        if (strcmp(insideDirectory->d_name, ".") != 0 && strcmp(insideDirectory->d_name, "..") != 0){
            stpcpy(path, directoryName);
            strcat(path, "/");
            strcat(path, insideDirectory->d_name);

            stat(insideDirectory->d_name, &sb);

            char* result = realpath(path, NULL);

            printf("At: %s", result);
            printf(",%lu", sb.st_nlink);
            char* type = defineType(insideDirectory->d_type);
            printf(", %s", type);
            printf(", %ld", sb.st_size);
            printf(", File access time %s", better_ctime(&sb.st_atime));
            printf(", File modify time %s\n", better_ctime(&sb.st_mtime));

            ransack(path);
        }
    }
    closedir(directory);
}

#endif

int main(int argc, char** argv){
    char* mainDirectoryName;
    DIR* mainDirectory;

    if (argc <= 1){
        mainDirectoryName = calloc(256, sizeof(char));
        printf("Give me name of directory you want me to ransack: ");
        scanf("%s", mainDirectoryName);
    }else{
        mainDirectoryName = argv[1];
    }

    #ifdef NFTW
        nftw(mainDirectoryName, printing, 50, FTW_NS);
    #endif

    #ifdef READDIR
    ransack(mainDirectoryName);
    #endif

    printf("normal files: %d ", normalFiles);
    printf("directories: %d ", directories);
    printf("special characters files: %d ", characters);
    printf("special blocks files: %d ", blocks);
    printf("fifos: %d ", fifo);
    printf("links: %d ", links);


    return 0;

}