//
// Created by mirabelka on 3/10/22.
//

//Biblioteka powinna umożliwiać:
//
//utworzenie tablicy wskaźników w której będą przechowywane wskaźniki na bloki pamięci zawierające wyniki ~
//przeprowadzenie zliczenia lini, słów i znaków dla zadanych plików i zapisanie wyniku zliczania w pliku tymczasowym ~
//zarezerwowanie bloku pamięci o rozmiarze odpowiadającym rozmiarowi pliku tymczasowego i zapisanie w tej pamięci jego
//zawartości, ustawienie w tablicy wskaźników wskazania na ten blok, funkcja powinna zwrócić indeks stworzonego bloku
//w tablicy, usunięcie z pamięci bloku o zadanym indeksie

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "first_library.h"


// tworze tablice wskaźników bloki, size to ilość bloków
struct PointersMatrix* create_table(int size){
    struct PointersMatrix* matrix = calloc(1, sizeof(struct PointersMatrix));

    matrix -> lastAddedIndex = -1;
    matrix -> size = size;
    matrix -> blocks = calloc(size, sizeof(struct MemoryBlock));
    printf("Created matrix\n ");

    return matrix;
}

// liczę sobie te linie, slowa i znaki, wpisuje do nowo stworzonego bloku
int wc_files(char* first, int numberOfFiles, struct PointersMatrix* matrix) {
    struct MemoryBlock* block = calloc(1, sizeof(struct MemoryBlock));


    FILE* temp = popen(first, "r");
    printf("counted things have been written to temporary file\n ");

    fseek(temp, 0, SEEK_END);
    long int size = ftell(temp);
    char* almostContent = calloc(size + 1, 1);
    fread(almostContent, 1, size, temp);
    block -> content = (char*) almostContent;
    int blockNumber = matrix->lastAddedIndex + 1;
    matrix->blocks[blockNumber] = block;
    matrix->lastAddedIndex = blockNumber; // uaktualniam lastAddedIndex
    return blockNumber;
}


void remove_block(struct PointersMatrix* matrix, int indexToRemove){
    if (matrix->blocks[indexToRemove] == NULL){
        return;
    }
    matrix->blocks[indexToRemove] = NULL;
    free( (void*) matrix->blocks[indexToRemove]);
    printf("Removed block at %d index\n", indexToRemove);
}

