#include "stdafx.h"
#include "NotepadCPP.h"
#include "ListaDuplaCirc.h"
#include <sys/stat.h>
#include <Wincon.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define CTRL_C 3
#define CTRL_S 19
#define CTRL_Z 26
#define CTRL_Y 25
#define END 79
#define HOME 71
#define DELETE 83
#define BACKSPACE 8
#define MAXIMO_STRING 78
#define SETAS_CRASE -32

/*

Color      Background    Foreground
---------------------------------------------
Black            0           0
Blue             1           1
Green            2           2
Cyan             3           3
Red              4           4
Magenta          5           5
Brown            6           6
White            7           7
Gray             -           8
Intense Blue     -           9
Intense Green    -           10
Intense Cyan     -           11
Intense Red      -           12
Intense Magenta  -           13
Yellow           -           14
Intense White    -           15



*/

NotepadCPP::NotepadCPP() : ehSobreescrever(ABRIR_EXISTENTE), corFundoAtual(0), corLetraAtual(7), topo(0), base(24)
{
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CTRL_C_EVENT, true);
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)CTRL_BREAK_EVENT, true);
	//hidecursor();
	//SetConsoleCtrlHandler((PHANDLER_ROUTINE)CTRL_CLOSE_EVENT, true);
	//SetConsoleCtrlHandler((PHANDLER_ROUTINE)CTRL_LOGOFF_EVENT, true);
	//SetConsoleCtrlHandler((PHANDLER_ROUTINE)CTRL_SHUTDOWN_EVENT, true);
	lista = ListaDuplaCirc<String>();
	acoesFeitas = Pilha<Acao>();
	acoesDesfeitas = Pilha<Acao>();
}


NotepadCPP::~NotepadCPP()
{
	
}

NotepadCPP::NotepadCPP(const String& diretorio) : dir(diretorio), ehSobreescrever(ABRIR_EXISTENTE), corFundoAtual(0), corLetraAtual(7), topo(0), base(24)
{
	//SetConsoleCtrlHandler((PHANDLER_ROUTINE)CTRL_C_EVENT, true);
	//SetConsoleCtrlHandler((PHANDLER_ROUTINE)CTRL_BREAK_EVENT, true);
	//hidecursor();
	lista = ListaDuplaCirc<String>();
	acoesFeitas = Pilha<Acao>();
	acoesDesfeitas = Pilha<Acao>();
}

NotepadCPP::NotepadCPP(const String& diretorio, const int ehSobre) : ehSobreescrever(ehSobre), corFundoAtual(0), corLetraAtual(7), topo(0), base(24)
{
	//SetConsoleCtrlHandler((PHANDLER_ROUTINE)CTRL_C_EVENT, true);
	//SetConsoleCtrlHandler((PHANDLER_ROUTINE)CTRL_BREAK_EVENT, true);
	//hidecursor();
	acoesFeitas = Pilha<Acao>();
	this->dir = String(diretorio);
	lista = ListaDuplaCirc<String>();
	acoesDesfeitas = Pilha<Acao>();
}

Acao NotepadCPP::CtrlY(const ListaDuplaCirc<String> &lst, const Acao &dis)
{
	String *ptr = (String*)malloc(dis.getTamanho() * sizeof(String));
	for (int i = 0; i < dis.getTamanho(); i++)
	{
		*(ptr + i) = lst[dis.getLinhaOcorrencia(i)];
		lst[dis.getLinhaOcorrencia(i)] = *(dis.getString() + i);
	}
	return Acao(ptr, String("Z"), dis.getLinhasOcorrencias(), dis.getTamanho());
}

Acao NotepadCPP::CtrlZ(const ListaDuplaCirc<String> &lst, const Acao &dis)
{
	String *ptr = (String*)malloc(dis.getTamanho() * sizeof(String));
	for (int i = 0; i < dis.getTamanho(); i++)
	{
		*(ptr + i) = lst[dis.getLinhaOcorrencia(i)];
		lst[dis.getLinhaOcorrencia(i)] = *(dis.getString() + i);
	}
	return Acao(ptr, String("Y"), dis.getLinhasOcorrencias(), dis.getTamanho());
}

Acao NotepadCPP::CtrlC(const ListaDuplaCirc<String> &lst, const Acao &dis)
{
	return Acao();
}

Acao NotepadCPP::CtrlX(const ListaDuplaCirc<String> &lst, const Acao &dis)
{
	return Acao();
}

Acao NotepadCPP::CtrlH(const ListaDuplaCirc<String> &lst, const Acao &dis)
{
	return Acao();
}

Acao NotepadCPP::Adicionar(const ListaDuplaCirc<String> &lst, const Acao &dis)
{
	return Acao();
}

Acao NotepadCPP::Remover(const ListaDuplaCirc<String> &lst, const Acao &dis)
{
	return Acao();
}

bool NotepadCPP::fexists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

void NotepadCPP::ssetcolor(WORD color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	return;
}

void NotepadCPP::setForeGroundAndBackGroundColor(int BackGroundColor)
{
	int color = 16 * BackGroundColor + 7;
	ssetcolor(color);
}

void NotepadCPP::gotoxy(int x, int y)
{
	//setForeGroundAndBackGroundColor(0);
	COORD pos;

	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	//setForeGroundAndBackGroundColor(1);
}

void NotepadCPP::ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void toClipboard(const std::string &s){
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size());
	if (!hg){
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

void fromClipboard(const std::string &s)
{
	HANDLE h;

	if (!OpenClipboard(NULL))
		throw ("Can't open clipboard");

	h = GetClipboardData(CF_TEXT);

	printf("%s\n", (char *)h);

	CloseClipboard();
}

int NotepadCPP::getACPx()
{
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &SBInfo);

	return SBInfo.dwCursorPosition.X;
}

int NotepadCPP::getACPy() // actual cursor position Y
{
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &SBInfo);

	return SBInfo.dwCursorPosition.Y;
}

void NotepadCPP::hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

bool NotepadCPP::setTamanho(int width, int height)
{
	COORD coord;
	coord.X = width;
	coord.Y = height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = height;
	Rect.Right = width;

	// Get handle of the standard output 
	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (Handle == NULL)
	{
		cout << "Failure in getting the handle\n" << GetLastError();
		return FALSE;
	}

	// Set the window size to that specified in Rect 
	if (!SetConsoleWindowInfo(Handle, TRUE, &Rect))
	{
		cout << "Failure in setting window size\n" << GetLastError();
		return FALSE;
	}

	// Set screen buffer size to that specified in coord 
	if (!SetConsoleScreenBufferSize(Handle, coord))
	{
		cout << "Failure in setting buffer size\n" << GetLastError();
		return FALSE;
	}

	return TRUE;
}

bool NotepadCPP::salvarArquivo(const String& dir)
{
	ofstream arq = ofstream();
	arq.open((char*)dir);
	if (arq.fail())
		return false;
	lista.iniciarPercursoSequencial();
	while (lista.podePercorrer())
	{
		arq.write(lista.getAtual(), lista.getAtual().length()*sizeof(char));
	}
	arq.close();
	return true;
}

bool NotepadCPP::abrirArquivo(const String& dir)
{
	if (this->ehSobreescrever == ABRIR_SOBREESCREVER)
	{
		return this->limparArquivo(dir);
	}
	else if (this->ehSobreescrever == CRIAR_NOVO)
	{
		return this->criarArquivo(dir);
	}
	ifstream arq = ifstream();
	arq.open((char*)dir);
	if (!arq.is_open())
		return false;

	std::string line("");
	while (!arq.eof())
	{
		std::getline(arq, line);
		int qtos = 0;
		while (line.length() > 80)
		{
			lista.inserirNoFinal(line.substr(80 * qtos++,80));
			line = line.substr(80 * qtos, 80);
		}
		lista.inserirNoFinal(line);
	}
	arq.close();
	return true;
}

bool NotepadCPP::criarArquivo(const String& dir)
{
	ofstream arq = ofstream();
	arq.open((char*)dir, fstream::out);
	if (arq.fail())
		return false;
	lista.inserirNoComeco("");
	arq.close();
	return true;
}

bool NotepadCPP::limparArquivo(const String& dir)
{
	ofstream arq = ofstream();
	arq.open((char*)dir, ios::out | ios::trunc);
	if (arq.fail())
		return false;
	lista.inserirNoComeco("");
	arq.close();
	return true;
}

void NotepadCPP::printarNaTela()
{
	int x = getACPx();
	int y = getACPy();
	ClearScreen();
	int indice = topo;
	if (base > lista.length() - 1)
	{
		if (topo == 0)
		{
			indice = lista.length() - 25;
			indice = topo;
			base = lista.length() - 1;
		}
		else
		{
			indice = lista.length() - 25;
			topo = indice;
			base = lista.length() - 1;
		}
	}

	while (indice < base)
	{
		cout << lista[indice++] << endl;
	}
	cout << lista[indice++];
	gotoxy(x, y);
}

void NotepadCPP::run()
{
	String vaiSalvar = 'N';
	int indiceAtual = 0;
	if (this->abrirArquivo(this->dir))
	{
		lista.iniciarPercursoSequencial();
		lista.podePercorrer();
		gotoxy(0,0);
		while (true)
		{
			printarNaTela();
			while (!_kbhit()) {}
			char c = _getch();
			if (c == SETAS_CRASE) // setas
			{
				c = _getch();
				switch (c) 
				{
					case KEY_UP:
						if (lista.getIndexAtual() > 0)
						{
							lista.voltar();
							int lDepo = lista.getAtual().length();
							if (lDepo - 1 < indiceAtual)
								indiceAtual = lDepo - 1;
							if (lista.getIndexAtual() < this->topo)
							{
								if (this->topo > 0)
								{
									this->base--;
									this->topo--;
								}
							}
							else
								gotoxy(indiceAtual, getACPy() - 1);
						}
						break;
					case KEY_DOWN:
						if (lista.getIndexAtual() < lista.length() - 1)//if (lista[lista.getIndiceAtual()] != lista[-1])
						{
							lista.avancar();
							int lDepo = lista.getAtual().length();
							if (lDepo - 1 < indiceAtual)
								indiceAtual = lDepo - 1;
							if (lista.getIndexAtual() > this->base)
							{
								if (lista.length() >= this->base)
								{
									this->base++;
									this->topo++;
								}
							}
							else
								gotoxy(indiceAtual, getACPy() + 1);

						}
						break;
					case KEY_RIGHT:
						if (indiceAtual < lista.getAtual().length()) // vai 1 a mais para a direita
						{
							gotoxy(++indiceAtual, getACPy());
						}
						else
						{
							if (lista.getIndexAtual() != lista.length() - 1)
							{
								lista.avancar();
								indiceAtual = 0;
								gotoxy(indiceAtual, getACPy() + 1);
							}
						}
						break;
					case KEY_LEFT:
						if (indiceAtual > 0)
							gotoxy(--indiceAtual, getACPy());
						else
						{
							if (lista.getIndexAtual() != 0)
							{
								lista.voltar();
								indiceAtual = lista.getAtual().length();
								gotoxy(indiceAtual, getACPy() - 1);
							}
						}
						break;
					case END:
						indiceAtual = lista.getAtual().length();
						gotoxy(indiceAtual, getACPy());
						break;

					case HOME:
						indiceAtual = 0;
						gotoxy(indiceAtual, getACPy());
						break;
					case CTRL_S:
					{
						cout << "Ctrl+S" << endl;
						break;
					}
					case CTRL_C:
					{
						cout << "Ctrl+C" << endl;
						break;
					}
					case CTRL_Z:
					{
						cout << "Ctrl+Z" << endl;
						break;
					}
					case CTRL_Y:
					{
						cout << "Ctrl+Y" << endl;
						break;
					}
					case DELETE:
					{
						cout << "delete" << endl;
						break;
					}
					case 17:
					{
						setForeGroundAndBackGroundColor(0);
						break;
					}
					default:
					{
						inserirNaAtual(SETAS_CRASE, indiceAtual);
						inserirNaAtual(c, indiceAtual);
						break;
					}
				}
			}
			else if (c >= 32) // caracter imprimível
			{
				inserirNaAtual(c, indiceAtual);
			}
			else if (c == BACKSPACE)
			{
				String aux = lista.getAtual();
				if (indiceAtual == 0)
				{
					String anteAux = lista[lista.getIndexAtual() - 1];
					if (aux.length() + anteAux.length() <= MAXIMO_STRING)
					{
						lista[lista.getIndexAtual() - 1] = anteAux + aux;
						lista.removaAtual();
						indiceAtual = anteAux.length();
						gotoxy(indiceAtual, getACPy() - 1);
						lista.voltar();
					}
					else if (anteAux.length() < MAXIMO_STRING)
					{
						int qtasPegar = MAXIMO_STRING - anteAux.length();
						lista[lista.getIndexAtual() - 1] = anteAux + aux.substr(0, qtasPegar);
						String oioioioio = lista[lista.getIndexAtual() - 1];
						aux.deletar(0, qtasPegar);
						lista[lista.getIndexAtual()] = aux;
						indiceAtual = anteAux.length();
						gotoxy(indiceAtual, getACPy()-1);
						//lista.voltar();
					}
				}
				else
				{
					aux.deleteCharAt(--indiceAtual);
					lista.setAtual(aux);
					gotoxy(indiceAtual, getACPy());
				}
				//Acao novaAcao = Acao(lista.getAtual(), ACAO_ADICAO, getACPy());
				//acoesFeitas.empilhar(novaAcao);
			}
		}
	}
}

void NotepadCPP::inserirNaAtual(char c, int &indiceAtual)
{
	String aux = lista.getAtual();

	if (aux.length() != indiceAtual + 1)
		aux.inserir(c, indiceAtual++);
	else
		aux[indiceAtual++] = c;
	acoesFeitas.empilhar(Acao(lista.getAtual(), ACAO_ADICAO, getACPy()));
	lista.setAtual(aux);
	gotoxy(indiceAtual, getACPy());
}

void NotepadCPP::inserirComRecursion(const char &ASerInserido)
{
	String aux = lista.getAtual();
	int atualReserva = lista.indiceDe(aux);
	int ateOndeMexer = primeiraComEspaco(atualReserva);

	if (ateOndeMexer > lista.length() - 1)
	{
		lista.inserirNoFinal(String(lista[-1][lista[-1].length() - 1])); // começando com o último char da lista anterior
		ateOndeMexer--;
	}
	
	char charAtual;
	for (; atualReserva < ateOndeMexer; charAtual = lista[++atualReserva][MAXIMO_STRING - 1])
	{
		char removido = lista[atualReserva+1].deleteCharAt(MAXIMO_STRING-1);
		lista[atualReserva + 1].inserir(charAtual);
	}
	lista[atualReserva + 2].inserir(lista[atualReserva + 1][MAXIMO_STRING - 1]);
}

int NotepadCPP::primeiraComEspaco(int atualReserva)
{
	for (int i = atualReserva + 1; lista[i] != lista[0]; i++) // acha a primeira string não cheia
		if (lista[i].length() < MAXIMO_STRING)
			return i;
	return lista.length();
}