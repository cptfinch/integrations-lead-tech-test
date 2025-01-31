// WindowsAPIProject.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsAPIProject.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <ShlObj.h>
#include <fstream>

#define MAX_LOADSTRING 100
#define MIN_WINDOW_WIDTH 200;
#define MIN_WINDOW_HEIGHT 150;

// Global Variables:
HINSTANCE hInst;                                  // current instance
WCHAR szTitle[ MAX_LOADSTRING ];                  // The title bar text
WCHAR szWindowClass[ MAX_LOADSTRING ];            // the main window class name


// Forward declarations of functions:
ATOM                MyRegisterClass( HINSTANCE hInstance );
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, int xPos, int yPos, int width, int height);
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
INT_PTR CALLBACK    About( HWND, UINT, WPARAM, LPARAM );

int APIENTRY wWinMain( _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow )
{
    std::shared_ptr<spdlog::logger> logger;
    PWSTR ppszPath;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &ppszPath))) {

        std::wstring wpath(ppszPath);
        CoTaskMemFree(ppszPath);  // Free the memory for the path
        wpath += L"\\WindowsAPIProject\\logs\\application.log";

        // Create directories if they don't exist
        CreateDirectoryW((wpath.substr(0, wpath.find_last_of(L'\\'))).c_str(), NULL);

        // Convert wide string to standard string
        std::string path(wpath.begin(), wpath.end());

        logger = spdlog::basic_logger_mt("basic_logger", path);
        logger->info("Logging setup complete.");
        
    }
    else {
        // Handle error by using a default logging path in the same directory as the executable
        logger = spdlog::basic_logger_mt("basic_logger", "application.log");
        logger->warn("Using default logging path due to error in retrieving AppData path.");

    }

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
	LoadStringW( hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING );
	LoadStringW( hInstance, IDC_WINDOWSAPIPROJECT, szWindowClass, MAX_LOADSTRING );
	MyRegisterClass( hInstance );

    // Read or create configuration file config.ini
    std::ifstream infile("config.ini");
    int windowWidth = 800;  // You can set default values
    int windowHeight = 600;
    int xPos = CW_USEDEFAULT;
    int yPos = CW_USEDEFAULT;

    if (infile.is_open()) {
        infile >> windowWidth >> windowHeight >> xPos >> yPos;
        infile.close();
    }
    else {
        std::ofstream outfile("config.ini");
        outfile << windowWidth << " " << windowHeight << " " << xPos << " " << yPos;
        outfile.close();
    }

    // Perform application initialization:
 	if ( !InitInstance(hInstance, nCmdShow, xPos, yPos, windowWidth, windowHeight ) )
    {
        logger->error("Application initialization failed.");
        return FALSE;
    }
    logger->info("Application initialization succeeded.");

	HACCEL hAccelTable = LoadAccelerators( hInstance, MAKEINTRESOURCE( IDC_WINDOWSAPIPROJECT ) );

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
		if ( !TranslateAccelerator( msg.hwnd, hAccelTable, &msg ) )
        {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
        }
    }

    logger->info("Application exited.");

    return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass( HINSTANCE hInstance )
{
    WNDCLASSEXW wcex;

	wcex.cbSize = sizeof( WNDCLASSEX );

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_WINDOWSAPIPROJECT ) );
	wcex.hCursor = LoadCursor( nullptr, IDC_ARROW );
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW( IDC_WINDOWSAPIPROJECT );
    wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon( wcex.hInstance, MAKEINTRESOURCE( IDI_SMALL ) );

    auto logger = spdlog::get("basic_logger");
    logger->info("Window class registered.");

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, int xPos, int yPos, int width, int height )
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW( szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,xPos, yPos, width, height, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        DWORD dwError = GetLastError();
        auto logger = spdlog::get("basic_logger");
        logger->error("Window creation failed. Error code: {}", dwError);
        return FALSE;
    }


//    if ( !hWnd )
//    {
//        auto logger = spdlog::get("basic_logger");
//        logger->error("Window creation failed.");
//        return FALSE;
//    }

    auto logger = spdlog::get("basic_logger");
    logger->info("Window created successfully.");

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    auto logger = spdlog::get("basic_logger");

    switch (message)
    {
    // Stop screen moving off screen
    case WM_WINDOWPOSCHANGING:
    {
        WINDOWPOS* pos = (WINDOWPOS*)lParam;

        // Get the screen dimensions
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);

        // Ensure the window stays within the screen bounds
        if (pos->x < 0) pos->x = 0;
        if (pos->y < 0) pos->y = 0;

        // Get the window dimensions
        RECT rect;
        GetWindowRect(hWnd, &rect);
        int windowWidth = rect.right - rect.left;
        int windowHeight = rect.bottom - rect.top;

        // Ensure the window doesn't go off the right edge of the screen
        if (pos->x + windowWidth > screenWidth) pos->x = screenWidth - windowWidth;

        // Ensure the window doesn't go off the bottom edge of the screen
        if (pos->y + windowHeight > screenHeight) pos->y = screenHeight - windowHeight;

        return 0;
    }
    // enforce minimum window dimensions
    case WM_GETMINMAXINFO:
    {
        MINMAXINFO* lpMMI = (MINMAXINFO*)lParam;
        lpMMI->ptMinTrackSize.x = 200;  // Minimum width
        lpMMI->ptMinTrackSize.y = 150;  // Minimum height
        return 0;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD( wParam );
        logger->info("WM_COMMAND received with ID: {}", wmId);
        // Parse the menu selections:
        switch ( wmId )
        {
        case IDM_ABOUT:
            DialogBox( hInst, MAKEINTRESOURCE( IDD_ABOUTBOX ), hWnd, About );
            logger->info("About dialog displayed.");
            break;
        case IDM_EXIT:
            DestroyWindow( hWnd );
            logger->info("Exit command received.");
            break;
        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint( hWnd, &ps );
        logger->info("WM_PAINT received.");
        // Some drawing code that uses hdc here...
		EndPaint( hWnd, &ps );
        break;
    }
    case WM_DESTROY:
    {
        RECT rect;
        GetWindowRect(hWnd, &rect);
        std::ofstream outfile("config.ini");
        outfile << rect.right - rect.left << " " << rect.bottom - rect.top << " " << rect.left << " " << rect.top;
        outfile.close();
        PostQuitMessage(0);
        logger->info("WM_DESTROY received, posting quit message.");
        break;
    }
    default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	UNREFERENCED_PARAMETER( lParam );
	switch ( message )
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if ( LOWORD( wParam ) == IDOK || LOWORD( wParam ) == IDCANCEL )
		{
			EndDialog( hDlg, LOWORD( wParam ) );
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
