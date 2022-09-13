#ifndef WIN_POS_H
#define WIN_POS_H
#include <windows.h>

#define POSX 0
#define LPOSX 30
#define MPOSX 48
#define BOOKPOSX 10
#define CLEAR system("cls");

#define WAIT \
	printf("按任意键返回主菜单\n");\
	getch();
//改回去！！！

static inline void SetPos(int x, int y)      //将光标移动到X,Y坐标处
{
	COORD pos = { x , y };
	HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Out, pos);
}
static inline int GetPosX()
{
	// 获取输出句柄
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