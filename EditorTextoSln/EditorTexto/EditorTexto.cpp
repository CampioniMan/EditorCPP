// EditorTexto.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "String.h"
#include "Acao.h"
#include "ListaDuplaCirc.h"
#include "Pilha.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int c = 0;
	ListaDuplaCirc<String>* lista;
	lista = new ListaDuplaCirc<String>();

	String nova("egrhgehi");
	nova.inserir('d');
	lista->inserir(nova);

	cout << lista->getValorPrimeiro() << endl;

	
	cin >> c;
	//unsigned char oi = '²';
	return 0;
}

