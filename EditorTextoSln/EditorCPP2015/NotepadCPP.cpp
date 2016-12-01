#include "stdafx.h"
#include "NotepadCPP.h"
#include "ListaDuplaCirc.h"
#include <sys/stat.h>
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define CTRL_R 18
#define CTRL_S 19
#define CTRL_Z 26
#define CTRL_Y 25
#define CTRL_V 22
#define CTRL_B 2
#define END 79
#define HOME 71
#define DELETE 83
#define BACKSPACE 8
#define MAXIMO_STRING 78
#define SETAS_CRASE -32
#define ENTER 13
#define PAGE 224
#define PAGE_DOWN 81
#define PAGE_UP 73
#define ESC 27

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
	//acoesFeitas = Pilha<Acao>();
	this->dir = diretorio;
	lista = ListaDuplaCirc<String>();
	//acoesDesfeitas = Pilha<Acao>();
}

void NotepadCPP::CtrlY(const Acao &dis)
{
	String txt = this->lista[dis.getPosY(0)];
	if (this->lista[dis.getPosY(0)].length() < MAXIMO_STRING)
		this->lista[dis.getPosY(0)] = dis.getString(0);
	this->gotoxy(dis.getPosX(), dis.getPosY(0));
	this->acoesFeitas.empilhar(Acao(txt, ACAO_CTRL_Z, dis.getPosY(0), dis.getPosX()));
}

int NotepadCPP::CtrlZ(const Acao &dis)
{
	if (dis.getString(0) == "" && dis.getTipo() == ACAO_REMOVE)
	{
		String* txt = new String[2]();
		txt[0] = lista[dis.getPosY(0)];
		txt[1] = String();

		unsigned int* posY = new unsigned int[2]{ (unsigned int)dis.getPosY(0) , (unsigned int)dis.getPosY(1) };

		Acao t;
		if (acoesDesfeitas.getTopo().getDado().getTipo() == dis.getTipo())
			t = acoesDesfeitas.getTopo().getDado();

		this->acoesDesfeitas.esvaziar();
		t = t + Acao(txt, ACAO_CTRL_Y, posY, 2, dis.getPosX());
		this->acoesDesfeitas.empilhar(t);

		String ttttt = dis.getString(1);
		this->lista[lista.getIndexAtual()] = dis.getString(0);
		this->lista.inserirNaPosicao(dis.getString(1) + dis.getString(0), dis.getPosY(1));
	}
	else
	{
		String txt = this->lista[dis.getPosY(0)];
		if (this->lista[dis.getPosY(0)].length() < MAXIMO_STRING)
			this->lista[dis.getPosY(0)] = dis.getString(0);

		this->gotoxy(dis.getPosX(), dis.getPosY(0));
		this->acoesDesfeitas.esvaziar();
		this->acoesDesfeitas.empilhar(Acao(txt, ACAO_CTRL_Y, dis.getPosY(0), dis.getPosX()));
	}
	return dis.getPosX();
}

Acao NotepadCPP::CtrlC(const Acao &dis)
{
	return Acao();
}

Acao NotepadCPP::CtrlX(const Acao &dis)
{
	return Acao();
}

Acao NotepadCPP::CtrlH(const Acao &dis)
{
	return Acao();
}

Acao NotepadCPP::removerParaTras(const Acao &dis)
{
	if (this->acoesFeitas.getTopo().getDado().getPosX() == dis.getPosX() + 1)
		this->acoesFeitas.empilhar(dis + this->acoesFeitas.desempilhar().getDado());

	return this->acoesFeitas.getTopo().getDado();
}

Acao NotepadCPP::removerParaFrente(const Acao &dis)
{
	if (this->acoesFeitas.getTopo().getDado().getPosX() == dis.getPosX() && this->acoesFeitas.getTopo().getDado().getTipo() == dis.getTipo())
		this->acoesFeitas.empilhar(this->acoesFeitas.desempilhar().getDado() + dis);

	return this->acoesFeitas.getTopo().getDado();
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

void NotepadCPP::showcursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;
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
		arq.write(lista.getAtual()+'\n', (lista.getAtual().length() + 1)*sizeof(char));
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
	if (!arq.is_open()) // se deu erro ao abrir o arquivo
		return false;

	std::string line;
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
	gotoxy(0, 0);
	hidecursor();
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
		cout << lista[indice] + (String(" ") * (MAXIMO_STRING - lista[indice].length() - 1)) << endl;
		indice++;
	}
	cout << lista[indice++] + (String(" ") * (MAXIMO_STRING - lista[indice].length() - 1));
	if (topo == 0)
	{
		while (indice <= 25)
		{
			cout << String(" ") * MAXIMO_STRING << endl;
			indice++;
		}
	}
	else
	{
		while (indice <= 25)
		{
			cout << String(" ") * MAXIMO_STRING << endl;
			indice++;
		}
	}
	gotoxy(x, y);
	showcursor();
}

void NotepadCPP::run()
{
	bool precisaPrintar = true;
	int indiceAtual = 0, qtosCtrlC = 0, posXIni = 0, posYIni = 0, posXFim = 0, posYFim = 0;
	if (this->abrirArquivo(this->dir))
	{
		ClearScreen();
		lista.iniciarPercursoSequencial();
		lista.podePercorrer();
		gotoxy(0,0);
		while (true)
		{
			if (precisaPrintar)
				printarNaTela();
			precisaPrintar = true;
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
							if (lDepo < indiceAtual)
								indiceAtual = lDepo;

							if (lista.getIndexAtual() < this->topo)
							{
								if (this->topo > 0)
								{
									this->base--;
									this->topo--;
								}
							}
							else
							{
								precisaPrintar = false;
								gotoxy(indiceAtual, getACPy() - 1);
							}
						}
						break;
					case KEY_DOWN:
						if (lista.getIndexAtual() < lista.length() - 1)//if (lista[lista.getIndiceAtual()] != lista[-1])
						{
							lista.avancar();

							int lDepo = lista.getAtual().length();
							if (lDepo < indiceAtual) // se a String nova for menor que o índice atual
								indiceAtual = lDepo;

							if (lista.getIndexAtual() > this->base)
							{
								if (lista.length() >= this->base)
								{
									this->base++;
									this->topo++;
								}
							}
							else
							{
								gotoxy(indiceAtual, getACPy() + 1);
								precisaPrintar = false;
							}

						}
						break;
					case KEY_RIGHT:
						if (indiceAtual < lista.getAtual().length()) // vai 1 a mais para a direita
						{
							gotoxy(++indiceAtual, getACPy());
							precisaPrintar = false;
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
						{
							gotoxy(--indiceAtual, getACPy());
							precisaPrintar = false;
						}
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
					case CTRL_R:
					{
						if (++qtosCtrlC == 2)
						{
							posXFim = this->getACPx();
							posYFim = this->getACPy();

							if (posYIni == posYFim) toClipboard(this->lista[posYIni].substr(posXIni, posXFim));
							else if (posYFim == posYIni + 1) toClipboard(this->lista[posYIni].substr(posXIni, this->lista[posYIni].length() - posXIni -1) + this->lista[posYFim].substr(0, posXFim));
							else
							{
								String txt = this->lista[posYIni].substr(posXIni, this->lista[posYIni].length() - 1 - posXIni);
								for (int i = posYIni + 1; i < posYFim; i++)
									txt = txt + this->lista[i];
								toClipboard(txt + this->lista[posYFim].substr(0, posXFim));
							}
						}

						else
						{
							posXIni = this->getACPx();
							posYIni = this->getACPy();
						}
						break;
					}
					case DELETE:
					{
						deletarAtual(indiceAtual);
						break;
					}
					case 17:
					{
						setForeGroundAndBackGroundColor(0);
						break;
					}
					case PAGE_DOWN:
					{
						if (base != lista.length())
						{
							if (lista.length() < base + 24)
							{
								if (lista.length() < 24)
									base = 24;
								else
									base = lista.length();

								lista.iniciarPercursoSequencial(false);
								lista.podePercorrer();
								lista.avancar();

								topo = base - 24;
								indiceAtual = 0;
								gotoxy(0, (lista.length()-1 < 24)?lista.length()-1:24);
							}
							else
							{
								topo += 24;
								base += 24;
								for (int i = 0; i < 25; i++)
									lista.avancar();
								indiceAtual = 0;
								gotoxy(0, getACPy());
							}
						}
						break;
					}
					case PAGE_UP:
					{
						if (topo != 0)
						{
							if (topo - 24 < 0)
							{
								topo = 0;
								base = 24;
								lista.iniciarPercursoSequencial();
								lista.podePercorrer();
							}
							else
							{
								topo -= 24;
								base -= 24;
								for (int i = 0; i < 25; i++)
									lista.voltar();
							}
						}
						indiceAtual = 0;
						gotoxy(0, 0);
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
				if (indiceAtual == 0) // 0 no X
				{
					if (lista.getIndexAtual() != 0) // não é o primeiro
					{
						String anteAux = lista[lista.getIndexAtual() - 1];
						if (aux.length() + anteAux.length() <= MAXIMO_STRING)
						{
							String* txt = new String[2]();
							txt[0] = lista.getAtual();
							txt[1] = lista[lista.getIndexAtual() + 1];

							unsigned int* posY = new unsigned int[2]{ (unsigned int)lista.getIndexAtual() , (unsigned int)lista.getIndexAtual() + 1 };

							this->acoesFeitas.empilhar(Acao(txt, ACAO_REMOVE, posY, 2, this->getACPx()));
							lista[lista.getIndexAtual() - 1] = anteAux + aux;
							lista.removaAtual();
							indiceAtual = anteAux.length();
							if (lista.getIndexAtual() != lista.length() - 1 && topo == 0) // se não for o último e o topo é o primeiro
							{
								gotoxy(indiceAtual, getACPy());
							}
							else
							{
								gotoxy(indiceAtual, getACPy()-1);
							}

							lista.voltar();
						}
						else if (anteAux.length() < MAXIMO_STRING)
						{
							String* txt = new String[2]();
							txt[0] = lista.getAtual();
							txt[1] = lista[lista.getIndexAtual() + 1];

							unsigned int* posY = new unsigned int[2]{ (unsigned int)lista.getIndexAtual() , (unsigned int)lista.getIndexAtual() + 1 };

							this->acoesFeitas.empilhar(Acao(txt, ACAO_REMOVE, posY, 2, this->getACPx()));

							int qtasPegar = MAXIMO_STRING - anteAux.length();
							lista[lista.getIndexAtual() - 1] = anteAux + aux.substr(0, qtasPegar);
							aux.deletar(0, qtasPegar);
							lista[lista.getIndexAtual()] = aux;
							indiceAtual = anteAux.length();
							lista.removaAtual();
							gotoxy(indiceAtual, getACPy() - 1);
							lista.avancar();
							lista.voltar();
							lista.avancar();
						}
					}
				}
				else
				{
					aux.deleteCharAt(--indiceAtual);
					lista.setAtual(aux);
					gotoxy(indiceAtual, getACPy());
				}
			}
			else if (c == CTRL_Z)
			{
				if (!this->acoesFeitas.ehVazia()) indiceAtual = this->CtrlZ(this->acoesFeitas.desempilhar().getDado());
			}
			else if (c == CTRL_Y)
			{
				if (!this->acoesDesfeitas.ehVazia()) this->CtrlY(this->acoesDesfeitas.desempilhar().getDado());
			}
			else if (c == ENTER)
			{
				if (indiceAtual == lista.getAtual().length())
					lista.inserirDepois(String());
				else
				{
					String tavaSobrando = lista.getAtual().substr(indiceAtual);
					lista[lista.getIndexAtual()].deletar(indiceAtual, lista.getAtual().length() - indiceAtual);
					lista.inserirDepois(tavaSobrando);
				}
				indiceAtual = 0;
				lista.avancar();
				gotoxy(indiceAtual, getACPy() + 1);
			}
			else if (c == ESC)
			{
				this->ClearScreen();
				char opcao = ' ';

				cout << "Deseja sair do arquivo?" << endl;
				cin >> opcao;

				if (opcao == 'y' || opcao == 'Y')
				{
					opcao = ' ';

					cout << "Deseja salvar o arquivo?" << endl;
					cin >> opcao;

					if (opcao == 'y' || opcao == 'Y')
					{
						salvarArquivo(dir);
						break;
					}
					break;
				}
				gotoxy(0, 0);
				indiceAtual = 0;

				this->lista.iniciarPercursoSequencial();
				this->lista.podePercorrer();
			}
			else if (c == CTRL_B)
			{
				salvarArquivo(dir);
			}
		}
	}
}

void NotepadCPP::inserirNaAtual(char c, int &indiceAtual)
{
	String aux = lista.getAtual();
	if (aux.length() >= MAXIMO_STRING) // máximo da string já alcançada
	{
		if (lista.getIndexAtual() == lista.length() - 1)
			lista.inserirNoFinal(String());
		lista.avancar();
		indiceAtual = 0;
		inserirNaAtual(c, indiceAtual);
	}
	else
	{
		if (aux.length() != indiceAtual + 1)
			aux.inserir(c, indiceAtual++);
		else
			aux[indiceAtual++] = c;

		if (this->acoesFeitas.ehVazia()) 
			this->acoesFeitas.empilhar(Acao(lista.getAtual(), ACAO_ADICIONAR, getACPy(), getACPx()));

		else if (this->acoesFeitas.getTopo().getDado().getPosY(0) != this->getACPy()) 
		    this->acoesFeitas.empilhar(Acao(lista.getAtual(), ACAO_ADICIONAR, getACPy(), getACPx()));

		this->lista.setAtual(aux);
		this->gotoxy(indiceAtual, getACPy());
	}
}

void NotepadCPP::deletarAtual(const int &indiceAtual)
{
	if (indiceAtual == lista.getAtual().length()) // truncar as linhas
	{
		if (lista.getAtual().length() + lista[lista.getIndexAtual() + 1].length() > MAXIMO_STRING) // não vai truncar completamente
		{
			int qtosCabem = MAXIMO_STRING - lista.getAtual().length();
			String truncada = lista.getAtual() + lista[lista.getIndexAtual() + 1].substr(0, qtosCabem);

			String* txt = new String[2]();
			txt[0] = lista.getAtual();
			txt[1] = lista[lista.getIndexAtual() + 1];

			unsigned int* posY = new unsigned int[2]{ (unsigned int)lista.getIndexAtual() , (unsigned int)lista.getIndexAtual() + 1 };

			this->acoesFeitas.empilhar(Acao(txt, ACAO_REMOVE, posY, 2, this->getACPx()));

			lista[lista.getIndexAtual()] = truncada;
			lista[lista.getIndexAtual() + 1] = lista[lista.getIndexAtual() + 1].substr(qtosCabem, lista.getAtual().length()-1 - qtosCabem);


			
			// Adicionar Acao de Deletar com 2 Strings alteradas
		}
		else
		{
			String truncada = lista.getAtual() + lista[lista.getIndexAtual() + 1];

			this->acoesFeitas.empilhar(Acao(lista.getAtual(), ACAO_REMOVE, lista.getIndexAtual(), this->getACPx()));

			lista.removaDepois();
			lista[lista.getIndexAtual()] = truncada;
			// adicionar acao de Deletar
		}
	}
	else
	{
		this->acoesFeitas.empilhar(Acao(lista.getAtual(), ACAO_REMOVE, lista.getIndexAtual(), this->getACPx()));
		lista[lista.getIndexAtual()].deleteCharAt(indiceAtual);
		// adicionar acao de Deletar
	}
}



/*
int indiceLoop = lista.getIndexAtual(); // obtendo os atuais
char removida;
if (indiceAtual == MAXIMO_STRING)
{
while (aux.length() == MAXIMO_STRING)
{
aux.inserir(c, indiceAtual); // inserindo o novo carater

lista[indiceLoop] = aux; // setando String com o novo caracter e sem o último

if (indiceLoop != lista.length() - 1) // se não for o último
aux = lista[indiceLoop++]; // indo para o próximo
else
{
break;
}
removida = aux.deleteCharAt(aux.length() - 1); // removendo o último caracter
}
}
else
{
while (aux.length() == MAXIMO_STRING)
{
removida = aux.deleteCharAt(aux.length() - 1); // removendo o último caracter
aux.inserir(c, indiceAtual); // inserindo o novo carater

lista[indiceLoop] = aux; // setando String com o novo caracter e sem o último

if (indiceLoop != lista.length() - 1) // se não for o último
aux = lista[indiceLoop++]; // indo para o próximo
else
{
break;
}
}
lista.inserirNoFinal(String(removida));
if (indiceAtual >= MAXIMO_STRING)
{
indiceAtual = indiceAtual - MAXIMO_STRING;

}
}
this->gotoxy(indiceAtual, getACPy());
*/