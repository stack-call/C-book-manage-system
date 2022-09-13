#ifndef WIN_POS_H
#define WIN_POS_H
#include <windows.h>

#define POSX 0
#define LPOSX 30
#define MPOSX 48
#define BOOKPOSX 10
#define CLEAR system("cls");

#define WAIT \
	printf("��������������˵�\n");\
	getch();
//�Ļ�ȥ������

static inline void SetPos(int x, int y)      //������ƶ���X,Y���괦
{
	COORD pos = { x , y };
	HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Out, pos);
}
static inline int GetPosX()
{
	// ��ȡ������
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(outputHandle, &info);
    return info.dwCursorPosition.X;
}

static inline int GetPosY()
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(outputHandle, &info);
    return info.dwCursorPosition.Y;
}
#endif