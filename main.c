#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "bookop.h"
#include "winpos.h"

//尽量把用户错误处理和信息输出留在上两层处理
static void display_menu();
//增加一定的提示
int main(int argc, char **argv)
{
	CLEAR
	char filename[20] = "database.txt";

	BOOK books_head = load_books(filename);
	if(books_head == NULL)
		exit(1);


	while(1)
	{
		display_menu();
		char option;
		option = getch();
		switch(option)
		{
			case '1':{
				CLEAR
				add_books(books_head);
				save_books(filename, books_head);
				break;}
			case '2':{
				CLEAR
				printf("****保存书籍信息****\n");
				save_books(filename, books_head);
				WAIT
				break;}
			case '3':{
				CLEAR
				printf("****显示书籍信息****\n");
				display_books(books_head);
				WAIT
				break;}
			case '4':{
				search_books(books_head);
				break;}
			case '5':{
				CLEAR
				printf("****增加一本书籍信息****\n");
				add_book(books_head);
				WAIT
				save_books(filename, books_head);
				break;}
			case '6':{
				delete_book(books_head);
				save_books(filename, books_head);
				break;}
			case '7':{
				CLEAR
				update_book(books_head);
				save_books(filename, books_head);
				break;}
			case '8':{
				statistic_books(books_head);
				break;}
			case '9':{
				CLEAR
				printf("****按书名对书籍信息排序****\n");
				sort_books(books_head);
				WAIT
				break;}
			case '0':
				do_exit(books_head);
		}
	}
	return 0;
}

void display_menu()
{
	CLEAR
	printf( "*************欢迎使用个人书籍管理系统*************\n");
	printf(	"--------------------------------------------------\n");
	printf(	"------------------1.录入书籍信息------------------\n");
	printf(	"------------------2.保存书籍信息------------------\n");
	printf(	"------------------3.浏览书籍信息------------------\n");
	printf(	"------------------4.查询书籍信息------------------\n");
	printf(	"------------------5.增加书籍信息------------------\n");
	printf(	"------------------6.删除书籍信息------------------\n");
	printf(	"------------------7.修改书籍信息------------------\n");
	printf(	"------------------8.按类别统计书籍的数量----------\n");
	printf(	"------------------9.按书名对书籍进行排序----------\n");
	printf(	"------------------0.退出--------------------------\n");
	printf(	"--------------------------------------------------\n");
	printf(	"*********************谢谢使用*********************\n");
}
