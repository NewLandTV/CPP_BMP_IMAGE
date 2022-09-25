#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include"resource.h"

static HWND hWnd;
static HINSTANCE hInst;

void Init()
{
    system("title Console Image");
    system("mode con cols=216 lines=54");

    CONSOLE_CURSOR_INFO consoleCursorInfo;

    consoleCursorInfo.bVisible = 0;
    consoleCursorInfo.dwSize = 1;

    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);

    hWnd = GetConsoleWindow();

    hInst = GetModuleHandle(NULL);
}

void Render(int x, int y)
{
    HDC hDC;
    HDC hMemDC;

    static HDC hBackDC;

    HBITMAP hBitmap;
    HBITMAP hOldBitmap;
    HBITMAP hBackBitmap;
    BITMAP bitmap;
    RECT windowRect;

    GetWindowRect(hWnd, &windowRect);

    hDC = GetDC(hWnd);
    hBackDC = CreateCompatibleDC(hDC);
    hMemDC = CreateCompatibleDC(hDC);

    hBackBitmap = CreateCompatibleBitmap(hDC, windowRect.right, windowRect.bottom);
    hOldBitmap = (HBITMAP)SelectObject(hBackDC, hBackBitmap);

    hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));

    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    SelectObject(hMemDC, hBitmap);
    BitBlt(hBackDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);
    BitBlt(hDC, x, y, x + bitmap.bmWidth, y + bitmap.bmHeight, hBackDC, 0, 0, SRCCOPY);

    DeleteObject(SelectObject(hBackDC, hBackBitmap));
    DeleteObject(hBitmap);
    DeleteDC(hBackDC);
    DeleteDC(hMemDC);

    ReleaseDC(hWnd, hDC);
}

int main(void)
{
    Init();

    int x = 0;
    int y = 0;

    Sleep(2000);

    while (1)
    {
        Render(x, y);

        x += 48;

        if (x == 1728)
        {
            x = 0;
            y += 48;
        }

        if (y == 864)
        {
            break;
        }
    }

    while (1);

    return 0;
}
