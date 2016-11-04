// EditorTexto.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "String.h"
#include "Acao.h"
#include "ListaDuplaCirc.h"
#include "Pilha.h"
#include <thread>
#include <fstream>

using namespace std;

typedef struct
{
	int tam;
	String *valor;
}Vetor;

String file_path;
ListaDuplaCirc<String> lista;
std::fstream arq;
Vetor opcoes;


void dormir(unsigned int mili)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(mili));
}

void inicializarVariaveis()
{
	cout << "Carregando modulos..." << endl;
	opcoes.tam = 2;
	opcoes.valor = new String[2]();
	opcoes.valor[0] = String("Abrir um arquivo");
	opcoes.valor[1] = String("Sair");
	//SetConsoleTitle(TEXT("CampStar"));
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

int _tmain(int argc, _TCHAR* argv[])
{
	/*
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
			cout << "Digitou 1\n";
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
	*/

	//Pilha oi = Pilha(2);
	String s1 = String("Pedro"), s2 = String("^Z"), *s3 = (String*)malloc(3 * sizeof(String));
	s3[0] = s1;
	s3[1] = s2;
	Acao a = Acao(*s3, 3, s2, 5, 2);

	cout << a.toString() << endl;

	int c = 0;
	cin >> c;
	return 0;
}

