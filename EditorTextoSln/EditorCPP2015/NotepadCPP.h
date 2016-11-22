#pragma once
#include "ListaDuplaCirc.h"
#include "String.h"
#include "Pilha.h"
#include "Acao.h"
#include <sstream>
#include <fstream>
#include <ostream>
#include <conio.h>
#include <windows.h>

class NotepadCPP
{
public:
	NotepadCPP();
	NotepadCPP(const String& diretorio);
	NotepadCPP(const String& diretorio, const int ehSobre);
	virtual ~NotepadCPP();

	void run();

	static bool fexists(const std::string& name);
	static void ClearScreen();
	static void gotoxy(int x, int y);
	static void setForeGroundAndBackGroundColor(int BackGroundColor);
	static void ssetcolor(WORD color);
	static void hidecursor();
	static bool setTamanho(int width, int height);

	const static int ABRIR_EXISTENTE = 0;
	const static int ABRIR_SOBREESCREVER = 1;
	const static int CRIAR_NOVO = 2;
private:
	bool salvarArquivo(const String& dir);
	bool abrirArquivo(const String& dir);
	bool criarArquivo(const String& dir);
	bool limparArquivo(const String& dir);
	void inserirComRecursion(const char &ASerInserido);
	int primeiraComEspaco(int);
	void printarNaTela();
	int getACPx();
	int getACPy();
	Acao CtrlZ(const ListaDuplaCirc<String> &lst, const Acao &dis);
	Acao CtrlY(const ListaDuplaCirc<String> &lst, const Acao &dis);
	Acao CtrlX(const ListaDuplaCirc<String> &lst, const Acao &dis);
	Acao CtrlC(const ListaDuplaCirc<String> &lst, const Acao &dis);
	Acao CtrlH(const ListaDuplaCirc<String> &lst, const Acao &dis);
	Acao Adicionar(const ListaDuplaCirc<String> &lst, const Acao &dis);
	Acao Remover(const ListaDuplaCirc<String> &lst, const Acao &dis);

	int ehSobreescrever, corFundoAtual, corLetraAtual, topo, base;
	String dir;
	ListaDuplaCirc<String> lista;
	Pilha<Acao> acoesFeitas;
	Pilha<Acao> acoesDesfeitas;
};

