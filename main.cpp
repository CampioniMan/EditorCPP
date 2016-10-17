#include "iostream"
#include "stdlib.h"
#include "stdio.h"
#include "ListaDuplaCirc.h"
#include "String.h"

using namespace std;
//using conio.h;

int main()
{
    ListaDuplaCirc<String> oi;


    String oil("gewegw");
    String oi2("rhnhrhrh");
    String oi3("utfyutf");
    oi.inserir(oil);
    oi.inserir(oi2);
    oi.inserir(oi3);

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
