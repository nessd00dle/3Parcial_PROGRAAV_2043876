#include "framework.h"
#include "WindowsProject3.h"
#include"targetver.h"
#include <fstream>
#include <CommDlg.h>
#include <cwchar>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <string>
using namespace std;

#define MAX_LOADSTRING 100

struct USUARIO {
    char usuaName[10];
    char contra[10];
    char ticket[10][160];

}usuario;

struct boletos {
    char nomevento[40];
    char claseevento[40];
    int precio;
    int mes;
    int dia;

}Boletos[10];

char Nomevento[40];
char Clasevento[40];
int Precio;
int Mes;
int Dia;

int index;
int rep = 0;


bool _login = true;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


INT_PTR CALLBACK sesion(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK eventos(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK venta(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK miscompras(HWND, UINT, WPARAM, LPARAM);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT3));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId){

            case EVENTOS:

                if (_login) {
                    DialogBox(hInst, MAKEINTRESOURCE(PT_EVENTOS), hWnd, eventos);
                }
                else
                {
                    MessageBox(0, "Debe conectarse primero", "ERROR",
                        MB_ICONEXCLAMATION + MB_OK);
                }
                break;

            case MISCOMPRAS:    
                DialogBox(hInst, MAKEINTRESOURCE(PT_MISCOMPRAS), hWnd, miscompras);
                break;

            case SESION:    
                DialogBox(hInst, MAKEINTRESOURCE(PT_INICIOSESION), hWnd, sesion);
                break;  

            case IDM_EXIT:
                 MessageBox(0, "ADIOoOS", "BYE",
                    MB_ICONEXCLAMATION + MB_OK);
                DestroyWindow(hWnd);
                 
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK sesion(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

    HWND hnomb = GetDlgItem(hDlg, NOMBRE_PTIC);
    HWND hcontra = GetDlgItem(hDlg, CONTRASENA_PTIC);
    
    HWND hconfirm = GetDlgItem(hDlg, BTN_INGRESAR_PTIC);

    UNREFERENCED_PARAMETER(lParam);
    switch (message) {

    case WM_INITDIALOG:
        

    case WM_COMMAND: {

        if (LOWORD(wParam) == BTN_INGRESAR_PTIC) {
            char nombre[10];
            char contrasena[10];
            char telefono[10];

            int nlength = GetWindowTextLength(hnomb);
            GetWindowText(hnomb, nombre, nlength + 1);

            int clength = GetWindowTextLength(hcontra);
            GetWindowText(hcontra, contrasena, clength + 1);

            
           
            strcpy(usuario.usuaName, nombre);
            strcpy(usuario.contra, contrasena);
            

            MessageBox(NULL, "Ha ingresado al sistema","si", MB_OK);
            EndDialog(hDlg, LOWORD(wParam));

        }

        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));

        }

    }

    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK eventos(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    if (LOWORD(wParam) == LIST_EVENTOS && HIWORD(wParam) == LBN_SELCHANGE) {
        int index = SendDlgItemMessage(hDlg, LIST_EVENTOS, LB_GETCURSEL, 0, 0);
        if (index != LB_ERR) {
            SetDlgItemText(hDlg, NOMBRE_PTE, Boletos[index].nomevento);
            SetDlgItemText(hDlg, TIPOEVENTO_PTE,Boletos [index].claseevento);

            char precioStr[10];
            sprintf(precioStr, "%d", Boletos[index].precio);
            SetDlgItemText(hDlg, PRECIO_PTE, precioStr);

            char diaStr[3];
            sprintf(diaStr, "%d", Boletos[index].dia);
            SetDlgItemText(hDlg, DIA_PTE, diaStr);


            strcpy(Nomevento, Boletos[index].claseevento);
            Precio = Boletos[index].precio;
            Mes = Boletos[index].mes;
            Dia = Boletos[index].dia;

            
        }
    }

    strcpy(Boletos[0].nomevento, "Blackpink:Born Pink");
    strcpy(Boletos[0].claseevento, "Concierto");
    Boletos[0].precio = 8000;
    Boletos[0].mes = 11;
    Boletos[0].dia = 27;

    strcpy(Boletos[1].nomevento, "Twice:Ready To BE");
    strcpy(Boletos[1].claseevento, "Concierto");
    Boletos[1].precio = 4750;
    Boletos[1].mes = 11;
    Boletos[1].dia = 30;

    strcpy(Boletos[2].nomevento, "El Cascanueces");
    strcpy(Boletos[2].claseevento, "Obra de teatro");
    Boletos[2].precio = 1500;
   Boletos[2].mes = 11;
   Boletos[2].dia = 31;

    strcpy(Boletos[3].nomevento, "Había una vez en diciembre");
    strcpy(Boletos[3].claseevento, "Sinfonica");
    Boletos[3].precio = 800;
    Boletos[3].mes = 12;
    Boletos[3].dia = 1;

    strcpy(Boletos[4].nomevento, "Economía y Negocios:Mexico");
    strcpy(Boletos[4].claseevento, "Conferencia");
    Boletos[4].precio = 160;
    Boletos[4].mes = 12;
    Boletos[4].dia = 2;

    strcpy(Boletos[5].nomevento, "La casa de Óscar Burgos");
    strcpy(Boletos[5].claseevento, "Stand UP");
    Boletos[5].precio = 650;
    Boletos[5].mes = 12;
    Boletos[5].dia = 10;

    strcpy(Boletos[6].nomevento, "Monterrey Flash Vs. Empire Strykers");
    strcpy(Boletos[6].claseevento, "Deportes");
    Boletos[6].precio = 1400;
    Boletos[6].mes = 12;
    Boletos[6].dia = 13;

    strcpy(Boletos[7].nomevento, "Circo ATAYDE");
    strcpy(Boletos[7].claseevento, "Entretenimiento");
    Boletos[7].precio = 630;
    Boletos[7].mes = 12;
    Boletos[7].dia = 22;

    strcpy(Boletos[8].nomevento, "Star Wars:sinfonico");
    strcpy(Boletos[8].claseevento, "Sinfonica");
    Boletos[8].precio = 1000;
    Boletos[8].mes = 12;
    Boletos[8].dia = 24;

    strcpy(Boletos[9].nomevento, "Woman Intelligence");
    strcpy(Boletos[9].claseevento, "Conferencia");
    Boletos[9].precio = 200;
   Boletos[9].mes = 12;
   Boletos[9].dia = 2;

    char NombresEv[10][40];

    for (int i = 0; i < 10; i++) {
        strcpy(NombresEv[i], Boletos[i].nomevento);
    }

    HWND hlist = GetDlgItem(hDlg, LIST_EVENTOS);
    HWND hnom = GetDlgItem(hDlg, NOMBRE_PTE);
    HWND htip = GetDlgItem(hDlg, TIPOEVENTO_PTE);
    HWND hprec = GetDlgItem(hDlg, PRECIO_PTE);
    HWND hmes = GetDlgItem(hDlg, MES_PTE);
    HWND hdia = GetDlgItem(hDlg, DIA_PTE);
    HWND hcomp = GetDlgItem(hDlg, COMPRAR_PTE);

    UNREFERENCED_PARAMETER(lParam);
    switch (message) {

    case WM_INITDIALOG:
        for (int i = 0; i < 10; i++) {
            SendDlgItemMessage(hDlg, LIST_EVENTOS, LB_ADDSTRING, NULL, (LPARAM)NombresEv[i]);
        }


    case WM_COMMAND: {
        if (LOWORD(wParam) == LIST_EVENTOS && HIWORD(wParam) == LBN_SELCHANGE) {
            int index = SendDlgItemMessage(hDlg, LIST_EVENTOS, LB_GETCURSEL, NULL, NULL);
            if (index != LB_ERR) {
                char nombreSeleccionado[40];
                SendDlgItemMessage(hDlg, LIST_EVENTOS, LB_GETTEXT, index, (LPARAM)nombreSeleccionado);
                SetDlgItemText(hDlg, NOMBRE_PTE, nombreSeleccionado);

                int i = 0;
                while (strcmp(Boletos[i].nomevento, nombreSeleccionado) != 0) {
                    i++;
                }

                SetDlgItemText(hDlg, TIPOEVENTO_PTE, Boletos[i].claseevento);

                switch (Boletos[i].mes) {
                case 1:
                    SetDlgItemText(hDlg, MES_PTE, "Enero");
                    break;

                case 2:
                    SetDlgItemText(hDlg, MES_PTE, "Febrero");
                    break;

                case 3:
                    SetDlgItemText(hDlg, MES_PTE, "Marzo ");
                    break;

                case 4:
                    SetDlgItemText(hDlg, MES_PTE, "Abril ");
                    break;

                case 5:
                    SetDlgItemText(hDlg, MES_PTE, "Mayo ");
                    break;

                case 6:
                    SetDlgItemText(hDlg, MES_PTE, "Junio ");
                    break;

                case 7:
                    SetDlgItemText(hDlg, MES_PTE, "Julio ");
                    break;

                case 8:
                    SetDlgItemText(hDlg, MES_PTE, "Agosto ");
                    break;

                case 9:
                    SetDlgItemText(hDlg, MES_PTE, "Septiembre ");
                    break;

                case 10:
                    SetDlgItemText(hDlg, MES_PTE, "Octubre ");
                    break;

                case 11:
                    SetDlgItemText(hDlg, MES_PTE, "Noviembre ");
                    break;

                case 12:
                    SetDlgItemText(hDlg, MES_PTE, "Diciembre ");
                    break;

                }
                strcpy(Nomevento, nombreSeleccionado);

            }
        }

        if (LOWORD(wParam) == COMPRAR_PTE) {
            if (SendDlgItemMessage(hDlg, LIST_EVENTOS, LB_GETCURSEL, NULL, NULL) == -1) {
                MessageBox(hDlg, " ningun evento seleccionado", "Error", MB_OK);
            }
            else {
                DialogBox(hInst, MAKEINTRESOURCE(PT_VENTA), hDlg, venta);
            }
        }

        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
        }

    }

    }
    return (INT_PTR)FALSE;

}

INT_PTR CALLBACK venta(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    
    HWND hcant = GetDlgItem(hDlg, CANTIDAD_PTVB);
    HWND hconf = GetDlgItem(hDlg, CONFIRMACION_PTVB);
    HWND hprom = GetDlgItem(hDlg, PROMOCIONES_PTVB);


    UNREFERENCED_PARAMETER(lParam);
    switch (message) {

    case WM_INITDIALOG: {
        HWND hpromo = GetDlgItem(hDlg, PROMOCIONES_PTVB);
        SendMessage(hpromo, CB_ADDSTRING, 0, (LPARAM)"Sin promoción");
        SendMessage(hpromo, CB_ADDSTRING, 0, (LPARAM)"10% de descuento");
        SendMessage(hpromo, CB_ADDSTRING, 0, (LPARAM)"2 x 1");
        

        SendMessage(hpromo, CB_SETCURSEL, 0, 0);

        char precioAC[10];
        sprintf(precioAC, "%d", Precio);
        SetDlgItemText(hDlg, PRECIO_PTVB, precioAC);

        char diaAC[3];
        sprintf(diaAC, "%d", Dia);
        SetDlgItemText(hDlg, DIA_PTVB, diaAC);

        SetDlgItemText(hDlg, EVENTO_PTVB, Nomevento);
        SetDlgItemText(hDlg, TIPOEVENTO_PTVB, Clasevento);

        switch (Mes) {
        case 1:
            SetDlgItemText(hDlg, MES_PTVB, "Enero");
            break;

        case 2:
            SetDlgItemText(hDlg, MES_PTVB, "Febrero");
            break;

        case 3:
            SetDlgItemText(hDlg, MES_PTVB, "Marzo ");
            break;

        case 4:
            SetDlgItemText(hDlg, MES_PTVB, "Abril ");
            break;

        case 5:
            SetDlgItemText(hDlg, MES_PTVB, "Mayo ");
            break;

        case 6:
            SetDlgItemText(hDlg, MES_PTVB, "Junio ");
            break;

        case 7:
            SetDlgItemText(hDlg, MES_PTVB, "Julio ");
            break;

        case 8:
            SetDlgItemText(hDlg, MES_PTVB, "Agosto ");
            break;

        case 9:
            SetDlgItemText(hDlg, MES_PTVB, "Septiembre ");
            break;

        case 10:
            SetDlgItemText(hDlg, MES_PTVB, "Octubre ");
            break;

        case 11:
            SetDlgItemText(hDlg, MES_PTVB, "Noviembre ");
            break;

        case 12:
            SetDlgItemText(hDlg, MES_PTVB, "Diciembre ");
            break;

        }

    }

    case WM_COMMAND: {

        if (LOWORD(wParam) == CONFIRMACION_PTVB) {
            char Tcant[3];
            int itxtlength = GetWindowTextLength(hcant);
            GetWindowText(hcant, Tcant, itxtlength + 1);

            int cantAC = atoi(Tcant);
            
            int monto = 0;
            int MONTO = 0;
            int iva = 0;
            float Miva = 0;
            
            int d10 = 0;
            int d2x1 = 0;

            char prom[20];
            int promlength = GetWindowTextLength(hprom);
            GetWindowText(hprom, prom, promlength + 1);
            
            if (strcmp(prom, "10% de descuento") == 0) {
                monto = cantAC * Precio;
                iva = monto * 0.16;
                Miva = monto * 1.16;
                MONTO = Miva * 0.90;
                d10 = 1;
            }
            else if (strcmp(prom, "2 x 1") == 0 and cantAC % 2 == 0 and cantAC >= 2) {
                monto = cantAC * Precio;
                iva = monto * 0.16;
                Miva = monto * 1.16;
                MONTO = Miva * 0.5;
                d2x1 = 1;

            }
            else if (strcmp(prom, "Sin promoción") == 0) {
                monto = cantAC * Precio;
                iva = monto * 0.16;
                Miva = monto * 1.16;
                MONTO = Miva;
            }
           
            char Liva[5];
            sprintf(Liva, "%d", iva);

            char Lprec[5];
            sprintf(Lprec, "%d", Precio);

            char Lmonto[5];
            sprintf(Lmonto, "%d", monto);

            char MONTOI[10];
            sprintf(MONTOI, "%d", MONTO);

            strcpy(usuario.ticket[rep], Nomevento);
            strcat(usuario.ticket[rep], " *** ");
            strcat(usuario.ticket[rep], Tcant);
            strcat(usuario.ticket[rep], " Boletos ingresados ***");
            strcat(usuario.ticket[rep], " Precio Unitario: $");
            strcat(usuario.ticket[rep], Lprec);
            strcat(usuario.ticket[rep], " *** IVA: $");
            strcat(usuario.ticket[rep], Liva);
            strcat(usuario.ticket[rep], "***Monto sin impuesto: $");
            strcat(usuario.ticket[rep], Lmonto);
            strcat(usuario.ticket[rep], " ** Total: $");
            strcat(usuario.ticket[rep], MONTOI);

            if (d10 == 1) {
                strcat(usuario.ticket[rep], " *** descuento 10%");
            }

            if (d2x1 == 1) {
                strcat(usuario.ticket[rep], " ***Promocion 2x1");
            }

            rep++;
            MessageBox(hDlg, "Gracias por su compra,verifiqué en la  pestaña Lista de  Compras", "Compra Realizada", MB_OK);
            EndDialog(hDlg, LOWORD(wParam));

        }

        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));

        }
        
    }

    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK miscompras(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

    HWND hlcompras = GetDlgItem(hDlg, MIS_COMPRAS);

    UNREFERENCED_PARAMETER(lParam);
    switch (message) {

    case WM_INITDIALOG:
        for (int i = 0; i < 10; i++) {
            SendDlgItemMessage(hDlg, MIS_COMPRAS, LB_ADDSTRING, NULL, (LPARAM)usuario.ticket[i]);
        }



    case WM_COMMAND: {
        if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            
        }

    }

    }
    return (INT_PTR)FALSE;
}

