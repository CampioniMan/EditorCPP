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

	String nova("tre");
	String novissima(nova);

	novissima.inserir('d');
	novissima.inserir('e');
	novissima.inserir('f');
	cout << novissima.getTamanhoMax() << endl;
	cout << novissima.length() << endl;
	lista->inserir(novissima);
	lista->inserir(nova);
	lista->remover(novissima);

	cout << ":" << lista->getValorPrimeiro() << ":" << endl;

	
	cin >> c;
	return 0;
}

