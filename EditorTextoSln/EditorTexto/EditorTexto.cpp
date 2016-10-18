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
	int esperador = 0;

	ListaDuplaCirc<String>* lista;
	lista = new ListaDuplaCirc<String>();

	String nova("trem");

	
	cout << "String = " << nova << '\n';

	

	//unsigned char oi = '²';
	//printf("%i", oi);
	cin >> esperador;
	return 0;
}

