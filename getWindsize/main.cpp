#include "wtypes.h"
#include <windows.h>
#include<string>
#include <iostream>
using namespace std;

//參考
//https://stackoverflow.com/questions/22259936/c-move-mouse-in-windows-using-setcursorpos
//https://stackoverflow.com/questions/14989062/set-a-window-to-be-topmost
// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowtexta

// Created by Zodiac
// Discord: Hippo#6524

DWORD ProcessID = NULL;
bool keypress;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


string GetActiveWindowTitle()
{
	char wnd_title[256];
	HWND hwnd = GetForegroundWindow(); // get handle of currently active window
	GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
	

	if (wnd_title[256] == NULL)
	{
		wnd_title == "Desktop";
	}

	return wnd_title;
}

DWORD GetPID()
{
	HWND hwnd = FindWindowA(0, GetActiveWindowTitle().c_str()); // GET the current window title
	
	if (GetWindowThreadProcessId(hwnd, &ProcessID) != NULL) // using current window therefore we can get each process pid 
	{
		
		return ProcessID;
	}
	else
	{
		system("cls");
		SetConsoleTextAttribute(hConsole, 91);
		std::cout << "Can't get ProcessID!";
		return -1; // return error
		std::cout << "Exit in 1 second";
		Sleep(1000);
		exit(-1); // Error exit
		
	}
}

void GetAccess()
{
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetPID());

	if (GetPID() == NULL || GetPID() == -1)
	{
		system("cls");
		SetConsoleTextAttribute(hConsole, 91);
		std::cout<<"Cannot obtain process!------> Access Denied !" << std::endl;
		std::cout << "EXE will be auto terminate in 1 second!" << std::endl;
		Sleep(1000);
		exit(-1);
	}
	else
	{
		std::cout << "Current Access state (R/W): Success" << std::endl;
		
	}

}

// Get the horizontal and vertical screen sizes in pixel
void GetDesktopResolution(int& horizontal, int& vertical)
{
	//RECT 存储一个矩形框的左上角坐标、宽度和高度
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
	
}

void GetCurrentWZ(int& width, int& height)
{
	RECT rect;
	HWND window = FindWindow(NULL, GetActiveWindowTitle().c_str());
	if (GetWindowRect(window, &rect))
	{
		 width = rect.right - rect.left;
		 height = rect.bottom - rect.top;
	}
}

std::string Randomtitle(const size_t length)
{
	std::string r;
	static const char bet[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890" };
	srand((unsigned)time(NULL) * 5);
	for (int i = 0; i < length; ++i)
	{
		r += bet[rand() % (sizeof(bet) - 1)];
	}
	return r;
}



int main()
{
	SetConsoleTitle(Randomtitle(26).c_str());

	// init var
	int horizontal = 0;
	int vertical = 0;
	int width = 0;
	int height = 0;

	HWND window = FindWindow(NULL, GetActiveWindowTitle().c_str());

	while (true)
	{
		if (window)
		{
			system("cls");
			GetDesktopResolution(horizontal, vertical);
			GetCurrentWZ(width, height);
			SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); // set the exe to top most ,so it wouldn't disappear when you click on other window


		
			std::cout << "Current Tab Name: " << GetActiveWindowTitle() << std::endl;
			std::cout << "Current Process ID: " << GetPID() << std::endl;
			std::cout << "Current Tab Resolution: " << width << " x " << height << std::endl;
			std::cout << "Current Full Screen Resolution: " << horizontal << " x " << vertical << std::endl;
			
			GetAccess();
			Sleep(2000);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 91);
			system("cls");
			std::cout << "Error! can't find any window" << std::endl;
			Sleep(1500);
			system("cls");
			std::cout <<  "Program terminated in 1 second!" << std::endl;
			Sleep(1000);
			exit(-1);
		}
	}

	return 0;
}

