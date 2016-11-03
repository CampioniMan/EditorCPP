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
	
	int i = 123;

	String re("rewrew");
	String str = String(re + i);

	cout << str << endl;
	
	cin >> c;
	return 0;
}

