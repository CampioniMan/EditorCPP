#include <iostream>
<<<<<<< 6e832f5b91867dd6dd30ba64f6f0b3308aefe79b
#include <stdlib.h>
=======
#include <stdio.h>
>>>>>>> String melhorada
#include "String.h"
#include "Acao.h"
#include "ListaDuplaCirc.h"
#include "Pilha.h"

using namespace std;
//using conio.h;

int main()
{
<<<<<<< 6e832f5b91867dd6dd30ba64f6f0b3308aefe79b
    char *c = new char[5]();

    *(c + 0) = 'a';
    *(c + 1) = 'b';

    //cin >> c;

    //if( *c == 22 )
        cout << *(c + 0) << endl;
        cout << *(c + 1) << endl;

    //int trem;
    //trem = 4;
    //String oi(trem);
    //cout << "Aperte enter para encerrar o programa" << endl;
=======
    unsigned int i;
    i = 1;
    cout << i << endl;
    String *ola = new String(i);
>>>>>>> String melhorada
    return 0;
}

/*
*  -sobe linha (normalmente, seta)
*  -desce linha (normalmente, seta)
*  -vai para a esquerda (normalmente, seta)
*  -vai para a direita (normalmente, seta)
*  -sobe p�gina (normalmente, PAGE UP)
*  -desce p�gina (normalmente, PAGE DOWN)
*  -vai para o inicio da linha (normalmente, HOME)
*  -vai para o fim da linha (normalmente, END)
*  -apaga char no cursor (normalmente, DELETE)
*  -apaga char antes do cursor (normalmente, BACKSPACE)
*  -desfazer (normalmente, CONTROL Z)
*  -refazer (normalmente, CONTROL Y)
*  -salvar (normalmente, CONTROL S)
*  -salvar como
*     perguntar se quer sobrescrever arquivo existente
*  -sair (normalmente, ESC)
*     perguntar se quer sair sem salvar
*/
