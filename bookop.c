#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "winpos.h"
#include "bookop.h"
#include "fileop.h"
#include "booklist.h"
#include "debug.h"

#define PRINT_NOTE printf( "���  ����\t\t\t\t  ����\t\t\t������\t\t ���\n");
//Ҳ����ʹ�ú궨��
static inline void display_results(BOOK_INFO ptr)
{
	printf("----------------------------------------------------------------------------------------\n");
	PRINT_NOTE
	int display_status = list_info_output(ptr);
	printf("--------------------------------------------��%d�����-----------------------------------\n",display_status);
	printf("----------------------------------------------------------------------------------------\n");
	list_info_free(ptr);
}

BOOK load_books(char* filename)
{
	BOOK books = file_load(filename);
	if(books == NULL)
	{
		printf("����\"%s\"ͼ����Ϣ���ִ���!\n",filename);
		return NULL;
	}
	printf("����\"%s\"ͼ����Ϣ�ɹ�!\n", filename);
	return books;
}


int add_book(BOOK books_head)
{
	assert(books_head != NULL);
	BOOK book_node = list_get_new_node();
	if(book_node == NULL)
	{
		printf("�����鼮ʧ�ܣ�\n");
		return -1;
	}
	while(1)
	{
		printf("�������鼮��ţ�");
		list_node_scanf_id(book_node);
		printf("������������");
		list_node_scanf_name(book_node);
		printf("���������ߣ������������';'�ֿ�����");
		list_node_scanf_author(book_node);
		printf("����������磺");
		list_node_scanf_press(book_node);
		printf("���������(רҵ��:0 ; �ο���:1 ; ����:2 ; С˵:3 ; ����:4)��");
		if(list_node_scanf_category(book_node) != 0)
		{
			printf("�Ƿ��鼮������������룡\n");
			continue;
		}
		if(list_check_node(book_node) != 0)
		{
			printf("�鼮��ʽ�Ƿ������������룡\n");
			continue;
		}
		else
		{
			int status = list_insert_by_id(books_head, book_node);
			if(status == -1)
			{
				printf("�鼮����ظ��������������鼮��Ϣ��\n");
				continue;
			}
			else if(status == 0)
			{
				printf("�����鼮��Ϣ�ɹ���\n");
				return 0;
			}
			else
			{
				printf("�����鼮ʧ�ܣ�\n");
				free(book_node);
				return -1;
			}
		}
	}
}
void add_books(BOOK books_head)
{
	assert(books_head != NULL);
	while(1)//�����˵�
	{
		printf( "*****���������鼮��Ϣ*****\n");
		printf( "-----1 ����鼮��Ϣ------\n"
				"-----0 �������˵�--------\n");
		printf( "*************************\n");
		char t = getch();
		if(t == '0') return;
		else if(t == '1')//ѡ1ʱ��3���˵�
		{
			while(1)
			{
				CLEAR
				printf("������Ҫ��ӵ��鼮������");
				int num;
				fflush(stdin);
				char c;
				int flag = scanf("%d%c", &num, &c);
				if(flag == 0 || num < 0 || c != '\n')
				{
					printf("�Ƿ��鼮������\n");//û��
					break;
				}
				int i;
				for(i = 0; i < num; i++)
				{
					CLEAR
					printf("�������%d/%d���鼮��Ϣ��\n", i+1, num);
					add_book(books_head);
				}
				CLEAR
				printf("�鼮��Ϣ����ɹ���\n");
				break;
			}
		}
		//����ѡ��ʱ
	}
}

int update_book(BOOK books_head)
{
	assert(books_head != NULL);
	while(1)
	{
		printf( "*****�޸��鼮��Ϣ*****\n");
		printf( "-----1 �޸��鼮��Ϣ---\n"
				"-----0 �������˵�-----\n");
		printf( "**********************\n");
		char t = getch();
		if(t == '0') return 0;
		else if(t == '1')//����3���˵�
		{
			while(1)
			{
				CLEAR
				printf("������Ҫ�޸ĵ��鼮��ţ�");
				char id[100];
				fflush(stdin);
				scanf("%99s", id);
				int i;
				for(i = 0; i < strlen(id); i++)//ѡ1�ķǷ��ж�
				{
					if(id[i] < '0' || id[i] > '9')
					{
						CLEAR
						printf("�Ƿ��鼮��ţ�\n");
						break;
					}
				}
				BOOK ptr = list_search_by_id(books_head, id);//��ѯ��Ӧ�鼮����Ϣ
				if(ptr == NULL)
				{
					CLEAR								//û�в�ѯ��ʱ��
					printf("δ��ѯ�������������鼮��\n");
					break;//���ض����˵�
				}
				PRINT_NOTE //��������޸Ĵ���
				list_node_display(ptr, GetPosY());//����Ȿ�鼮��Ϣ

				char opt, c;
				do
				{
					printf("�Ƿ�ȷ���޸ģ�y/n:");//����ȷ�ϲ������ж��Ƿ����3���˵�
					fflush(stdin);
					scanf("%c%c", &opt, &c);
				} while (c != '\n');

				if(opt == 'y')//����3���˵�
				{
					CLEAR
					while(1)
					{
												//���������3���˵�
						printf("***�޸ı����鼮��Ϣ***\n");
						printf( "--1 �޸� ����-----\n"
								"--2 �޸� ����-----\n"
								"--3 �޸ĳ�����----\n"
								"--4 �޸� ���-----\n"
								"--0 �����ϼ��˵�---\n");
						printf( "******************\n");


						char ch = getch();				//����ѡ��ض����˵����߽����޸�
						if(ch < '0' || ch > '4')		//�Ƿ�ѡ��
						{
							CLEAR
							printf("�Ƿ�ѡ�\n");
							break;
						}
						if(ch == '0') //ѡ��0�����ض����˵�
						{
							CLEAR
							break;	
						}
						CLEAR								 //ѡ���������޸���
						printf("***�޸ı����鼮��Ϣ***\n");
						printf( "--1 �޸� ����-----\n"
								"--2 �޸� ����-----\n"
								"--3 �޸ĳ�����----\n"
								"--4 �޸� ���-----\n"
								"--0 �����ϼ��˵�---\n");
						printf( "******************\n");
						switch(ch)
						{
							case '0':{
								break;
							}
							case '1':
							{
								printf("�������µ��鼮���ƣ�");
								list_node_scanf_name(ptr);
								break;
							}
							case '2':
							{
								printf("�������µ����������������������';'�ֿ�����");
								list_node_scanf_author(ptr);
								break;
							}
							case '3':
							{
								printf("�������µĳ��������ƣ�");
								list_node_scanf_press(ptr);
								break;
							}
							case '4':
							{
								printf("�������µ����(רҵ��:0 ; �ο���:1 ; ����:2 ; С˵:3 ; ����:4)��");
								if(list_node_scanf_category(ptr) != 0)
								{
									CLEAR
									printf("�Ƿ��鼮���\n");
									continue;
								}
								break;
							}
						}
						CLEAR
						printf("�޸ĳɹ���\n");
						break;
					}
				}
				else if(opt == 'n')//����2���˵�
				{
					CLEAR
					break;
				}
				else
				{
					CLEAR
					printf("�Ƿ�ѡ��!\n");
					break;
				}
				break;
			}
			//?break;
		}
		//����ѡ��
	}
	return 0;
}

int delete_book(BOOK books_head)
{
	assert(books_head != NULL);
	CLEAR //����
	while(1)
	{
		printf( "*****ɾ���鼮��Ϣ*****\n");
		printf( "---1 ���鼮���ɾ��---\n"
				"---0 �������˵�-------\n");
		printf( "*********************\n");
		char t = getch();
		if(t == '0') return 0;
		else if(t == '1') //3���˵�
		{
			CLEAR
			while(1)
			{
				printf("������Ҫɾ�����鼮��ţ�");
				char id[100];
				fflush(stdin);
				scanf("%99s", id);
				int i;
				for(i = 0; i < strlen(id); i++)
				{
					if(id[i] < '0' || id[i] > '9')
					{
						CLEAR
						printf("�Ƿ��鼮��ţ�\n");
						break;
					}
				}
				BOOK ptr = list_search_by_id(books_head, id);
				if(ptr == NULL)
				{
					CLEAR
					printf("δ��ѯ�������������鼮��\n");
					break;
				}
				else
				{
					list_node_display(ptr, GetPosY());
					again:
					printf("�Ƿ�ȷ��ɾ����y/n:");
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
							printf("�鼮��Ϣɾ���ɹ���\n");
							break;
						}
						else
						{
							CLEAR
							printf("�鼮��Ϣɾ��ʧ�ܣ�\n");
							break;
						}
					}
					else if(opt == 'n')
					{
						CLEAR
						printf("�鼮��Ϣɾ��ȡ����\n");
						break;
					}
					else
					{
						break;
					}
				}
			}
		}
		//�������
	}
}

int save_books(char* filename, BOOK books_head)
{
	assert(books_head != NULL);
	int status = file_save(filename, books_head);
	if(status == 0)
	{
		printf("�鼮��Ϣ����ɹ���\n");
		return 0;
	}
	else if(status == -1)
	{
		printf("�鼮��Ϣ����ʧ�ܣ�\n");
		return -1;
	}
	else
	{
		printf("δ֪���!\n");
		return -1;
	}
}


void do_exit(BOOK books_head)
{
	CLEAR
	char t;
	printf("*********�˳�********\n");
	printf("   ��ȷ��Ҫ�˳���   \n");
	printf(" 1.ȷ��     2.ȡ��   \n");
	printf("*********************\n");
	while(1)
	{
		t=getch();         //����t
		switch(t)
		{
			case '1':
				CLEAR
				list_free(books_head);
				printf("�ɹ��˳�����лʹ��^_^\n");
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
	   		"                                       �鼮��Ϣ���£�\n"
	   		"----------------------------------------------------------------------------------------\n");
	PRINT_NOTE
	int num = list_display(books_head);
	if(num == 0)
	{
		printf("�鼮��ϢΪ�գ�\n");
	}
	printf( "----------------------------------------����%d���鼮��Ϣ---------------------------------\n", num);
	printf( "=========================================================================================\n");
}

int search_books(BOOK books_head)
{
	assert(books_head != NULL);
	CLEAR
	while(1)
	{
		printf("*****�����鼮��Ϣ*****\n");
		printf(	"----1 ����   ��ѯ----\n"
				"----2 ����   ��ѯ----\n"
				"----3 ������ ��ѯ----\n"
				"----4 ���   ��ѯ----\n"
				"----0 �������˵�-----\n");
		printf( "**********************\n");
		char c = getch();
		/*if(c < '0' || c > '4')
		{
			CLEAR
			printf("�Ƿ�ѡ��\n");
			break;//���ܷ���
		}*///���ֲ��ô���
		switch(c)
		{
			case '0':{
				return 0;
			}
			case '1':{
				printf("������������");
				char name[100];
				fflush(stdin);
				scanf("%99[^\n]", name);
				BOOK_INFO ptr = list_search_by_name(books_head, name);
				CLEAR
				display_results(ptr);
				break;}
			case '2':{
				printf("���������ߣ�");
				char author[50];
				fflush(stdin);
				scanf("%49[^\n]", author);
				BOOK_INFO ptr = list_search_by_author(books_head, author);
				CLEAR
				display_results(ptr);
				break;}
			case '3':{
				printf("����������磺");
				char press[50];
				fflush(stdin);
				scanf("%49[^\n]", press);
				BOOK_INFO ptr = list_search_by_press(books_head, press);
				CLEAR
				display_results(ptr);
				break;}
			case '4':{
				printf("���������(רҵ��:0 ; �ο���:1 ; ����:2 ; С˵:3 ; ����:4)��");
				BOOK_TYPE type;
				fflush(stdin);
				char c;
				int flag = scanf("%1d%c", &type, &c);
				if(flag == 0 || type < 0 || type > 4 || c!='\n')
				{
					CLEAR
					printf("�Ƿ�ѡ�\n");
				}
				BOOK_INFO ptr = list_search_by_category(books_head, type);
				CLEAR
				display_results(ptr);
				break;}
			default:{
				CLEAR
				printf("�Ƿ�ѡ��\n");}
		}
	}
}

int statistic_books(BOOK books_head)
{
	assert(books_head != NULL);
	CLEAR
	while(1)
	{
		printf( "*****ͳ���鼮��Ϣ*****\n");
		printf( "----0 ͳ�� רҵ��----\n"
				"----1 ͳ�� �ο���----\n"
				"----2 ͳ��  ����-----\n"
				"----3 ͳ��  С˵-----\n"
				"----4 ͳ��  ����-----\n"
				"----5 �������˵�-----\n");
		printf( "*********************\n");
		char c = getch();
		if(c == '5') return 0;
		if(c < '0' || c > '5')
		{
			CLEAR
			printf("�Ƿ�ѡ�\n");
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
