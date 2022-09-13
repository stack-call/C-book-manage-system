#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "winpos.h"
#include "bookop.h"
#include "fileop.h"
#include "booklist.h"
#include "debug.h"

#define PRINT_NOTE printf( "序号  书名\t\t\t\t  作者\t\t\t出版社\t\t 类别\n");
//也可以使用宏定义
static inline void display_results(BOOK_INFO ptr)
{
	printf("----------------------------------------------------------------------------------------\n");
	PRINT_NOTE
	int display_status = list_info_output(ptr);
	printf("--------------------------------------------共%d条结果-----------------------------------\n",display_status);
	printf("----------------------------------------------------------------------------------------\n");
	list_info_free(ptr);
}

BOOK load_books(char* filename)
{
	BOOK books = file_load(filename);
	if(books == NULL)
	{
		printf("加载\"%s\"图书信息出现错误!\n",filename);
		return NULL;
	}
	printf("加载\"%s\"图书信息成功!\n", filename);
	return books;
}


int add_book(BOOK books_head)
{
	assert(books_head != NULL);
	BOOK book_node = list_get_new_node();
	if(book_node == NULL)
	{
		printf("增加书籍失败！\n");
		return -1;
	}
	while(1)
	{
		printf("请输入书籍序号：");
		list_node_scanf_id(book_node);
		printf("请输入书名：");
		list_node_scanf_name(book_node);
		printf("请输入作者（多个作者请用';'分开）：");
		list_node_scanf_author(book_node);
		printf("请输入出版社：");
		list_node_scanf_press(book_node);
		printf("请输入类别(专业书:0 ; 参考书:1 ; 报告:2 ; 小说:3 ; 其他:4)：");
		if(list_node_scanf_category(book_node) != 0)
		{
			printf("非法书籍类别！请重新输入！\n");
			continue;
		}
		if(list_check_node(book_node) != 0)
		{
			printf("书籍格式非法！请重新输入！\n");
			continue;
		}
		else
		{
			int status = list_insert_by_id(books_head, book_node);
			if(status == -1)
			{
				printf("书籍序号重复，请重新输入书籍信息！\n");
				continue;
			}
			else if(status == 0)
			{
				printf("增加书籍信息成功！\n");
				return 0;
			}
			else
			{
				printf("增加书籍失败！\n");
				free(book_node);
				return -1;
			}
		}
	}
}
void add_books(BOOK books_head)
{
	assert(books_head != NULL);
	while(1)//二级菜单
	{
		printf( "*****批量增加书籍信息*****\n");
		printf( "-----1 添加书籍信息------\n"
				"-----0 返回主菜单--------\n");
		printf( "*************************\n");
		char t = getch();
		if(t == '0') return;
		else if(t == '1')//选1时的3级菜单
		{
			while(1)
			{
				CLEAR
				printf("请输入要添加的书籍数量：");
				int num;
				fflush(stdin);
				char c;
				int flag = scanf("%d%c", &num, &c);
				if(flag == 0 || num < 0 || c != '\n')
				{
					printf("非法书籍数量！\n");//没用
					break;
				}
				int i;
				for(i = 0; i < num; i++)
				{
					CLEAR
					printf("请输入第%d/%d本书籍信息：\n", i+1, num);
					add_book(books_head);
				}
				CLEAR
				printf("书籍信息保存成功！\n");
				break;
			}
		}
		//其他选项时
	}
}

int update_book(BOOK books_head)
{
	assert(books_head != NULL);
	while(1)
	{
		printf( "*****修改书籍信息*****\n");
		printf( "-----1 修改书籍信息---\n"
				"-----0 返回主菜单-----\n");
		printf( "**********************\n");
		char t = getch();
		if(t == '0') return 0;
		else if(t == '1')//进入3级菜单
		{
			while(1)
			{
				CLEAR
				printf("请输入要修改的书籍序号：");
				char id[100];
				fflush(stdin);
				scanf("%99s", id);
				int i;
				for(i = 0; i < strlen(id); i++)//选1的非法判断
				{
					if(id[i] < '0' || id[i] > '9')
					{
						CLEAR
						printf("非法书籍序号！\n");
						break;
					}
				}
				BOOK ptr = list_search_by_id(books_head, id);//查询相应书籍的信息
				if(ptr == NULL)
				{
					CLEAR								//没有查询到时候
					printf("未查询到符合条件的书籍！\n");
					break;//返回二级菜单
				}
				PRINT_NOTE //否则进行修改处理
				list_node_display(ptr, GetPosY());//输出这本书籍信息

				char opt, c;
				do
				{
					printf("是否确认修改？y/n:");//进行确认并根据判断是否进入3级菜单
					fflush(stdin);
					scanf("%c%c", &opt, &c);
				} while (c != '\n');

				if(opt == 'y')//进入3级菜单
				{
					CLEAR
					while(1)
					{
												//这里进入了3级菜单
						printf("***修改本书书籍信息***\n");
						printf( "--1 修改 书名-----\n"
								"--2 修改 作者-----\n"
								"--3 修改出版社----\n"
								"--4 修改 类别-----\n"
								"--0 返回上级菜单---\n");
						printf( "******************\n");


						char ch = getch();				//根据选项返回二级菜单或者进行修改
						if(ch < '0' || ch > '4')		//非法选项
						{
							CLEAR
							printf("非法选项！\n");
							break;
						}
						if(ch == '0') //选了0，返回二级菜单
						{
							CLEAR
							break;	
						}
						CLEAR								 //选了其他的修改项
						printf("***修改本书书籍信息***\n");
						printf( "--1 修改 书名-----\n"
								"--2 修改 作者-----\n"
								"--3 修改出版社----\n"
								"--4 修改 类别-----\n"
								"--0 返回上级菜单---\n");
						printf( "******************\n");
						switch(ch)
						{
							case '0':{
								break;
							}
							case '1':
							{
								printf("请输入新的书籍名称：");
								list_node_scanf_name(ptr);
								break;
							}
							case '2':
							{
								printf("请输入新的作者姓名（多个作者请用';'分开）：");
								list_node_scanf_author(ptr);
								break;
							}
							case '3':
							{
								printf("请输入新的出版社名称：");
								list_node_scanf_press(ptr);
								break;
							}
							case '4':
							{
								printf("请输入新的类别：(专业书:0 ; 参考书:1 ; 报告:2 ; 小说:3 ; 其他:4)：");
								if(list_node_scanf_category(ptr) != 0)
								{
									CLEAR
									printf("非法书籍类别！\n");
									continue;
								}
								break;
							}
						}
						CLEAR
						printf("修改成功！\n");
						break;
					}
				}
				else if(opt == 'n')//返回2级菜单
				{
					CLEAR
					break;
				}
				else
				{
					CLEAR
					printf("非法选项!\n");
					break;
				}
				break;
			}
			//?break;
		}
		//其他选项
	}
	return 0;
}

int delete_book(BOOK books_head)
{
	assert(books_head != NULL);
	CLEAR //放哪
	while(1)
	{
		printf( "*****删除书籍信息*****\n");
		printf( "---1 按书籍序号删除---\n"
				"---0 返回主菜单-------\n");
		printf( "*********************\n");
		char t = getch();
		if(t == '0') return 0;
		else if(t == '1') //3级菜单
		{
			CLEAR
			while(1)
			{
				printf("请输入要删除的书籍序号：");
				char id[100];
				fflush(stdin);
				scanf("%99s", id);
				int i;
				for(i = 0; i < strlen(id); i++)
				{
					if(id[i] < '0' || id[i] > '9')
					{
						CLEAR
						printf("非法书籍序号！\n");
						break;
					}
				}
				BOOK ptr = list_search_by_id(books_head, id);
				if(ptr == NULL)
				{
					CLEAR
					printf("未查询到符合条件的书籍！\n");
					break;
				}
				else
				{
					list_node_display(ptr, GetPosY());
					again:
					printf("是否确认删除？y/n:");
					char opt;
					fflush(stdin);
					char c;
					scanf("%c%c", &opt, &c);
					if(c != '\n')
					{
						break;
					}
					if(opt == 'y')
					{
						int sta = list_delete(books_head, ptr);
						if(sta == 0)
						{
							CLEAR
							printf("书籍信息删除成功！\n");
							break;
						}
						else
						{
							CLEAR
							printf("书籍信息删除失败！\n");
							break;
						}
					}
					else if(opt == 'n')
					{
						CLEAR
						printf("书籍信息删除取消！\n");
						break;
					}
					else
					{
						break;
					}
				}
			}
		}
		//其他情况
	}
}

int save_books(char* filename, BOOK books_head)
{
	assert(books_head != NULL);
	int status = file_save(filename, books_head);
	if(status == 0)
	{
		printf("书籍信息保存成功！\n");
		return 0;
	}
	else if(status == -1)
	{
		printf("书籍信息保存失败！\n");
		return -1;
	}
	else
	{
		printf("未知情况!\n");
		return -1;
	}
}


void do_exit(BOOK books_head)
{
	CLEAR
	char t;
	printf("*********退出********\n");
	printf("   您确定要退出吗？   \n");
	printf(" 1.确定     2.取消   \n");
	printf("*********************\n");
	while(1)
	{
		t=getch();         //输入t
		switch(t)
		{
			case '1':
				CLEAR
				list_free(books_head);
				printf("成功退出！感谢使用^_^\n");
				exit(0);
				break;
			case '2':
				return;
			default:
				break;
		}
	}
} 

int display_books(BOOK books_head)
{
	assert(books_head != NULL);
	printf("=========================================================================================\n"
	   		"                                       书籍信息如下：\n"
	   		"----------------------------------------------------------------------------------------\n");
	PRINT_NOTE
	int num = list_display(books_head);
	if(num == 0)
	{
		printf("书籍信息为空！\n");
	}
	printf( "----------------------------------------共有%d本书籍信息---------------------------------\n", num);
	printf( "=========================================================================================\n");
}

int search_books(BOOK books_head)
{
	assert(books_head != NULL);
	CLEAR
	while(1)
	{
		printf("*****查找书籍信息*****\n");
		printf(	"----1 书名   查询----\n"
				"----2 作者   查询----\n"
				"----3 出版社 查询----\n"
				"----4 类别   查询----\n"
				"----0 返回主菜单-----\n");
		printf( "**********************\n");
		char c = getch();
		/*if(c < '0' || c > '4')
		{
			CLEAR
			printf("非法选择！\n");
			break;//不能返回
		}*///这种不用处理
		switch(c)
		{
			case '0':{
				return 0;
			}
			case '1':{
				printf("请输入书名：");
				char name[100];
				fflush(stdin);
				scanf("%99[^\n]", name);
				BOOK_INFO ptr = list_search_by_name(books_head, name);
				CLEAR
				display_results(ptr);
				break;}
			case '2':{
				printf("请输入作者：");
				char author[50];
				fflush(stdin);
				scanf("%49[^\n]", author);
				BOOK_INFO ptr = list_search_by_author(books_head, author);
				CLEAR
				display_results(ptr);
				break;}
			case '3':{
				printf("请输入出版社：");
				char press[50];
				fflush(stdin);
				scanf("%49[^\n]", press);
				BOOK_INFO ptr = list_search_by_press(books_head, press);
				CLEAR
				display_results(ptr);
				break;}
			case '4':{
				printf("请输入类别(专业书:0 ; 参考书:1 ; 报告:2 ; 小说:3 ; 其他:4)：");
				BOOK_TYPE type;
				fflush(stdin);
				char c;
				int flag = scanf("%1d%c", &type, &c);
				if(flag == 0 || type < 0 || type > 4 || c!='\n')
				{
					CLEAR
					printf("非法选项！\n");
				}
				BOOK_INFO ptr = list_search_by_category(books_head, type);
				CLEAR
				display_results(ptr);
				break;}
			default:{
				CLEAR
				printf("非法选择！\n");}
		}
	}
}

int statistic_books(BOOK books_head)
{
	assert(books_head != NULL);
	CLEAR
	while(1)
	{
		printf( "*****统计书籍信息*****\n");
		printf( "----0 统计 专业书----\n"
				"----1 统计 参考书----\n"
				"----2 统计  报告-----\n"
				"----3 统计  小说-----\n"
				"----4 统计  其他-----\n"
				"----5 返回主菜单-----\n");
		printf( "*********************\n");
		char c = getch();
		if(c == '5') return 0;
		if(c < '0' || c > '5')
		{
			CLEAR
			printf("非法选项！\n");
		}
		else
		{
			BOOK_INFO ptr = list_search_by_category(books_head, atoi(&c));
			CLEAR
			display_results(ptr);
		}
	}
}

void sort_books(BOOK books_head)
{
	assert(books_head != NULL);
	BOOK_INFO books = list_sort_by_name(books_head);
	display_results(books);
}
