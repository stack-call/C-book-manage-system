#ifndef FILEOP_H
#define FILEOP_H
#include <stdio.h>

typedef struct book_list_node LIST_NODE;

LIST_NODE* file_load(char* file_name); 
int file_save(char* filename, LIST_NODE* head);

#endif
