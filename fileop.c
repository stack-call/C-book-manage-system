#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileop.h"
#include "booklist.h"
#include "debug.h"

static LIST_NODE* file_format_get(FILE* fp)
{
	if(!fp)
	{
		return NULL;
	}
	LIST_NODE* ptr = list_get_new_node();
	assert(ptr!=NULL);
	fscanf(fp, "%99[^\n]", ptr->id);
	fgetc(fp);
	fscanf(fp, "%d", &ptr->book_category);
	fgetc(fp);
	fscanf(fp, "%99[^\n]", ptr->name);
	fgetc(fp);
	fscanf(fp, "%49[^\n]", ptr->author);
	fgetc(fp);
	fscanf(fp, "%49[^\n]", ptr->press);
	fgetc(fp);
	return ptr;
}

static int file_format_puts(FILE* fp, LIST_NODE* head)
{
	if(!fp || !head)
	{
		return -1;
	}
	LIST_NODE* ptr;
    for(ptr = head->next; ptr != NULL; ptr = ptr->next){
    	if(ptr-> next == NULL)//如果不处理 feof会再次读取
    	{
    		fprintf(fp,"%s\n%d\n%s\n%s\n%s", ptr->id, ptr->book_category, ptr->name, ptr->author, ptr->press);
    		break;
		}
		fprintf(fp,"%s\n%d\n%s\n%s\n%s\n", ptr->id, ptr->book_category, ptr->name, ptr->author, ptr->press);
    }
	return 0;
}

LIST_NODE* file_load(char* filename)
{
	FILE* fp;
	if ((fp=fopen(filename,"r+"))==NULL)
		return NULL;
	assert(fp != NULL);
	LIST_NODE* books_head = list_create();
	if(!books_head)
		return NULL;

	char ch;
	ch=fgetc(fp);
	if(ch==EOF)
		return books_head;
	rewind(fp);

	while(!feof(fp))
	{
		LIST_NODE* ptr = file_format_get(fp);
    	int sta = list_check_node(ptr);
    	if(sta != 0)
    	{
    		list_free(books_head);
    		fclose(fp);
    		return NULL;
		}
		else
		{
			list_append(books_head, ptr);
		}
	}
	fclose(fp);
	return books_head;
}

int file_save(char* filename, LIST_NODE* head)
{
	FILE* fp;
	if ((fp = fopen(filename, "w+"))==NULL)
	{
		return -1;
    }
	assert(fp != NULL);
	file_format_puts(fp, head);
	fclose(fp);
	return 0;
}