// EditorTexto.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "String.h"
#include "Acao.h"
#include "ListaDuplaCirc.h"
#include "Pilha.h"
#include <stdio.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int c = 0;
	ListaDuplaCirc<String>* lista;
	lista = new ListaDuplaCirc<String>();

	String nova("tre");
	String novissima(nova);
	//char* c[] = (char**)MK_FP(0xB800, 0X0000);
	nova.inserir('d');
	nova.inserir('e');
	nova.inserir('f');

	lista->inserirNoFinal(novissima);
	lista->inserirNoFinal(nova);
	//lista->remover(novissima);

	cout << lista->length() << endl;
	cout << ":" << lista[0][1] << ":" << endl;
	
	cin >> c;
	return 0;
}

