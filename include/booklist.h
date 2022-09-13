#ifndef BOOKLIST_H
#define BOOKLIST_H


enum category
{
	professional,
	reference,
	report,
	novel,
	others
};

struct book_list_node
{
	char id[100];
	char name[100];
	char author[50];
	char press[50];
	short int read;
	enum category book_category;
	struct book_list_node * next;
};

struct book_node
{
	struct book_list_node* book_addr;
	struct book_node* next;
};

struct book_list_node* list_get_new_node();

static inline struct book_list_node* list_create(){return list_get_new_node();}
void list_free(struct book_list_node* head); 


void list_append(struct book_list_node* head, struct book_list_node* new_node);
int list_delete(struct book_list_node* head, struct book_list_node* delete_node);
int list_insert_by_id(struct book_list_node* head, struct book_list_node* new_node);

int list_check_node(struct book_list_node* node);

void list_node_display(struct book_list_node* node, int line);
int list_display(struct book_list_node* head);

/*
	查询返回的是书籍信息地址链表 book_node
*/
void list_info_free(struct book_node* head);
int list_info_output(struct book_node* head);
struct book_node* list_sort_by_name(struct book_list_node* head);
struct book_list_node* list_search_by_id(struct book_list_node* head, char* str);
struct book_node*      list_search_by_name(struct book_list_node* head, char* str);
struct book_node*      list_search_by_author(struct book_list_node* head, char* str);
struct book_node*      list_search_by_press(struct book_list_node* head, char* str);
struct book_node*      list_search_by_category(struct book_list_node* head, enum category kind);

void list_node_scanf_id(struct book_list_node* node);
void list_node_scanf_name(struct book_list_node* node);
void list_node_scanf_author(struct book_list_node* node);
void list_node_scanf_press(struct book_list_node* node);
int list_node_scanf_category(struct book_list_node* node);

#endif
