#include <windows.h>

HWND hButton;

void CenterButton(HWND hwnd)
{
    RECT rc;
    GetClientRect(hwnd, &rc);

    int buttonWidth = 120;
    int buttonHeight = 40;

    int x = (rc.right - buttonWidth) / 2;
    int y = (rc.bottom - buttonHeight) / 2;

    MoveWindow(hButton, x, y, buttonWidth, buttonHeight, TRUE);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg,
                            WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
            hButton = CreateWindow(
                "BUTTON",
                "AZ-5",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                0, 0, 120, 40,
                hwnd,
                (HMENU)1,
                ((LPCREATESTRUCT)lParam)->hInstance,
                NULL
            );

            CenterButton(hwnd);
            return 0;

        case WM_SIZE:
            CenterButton(hwnd);
            return 0;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1)
            {
                MessageBox(
                    hwnd,
                    "The reactor has exploded!",
                    "GAME OVER",
                    MB_OK
                );
            }
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nShowCmd)
{
    const char CLASS_NAME[] = "MyWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Average Reactor Game 1.0",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        NULL, NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
        return 0;

    ShowWindow(hwnd, nShowCmd);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}