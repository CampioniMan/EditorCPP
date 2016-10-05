#include "String.h"
#include <stdio.h>

String::String(String &original)
{
    //ctor
}

String::String(int novoTamanho)
{

}

String::~String()
{
    //dtor
}

        // Métodos normais
char String::charAt(int indice) const
{
    if (indice < 0 || indice > (*this).length()-1)
        return (*this).null;
    return (*this).minhaString[indice];
}

void String::deleteCharAt(unsigned int posicao)
{
    if (posicao < 0) // não pode ser menor que 0
        return;

    for (int i = posicao; i < (*this).length()-1;) // mexendo, de posicao pra frente, 1 para trás
        (*this).minhaString[i] = (*this).minhaString[++i];

    (*this).minhaString[(*this).length()-1] = (*this).null; // deixando o último nulo
    (*this).tamanho--;
}

void String::deletar(unsigned int posIni, unsigned int posFim)
{
    if (posIni < 0 || posIni > (*this).length()-1 || posFim < 0 || posFim > (*this).length()-1)
        return;


    if (posIni > posFim) // pode estar ao contrário
    {
        unsigned int aux = posIni;
        posIni = posFim;
        posFim = aux;
    }
    unsigned int diff = posFim - posIni;
    /*
    while (diff != 0)
    {
        deleteCharAt(posIni+diff);
    }
    */
    for (int i = posIni; i+diff <= (*this).length();i++) // mexendo, de posicao pra frente, 1 para trás
        (*this).minhaString[i] = (*this).minhaString[i+diff];

    for (int i = posFim; i <= (*this).length();i++) // deixando os últimos nulos
        (*this).minhaString[posFim] = (*this).null;
    (*this).tamanho -= diff;

}

void String::inserir(unsigned int posicao, char letra)
{
    (*this).tamanho++;
}

void String::inserir(char letra)
{
    (*this).tamanho++;
}

void String::replace(unsigned int posicao, char letra)
{
    return;
}

void String::destroy()
{
    return;
}

        // Apocalipticos
char* String::toString() const
{
    char* aux = new char[(*this).length()-1];
    for (int i = 0; i <= (*this).length(); i++)
        aux[i] = (*this).charAt(i);
    return aux;
}

        // getters e setters
int String::length() const
{
    return (*this).tamanho;
}

        // operators
void String::operator= (String primeira)
{
    (*this).deletar(0, (*this).length()-1);
    for (int i = 0; i <= primeira.length(); i++)
    {
        (*this).inserir((*this).length(), primeira.charAt(i));
    }
}

void String::operator+ (String outra)
{
    for (int i = 0; i <= outra.length(); i++)
    {
        (*this).inserir((*this).length(), outra.charAt(i));
    }
}

bool operator< (String primeira, String segunda)
{
    return primeira.length() < segunda.length();
}

bool operator> (String primeira, String segunda)
{
    return primeira.length() > segunda.length();
}

bool operator<= (String primeira, String segunda)
{
    return primeira.length() <= segunda.length();
}

bool operator>= (String primeira, String segunda)
{
    return primeira.length() >= segunda.length();
}

bool operator== (String primeira, String segunda) // verificar conteúdo também
{
    return primeira.length() == segunda.length();
}

bool operator!= (String primeira, String segunda) // verificar conteúdo também
{
    return primeira.length() != segunda.length();
}

