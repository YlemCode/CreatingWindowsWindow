#include <windows.h>
#define DEBUG

#ifdef DEBUG
    #include <stdio.h>
#else
    #define printf(...)
#endif// DEBUG


//The entry point doesn't need to be WinMain, however if WinMain isn't used you need to get the ARGs manually this is how.
int main(int argc, char* argv[]) {
    return WinMain(

        //Gives the handle to the current program.
        GetModuleHandle(NULL),  

        //Legacy feature that is no longer used (is always null).
        NULL,                   

        //Gets any command line ARGs passed when the program is run (is a char[] needs to be parsed).
        GetCommandLine(),       

        //The paramater for how the window should start (minimized maximized... used in ShowWindow(hwnd, nCmdShow).
        SW_SHOWDEFAULT);        
}

//Used as the handler to any messages that get sent to a window (mouse events, keyboard event, resize, window close, etc.)
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

/*WinMain isn't needed if the code entry point is something else but requires manual retrival of the hInstance
and optional retrival of lpCmdLine*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

   

    /* Define window class
    Options:
        WNDCLASSEX
            Extra values:
            cbSize  (required)
            hCursor (required)
            hIconSm
            
            Details:
            Has cbSize for future proffing.
            Can change the cursor look when over this window.
            Control over different sized icons (for presentation) (hIcon, hIconSm).

            Doesn't support Windows 3.1/3.0 or NT 3.x

        WNDCLASS
            Better for backwards compatability.
            Supports Windows 3.1/3.0 or NT 3.x

            lpfnWndProc     (required)
            hInstance       (required)
            hbrBackground   (required)
            lpszClassName   (required)
    */
    const char CLASS_NAME[] = "ClassName";      //Doesn't really matter what this is as long as it is consistent.
    const wchar_t WINDOW_TITLE[] = L"Title";    //Has to be wide character in order to display properly

    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProcedure;                   //What function will proccess the windows messages.
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);      //Supposed to use +1 to distinguish themes from a real brush
    wc.lpszClassName = CLASS_NAME;



    /* Register the window class and exits if fails.
        Could fail because:
            CLASS_NAME already registered
            out of memory

    */
    if (!RegisterClassEx(&wc)) {
        return 0;
    }

    /*Create Window
        All windows can have the extention A or W (CreateWindowA,CreateWindowW,CreateWindowExA...)
        for ANSCII or WIDE should use Wide to support UNICODE or use default.

        CreateWindowEx
            Supports WS_EX styles (More customizable)
            Future Support

        CreateWindow
            Used when using WNDCLASS
            
    */

    //returns the handle to the created window.
    HWND hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,                       // Extended window style use bitwise or to combine different styles or use 0 for no style
        CLASS_NAME,                             // Must be the same class name stored in lpszClassName Window Class structure
        WINDOW_TITLE,                           // Text that will apear as the window name.
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,       // Window style use bitwise or to combine different styles or use 0 for no style
        0, 0,                                   // Window position (x,y) (0,0) being top left.
        800, 600,                               // Window size (Width, Height) can be negative but why
        NULL, NULL,                             // Parent window, Menu I have not found a use for them
        hInstance,                              // Must be the same instance stored in hInstance Window Class structure
        NULL                                    // Additional parameters will be sent as lpParam to the WindowProcedure when program starts and the system sends WM_CREATE msg
    );

    /* Create the Window and exits if fails.
    Could fail because:
        non matching class or instance
        out of memory
    */
    if (hwnd == NULL) {
        return 0;
    }

    MSG msg = { 0 };
    /*Msg handling
        
    */
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);     /*Not needed but queues the WM_CHAR msg apon reciving the WN_KEYDOWN msg (will receive both msgs)
                                        WM_CHAR puts the actual character in the wParam field for ease of use.*/
        DispatchMessage(&msg);      /*Sends the msg to be proccessed*/
    }

    return 0;
}





