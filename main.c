#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "bookop.h"
#include "winpos.h"

//�������û����������Ϣ������������㴦��
static void display_menu();
//����һ������ʾ
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
				printf("****�����鼮��Ϣ****\n");
				save_books(filename, books_head);
				WAIT
				break;}
			case '3':{
				CLEAR
				printf("****��ʾ�鼮��Ϣ****\n");
				display_books(books_head);
				WAIT
				break;}
			case '4':{
				search_books(books_head);
				break;}
			case '5':{
				CLEAR
				printf("****����һ���鼮��Ϣ****\n");
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
				printf("****���������鼮��Ϣ����****\n");
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
	printf( "*************��ӭʹ�ø����鼮����ϵͳ*************\n");
	printf(	"--------------------------------------------------\n");
	printf(	"------------------1.¼���鼮��Ϣ------------------\n");
	printf(	"------------------2.�����鼮��Ϣ------------------\n");
	printf(	"------------------3.����鼮��Ϣ------------------\n");
	printf(	"------------------4.��ѯ�鼮��Ϣ------------------\n");
	printf(	"------------------5.�����鼮��Ϣ------------------\n");
	printf(	"------------------6.ɾ���鼮��Ϣ------------------\n");
	printf(	"------------------7.�޸��鼮��Ϣ------------------\n");
	printf(	"------------------8.�����ͳ���鼮������----------\n");
	printf(	"------------------9.���������鼮��������----------\n");
	printf(	"------------------0.�˳�--------------------------\n");
	printf(	"--------------------------------------------------\n");
	printf(	"*********************ллʹ��*********************\n");
}
