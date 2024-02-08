#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define SOLV_ST 5
#define NEW_ST 6
#define BACK_ST 7
#define MENU_PROG 10
#define HELP_NON 11
#define EXIT_PROG 12
#define IESIRE_BUTT 16
#define CAT_BUT 20
#define START_BUT 100
#define LOAD_BUT 101





LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);
void textBox(HWND hwnd);

HMENU hMenu;
HWND textMenu, button, button2, button3, platforma, textP, solve, newG, bacK, ajut, cat_pisi, POza;
HWND boxy[9][9];
int y = 800;
int x = 1000;
HBITMAP help_butt[4], titlu, start, help, exit_1, icon, pisi,Poza_psiu[17],txt0;
int ct=0;

void AddMenus(HWND);
void emptybox(HWND hwnd);
int Solve(HWND hwnd);
void print(int arr[9][9]);
void loadImage();

void pisica(HWND hwnd){
    int random;
    srand(time(0));
    random = (rand() % 16 +1);
            POza = CreateWindow("STATIC" ,NULL ,WS_VISIBLE | WS_CHILD | WS_POPUPWINDOW | SS_BITMAP , 450, 100, 600, 600 ,hwnd,NULL,NULL,NULL);
            SendMessageW(POza, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)Poza_psiu[random]);
        ShowWindow(POza, SW_SHOW);
        Sleep(2500);
        ShowWindow(POza,SW_HIDE);


}


int grid[9][9]={0};

bool check(int grid[9][9]){
    for (int i=0; i<9; i++){
        for(int j=0; j<8; j++){
            for(int k=j+1; k<9; k++){
                if(grid[i][j] == grid[i][k] && grid[i][k] != 0)
                    return false;
                if(grid[j][i] == grid[k][i] && grid[k][i] != 0)
                    return false;
            }
        }
    }



    for(int startVal=0; startVal<=6; startVal+=3)
    for(int startCol=0; startCol<=6; startCol+=3){
        int b=startVal;
        while(b<=startVal+2) {
            int m=startCol;
            while(m<=startCol+2){
                for(int i= startVal; i<=startVal+2; i++){
                    for(int j=startCol; j<=startCol+2; j++){
                        if(grid[b][m] == grid[i][j] && b!=i && m!=j && grid[b][m] != 0) return false;
                    }
                }
                m++;
            }
        b++;
        }


    }



    return true;
}

bool isSafe(int grid[9][9], int row, int col, int num){

    for (int i = 0; i <= 8; i++)
        if (grid[row][i] == num)
            return false;

    for (int i = 0; i <= 8; i++)
        if (grid[i][col] == num)
            return false;

    int startRow = row - row % 3,
            startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

bool solveSuduko(int grid[9][9], int row, int col)
{

    if (row == 9 - 1 && col == 9)
        return true;

    if (col == 9) {
        row++;
        col = 0;
    }


    if (grid[row][col] > 0)
        return solveSuduko(grid, row, col + 1);

    for (int num = 1; num <= 9; num++)
    {

        if (isSafe(grid, row, col, num))
        {
            grid[row][col] = num;

            if (solveSuduko(grid, row, col + 1))
                return true;
        }

        grid[row][col] = 0;
    }
    return false;
}




int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount) {

    ///hide console

    ShowWindow(GetConsoleWindow(), SW_HIDE);


	/// register the window class

	const char* CLASS_NAME = "myWin32WindowClass";
	WNDCLASS wc = {0};
	wc.hInstance = currentInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
 	wc.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
	wc.lpfnWndProc = WindowProcessMessages;
	RegisterClass(&wc);

	///create aplication window

	CreateWindow(CLASS_NAME, "Sudoku Solver",
		WS_OVERLAPPED | WS_VISIBLE,             //bodystyle
		250, 15,                                //position
		 x, y,									//size
		NULL, NULL, NULL, NULL);

	///win loop

	MSG msg {};
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}
LRESULT WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {

	switch (msg)
	{

    case WM_COMMAND:

        switch(param){
        case FILE_MENU_EXIT:

            PostQuitMessage(0);
            break;
        case NEW_ST:
            emptybox(hwnd);
            break;

        case FILE_MENU_NEW:

            MessageBeep(MB_ICONINFORMATION);
            MessageBoxA(hwnd," Sudoku Solver\n Proiect Realizat de Damean Andrei", "About us",MB_OK);
            break;

        case MENU_PROG:

            ShowWindow(platforma,SW_HIDE);
            ShowWindow(textP, SW_HIDE);
            ShowWindow(solve, SW_HIDE);
            ShowWindow(newG, SW_HIDE);
            ShowWindow(bacK, SW_HIDE);
            ShowWindow(button, SW_SHOW);
            ShowWindow(button2, SW_SHOW);
            ShowWindow(button3, SW_SHOW);
            ShowWindow(textMenu, SW_SHOW);
            ct++;
            if(ct>=5)
                ShowWindow(cat_pisi, SW_SHOW);
            break;

        case HELP_NON:
            loadImage();
            ajut = CreateWindow("STATIC",NULL,WS_VISIBLE | WS_CHILD | WS_POPUPWINDOW | SS_BITMAP,400,80,650,650,hwnd,NULL,NULL,NULL);
            for(int i=1; i<=3; i++){
                SendMessageW(ajut,STM_SETIMAGE,IMAGE_BITMAP, (LPARAM)help_butt[i]);
            ShowWindow(ajut, SW_SHOW);
            Sleep(4000);
            }

            ShowWindow(ajut, SW_HIDE);

            break;

        case START_BUT:

            ShowWindow(button, SW_HIDE);
            ShowWindow(button2, SW_HIDE);
            ShowWindow(button3, SW_HIDE);
            ShowWindow(textMenu, SW_HIDE);
            platforma = CreateWindow("STATIC", NULL , WS_BORDER | WS_CHILD | WS_VISIBLE| SS_BITMAP, 175, 40, 650 ,690 ,hwnd ,NULL ,NULL , NULL);
            SendMessageW(platforma, STM_SETIMAGE, IMAGE_BITMAP,(LPARAM)txt0);
            textBox(hwnd);
            break;

        case SOLV_ST:

            Solve(hwnd);
            break;

        case CAT_BUT:

            pisica(hwnd);

            break;

        case IESIRE_BUTT:

            PostQuitMessage(0);
            return 0;
            break;

        default:

            MessageBeep(MB_ERR_INVALID_CHARS);

        }
        break;
    case WM_CREATE:
        loadImage();
        AddMenus(hwnd);
        break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, param, lparam);
	}

}

void AddMenus(HWND hwnd){

    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSub = CreateMenu();
    textMenu = CreateWindow("STATIC", nullptr,WS_VISIBLE | WS_CHILD  | SS_BITMAP,300,15,200,100,hwnd,nullptr,nullptr,nullptr);
        SendMessageW(textMenu,STM_SETIMAGE,IMAGE_BITMAP, (LPARAM)titlu);
    button = CreateWindow("BUTTON", nullptr, WS_VISIBLE | WS_CHILD | WS_BORDER | BS_BITMAP,
                          x/2-100, 240, 200, 80,
                          hwnd, (HMENU)START_BUT, nullptr, nullptr);
        SendMessageW(button,BM_SETIMAGE, IMAGE_BITMAP,(LPARAM)start);
    button2 = CreateWindow("BUTTON", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | BS_BITMAP,
                          x/2-100, 340, 200, 80,
                          hwnd, (HMENU)HELP_NON, NULL, NULL);
        SendMessageW(button2,BM_SETIMAGE, IMAGE_BITMAP,(LPARAM)help);
    button3 = CreateWindow("BUTTON", NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | BS_BITMAP,
                          x/2-100, 440, 200, 80,
                          hwnd, (HMENU)IESIRE_BUTT, NULL, NULL);
        SendMessageW(button3, BM_SETIMAGE, IMAGE_BITMAP,(LPARAM)exit_1);

    cat_pisi = CreateWindow("BUTTON", NULL, WS_VISIBLE | WS_CHILD | WS_OVERLAPPED | BS_BITMAP,
                          850, 652, 150, 100,
                          hwnd, (HMENU)CAT_BUT, NULL, NULL);
        SendMessageW(cat_pisi, BM_SETIMAGE, IMAGE_BITMAP,(LPARAM)pisi);
        ShowWindow(cat_pisi,SW_HIDE);

    AppendMenu(hMenu, MF_STRING, HELP_NON, "Help");
    AppendMenu(hMenu, MF_STRING, MENU_PROG, "Menu");
    AppendMenu(hMenu, MF_STRING, FILE_MENU_NEW, "Info");
    AppendMenu(hMenu, MF_SEPARATOR,NULL,NULL);
    AppendMenu(hMenu, MF_STRING, IESIRE_BUTT, "Exit");

    SetMenu(hwnd,hMenu);


}

void textBox(HWND hwnd){


    solve = CreateWindow("BUTTON", "Solve", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON
                         , 300, 650, 100, 40, hwnd,(HMENU)SOLV_ST ,NULL ,NULL);
    newG = CreateWindow("BUTTON", "New Grid", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHBUTTON
                        , 450, 650, 100, 40, hwnd, (HMENU)NEW_ST ,NULL, NULL);
    bacK = CreateWindow("BUTTON", "Back", WS_CHILD | WS_VISIBLE | WS_BORDER
                        , 600, 650, 100, 40, hwnd, (HMENU)MENU_PROG ,NULL, NULL);


    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            boxy[i][j] = CreateWindow("EDIT", "", WS_CHILD | WS_OVERLAPPED | WS_GROUP | WS_VISIBLE
                        | SS_CENTER | ES_NUMBER |ES_MULTILINE, 80+(55*j),100+(55*i),40,40,platforma,NULL,NULL,NULL);
            SendMessage(boxy[i][j],EM_LIMITTEXT,1,NULL);
        }
    }
}

void emptybox(HWND hwnd){
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			SendMessage(boxy[i][j],WM_SETTEXT,0,(LPARAM)L"");
		}
	}
}

int Solve(HWND hwnd){
    char temp[2];
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            GetWindowTextA(boxy[i][j],temp,2);
            if(strcmp(temp,"")) grid[i][j] = 0;
            grid[i][j]=atoi(temp);

        }
    }

    if(check(grid)){
        if (solveSuduko(grid,0,0))
            print(grid);

    }else MessageBoxW(hwnd,L"Eroare, verifica-ti numerele introduse",L"Warning",MB_ICONWARNING);

}

void print(int grid[9][9])
{
    char te[2];
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++){

            SendMessage(boxy[i][j],WM_SETTEXT,NULL,(LPARAM)itoa(grid[i][j],te,10));

        }

    }
}
void loadImage(){
    help_butt[1] = (HBITMAP)LoadImageW(NULL, L"D:\\info c\\fata_sudo\\buttons\\Capture.bmp",IMAGE_BITMAP,650,650,LR_LOADFROMFILE);
    help_butt[2] = (HBITMAP)LoadImageW(NULL, L"D:\\info c\\fata_sudo\\buttons\\Capture2.bmp",IMAGE_BITMAP,650,650,LR_LOADFROMFILE);
    help_butt[3] = (HBITMAP)LoadImageW(NULL, L"D:\\info c\\fata_sudo\\buttons\\Capture3.bmp",IMAGE_BITMAP,650,650,LR_LOADFROMFILE);
    titlu = (HBITMAP)LoadImageW(NULL, L"D:\\info c\\fata_sudo\\buttons\\titlu.bmp", IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
    start = (HBITMAP)LoadImageW(NULL, L"D:\\info c\\fata_sudo\\buttons\\start.bmp", IMAGE_BITMAP,200,80,LR_LOADFROMFILE);
    help = (HBITMAP)LoadImageW(NULL, L"D:\\info c\\fata_sudo\\buttons\\help.bmp", IMAGE_BITMAP,200,80,LR_LOADFROMFILE);
    exit_1 = (HBITMAP)LoadImageW(NULL, L"D:\\info c\\fata_sudo\\buttons\\exit.bmp", IMAGE_BITMAP,200,80,LR_LOADFROMFILE);
    icon = (HBITMAP)LoadImageW(NULL, L"D:\\info c\\fata_sudo\\buttons\\icon.bmp", IMAGE_BITMAP,200,200,LR_LOADFROMFILE);
    pisi = (HBITMAP)LoadImageW(NULL, L"D:\\info c\\fata_sudo\\buttons\\button.bmp", IMAGE_BITMAP,150,100,LR_LOADFROMFILE);
    Poza_psiu[1] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\1.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[2] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\2.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[3] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\3.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[4] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\4.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[5] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\5.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[6] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\6.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[7] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\7.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[8] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\8.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[9] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\9.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[10] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\10.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[11] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\11.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[12] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\12.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[13] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\13.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[14] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\14.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[15] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\15.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    Poza_psiu[16] = (HBITMAP)LoadImageW(NULL,L"D:\\info c\\fata_sudo\\buttons\\16.bmp", IMAGE_BITMAP,600,600,LR_LOADFROMFILE);
    txt0 = (HBITMAP)LoadImageW(NULL, L"D:\\info c\\fata_sudo\\buttons\\txt.bmp", IMAGE_BITMAP, 650, 690, LR_LOADFROMFILE);


}
