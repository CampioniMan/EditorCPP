// EditorCPP2015.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "String.h"
#include "Acao.h"
#include "ListaDuplaCirc.h"
#include "Pilha.h"
#include "NotepadCPP.h"
#include <thread>

using namespace std;

typedef struct
{
	int tam;
	String *valor;
}Vetor;

String file_path;
Vetor opcoes;


void dormir(unsigned int mili)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(mili));
}

void inicializarVariaveis()
{
	//setlocale(LC_ALL, ""); // Restore the CRT.
	cout << "Carregando módulos..." << endl;
	NotepadCPP::setTamanho(80, 25);
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

int main()
{
	inicializarVariaveis();
	bool valido = false;
	char opcao = ' ';
	while (!valido)
	{
		NotepadCPP::ClearScreen();
		cout << "Bem vindo ao editor de texto CampStar" << endl;
		cout << "-------------------------------------" << endl;
		cout << "   Digite 'h' para mais informações  " << endl;
		switch (opcao = selecionaMenu())
		{
		case '1':
			NotepadCPP::ClearScreen();
			cout << "Você selecionou a opção '1'\n";
			cout << "Digite o diretório do arquivo que deseja-se abrir:";
			//cin >> file_path;
			file_path = "C:\\Temp\\trabalho.txt";
			if (NotepadCPP::fexists(file_path))
			{
				NotepadCPP editar(file_path, NotepadCPP::ABRIR_EXISTENTE);
				editar.run();
			}
			opcao = ' ';
			break;
		case '2':
			NotepadCPP::ClearScreen();
			cout << "Você selecionou a opção '2'\n";
			cout << "Digite a pasta do arquivo de saída:";
			cin >> file_path;
			if (!NotepadCPP::fexists(file_path))
			{
				NotepadCPP editar(file_path, NotepadCPP::CRIAR_NOVO);
				editar.run();
			}
			else
			{
				cout << "Deseja sobreescrever o arquivo(Y/[N])?\n";
				String resposta = "N";
				cin >> resposta;
				if (resposta == "Y")
				{
					NotepadCPP editar(file_path, NotepadCPP::ABRIR_SOBREESCREVER);
					editar.run();
				}
			}
			opcao = ' ';
			break;
		case '3':
			cout << '\n' << "Você selecionou a opção '3'\n";
			valido = true;
			opcao = ' ';
			break;
		case 'h':
			cout << '\n';
			cout << "a. Backspace apaga o caracter anterior." << endl;
			dormir(100);
			cout << "b. Delete apaga o caracter atual." << endl;
			dormir(100);
			cout << "c. Page down para descer bastante." << endl;
			dormir(100);
			cout << "d. Page up para subir bastante." << endl;
			dormir(100);
			cout << "e. Utilize as setas para mover o cursor." << endl;
			dormir(100);
			cout << "f. ESC sai do modo de edição." << endl;
			dormir(100);
			cout << "g. Ctrl+Z retrocede o arquivo ao estado anterior." << endl;
			dormir(100);
			cout << "h. Ctrl+Y volta o arquivo ao estado editado." << endl;
			dormir(100);
			cout << "Pressione qualquer tecla para continuar" << endl;
			_getch();
			break;
		default:
			opcao = ' ';
			continue;
		}
	}
	return esperaEnter();
}

