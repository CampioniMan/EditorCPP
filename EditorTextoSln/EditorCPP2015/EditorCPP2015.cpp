// EditorCPP2015.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "String.h"
#include "Acao.h"
#include "ListaDuplaCirc.h"
#include "Pilha.h"
#include <fstream>
#include <ostream>
#include <thread>
#include <conio.h>
#include <windows.h>

void gotoxy(int x, int y)
{
	HANDLE stdOutput;
	COORD pos;

	stdOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(stdOutput, pos);
}

using namespace std;

typedef struct
{
	int tam;
	String *valor;
}Vetor;

String file_path;
ListaDuplaCirc<String> lista;
fstream arq;
Vetor opcoes;
const int MAXIMO_STRING = 80;


void dormir(unsigned int mili)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(mili));
}

void inicializarVariaveis()
{
	setlocale(LC_ALL, ""); // Restore the CRT.
	cout << "Carregando módulos..." << endl;
	opcoes.tam = 2;
	opcoes.valor = new String[2]();
	opcoes.valor[0] = "Abrir um arquivo";
	opcoes.valor[1] = "Sair";
	SetConsoleTitle(TEXT("CampStar"));
	dormir(500);
	cout << "Modulos carregados" << endl; // maligno vai adorar
	dormir(300);
}

char selecionaMenu()
{
	cout << "O que deseja fazer?" << endl;
	for (char i = '1'; i - 49 < opcoes.tam; i++)
	{
		cout << i << ") " << opcoes.valor[i - 49] << endl;
	}
	cout << "Opcao: ";
	String ret;
	cin >> ret;
	return ret[0];
}

void pulaLinha(unsigned int qtas)
{
	for (int i = 0; i < qtas; i++)
		cout << "\n" << endl;
}

void print(String txt, unsigned int pulLi)
{
	cout << txt << endl;
	if (pulLi > 0) pulaLinha(1);
}

void print(unsigned int numb, unsigned int pulLi)
{
	cout << numb << endl;
	if (pulLi > 0) pulaLinha(1);
}

int esperaEnter()
{
	cout << "Pressione [ENTER] para continuar" << endl;
	char carac = ' ';
	fflush(stdin);
	scanf_s("%c", &carac);
	return 0;
}

bool salvarArquivo(const String& dir, ListaDuplaCirc<String> *lst)
{
	ofstream arq = ofstream();
	arq.open(dir);
	if (arq.fail())
		return false;
	lst->iniciarPercursoSequencial();
	while (lst->podePercorrer())
	{
		arq.write(lst->getValorAtual(), lst->getValorAtual().length()*sizeof(char));
	}
	arq.close();
	return true;
}

bool abrirArquivo(const String& dir, ListaDuplaCirc<String> *lst)
{
	ifstream arq = ifstream();
	arq.open(dir);
	if (arq.fail())
		return false;
	String linha;
	while ((arq.read(linha, 2048 * sizeof(char))))
	{
		lst->inserirNoFinal(linha);
	}
	arq.close();
	return true;
}

int main()
{
	inicializarVariaveis();
	int c = 0;
	bool valido = false;
	char opcao = ' ';
	while (!valido)
	{
		system("cls");
		cout << "Bem vindo ao editor de texto CampStar" << endl;
		cout << "-------------------------------------" << endl;
		switch (opcao = selecionaMenu())
		{
		case '1':
			cout << "Você selecionou a opção '1'\n";
			cin >> file_path;
			abrirArquivo(file_path, &lista);
			valido = true;
			break;
		case '2':
			cout << "Digitou 2\n";
			valido = true;
			break;
		default:
			continue;
		}
	}

	switch (opcao)
	{
	default:
		break;
	}
	return esperaEnter();
}

