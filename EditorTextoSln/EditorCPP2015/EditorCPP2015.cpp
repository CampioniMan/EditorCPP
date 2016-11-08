// EditorCPP2015.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "String.h"
#include "Acao.h"
#include "ListaDuplaCirc.h"
#include "Pilha.h"
#include <iomanip>
#include <sstream>
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

inline bool fexists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
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
	//setlocale(LC_ALL, ""); // Restore the CRT.
	cout << "Carregando módulos..." << endl;
	opcoes.tam = 3;
	opcoes.valor = new String[opcoes.tam]();
	opcoes.valor[0] = "Abrir um arquivo";
	opcoes.valor[1] = "Criar um arquivo";
	opcoes.valor[2] = "Sair";
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
	arq.open((char*)dir);
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
	arq.open((char*)dir);
	if (!arq.is_open())
		return false;

	String linha;
	std::string line;
	while (!arq.eof())
	{
		std::getline(arq, line);
		lst->inserirNoFinal(line);
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
			system("cls");
			cout << "Você selecionou a opção '1'\n";
			cout << "Digite o diretório do arquivo que deseja-se abrir:";
			cin >> file_path;
			if (abrirArquivo(file_path, &lista))
			{
				system("cls");
				lista.iniciarPercursoSequencial();
				while (lista.podePercorrer())
					cout << lista.getValorAtual() + '\n';
				gotoxy(0, 0);
				system("notepad "+file_path);
				//dormir(15000);
			}
			opcao = ' ';
			break;
		case '2':
			system("cls");
			cout << "Você selecionou a opção '2'\n";
			cout << "Digite a pasta do arquivo de saída:";
			cin >> file_path;
			if (!fexists(file_path))
				valido = true;
			else
			{
				cout << "Deseja sobreescrever o arquivo(Y/[N])?\n";
				String resposta = "N";
				cin >> resposta;
				if (resposta == "Y")
				{
					system("notepad "+file_path);
				}
			}
			opcao = ' ';
			break;
		case '3':
			cout << '\n' << "Você selecionou a opção '3'\n";
			valido = true;
			opcao = ' ';
			break;
		default:
			opcao = ' ';
			continue;
		}
	}

	esperaEnter();
	return esperaEnter();
}

