// Win32Project2.cpp : Define o ponto de entrada para a aplicação.
//

#include "stdafx.h"
#include "Win32Project2.h"
#include <windows.h>
#include <iostream>

#define MAX_LOADSTRING 100

// Variáveis Globais:
HWND janelaPrincipal;
HINSTANCE hInst;                                // instância atual
WCHAR szTitle[MAX_LOADSTRING];                  // O texto da barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // o nome da classe da janela principal
UINT_PTR TIMER_ELEVADOR;
HWND elevador_aux;


// Declarações de encaminhamento de funções incluídas nesse módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    DialogPrincipal(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Coloque código aqui.

    //Inicializar cadeias de caracteres globais
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realiza a inicialização da aplicação:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT2));

    MSG msg;

    // Loop da mensagem principal:
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



//
//  FUNÇÃO: MyRegisterClass()
//
//  PROPÓSITO: Registra a classe de janela.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNÇÃO: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Salva gerenciador de instância e cria janela principal
//
//   COMENTÁRIOS:
//
//        Nesta função, o gerenciador de instâncias é salvo em uma variável global e
//        a janela do programa principal é criada e apresentada.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Salvar gerenciador de instância na variável global

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNÇÃO: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO:  Processa as mensagens para a janela principal.
//
//  WM_COMMAND - processar o menu do aplicativo
//  WM_PAINT - Pintar a janela principal
//  WM_DESTROY - postar uma mensagem de saída e retornar
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId;
	PAINTSTRUCT ps;
	HDC hdc;
	janelaPrincipal = hWnd;

    switch (message)
    {

	case WM_CREATE:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOGPRINCIPAL), hWnd, DialogPrincipal);	//Cria uma DialogBox ao instanciar a aplicacao
		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Interpreta as seleções do menu:
            switch (wmId)
            {
            case IDM_SERIAL:

				
				//Enviar sempre 1 byte por vez, ´e mais seguro
				//ReadFile(handleFile, dataBuffer, bytesToRead, numberOfBytesRead, overlapped); //Le os bytes da com4
				//Para escrever pode enviar mais de 1 por vez
				//WriteFile(serialArduino, vetorArduino, 3, &nBytesEscritos, NULL); //Escreve os bytes na com4
				//CloseHandle(serialArduino);

				/*********/

                //DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
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
            // TODO: adicione qualquer código de desenho que use hdc aqui...
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

// Manipulador de mensagem para caixa 'Sobre'.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:

		if (HIWORD(wParam) == BN_CLICKED) {

			switch (LOWORD(wParam))
			{
			case (IDSOBE):
				OutputDebugStringW(L"Clicou no botao sobe...");
				break;
			}
		}
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//Verifica se o peso do elevador foi excedido
BOOL excedeuPesoMax(int pesoTotal, HWND hDlg) {

	bool excedeu = true;

	//Considerando peso maximo de 420 Kg
	if (pesoTotal >= 420) {
		excedeu = true;
		MessageBox(hDlg,
			L"Não foi possível adicionar passageiro\n Peso Máximo excedido!",
			L"Erro",
			MB_OK);
	}
	else {
		excedeu = false;
	}
	return excedeu;
}

//Seleciona a imagem do elevador conforme o num. de passageiros
HWND selecionaImgElevador(int passageiros, HWND hDlg) {
	
	HWND elevador;

	switch (passageiros) {

	case 1:
		elevador = GetDlgItem(hDlg, IDC_IMGELEVADOR1);
		break;
	case 2:
		elevador = GetDlgItem(hDlg, IDC_IMGELEVADOR2);
		elevador_aux = GetDlgItem(hDlg, IDC_IMGELEVADOR1);
		break;
	case 3:
		elevador = GetDlgItem(hDlg, IDC_IMGELEVADOR3);
		elevador_aux = GetDlgItem(hDlg, IDC_IMGELEVADOR2);
		break;

	case 4:
		elevador = GetDlgItem(hDlg, IDC_IMGELEVADOR4);
		elevador_aux = GetDlgItem(hDlg, IDC_IMGELEVADOR3);
		break;

	case 5:
		elevador = GetDlgItem(hDlg, IDC_IMGELEVADOR5);
		elevador_aux = GetDlgItem(hDlg, IDC_IMGELEVADOR4);
		break;

	case 6:
		elevador = GetDlgItem(hDlg, IDC_IMGELEVADOR6);
		elevador_aux = GetDlgItem(hDlg, IDC_IMGELEVADOR5);
		break;
	}

	return elevador;
}
//Funcao para ler os dados do Arduino
//Retorna um char de acordo ao comando enviado pela porta USB
char leDadosArduino(HWND hDlg) {

	char retorno = '0';
	HANDLE serialArduino;
	char dadosArduino[10];
	char dados[10];
	LPWSTR bytes;
	DWORD nBytesLidos;
	DWORD nBytesEscritos;

	serialArduino = CreateFile(L"COM9", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	OutputDebugStringW(L"Abrindo porta serial...");

	if (serialArduino == INVALID_HANDLE_VALUE) {
		MessageBox(hDlg,
			L"Erro ao abrir serial",
			L"Erro",
			MB_OK);

	}
	else {
		OutputDebugStringW(L"Porta aberta com sucesso!");


		ReadFile(serialArduino, dadosArduino, 1, &nBytesLidos, NULL);		//lendo 1 byte por vez
																				//ReadFile(serialArduino, dadosArduino, 1, &nBytesLidos, NULL);

		OutputDebugStringW(L"Lendo porta serial...");

		if (dadosArduino[0] == '2') {		//botao 'para cima' pressionado
			OutputDebugStringW(L"Leu A2");
			retorno = '2';
		}
		if (dadosArduino[0] == '1') {		//botao 'para baixo' pressionado
			OutputDebugStringW(L"Leu A1");
			retorno = '1';
		}
		if (dadosArduino[0] == '8') {		//botao de emergencia pressionado
			OutputDebugStringW(L"Leu A8");
			retorno = '8';
		}

		CloseHandle(serialArduino);
	}

	return retorno;
}


//Manipulador de eventos da DialogPrincipal
INT_PTR CALLBACK DialogPrincipal(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	//HANDLE serialArduino;
	static int posicaoY = 290; //200
	static int posicaoX = 490; //500
	static int pesoTotal = 0;	//Quantidade total de peso
	static int passTotal = 0;	//Quantidade total de passageiros
	static int andar = 1;		//Andar onde o elevador esta posicionado
	int peso = 0;
	HWND imgelevador;
	HWND elevador;
	HWND elevador1, elevador2, elevador3, elevador4, elevador5, elevador6;


	//UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{

	case WM_INITDIALOG:
		//elevador = GetDlgItem(hDlg, IDC_IMGELEVADOR);
		elevador1 = GetDlgItem(hDlg, IDC_IMGELEVADOR1);
		elevador2 = GetDlgItem(hDlg, IDC_IMGELEVADOR2);
		elevador3 = GetDlgItem(hDlg, IDC_IMGELEVADOR3);
		elevador4 = GetDlgItem(hDlg, IDC_IMGELEVADOR4);
		elevador5 = GetDlgItem(hDlg, IDC_IMGELEVADOR5);
		elevador6 = GetDlgItem(hDlg, IDC_IMGELEVADOR6);
		ShowWindow(elevador1, SW_HIDE);
		ShowWindow(elevador2, SW_HIDE);
		ShowWindow(elevador3, SW_HIDE);
		ShowWindow(elevador4, SW_HIDE);
		ShowWindow(elevador5, SW_HIDE);
		ShowWindow(elevador6, SW_HIDE);
		imgelevador = GetDlgItem(hDlg, IDB_ELEVADOR);
		SetTimer(hDlg, TIMER_ELEVADOR, 100, NULL);
		break;

	//case WM_TIMER:
	//	if (wParam == TIMER_ELEVADOR)
	//	{
	//		elevador = GetDlgItem(hDlg, IDC_IMGELEVADOR);
	//		SetWindowPos(elevador, HWND_TOP, posicaoX, 50 - posicaoY, 0, 0, SWP_NOSIZE);
	//		posicaoX++;
	//	}
	//	break;
		

	case WM_COMMAND:

		if ( (HIWORD(wParam)) == BN_CLICKED) {

			switch ( LOWORD(wParam)	)
			{

				case IDC_SERIAL:

					while (true) {
						
						//sobe
						if (leDadosArduino(hDlg) == '2') {
							OutputDebugStringW(L"COMANDO PARA SUBIR");

							if (andar == 3) {
								MessageBox(
									hDlg,
									L"Andar máximo atingido!",
									L"Erro",
									MB_OK);
							}
							else {
								EnableWindow(GetDlgItem(hDlg, IDC_INSEREPASS), FALSE);	//desabilita botao para inserir passageiros
								elevador = selecionaImgElevador(passTotal, hDlg);

								for (int i = 0; i < 15; i++) {
									SetWindowPos(elevador, HWND_TOP, posicaoX, posicaoY, 0, 0, SWP_NOSIZE);
									posicaoY -= 10;
									Sleep(250);
								}
								andar++;
								EnableWindow(GetDlgItem(hDlg, IDC_INSEREPASS), TRUE);	//habilita botao para inserir passageiros
							}

							break;
						}

						//desce
						if (leDadosArduino(hDlg) == '1') {
							OutputDebugStringW(L"COMANDO PARA DESCER");

							if (andar == 1) {
								MessageBox(
									hDlg,
									L"Andar mínimo atingido!",
									L"Erro",
									MB_OK);
							}
							else {

								EnableWindow(GetDlgItem(hDlg, IDC_INSEREPASS), FALSE);	//desabilita botao para inserir passageiros
								elevador = selecionaImgElevador(passTotal, hDlg);

								for (int i = 0; i < 15; i++) {

									posicaoY += 10;
									SetWindowPos(elevador, HWND_TOP, posicaoX, posicaoY, 0, 0, SWP_NOSIZE);
									Sleep(250);
								}
								andar--;
								EnableWindow(GetDlgItem(hDlg, IDC_INSEREPASS), TRUE);	//habilita botao para inserir passageiros
							}

							break;
						}

					}


					break;

				//Pressionou o botao Sobe:
				case IDC_SOBE:

					if (andar == 3) {
						MessageBox(
							hDlg,
							L"Andar máximo atingido!",
							L"Erro",
							MB_OK);
					}
					else {
						EnableWindow(GetDlgItem(hDlg, IDC_INSEREPASS), FALSE);	//desabilita botao para inserir passageiros
						elevador = selecionaImgElevador(passTotal, hDlg);

						for (int i = 0; i < 15; i++) {
							SetWindowPos(elevador, HWND_TOP, posicaoX, posicaoY, 0, 0, SWP_NOSIZE);
							posicaoY -= 10;
							Sleep(250);
						}
						andar++;
						EnableWindow(GetDlgItem(hDlg, IDC_INSEREPASS), TRUE);	//habilita botao para inserir passageiros
					}
					
					break;

				//Pressionou o botão desce
				case IDC_DESCE:

					if (andar == 1) {
						MessageBox(
							hDlg,
							L"Andar mínimo atingido!",
							L"Erro",
							MB_OK);
					}
					else {

						EnableWindow(GetDlgItem(hDlg, IDC_INSEREPASS), FALSE);	//desabilita botao para inserir passageiros
						elevador = selecionaImgElevador(passTotal, hDlg);

						for (int i = 0; i < 15; i++) {

							posicaoY += 10;
							SetWindowPos(elevador, HWND_TOP, posicaoX, posicaoY, 0, 0, SWP_NOSIZE);
							Sleep(250);
						}
						andar --;
						EnableWindow(GetDlgItem(hDlg, IDC_INSEREPASS), TRUE);	//habilita botao para inserir passageiros
					}
					break;

				//Insere passageiros no elevador
				case IDC_INSEREPASS:

					if ( (GetDlgItemInt(hDlg, IDC_EDITPESO, NULL, FALSE)) == NULL) {
						
						MessageBox(
							hDlg,
							L"Informe o peso do passageiro!",
							L"Erro",
							MB_OK);

						break;
					}

					elevador = GetDlgItem(hDlg, IDC_IMGELEVADOR);
					ShowWindow(elevador, SW_HIDE);

					pesoTotal += GetDlgItemInt(hDlg, IDC_EDITPESO, NULL, FALSE);
					
					if ( excedeuPesoMax(pesoTotal, hDlg) ) {
						pesoTotal -= GetDlgItemInt(hDlg, IDC_EDITPESO, NULL, FALSE);
					}
					else {
						passTotal++;
						//SetDlgItemInt(hDlg, IDC_EDITPESO, NULL, FALSE);
						elevador = selecionaImgElevador(passTotal, hDlg);
						ShowWindow(elevador_aux, SW_HIDE);
						ShowWindow(elevador, SW_SHOW);
						SetWindowPos(elevador, HWND_TOP, posicaoX, posicaoY, 0, 0, SWP_NOSIZE);
					}

					SetDlgItemInt(hDlg, IDC_EDITPESOT, pesoTotal, FALSE);
					SetDlgItemInt(hDlg, IDC_EDITNUMPASS, passTotal, FALSE);
					break;

				case IDM_EXIT:
					EndDialog(hDlg, 0);
					DestroyWindow(janelaPrincipal);
					break;

				case IDSAIR:
					EndDialog(hDlg, 0);
					DestroyWindow(janelaPrincipal);
					break;
			}
		}

		break;
	
	}

	//***BUG : causa problemas ao carregar a Dialog!
	/*if (leDadosArduino(hDlg) == '2') {
		OutputDebugStringW(L"ELEVADOR VAI COMECAR A SUBIR");
	}*/

	return 0;
}
