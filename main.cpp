#include <iostream>
#include "String.h"
#include "Acao.h"
#include "ListaDuplaCirc.h"
#include "Pilha.h"

using namespace std;
//using conio.h;

int main()
{
    int trem;
    trem = 4;
    String oi(trem);
    cout << "Aperte enter para encerrar o programa" << endl;
    return 0;
}

/*
*  -sobe linha (normalmente, seta)
*  -desce linha (normalmente, seta)
*  -vai para a esquerda (normalmente, seta)
*  -vai para a direita (normalmente, seta)
*  -sobe página (normalmente, PAGE UP)
*  -desce página (normalmente, PAGE DOWN)
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
