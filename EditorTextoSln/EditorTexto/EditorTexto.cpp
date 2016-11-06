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

void pulaLinha(unsigned int qtas)
{
	for (int i = 0; i < qtas; i++)
		cout << "\n" << endl;
}

int esperaEnter()
{
	cout << "Pressione [ENTER] para continuar" << endl;
	char carac = ' ';
	scanf_s("%c", &carac);
	return 0;
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
	String s1 = String("Pedro"), s2 = String("Daniel"), s3 = String("Regis"), s4 = String("^Z"), *s5 = (String*)malloc(3 * sizeof(String));
	*(s5 + 0) = s1;
	*(s5 + 1) = s2;
	*(s5 + 2) = s3;

	//cout << (s5 + 0)->toString() << (s5 + 1)->toString() << (s5 + 2)->toString() << endl;

	Acao a = Acao(s5, 3, s4, 5, 2),
		 b = *a.clone(), 
		 c = a;

	cout << a.toString() << endl;
	//a.setX(90);
	a.setPalavra("Alex", 2);
	pulaLinha(1);
	///////////////////////////////////////////////////////////////////////////////////
	cout << b.toString() << endl;
	//b.setX(90);
	pulaLinha(1);
	///////////////////////////////////////////////////////////////////////////////////
	cout << c.toString() << endl;
	//c.setX(90);
	pulaLinha(1);
	///////////////////////////////////////////////////////////////////////////////////
	return esperaEnter();
}

