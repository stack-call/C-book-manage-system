#ifndef BOOKOP_H
#define BOOKOP_H

typedef struct book_list_node* BOOK;
typedef struct book_node*      BOOK_INFO;
typedef enum category          BOOK_TYPE;

BOOK load_books(char* filename);
int add_book(BOOK books_head);
void add_books(BOOK books_head);
int update_book(BOOK books_head);
int delete_book(BOOK books_head);
int save_books(char* filename, BOOK books_head);
int display_books(BOOK books_head);
int search_books(BOOK books_head);
int statistic_books(BOOK books_head);
void sort_books(BOOK books_head);
void do_exit(BOOK books_head);

#endif
