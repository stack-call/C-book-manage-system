/*
	主要处理struct book_list_node相关的功能，与bookinfo.c相互独立
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "booklist.h"
#include "debug.h"
#include "winpos.h"


struct book_list_node* list_get_new_node()
{
	struct book_list_node* ptr;
	ptr = (struct book_list_node*) malloc(sizeof(struct book_list_node));
	if(ptr)
	{
		ptr->next = NULL;
		ptr->read = 0;
		return ptr;
	}
	return NULL;
}

void list_append(struct book_list_node *head, struct book_list_node *new_node)
{
	assert((head != NULL) && (new_node != NULL));
	struct book_list_node* ptr = head;
	while(ptr->next)
	{
		ptr = ptr->next;
	}
	ptr->next = new_node;
}

int list_delete(struct book_list_node* head, struct book_list_node* delete_node)
{
	assert((head != NULL) && (delete_node != NULL));
	struct book_list_node* ptr;
	for(ptr = head; ptr->next != NULL; ptr = ptr->next)//while statement?
	{
		if(ptr->next == delete_node)
		{
			ptr->next = delete_node->next;
			free(delete_node);
			return 0;
		}
	}
	return -1;
}

int list_insert_by_id(struct book_list_node* head, struct book_list_node* new_node)
{
	assert((head != NULL) && (new_node != NULL));
	struct book_list_node* ptr;
	for(ptr = head; ptr->next != NULL; ptr = ptr->next)
	{
		if(atoi(new_node->id) == atoi(ptr->next->id))
		{
			return -1;
		}
		if(atoi(new_node->id) < atoi(ptr->next->id))
		{
			new_node->next = ptr->next;
			ptr->next = new_node;
			return 0;
		}
	}
	list_append(head, new_node);
	return 0;
}

int list_check_node(struct book_list_node* node)
{
	assert(node != NULL);
	int i;
	for(i = 0; i < strlen(node->id); i++)
	{
		if(node->id[i] < '0' || node->id[i] > '9' || node->id[i] == '\n')
		{
			return -1;
		}
	}
	if( (node->book_category < 0) || (node->book_category > 4) )
	{
		return -1;
	}
	return 0;
}

void list_node_display(struct book_list_node* node, int line)
{
	assert((node != NULL) && (list_check_node(node) == 0));
	int row = 0;
	SetPos(row , line);
	printf("%s", node->id);
	SetPos(row+5 , line);
	printf("%s", node->name);
	SetPos(row+42 , line);
	char str_temp[100];
	strcpy(str_temp, node->author);
	char *token = NULL;
	const char s[2] = ";";
	token = strtok(str_temp, s);
    while (token)
	{
		printf("【%s】", token);
       	token = strtok(NULL, s);
   	}
	SetPos(row+64 , line);
	printf("%s", node->press);
	SetPos(row+81 , line);
	switch(node->book_category)
	{
		case 0:{
			printf("专业书");
			break;}
		case 1:{
			printf("参考书");
			break;}
		case 2:{
			printf("报告");
			break;}
		case 3:{
			printf("小说");
			break;}
		case 4:{
			printf("其他");
			break;}
		default:{
			printf("读取书籍类别错误！");}
	}
	printf("\n");
};

int list_display(struct book_list_node* head)
{
	assert(head != NULL);
	struct book_list_node* ptr = head;
	ptr = ptr->next;
	int count = 0;
	int line = GetPosY();
	while(ptr)
	{
		list_node_display(ptr, line);
		ptr = ptr->next;
		count++;
		line++;
	}
	return count;
}

void list_free(struct book_list_node* head)
{
	assert(head != NULL);
	struct book_list_node* ptr = head;
	struct book_list_node* temp;
	while(ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp);
	}
}

void list_node_scanf_id(struct book_list_node* node)
{
	assert(node != NULL);
	fflush(stdin);
	scanf("%99s", node->id);
}

void list_node_scanf_name(struct book_list_node* node)
{
	assert(node != NULL);
	fflush(stdin);
	scanf("%99[^\n]", node->name);
}

void list_node_scanf_author(struct book_list_node* node)
{
	assert(node != NULL);
	fflush(stdin);
	scanf("%49[^\n]", node->author);
}

void list_node_scanf_press(struct book_list_node* node)
{
	assert(node != NULL);
	fflush(stdin);
	scanf("%49[^\n]", node->press);
}

//为这个单独写处理函数是因为要处理 1' 这样的输入
int list_node_scanf_category(struct book_list_node* node)
{
	assert(node != NULL);
	fflush(stdin);
	char c;
	enum category temp;
	int flag = scanf("%1d%c", &temp, &c);
	if(flag == 0 || temp < 0 || temp > 4 || c != '\n')
	{
		return -1;
	}
	node->book_category = temp;
	return 0;
}

struct book_list_node* list_search_by_id(struct book_list_node* head, char* str)
{
	assert(head != NULL || str != NULL);
	struct book_list_node* ptr;
	for(ptr = head->next; ptr != NULL; ptr = ptr->next)
	{
		if(strcmp(ptr->id, str) == 0)
		{
			return ptr;
		}
	}
	return NULL;
}
