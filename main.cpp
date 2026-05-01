/*
* Copyright (C) Leonid Kostikov
*
* This file is part of Single_phase_rectifiers
*
* Single_phase_rectifiers is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Single_phase_rectifiers is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Foobar.
If not, see <https://www.gnu.org/licenses/>.
*/


#include <windows.h>
#include <commdlg.h>
#include <stdio.h>   // sprintf, _stprintf
#include <stdlib.h>  // atof
#include "resource.h"
#include "calculations.h"


HINSTANCE g_hInst = NULL;
HBITMAP   g_hBmp  = NULL;
HWND hBmp = NULL;

HWND hRadio1 = NULL;
HWND hRadio2 = NULL;
HWND hRadio3 = NULL;

HWND hGroupBox1 = NULL;
HWND hGroupBox2 = NULL;
HWND hGroupBox3 = NULL;

HWND hLText1 = NULL;
HWND hLText2 = NULL;
HWND hLText3 = NULL;
HWND hLText4 = NULL;

HWND hLText5 = NULL;
HWND hLText6 = NULL;
HWND hLText7 = NULL;
HWND hLText8 = NULL;
HWND hLText9 = NULL;
HWND hLText10 = NULL;
HWND hLText11 = NULL;
HWND hLText12 = NULL;

HWND hNumberEdit1 = NULL;
HWND hNumberEdit2 = NULL;
HWND hNumberEdit3 = NULL;
HWND hNumberEdit4 = NULL;

HWND hNumberEdit5 = NULL;
HWND hNumberEdit6 = NULL;
HWND hNumberEdit7 = NULL;
HWND hNumberEdit8 = NULL;
HWND hNumberEdit9 = NULL;
HWND hNumberEdit10 = NULL;
HWND hNumberEdit11 = NULL;
HWND hNumberEdit12 = NULL;

WNDPROC g_limitFloatEditProc = NULL; // Одна для всех!

HWND hBtnCalc = NULL;
HWND hBtnClear = NULL;
HWND hBtnSaveResults = NULL;

unsigned char enc_aut[] = {
    0x8A, 0xBA, 0xBD, 0xAA, 0xBA, 0xBB, 0xB4, 0xA8,
    0xAD, 0xB2, 0xB0, 0x60, 0x7A, 0x90, 0xB4, 0xAB,
    0xA8, 0xB2, 0xB0, 0xB4, 0xB8, 0x7A, 0x91, 0xBF,
    0xB4, 0xB7, 0xB2, 0xBE, 0x7A, 0x90, 0xB4, 0xB7,
    0xAB, 0xA8, 0xBA, 0xB7, 0xA8, 0xB2, 0xB7, 0xB4,
    0xB8, 0xB2, 0xAD, 0x00
};

unsigned char enc_lic[] = {
    0x91, 0xB2, 0xAC, 0xBF, 0xB7, 0xBD, 0xB2, 0xA5,
    0x60, 0x7A, 0x1D, 0x14, 0x0F, 0x7A, 0x1D, 0x3F,
    0x34, 0x3F, 0x28, 0x3B, 0x36, 0x7A, 0x0A, 0x2F,
    0x38, 0x36, 0x33, 0x39, 0x7A, 0x16, 0x33, 0x39,
    0x3F, 0x34, 0x29, 0x3F, 0x7A, 0x2C, 0x3F, 0x28,
    0x29, 0x33, 0x35, 0x34, 0x7A, 0x69, 0x00
};

unsigned char enc_re[] = {
    0x8A, 0xBF, 0xB5, 0xB4, 0xBD, 0xB2, 0xA8, 0xB4,
    0xAA, 0xB2, 0xB3, 0x60, 0x7A, 0x32, 0x2E, 0x2E,
    0x2A, 0x29, 0x60, 0x75, 0x75, 0x3D, 0x33, 0x2E,
    0x32, 0x2F, 0x38, 0x74, 0x39, 0x35, 0x37, 0x75,
    0x16, 0x3F, 0x35, 0x34, 0x33, 0x3E, 0x77, 0x11,
    0x35, 0x29, 0x2E, 0x33, 0x31, 0x35, 0x2C, 0x77,
    0x33, 0x2C, 0x2E, 0x77, 0x68, 0x69, 0x68, 0x75,
    0x09, 0x33, 0x34, 0x3D, 0x36, 0x3F, 0x05, 0x2A,
    0x32, 0x3B, 0x29, 0x3F, 0x05, 0x28, 0x3F, 0x39,
    0x2E, 0x33, 0x3C, 0x33, 0x3F, 0x28, 0x29, 0x00
};

float GetFloatFromEdit(HWND hWnd, int editId);
int save_the_calculation_results();
void SetFloatToEdit(HWND hWnd, int editId, float value);
void SetBitmapToStatic(HWND hWnd, int resId);
BOOL LoadFontFromFile(LPCWSTR fontPath);
HFONT CreateInterFont(HWND hWnd, int height, BOOL bold = FALSE);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK FloatEditSubclassProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    g_hInst = hInstance;

    // Регистрируем класс окна
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = TEXT("RectifierWindow");
    // Серый фон Windows 9x
    wc.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));  // классический серый
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);

    // Загружаем меню из ресурсов
    HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

    // Создаём ГЛАВНОЕ окно
    HWND hWnd = CreateWindowEx(
        0,
        TEXT("RectifierWindow"),
        TEXT("Single phase rectifiers"),
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 771, 483,
        NULL, hMenu, hInstance, NULL
    );

    if (!hWnd) return 0;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (g_hBmp) DeleteObject(g_hBmp);
    return (int)msg.wParam;
}

void CreateControls(HWND hWnd)
{
    HFONT hInterFont1 = CreateInterFont(hWnd, -13, FALSE);  // 10pt
    HFONT hInterFont2 = CreateInterFont(hWnd, -14, TRUE);
    HFONT hInterFont3 = CreateInterFont(hWnd, -13, TRUE);

    hBmp = CreateWindowEx(0, "STATIC", TEXT(""),
                   WS_CHILD | WS_VISIBLE | SS_BITMAP,
                   10, 10, 200, 150,
                   hWnd, (HMENU)102, g_hInst, NULL);

    // GroupBox — ID 200
    hGroupBox1 = CreateWindowEx(0, "BUTTON", TEXT("Схемы выпрямителей"),
                   WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                   380, 10, 375, 105,  // x, y, ширина, высота
                   hWnd, (HMENU)200, g_hInst, NULL);

    hRadio1 = CreateWindowEx(0, "BUTTON", TEXT("Однополупериодный выпрямитель"),
                   WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
                   395, 30, 275, 25,
                   hWnd, (HMENU)IDC_RADIO1, g_hInst, NULL);

    hRadio2 = CreateWindowEx(0, "BUTTON", TEXT("Двухполупериодный выпрямитель со средней точкой"),
                   WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                   395, 55, 345, 25,
                   hWnd, (HMENU)IDC_RADIO2, g_hInst, NULL);

    hRadio3 = CreateWindowEx(0, "BUTTON", TEXT("Мостовая схема двухполупериодного выпрямителя"),
                   WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
                   395, 80, 345, 25,
                   hWnd, (HMENU)IDC_RADIO3, g_hInst, NULL);

    SendMessage(hGroupBox1, WM_SETFONT, (WPARAM)hInterFont2, TRUE);

    SendMessage(hRadio1, WM_SETFONT, (WPARAM)hInterFont1, FALSE);
    SendMessage(hRadio2, WM_SETFONT, (WPARAM)hInterFont1, FALSE);
    SendMessage(hRadio3, WM_SETFONT, (WPARAM)hInterFont1, FALSE);

    // GroupBox (Входные данные) — ID 201
    hGroupBox2 = CreateWindowEx(0, "BUTTON", TEXT("Входные данные"),
                   WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                   10, 200, 356, 155,  // x, y, ширина, высота
                   hWnd, (HMENU)201, g_hInst, NULL);

    hLText1 = CreateWindowEx(0, "STATIC", TEXT("Напряжение на вторич. обмотке тр-ра Uвт, В"),
                   WS_CHILD | WS_VISIBLE | SS_LEFT,
                   18, 227, 300, 20,
                   hWnd, (HMENU)401, g_hInst, NULL);

    hLText2 = CreateWindowEx(0, "STATIC", TEXT("Частота f, Гц"),
                   WS_CHILD | WS_VISIBLE | SS_LEFT,
                   18, 257, 300, 20,
                   hWnd, (HMENU)402, g_hInst, NULL);

    hLText3 = CreateWindowEx(0, "STATIC", TEXT("Ток нагрузки Iн, А"),
                   WS_CHILD | WS_VISIBLE | SS_LEFT,
                   18, 287, 300, 20,
                   hWnd, (HMENU)403, g_hInst, NULL);

    hLText4 = CreateWindowEx(0, "STATIC", TEXT("Пульсации dU, В"),
                   WS_CHILD | WS_VISIBLE | SS_LEFT,
                   18, 317, 300, 20,
                   hWnd, (HMENU)404, g_hInst, NULL);


    hNumberEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TEXT("0"),
                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                   295, 225, 60, 25,
                   hWnd, (HMENU)301, g_hInst, NULL);

    hNumberEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TEXT("0"),
                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                   295, 255, 60, 25,
                   hWnd, (HMENU)302, g_hInst, NULL);

    hNumberEdit3 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TEXT("0"),
                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                   295, 285, 60, 25,
                   hWnd, (HMENU)303, g_hInst, NULL);

    hNumberEdit4 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TEXT("0"),
                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
                   295, 315, 60, 25,
                   hWnd, (HMENU)304, g_hInst, NULL);

    SendMessage(hGroupBox2, WM_SETFONT, (WPARAM)hInterFont2, TRUE);

    SendMessage(hLText1, WM_SETFONT, (WPARAM)hInterFont1, FALSE);
    SendMessage(hLText2, WM_SETFONT, (WPARAM)hInterFont1, FALSE);
    SendMessage(hLText3, WM_SETFONT, (WPARAM)hInterFont1, FALSE);
    SendMessage(hLText4, WM_SETFONT, (WPARAM)hInterFont1, FALSE);

    SendMessage(hNumberEdit1, WM_SETFONT, (WPARAM)hInterFont3, TRUE);
    SendMessage(hNumberEdit2, WM_SETFONT, (WPARAM)hInterFont3, TRUE);
    SendMessage(hNumberEdit3, WM_SETFONT, (WPARAM)hInterFont3, TRUE);
    SendMessage(hNumberEdit4, WM_SETFONT, (WPARAM)hInterFont3, TRUE);

    //Одна строка для всех EditBox!
    g_limitFloatEditProc = (WNDPROC)SetWindowLongPtr(hNumberEdit1, GWLP_WNDPROC, (LONG_PTR)FloatEditSubclassProc);

    SetWindowLongPtr(hNumberEdit2, GWLP_WNDPROC, (LONG_PTR)FloatEditSubclassProc);
    SetWindowLongPtr(hNumberEdit3, GWLP_WNDPROC, (LONG_PTR)FloatEditSubclassProc);
    SetWindowLongPtr(hNumberEdit4, GWLP_WNDPROC, (LONG_PTR)FloatEditSubclassProc);

    hGroupBox3 = CreateWindowEx(0, "BUTTON", TEXT("Результаты расчета"),
                   WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                   380, 128, 375, 257,  // x, y, ширина, высота
                   hWnd, (HMENU)202, g_hInst, NULL);

    hLText5 = CreateWindowEx(0, "STATIC", TEXT("Амплитуда напряжения Uмакс, В"),
                   WS_CHILD | WS_VISIBLE | SS_LEFT,
                   395, 154, 300, 20,
                   hWnd, (HMENU)405, g_hInst, NULL);

    hLText6 = CreateWindowEx(0, "STATIC", TEXT("Среднее напряжение Uср, В"),
                   WS_CHILD | WS_VISIBLE | SS_LEFT,
                   395, 182, 300, 20,
                   hWnd, (HMENU)406, g_hInst, NULL);

    hLText7 = CreateWindowEx(0, "STATIC", TEXT("Средний ток Iср, А"),
                   WS_CHILD | WS_VISIBLE | SS_LEFT,
                   395, 210, 300, 20,
                   hWnd, (HMENU)407, g_hInst, NULL);

    hLText8 = CreateWindowEx(0, "STATIC", TEXT("Сопротивление нагрузки Rн, Ом"),
                   WS_CHILD | WS_VISIBLE | SS_LEFT,
                   395, 238, 300, 20,
                   hWnd, (HMENU)408, g_hInst, NULL);

    hLText9 = CreateWindowEx(0, "STATIC", TEXT("Типовая мощьность трансф. Pтип, Вт"),
                   WS_CHILD | WS_VISIBLE | SS_LEFT,
                   395, 266, 300, 20,
                   hWnd, (HMENU)409, g_hInst, NULL);

    hLText10 = CreateWindowEx(0, "STATIC", TEXT("Обратное напряжение Uобр, В"),
                   WS_CHILD | WS_VISIBLE | SS_LEFT,
                   395, 294, 300, 20,
                   hWnd, (HMENU)410, g_hInst, NULL);

    hLText11 = CreateWindowEx(0, "STATIC", TEXT("Емкость сглаживающего фильтра Сф, мкФ"),
                   WS_CHILD | WS_VISIBLE | SS_LEFT,
                   395, 322, 300, 20,
                   hWnd, (HMENU)411, g_hInst, NULL);

    hLText12 = CreateWindowEx(0, "STATIC", TEXT("Рабочее напряжение сгл. фильтра Uc, В"),
                   WS_CHILD | WS_VISIBLE | SS_LEFT,
                   395, 350, 300, 20,
                   hWnd, (HMENU)412, g_hInst, NULL);

    hNumberEdit5 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TEXT("0"),
                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY, //только для чтения
                   685, 153, 60, 25,
                   hWnd, (HMENU)305, g_hInst, NULL);

    hNumberEdit6 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TEXT("0"),
                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY, //только для чтения
                   685, 181, 60, 25,
                   hWnd, (HMENU)306, g_hInst, NULL);

    hNumberEdit7 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TEXT("0"),
                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY, //только для чтения
                   685, 209, 60, 25,
                   hWnd, (HMENU)307, g_hInst, NULL);

    hNumberEdit8 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TEXT("0"),
                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY, //только для чтения
                   685, 237, 60, 25,
                   hWnd, (HMENU)308, g_hInst, NULL);

    hNumberEdit9 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TEXT("0"),
                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY, //только для чтения
                   685, 265, 60, 25,
                   hWnd, (HMENU)309, g_hInst, NULL);

    hNumberEdit10 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TEXT("0"),
                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY, //только для чтения
                   685, 293, 60, 25,
                   hWnd, (HMENU)310, g_hInst, NULL);

    hNumberEdit11 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TEXT("0"),
                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY, //только для чтения
                   685, 321, 60, 25,
                   hWnd, (HMENU)311, g_hInst, NULL);

    hNumberEdit12 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", TEXT("0"),
                   WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER | ES_READONLY, //только для чтения
                   685, 349, 60, 25,
                   hWnd, (HMENU)312, g_hInst, NULL);

    SendMessage(hGroupBox3, WM_SETFONT, (WPARAM)hInterFont2, TRUE);

    SendMessage(hLText5, WM_SETFONT, (WPARAM)hInterFont1, FALSE);
    SendMessage(hLText6, WM_SETFONT, (WPARAM)hInterFont1, FALSE);
    SendMessage(hLText7, WM_SETFONT, (WPARAM)hInterFont1, FALSE);
    SendMessage(hLText8, WM_SETFONT, (WPARAM)hInterFont1, FALSE);
    SendMessage(hLText9, WM_SETFONT, (WPARAM)hInterFont1, FALSE);
    SendMessage(hLText10, WM_SETFONT, (WPARAM)hInterFont1, FALSE);
    SendMessage(hLText11, WM_SETFONT, (WPARAM)hInterFont1, FALSE);
    SendMessage(hLText12, WM_SETFONT, (WPARAM)hInterFont1, FALSE);

    SendMessage(hNumberEdit5, WM_SETFONT, (WPARAM)hInterFont3, FALSE);
    SendMessage(hNumberEdit6, WM_SETFONT, (WPARAM)hInterFont3, FALSE);
    SendMessage(hNumberEdit7, WM_SETFONT, (WPARAM)hInterFont3, FALSE);
    SendMessage(hNumberEdit8, WM_SETFONT, (WPARAM)hInterFont3, FALSE);
    SendMessage(hNumberEdit9, WM_SETFONT, (WPARAM)hInterFont3, FALSE);
    SendMessage(hNumberEdit10, WM_SETFONT, (WPARAM)hInterFont3, FALSE);
    SendMessage(hNumberEdit11, WM_SETFONT, (WPARAM)hInterFont3, FALSE);
    SendMessage(hNumberEdit12, WM_SETFONT, (WPARAM)hInterFont3, FALSE);

    // Кнопка "РАСЧЁТ" (ID = 501)
    hBtnCalc = CreateWindow(TEXT("BUTTON"), TEXT("Расчет"),
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
        534, 390, 220, 35,     // x, y, ширина, высота
        hWnd, (HMENU)501, g_hInst, NULL);

    // Кнопка "ОЧИСТИТЬ" (ID = 502)
    hBtnClear = CreateWindow(TEXT("BUTTON"), TEXT("Сброс"),
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
        380, 390, 150, 35,
        hWnd, (HMENU)502, g_hInst, NULL);

    // Кнопка "Сохранить результаты расчета" (ID = 503)
    hBtnSaveResults = CreateWindow(TEXT("BUTTON"), TEXT("Сохранить результаты расчета"),
        WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON,
        10, 360, 356, 65,     // x, y, ширина, высота
        hWnd, (HMENU)503, g_hInst, NULL);

    SendMessage(hBtnCalc, WM_SETFONT, (WPARAM)hInterFont2, FALSE);
    SendMessage(hBtnClear, WM_SETFONT, (WPARAM)hInterFont2, FALSE);
    SendMessage(hBtnSaveResults, WM_SETFONT, (WPARAM)hInterFont2, FALSE);
}

void SetBitmapToStatic(HWND hWnd, int resId)
{
    if (g_hBmp) {
        DeleteObject(g_hBmp);
        g_hBmp = NULL;
    }

    g_hBmp = LoadBitmap(g_hInst, MAKEINTRESOURCE(resId));
    if (!g_hBmp) return;

    HWND hStatic = GetDlgItem(hWnd, 102);
    SendMessage(hStatic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)g_hBmp);

    InvalidateRect(hStatic, NULL, TRUE);
    UpdateWindow(hStatic);
}

HFONT CreateInterFont(HWND hWnd, int height, BOOL bold)
{
    LOGFONT lf = {0};
    lf.lfHeight = height;
    lf.lfWeight = bold ? FW_BOLD : FW_NORMAL;  // ЖИРНОСТЬ!
    lstrcpy(lf.lfFaceName, TEXT("Tahoma"));
    return CreateFontIndirect(&lf);
}

LRESULT CALLBACK FloatEditSubclassProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // Ограничение ввода символов в EditBox
{
    if (msg == WM_CHAR)
    {
        TCHAR ch = (TCHAR)wParam;
        if (!((ch >= '0' && ch <= '9') || ch == '.' || ch == VK_BACK))
            return 0;
    }
    return CallWindowProc(g_limitFloatEditProc, hWnd, msg, wParam, lParam);
}


// ЧИТАЕМ float из EditBox
float GetFloatFromEdit(HWND hWnd, int editId)
{
    TCHAR buf[32];
    GetWindowText(GetDlgItem(hWnd, editId), buf, 32);
    return (float)atof(buf);
}

// ЗАПИСЫВАЕМ float в ReadOnly EditBox
void SetFloatToEdit(HWND hWnd, int editId, float value)
{
    TCHAR buf[32];
    SetWindowText(GetDlgItem(hWnd, editId), buf);
}


int save_the_calculation_results(int id_idc_radio,
                                 float u2,
                                 float f,
                                 float i_n,
                                 float du,
                                 float* u_max,
                                 float* u_sr,
                                 float* r_n,
                                 float* p_tip,
                                 float* u_obr,
                                 float* c_f,
                                 float* u_c,
                                 float* i2,
                                 float* i_max)
{
    OPENFILENAME ofn = {0};
    char szFile[MAX_PATH] = {0};     // Полный путь
    char szFileTitle[MAX_PATH] = {0}; // Только имя файла

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = GetForegroundWindow();
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Текстовый файл\0*.txt\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = szFileTitle;
    ofn.nMaxFileTitle = sizeof(szFileTitle);
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    if (GetSaveFileNameA(&ofn))
    {
        char filename[MAX_PATH] = {0};

        // Копируем имя файла без расширения
        int len = ofn.nFileExtension ? (ofn.nFileExtension - ofn.nFileOffset) : strlen(szFile + ofn.nFileOffset);
        strncpy(filename, szFile + ofn.nFileOffset, len);

        // Добавляем ".txt"
        strcat(filename, ".txt");

        printf("Имя с расширением: %s\n", filename);  // "name.txt"

        FILE *file = fopen(filename, "w");

        if (file == NULL)
        {
            perror("Ошибка сохранеия файла");
            return 1;
        }

        fprintf(file, "***********************************************************************\n");
        fprintf(file, "*                      Single_phase_rectifiers 1.0                    *\n");
        fprintf(file, "***********************************************************************\n\n");
        fprintf(file, "*                            Входные данные                           *\n");
        fprintf(file, "-----------------------------------------------------------------------\n\n");
        fprintf(file, "Напряжение на вторичной обмотке трансформатора Uвт, В: %.3f\n", u2);
        fprintf(file, "Частота сети f, Гц: %.3f\n", f);
        fprintf(file, "Ток нагрузки Iн, А: %.3f\n", i_n);
        fprintf(file, "Пульсации dU, В: %.3f\n\n", du);

        printf("%d", id_idc_radio);

        if (id_idc_radio == 1)
            fprintf(file, "*          Результаты расчета однополупериодного выпрямителя          *\n");
        else if (id_idc_radio == 2)
            fprintf(file, "* Результаты расчета двухполупериодного выпрямителя со средней точкой *\n");
        else if (id_idc_radio == 3)
            fprintf(file, "*  Результаты расчета мостовой схемы двухполупериодного выпрямителя   *\n");

        fprintf(file, "-----------------------------------------------------------------------\n\n");
        fprintf(file, "Амплитудное значение напряжения Uмакс, В: %.3f\n", *u_max);
        fprintf(file, "Среднее значение выпрямленного напряжения Uср, В: %.3f\n", *u_sr);
        fprintf(file, "Амплитудное значение тока Iмакс, А: %.3f\n", *i_max);
        fprintf(file, "Ток на вторичной обмотке трансформатора Iвт, А: %.3f\n", *i2);
        fprintf(file, "Среднее значение выпрямленного тока Iср, А: %.3f\n", i_n);
        fprintf(file, "Сопротивление нагрузки Rн, Ом: %.3f\n", *r_n);
        fprintf(file, "Типовая мощьность трансформатора Pтип, Вт: %.3f\n", *p_tip);
        fprintf(file, "Обратное напряжение Uобр, В: %.3f\n", *u_obr);
        fprintf(file, "Емкость сглаживающего фильтра Сф, мкФ: %.3f\n", *c_f);
        fprintf(file, "Рабочее напряжение сгл. фильтра Uc, В: %.3f\n", *u_c);

        fclose(file);
    }

    return 0;
}


BOOL LoadFontFromFile(LPCWSTR fontPath)
{
    return AddFontResourceExW(fontPath, FR_PRIVATE, NULL) > 0;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    HINSTANCE hInst;
    HICON hIcon;

    switch (uMsg)
    {
    case WM_CREATE:
        CreateControls(hWnd);
        CheckDlgButton(hWnd, IDC_RADIO1, BST_CHECKED);
        SetBitmapToStatic(hWnd, IDB_BITMAP1);
        hInst = GetModuleHandle(NULL);
		hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_MAIN_ICON));
		SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        return 0;

    case WM_COMMAND:
    {
        int id = LOWORD(wParam);
        int code = HIWORD(wParam);
        int id_idc_radio;
        static float u2, f, i_n, du;
        static float u_max, u_sr, i_sr, r_n, p_tip, u_obr, c_f, u_c, i2, i_max;

        ///////////////////////////////////////////
        // КНОПКА РАСЧЁТ (501)
        if (id == 501 && code == BN_CLICKED)
        {
            // Проверяем RADIO1 активна
            if (SendMessage(GetDlgItem(hWnd, IDC_RADIO1), BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
                char buf[32];

                GetWindowTextA(GetDlgItem(hWnd, 301), buf, 32); u2  = (float)atof(buf);
                GetWindowTextA(GetDlgItem(hWnd, 302), buf, 32); f   = (float)atof(buf);
                GetWindowTextA(GetDlgItem(hWnd, 303), buf, 32); i_n = (float)atof(buf);
                GetWindowTextA(GetDlgItem(hWnd, 304), buf, 32); du  = (float)atof(buf);

                // Расчёт
                single_half_period_rectifier(u2, f, i_n, du, &u_max, &u_sr, &r_n,
                                             &p_tip, &u_obr, &c_f, &u_c, &i2, &i_max);

                // Вывод
                sprintf(buf, "%.3f", u_max); SetWindowText(GetDlgItem(hWnd, 305), buf);
                sprintf(buf, "%.3f", u_sr); SetWindowText(GetDlgItem(hWnd, 306), buf);
                sprintf(buf, "%.3f", i_n); SetWindowText(GetDlgItem(hWnd, 307), buf);
                sprintf(buf, "%.3f", r_n); SetWindowText(GetDlgItem(hWnd, 308), buf);
                sprintf(buf, "%.3f", p_tip); SetWindowText(GetDlgItem(hWnd, 309), buf);
                sprintf(buf, "%.3f", u_obr); SetWindowText(GetDlgItem(hWnd, 310), buf);
                sprintf(buf, "%.3f", c_f); SetWindowText(GetDlgItem(hWnd, 311), buf);
                sprintf(buf, "%.3f", u_c); SetWindowText(GetDlgItem(hWnd, 312), buf);
            }
            else if (SendMessage(GetDlgItem(hWnd, IDC_RADIO2), BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
                char buf[32];

                GetWindowTextA(GetDlgItem(hWnd, 301), buf, 32); u2  = (float)atof(buf);
                GetWindowTextA(GetDlgItem(hWnd, 302), buf, 32); f   = (float)atof(buf);
                GetWindowTextA(GetDlgItem(hWnd, 303), buf, 32); i_n = (float)atof(buf);
                GetWindowTextA(GetDlgItem(hWnd, 304), buf, 32); du  = (float)atof(buf);

                // Расчёт
                two_half_period_rectifier_with_a_midpoint(u2, f, i_n, du, &u_max, &u_sr, &r_n,
                                                          &p_tip, &u_obr, &c_f, &u_c, &i2, &i_max);

                // Вывод
                sprintf(buf, "%.3f", u_max); SetWindowText(GetDlgItem(hWnd, 305), buf);
                sprintf(buf, "%.3f", u_sr); SetWindowText(GetDlgItem(hWnd, 306), buf);
                sprintf(buf, "%.3f", i_n); SetWindowText(GetDlgItem(hWnd, 307), buf);
                sprintf(buf, "%.3f", r_n); SetWindowText(GetDlgItem(hWnd, 308), buf);
                sprintf(buf, "%.3f", p_tip); SetWindowText(GetDlgItem(hWnd, 309), buf);
                sprintf(buf, "%.3f", u_obr); SetWindowText(GetDlgItem(hWnd, 310), buf);
                sprintf(buf, "%.3f", c_f); SetWindowText(GetDlgItem(hWnd, 311), buf);
                sprintf(buf, "%.3f", u_c); SetWindowText(GetDlgItem(hWnd, 312), buf);
            }
            else if (SendMessage(GetDlgItem(hWnd, IDC_RADIO3), BM_GETCHECK, 0, 0) == BST_CHECKED)
            {
                char buf[32];

                GetWindowTextA(GetDlgItem(hWnd, 301), buf, 32); u2  = (float)atof(buf);
                GetWindowTextA(GetDlgItem(hWnd, 302), buf, 32); f   = (float)atof(buf);
                GetWindowTextA(GetDlgItem(hWnd, 303), buf, 32); i_n = (float)atof(buf);
                GetWindowTextA(GetDlgItem(hWnd, 304), buf, 32); du  = (float)atof(buf);

                // Расчёт
                bridge_circuit_of_a_two_half_period_rectifier(u2, f, i_n, du, &u_max, &u_sr, &r_n,
                                                              &p_tip, &u_obr, &c_f, &u_c, &i2, &i_max);

                // Вывод
                sprintf(buf, "%.3f", u_max); SetWindowText(GetDlgItem(hWnd, 305), buf);
                sprintf(buf, "%.3f", u_sr); SetWindowText(GetDlgItem(hWnd, 306), buf);
                sprintf(buf, "%.3f", i_n); SetWindowText(GetDlgItem(hWnd, 307), buf);
                sprintf(buf, "%.3f", r_n); SetWindowText(GetDlgItem(hWnd, 308), buf);
                sprintf(buf, "%.3f", p_tip); SetWindowText(GetDlgItem(hWnd, 309), buf);
                sprintf(buf, "%.3f", u_obr); SetWindowText(GetDlgItem(hWnd, 310), buf);
                sprintf(buf, "%.3f", c_f); SetWindowText(GetDlgItem(hWnd, 311), buf);
                sprintf(buf, "%.3f", u_c); SetWindowText(GetDlgItem(hWnd, 312), buf);
            }
            return 0;
        }
        // КНОПКА СБРОС (502)
        if (id == 502 && code == BN_CLICKED)
        {
            SetWindowText(GetDlgItem(hWnd, 301), "0");
            SetWindowText(GetDlgItem(hWnd, 302), "0");
            SetWindowText(GetDlgItem(hWnd, 303), "0");
            SetWindowText(GetDlgItem(hWnd, 304), "0");
            SetWindowText(GetDlgItem(hWnd, 305), "0");
            SetWindowText(GetDlgItem(hWnd, 306), "0");
            SetWindowText(GetDlgItem(hWnd, 307), "0");
            SetWindowText(GetDlgItem(hWnd, 308), "0");
            SetWindowText(GetDlgItem(hWnd, 309), "0");
            SetWindowText(GetDlgItem(hWnd, 310), "0");
            SetWindowText(GetDlgItem(hWnd, 311), "0");
            SetWindowText(GetDlgItem(hWnd, 312), "0");
        }
        if (id == 503 && code == BN_CLICKED)
        {
            if (SendMessage(GetDlgItem(hWnd, IDC_RADIO1), BM_GETCHECK, 0, 0) == BST_CHECKED)
                id_idc_radio = 1;
            else if (SendMessage(GetDlgItem(hWnd, IDC_RADIO2), BM_GETCHECK, 0, 0) == BST_CHECKED)
                id_idc_radio = 2;
            if (SendMessage(GetDlgItem(hWnd, IDC_RADIO3), BM_GETCHECK, 0, 0) == BST_CHECKED)
                id_idc_radio = 3;
            printf("1: %d", id_idc_radio);
            save_the_calculation_results(id_idc_radio,u2, f, i_n, du, &u_max, &u_sr, &r_n,
                                         &p_tip, &u_obr, &c_f, &u_c, &i2, &i_max);
        }
        ///////////////////////////////////////////

        if (code == BN_CLICKED)
        {
            switch (id)
            {
            case IDC_RADIO1:
                SetBitmapToStatic(hWnd, IDB_BITMAP1);
                SetWindowPos(hBmp, NULL, 10, 10, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                // НОВОЕ положение: x=10, y=200
                SetWindowPos(hGroupBox2, NULL, 10, 200, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hLText1, NULL, 18, 227, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hLText2, NULL, 18, 257, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hLText3, NULL, 18, 287, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hLText4, NULL, 18, 317, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hNumberEdit1, NULL, 295, 225, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hNumberEdit2, NULL, 295, 255, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hNumberEdit3, NULL, 295, 285, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hNumberEdit4, NULL, 295, 315, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

                SetWindowPos(hBtnSaveResults, NULL, 10, 360, 356, 65,
                             SWP_NOZORDER | SWP_NOACTIVATE);

                RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE); // Обновляем все окно
                break;
            case IDC_RADIO2:
                SetBitmapToStatic(hWnd, IDB_BITMAP2);
                SetWindowPos(hBmp, NULL, 10, 10, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hGroupBox2, NULL, 10, 230, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hLText1, NULL, 18, 257, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hLText2, NULL, 18, 287, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hLText3, NULL, 18, 317, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hLText4, NULL, 18, 347, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hNumberEdit1, NULL, 295, 255, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hNumberEdit2, NULL, 295, 285, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hNumberEdit3, NULL, 295, 315, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hNumberEdit4, NULL, 295, 345, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

                SetWindowPos(hBtnSaveResults, NULL, 10, 390, 356, 35,
                             SWP_NOZORDER | SWP_NOACTIVATE);

                RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
                break;
            case IDC_RADIO3:
                SetBitmapToStatic(hWnd, IDB_BITMAP3);
                SetWindowPos(hBmp, NULL, 20, 20, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hLText1, NULL, 18, 227, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hLText2, NULL, 18, 257, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hLText3, NULL, 18, 287, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hLText4, NULL, 18, 317, 0, 0,
                        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hGroupBox2, NULL, 10, 200, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hNumberEdit1, NULL, 295, 225, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hNumberEdit2, NULL, 295, 255, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hNumberEdit3, NULL, 295, 285, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
                SetWindowPos(hNumberEdit4, NULL, 295, 315, 0, 0,
                            SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);

                SetWindowPos(hBtnSaveResults, NULL, 10, 360, 356, 65,
                             SWP_NOZORDER | SWP_NOACTIVATE);

                RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
                break;
            }
        }

        // Меню из resources.rc
        if (id == ID_MENUITEM40001) {
            DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, DialogProc);
            return 0;
        }
        if (id == ID_MENUITEM40002) {
            ShellExecuteA(NULL, "open", "Single_phase_rectifiers.chm", NULL, NULL, SW_SHOWNORMAL);
            return 0;
        }

        if (id == IDCANCEL) {
            DestroyWindow(hWnd);
            return 0;
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        return 0;
    }

    case WM_CLOSE:
        DestroyWindow(hWnd);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

    HFONT hInterFontDlg1 = CreateInterFont(hDlg, -20, TRUE);
    HFONT hInterFontDlg2 = CreateInterFont(hDlg, -12, FALSE);
    HFONT hInterFontDlg3 = CreateInterFont(hDlg, -12, FALSE);
    HFONT hInterFontDlg4 = CreateInterFont(hDlg, -12, FALSE);
    HFONT hInterFontDlg5 = CreateInterFont(hDlg, -12, FALSE);
    HFONT hInterFontDlg6 = CreateInterFont(hDlg, -12, FALSE);

    static HWND hStatic1;
    static HWND hStatic2;
    static HWND hStatic3;
    static HWND hStatic4;
    static HWND hStatic5;
    static HWND hStatic6;

    char aut[50];
    char lic[90];
    char re[300];

    int i, j, k;

    for(i = 0; enc_aut[i] != 0 && i < 49; i++) {
        aut[i] = enc_aut[i] ^ 0x5A;
    }

    for(j = 0; enc_lic[j] != 0 && j < 90; j++) {
        lic[j] = enc_lic[j] ^ 0x5A;
    }

    for(k = 0; enc_re[k] != 0 && k < 90; k++) {
        re[k] = enc_re[k] ^ 0x5A;
    }

    aut[i] = 0;
    lic[j] = 0;
    re[k] = 0;

    switch (message) {
        case WM_INITDIALOG:{

            hStatic1 = GetDlgItem(hDlg, IDC_STATIC15);
            hStatic2 = GetDlgItem(hDlg, IDC_STATIC16);
            hStatic3 = GetDlgItem(hDlg, IDC_STATIC17);
            hStatic4 = GetDlgItem(hDlg, IDC_STATIC18);
            hStatic5 = GetDlgItem(hDlg, IDC_STATIC19);
            hStatic6 = GetDlgItem(hDlg, IDC_STATIC20);

            SendMessage(hStatic1, WM_SETFONT, (WPARAM)hInterFontDlg1, TRUE);
            SendMessage(hStatic2, WM_SETFONT, (WPARAM)hInterFontDlg2, TRUE);
            SendMessage(hStatic3, WM_SETFONT, (WPARAM)hInterFontDlg3, TRUE);
            SendMessage(hStatic4, WM_SETFONT, (WPARAM)hInterFontDlg4, TRUE);
            SendMessage(hStatic5, WM_SETFONT, (WPARAM)hInterFontDlg5, TRUE);
            SendMessage(hStatic6, WM_SETFONT, (WPARAM)hInterFontDlg6, TRUE);

            SetDlgItemTextA(hDlg, IDC_STATIC19, aut);
            SetDlgItemTextA(hDlg, IDC_STATIC17, lic);
            SetDlgItemTextA(hDlg, IDC_STATIC20, re);

            return TRUE;}
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case IDOK:
                    DeleteObject(hInterFontDlg1);
                    DeleteObject(hInterFontDlg2);
                    DeleteObject(hInterFontDlg3);
                    DeleteObject(hInterFontDlg4);
                    DeleteObject(hInterFontDlg5);
                    DeleteObject(hInterFontDlg6);
                    EndDialog(hDlg, IDOK);
                    return TRUE;
            }
            break;
        case WM_CLOSE:
            DeleteObject(hInterFontDlg1);
            DeleteObject(hInterFontDlg2);
            DeleteObject(hInterFontDlg3);
            DeleteObject(hInterFontDlg4);
            DeleteObject(hInterFontDlg5);
            DeleteObject(hInterFontDlg6);
            EndDialog(hDlg, IDOK);
            return TRUE;
    }
    return FALSE;
}
