/*
	主要处理struct book_node相关的功能，与booknode.c分开
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "winpos.h"
#include "booklist.h"
#include "debug.h"

static inline struct book_node* get_book_node()//free!!!!
{
	struct book_node* ptr;
	ptr = (struct book_node*) malloc(sizeof(struct book_node));
	if(ptr != NULL){
		ptr->next = NULL;
		return ptr;
	}
	return NULL;
}

static int book_node_append(struct book_node *head, struct book_node *new_node)
{
	assert(head != NULL);
	if(new_node == NULL)
		return -1;
	struct book_node* ptr = head;
	while(ptr->next)
	{
		ptr = ptr->next;
	}
	ptr->next = new_node;
	return 0;
}

static void list_reset_read(struct book_list_node* head)
{
	assert(head != NULL);
	struct book_list_node* ptr;
	for(ptr = head->next; ptr != NULL; ptr = ptr->next)
	{
		ptr->read = 0;
	}
}

int list_info_output(struct book_node* head)
{
	assert(head != NULL);
	int count = 0;
	int line = GetPosY();
	struct book_node* itor;
	for(itor = head->next; itor != NULL; itor = itor->next)
	{
		list_node_display(itor->book_addr, line);
		count++;
		line++;
	}
	return count;
}

void list_info_free(struct book_node* head)
{
	assert(head != NULL);
	struct book_node* ptr = head;
	struct book_node* temp;
	while(ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp);
	}
}

struct book_node* list_search_by_name(struct book_list_node* head, char* str)//search中有很多重复代码，尝试修改 
{
	assert(head != NULL);
	if(!str)
		return NULL;
	struct book_list_node* ptr;
	struct book_node* temp = get_book_node();
	for(ptr = head->next; ptr != NULL; ptr = ptr->next)
	{
		if(strcmp(ptr->name, str) == 0)
		{
			struct book_node* temp1 = get_book_node();
			temp1->book_addr = ptr;
			book_node_append(temp, temp1);
		}
	}
	return temp;
}


struct book_node* list_search_by_author(struct book_list_node* head, char* str)
{
	assert(head != NULL);
	if(!str)
		return NULL;
	struct book_list_node* ptr;
	struct book_node* temp = get_book_node();
	char str_temp[100];
	for(ptr = head->next; ptr != NULL; ptr = ptr->next)
	{
		strcpy(str_temp, ptr->author);
		char *token = NULL;
		const char s[2] = ";";
		token = strtok(str_temp, s);
	    while (token != NULL)
    	{
			if(strcmp(token, str) == 0)
			{
				struct book_node* temp1 = get_book_node();
				temp1->book_addr = ptr;
				book_node_append(temp, temp1);
				break;
			}
        	token = strtok(NULL, s);
    	}
	}
	return temp;
}

struct book_node* list_search_by_press(struct book_list_node* head, char* str)
{
	assert(head != NULL);
	if(!str)
		return NULL;
	struct book_list_node* ptr;
	struct book_node* temp = get_book_node();
	for(ptr = head->next; ptr != NULL; ptr = ptr->next)
	{
		if(strcmp(ptr->press, str) == 0)
		{
			struct book_node* temp1 = get_book_node();
			temp1->book_addr = ptr;
			book_node_append(temp, temp1);
		}
	}
	return temp;
}

struct book_node* list_search_by_category(struct book_list_node* head, enum category kind)
{
	assert(head != NULL);
	if(kind < 0 || kind > 4)
		return NULL;
	struct book_list_node* ptr;
	struct book_node* temp = get_book_node();
	for(ptr = head->next; ptr != NULL; ptr = ptr->next)
	{
		if(ptr->book_category == kind)
		{
			struct book_node* temp1 = get_book_node();
			temp1->book_addr = ptr;
			book_node_append(temp, temp1);
		}
	}
	return temp;
}

struct book_node* list_sort_by_name(struct book_list_node* head)
{
	assert(head != NULL);
	struct book_node* result = get_book_node();
	if(!result)
		return NULL;
	struct book_list_node* min;
	struct book_list_node *i;
	min = head->next;
	while(min)
	{
		min = head->next;
		while((min->read == 1) && (min != NULL))
		{
			if(min->next == NULL)
			{
				list_reset_read(head);
				return result;
			}
			min = min->next;
		}
		for(i = min->next; i != NULL; i = i->next)
		{
			if((strcasecmp(min->name, i->name) > 0) && (i->read == 0))
			{
				min = i;
			}
		}
		min->read = 1;
		struct book_node* ptr = get_book_node();
		ptr->book_addr = min;
		book_node_append(result, ptr);
	}
	return result;
}