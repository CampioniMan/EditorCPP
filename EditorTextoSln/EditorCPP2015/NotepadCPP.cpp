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
#define TAB 9
#define MAXIMO_LINHAS 25

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

int NotepadCPP::CtrlY(const Acao &dis)
{
	String txt = this->lista[dis.getPosY(0)];
	if (this->lista[dis.getPosY(0)].length() < MAXIMO_STRING)
		this->lista[dis.getPosY(0)] = dis.getString(0);
	this->gotoxy(dis.getPosX(), dis.getPosY(0));
	this->acoesFeitas.empilhar(Acao(txt, ACAO_CTRL_Z, dis.getPosY(0), dis.getPosX()));
	return dis.getPosX();
}

int NotepadCPP::CtrlZ(const Acao &dis)
{
	if (dis.getTipo() == ACAO_REMOVE && dis.getTamanho() == 2)
	{
		if (dis.getPosY(0) == 0)
		{
			String *txt = new String[2]{ this->lista.getPrimeiro(), String() };
			unsigned int *posY = new unsigned int[2]{dis.getPosY(0), dis.getPosY(1)};

			this->lista.remover(0);
			this->lista.inserirNoComeco(dis.getString(1));
			this->lista.inserirNoComeco(dis.getString(0));

			this->gotoxy(dis.getPosX(), dis.getPosY(0));
			this->acoesDesfeitas.empilhar(Acao(txt, ACAO_REMOVE, posY, 2, dis.getPosX()));
			
			free(txt);
			free(posY);
		}

		else if (dis.getPosY(1) == this->lista.length() - 1)
		{
			String *txt = new String[2]{ String(), this->lista.getUltimo() };
			unsigned int *posY = new unsigned int[2]{ dis.getPosY(0), dis.getPosY(1) };

			this->lista.remover(this->lista.length() - 1);
			this->lista.inserirNoFinal(dis.getString(0));
			this->lista.inserirNoFinal(dis.getString(1));

			this->gotoxy(dis.getPosX(), dis.getPosY(0));
			this->acoesDesfeitas.empilhar(Acao(txt, ACAO_REMOVE, posY, 2, dis.getPosX()));

			free(txt);
			free(posY);
		}

		else
		{
			String *txt = new String[2]{ String(), this->lista.getUltimo() };
			unsigned int *posY = new unsigned int[2]{ dis.getPosY(0), dis.getPosY(1) };

			this->lista[dis.getPosY(0)] = dis.getString(0);
			this->lista.inserirNaPosicao(dis.getString(1), dis.getPosY(1));

			this->gotoxy(dis.getPosX(), dis.getPosY(0));
			this->acoesDesfeitas.empilhar(Acao(txt, ACAO_REMOVE, posY, 2, dis.getPosX()));

			free(txt);
			free(posY);
		}
	}
	else
	{
		String txt = this->lista[dis.getPosY(0)];
		if (this->lista[dis.getPosY(0)].length() < MAXIMO_STRING)
			this->lista[dis.getPosY(0)] = dis.getString(0);

		this->gotoxy(dis.getPosX(), dis.getPosY(0));
		this->acoesDesfeitas.empilhar(Acao(txt, ACAO_CTRL_Y, dis.getPosY(0), 0));
		this->acoesDesfeitas.getTopo().getDado().setTipo((dis.getTipo() == ACAO_REMOVE) ? getACPx() : dis.getPosX());
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
		while (line.length() > MAXIMO_STRING)
		{
			lista.inserirNoFinal(line.substr(MAXIMO_STRING * qtos++,MAXIMO_STRING));
			line = line.substr(MAXIMO_STRING * qtos, MAXIMO_STRING);
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
	lista.inserirNoComeco(String());
	arq.close();
	return true;
}

bool NotepadCPP::limparArquivo(const String& dir)
{
	ofstream arq = ofstream();
	arq.open((char*)dir, ios::out | ios::trunc);
	if (arq.fail())
		return false;
	lista.inserirNoComeco(String());
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
			indice = topo;
			base = MAXIMO_LINHAS-1;
		}
		else
		{
			indice = lista.length() - MAXIMO_LINHAS;
			topo = indice;
			base = lista.length() - 1;
		}
	}

	if (lista.length() - 1 < MAXIMO_LINHAS-1)
	{
		while (indice < lista.length() - 1)
		{
			cout << lista[indice] + (String(" ") * (MAXIMO_STRING - lista[indice].length())) << endl;
			indice++;
		}
	}
	else
	{
		while (indice < base)
		{
			cout << lista[indice] + (String(" ") * (MAXIMO_STRING - lista[indice].length())) << endl;
			indice++;
		}
	}
	cout << lista[indice++] + (String(" ") * (MAXIMO_STRING - lista[indice].length()));
	if (topo == 0)
	{
		while (indice < MAXIMO_LINHAS)
		{
			cout << String(" ") * MAXIMO_STRING << endl;
			indice++;
		}
	}
	else
	{
		while (indice < MAXIMO_LINHAS)
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
						else
							precisaPrintar = false;
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
						else
							precisaPrintar = false;
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
								
								if (getACPy() >= base)
								{
									topo++;
									base++;
									gotoxy(indiceAtual, getACPy());
								}
								else
								{
									gotoxy(indiceAtual, getACPy() + 1);
									precisaPrintar = false;
								}
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
								if (getACPy() <= topo)
								{
									topo--;
									base--;
									gotoxy(indiceAtual, getACPy());
								}
								else
								{
									gotoxy(indiceAtual, getACPy() - 1);
									precisaPrintar = false;
								}
							}
						}
						break;
					case END:
						indiceAtual = lista.getAtual().length();
						gotoxy(indiceAtual, getACPy());
						precisaPrintar = false;
						break;

					case HOME:
						indiceAtual = 0;
						gotoxy(indiceAtual, getACPy());
						precisaPrintar = false;
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
						deletarAtual(indiceAtual, precisaPrintar);
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
							if (lista.length() < base + MAXIMO_LINHAS-1)
							{
								if (lista.length() < MAXIMO_LINHAS-1)
									base = MAXIMO_LINHAS-1;
								else
									base = lista.length();

								lista.iniciarPercursoSequencial();
								lista.podePercorrer();
								lista.voltar();

								topo = base - MAXIMO_LINHAS-1;
								indiceAtual = 0;
								gotoxy(0, (lista.length() - 1 < MAXIMO_LINHAS - 1) ? lista.length() - 1 : MAXIMO_LINHAS-1);
							}
							else
							{
								topo += MAXIMO_LINHAS-1;
								base += MAXIMO_LINHAS-1;
								for (int i = 0; i < MAXIMO_LINHAS-1; i++)
									lista.avancar();
								indiceAtual = 0;
								gotoxy(0, getACPy());
							}
						}
						break;
					}
					case PAGE_UP:
					{
						if (topo != 0) // não é o primeiro
						{
							if (topo - MAXIMO_LINHAS-1 < 0) // se faltar menos que 24 pro topo
							{
								topo = 0;
								base = MAXIMO_LINHAS-1;
								lista.iniciarPercursoSequencial();
								lista.podePercorrer();
							}
							else
							{
								topo -= MAXIMO_LINHAS-1;
								base -= MAXIMO_LINHAS-1;
								for (int i = 0; i < MAXIMO_LINHAS; i++)
									lista.voltar();
							}
						}
						indiceAtual = 0;
						gotoxy(0, lista.getIndexAtual()-topo);
						break;
					}
					default:
					{
						inserirNaAtual(SETAS_CRASE, indiceAtual, precisaPrintar);
						inserirNaAtual(c, indiceAtual, precisaPrintar);
						break;
					}
				}
			}
			else if (c >= 32) // caracter imprimível
			{
				inserirNaAtual(c, indiceAtual, precisaPrintar);
			}
			else if (c == BACKSPACE)
			{
				String aux = lista.getAtual();
				if (indiceAtual == 0) // se é o primeiro caracter da linha
				{
					if (lista.getIndexAtual() != 0) // não é a primeira linha
					{
						String anteAux = lista[lista.getIndexAtual() - 1];
						if (aux.length() + anteAux.length() <= MAXIMO_STRING)
						{
							//Acao a ser registrada
							String* txt = new String[2]{lista.getAtual(), lista[lista.getIndexAtual() + 1]};
							unsigned int* posY = new unsigned int[2]{ (unsigned int)lista.getIndexAtual() , (unsigned int)lista.getIndexAtual() + 1 };
							this->acoesFeitas.empilhar(Acao(txt, ACAO_REMOVE, posY, 2, this->getACPx()));

							free(txt);
							free(posY);

							// fim da acao registrada
							lista[lista.getIndexAtual() - 1] = anteAux + aux;
							lista.removaAtual();
							indiceAtual = anteAux.length();

							if (lista.getIndexAtual() != lista.length() - 1 && topo == 0) // se não for o último e o topo é o primeiro					
								gotoxy(indiceAtual, getACPy()-1);
							else
							{
								gotoxy(indiceAtual, getACPy());
								topo--;
								base--;
							}
						}
						else if (anteAux.length() < MAXIMO_STRING)
						{
							if (this->acoesFeitas.ehVazia() || this->acoesFeitas.getTopo().getDado().getPosY(0) != this->getACPy())
							{
								String *txt = new String[2]{lista.getAtual(), lista[lista.getIndexAtual() + 1]};
								unsigned int *posY = new unsigned int[2]{((unsigned int)lista.getIndexAtual()), ((unsigned int)lista.getIndexAtual() + (unsigned int)1)};
								this->acoesFeitas.empilhar(Acao(txt, ACAO_REMOVE, posY, 2, getACPx()));

								free(txt);
								free(posY);
							}

							// Fim da acao
							int qtasPegar = MAXIMO_STRING - anteAux.length(); // acha quantas cabem na string de cima
							lista[lista.getIndexAtual() - 1] = (anteAux + aux.deletar(0, qtasPegar)).substr(0, 78); // adiciona na string de cima quantas foram deletadas

							lista[lista.getIndexAtual()] = aux; // atualiza o atual com a string que teve uma parte deletada
							indiceAtual = anteAux.length(); // atualiza o lugar do cursor

							gotoxy(indiceAtual, getACPy() - 1); // volta para o anterior na tela
							lista.voltar();
						}
						else
						{
							// "aaaa"
							// "bbbb"
							// "aaab"
							// "bbb"
							char primeiroDaAtual = lista[lista.getIndexAtual()].deleteCharAt(0);
							lista[lista.getIndexAtual()-1].deleteCharAt(lista[lista.getIndexAtual() - 1].length()-1);
							lista[lista.getIndexAtual() - 1].inserir(primeiroDaAtual);

							indiceAtual = MAXIMO_STRING - 1;
							gotoxy(indiceAtual, getACPy() - 1);
							lista.voltar();
						}
					}
				}
				else
				{

					if (this->acoesFeitas.ehVazia() || this->acoesFeitas.getTopo().getDado().getPosY(0) != this->getACPy())
						this->acoesFeitas.empilhar(Acao(lista.getAtual(), ACAO_REMOVE, getACPy(), getACPx()));

					aux.deleteCharAt(--indiceAtual);
					lista.setAtual(aux);
					precisaPrintar = false;
					gotoxy(0, getACPy());
					cout << aux + (String(" ") * (MAXIMO_STRING - aux.length()));
					gotoxy(indiceAtual, getACPy());
				}
			}
			else if (c == CTRL_Z)
			{
				if (!this->acoesFeitas.ehVazia()) indiceAtual = this->CtrlZ(this->acoesFeitas.desempilhar().getDado()); 
				//desempilha dos feitos pros desfeitos
			}
			else if (c == CTRL_Y)
			{
				if (!this->acoesDesfeitas.ehVazia()) indiceAtual = this->CtrlY(this->acoesDesfeitas.desempilhar().getDado()); 
				//desempilha dos desfeitos pros feitos
			}
			else if (c == ENTER)
			{
				if (indiceAtual == lista.getAtual().length())
				{
					lista.inserirDepois(String());
					lista.avancar();
				}
				else if (indiceAtual == 0)
				{
					lista.inserirAntes(String());
				}
				else
				{
					String temAMais = lista[lista.getIndexAtual()].deletar(indiceAtual, lista.getAtual().length() - indiceAtual);
					lista.inserirDepois(temAMais);
					lista.avancar();
				}
				indiceAtual = 0;
				gotoxy(indiceAtual, getACPy() + 1);
			}
			else if (c == ESC)
			{
				this->ClearScreen();
				char opcao = ' ';

				cout << "> Deseja sair do arquivo?(Y/[N])" << endl << "> ";
				cin >> opcao;

				if (opcao == 'y' || opcao == 'Y')
				{
					opcao = ' ';

					cout << "> Deseja salvar o arquivo?(Y/[N])" << endl << "> ";
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
			else if (c == TAB)
			{
				inserirNaAtual(' ', indiceAtual, precisaPrintar);
				inserirNaAtual(' ', indiceAtual, precisaPrintar);
				inserirNaAtual(' ', indiceAtual, precisaPrintar);
				inserirNaAtual(' ', indiceAtual, precisaPrintar);
			}
		}
	}
}

void NotepadCPP::inserirNaAtual(char c, int &indiceAtual, bool &precisaprintar)
{
	String aux = lista.getAtual();
	if (aux.length() >= MAXIMO_STRING) // máximo da string já alcançada
	{
		if (indiceAtual == lista.getAtual().length())
		{
			if (lista.getIndexAtual() == lista.length() - 1)
				lista.inserirNoFinal(String());

			lista.avancar();
			indiceAtual = 0;

			inserirNaAtual(c, indiceAtual, precisaprintar);
			precisaprintar = true;

			if (!(lista.getIndexAtual() == lista.length() - 1))
				gotoxy(indiceAtual, getACPy() + 1);
		}
		else
		{
			char reserva = lista[lista.getIndexAtual()].deleteCharAt(lista.getAtual().length()-1);
			lista[lista.getIndexAtual()].inserir(c, indiceAtual++);

			if (lista.getIndexAtual() == lista.length() - 1)
			{
				lista.inserirNoFinal(String());
				topo++;
				base++;
			}
			lista.avancar();

			int r = 0;
			inserirNaAtual(reserva, r, precisaprintar);
			lista.voltar();

			gotoxy(indiceAtual, getACPy());
			precisaprintar = true;
		}
	}
	else
	{
		aux.inserir(c, indiceAtual++);
		precisaprintar = false;
		int y = getACPy();
		gotoxy(0, y);
		cout << aux + (String(" ") * (MAXIMO_STRING - aux.length()));
		gotoxy(indiceAtual, y);

		if (this->acoesFeitas.ehVazia() || this->acoesFeitas.getTopo().getDado().getPosY(0) != this->getACPy()) 
		    this->acoesFeitas.empilhar(Acao(lista.getAtual(), ACAO_ADICIONAR, getACPy(), getACPx()));

		this->lista.setAtual(aux);
	}
}

void NotepadCPP::deletarAtual(const int &indiceAtual, bool &precisaPrintar)
{
	if (indiceAtual == lista.getAtual().length()) // truncar as linhas
	{
		if (lista.getAtual().length() + lista[lista.getIndexAtual() + 1].length() > MAXIMO_STRING) // não vai truncar completamente
		{
			int qtosCabem = MAXIMO_STRING - lista.getAtual().length();
			String truncada = lista.getAtual() + lista[lista.getIndexAtual() + 1].substr(0, qtosCabem);

			String* txt = new String[2]{ lista.getAtual(), lista[lista.getIndexAtual() + 1] };
			unsigned int* posY = new unsigned int[2]{ ((unsigned int)lista.getIndexAtual()), ((unsigned int)lista.getIndexAtual() + (unsigned int)1) };
			this->acoesFeitas.empilhar(Acao(txt, ACAO_REMOVE, posY, 2, this->getACPx()));

			free(txt);
			free(posY);

			lista[lista.getIndexAtual()] = truncada;
			lista[lista.getIndexAtual() + 1] = lista[lista.getIndexAtual() + 1].substr(qtosCabem, lista.getAtual().length()-1 - qtosCabem);

			// Adicionar Acao de Deletar com 2 Strings alteradas
		}
		else
		{
			if (this->acoesFeitas.ehVazia() || this->acoesFeitas.getTopo().getDado().getPosY(0) != this->getACPy())
			{
				String *txt = new String[2]{lista.getAtual(), lista[lista.getIndexAtual() + 1]};
				unsigned int *posY = new unsigned int[2]{((unsigned int)lista.getIndexAtual()), ((unsigned int)lista.getIndexAtual() + (unsigned int)1)};
				this->acoesFeitas.empilhar(Acao(txt, ACAO_REMOVE, posY, 2, getACPx()));

				free(txt);
				free(posY);
			}
			String truncada = lista.getAtual() + lista[lista.getIndexAtual() + 1];
			lista.removaDepois();
			lista[lista.getIndexAtual()] = truncada;
		}
	}
	else
	{
		if (this->acoesFeitas.ehVazia() || this->acoesFeitas.getTopo().getDado().getPosY(0) != this->getACPy())
			this->acoesFeitas.empilhar(Acao(lista.getAtual(), ACAO_REMOVE, getACPy(), getACPx()));

		lista[lista.getIndexAtual()].deleteCharAt(indiceAtual);
		String aux = lista[lista.getIndexAtual()];

		precisaPrintar = false;
		gotoxy(0, getACPy());
		cout << aux + (String(" ") * (MAXIMO_STRING - aux.length()));
	}
}