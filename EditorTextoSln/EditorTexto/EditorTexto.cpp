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
	ListaDuplaCirc<String> lista;
	lista = ListaDuplaCirc<String>();

	char *oi = "ola";
	String trem(oi);
	String trem2("trem2");
	String nova("nova");
	String novissima("novissima");
	//int * c = (int *)MK_FP(0xB800, 0X0000);

	lista.inserirNoComeco(nova);
	lista.inserirNoFinal(novissima);
	lista.inserirNoFinal(trem);
	lista.inserirNoFinal(trem2);

	cout << lista[2] << endl;

	lista.iniciarPercursoSequencial();
	while (lista.podePercorrer())
		cout << lista.getValorAtual() << endl;

	cout << lista.length() << endl;
	//cout << ":" << lista[0] << ":" << endl;
	
	cin >> c;
	return 0;
}

