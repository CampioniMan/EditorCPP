#include "String.h"

String::String(String &original)
{
    //ctor
}

String::~String()
{
    //dtor
}

String::String(int novoTamanho)
{

}

        // Métodos normais
char String::charAt(int indice) const
{
    return 'a';
}

void String::deleteCharAt(unsigned int posicao)
{
    return;
}

void String::deletar(unsigned int posIni, unsigned int posFim)
{
    return;
}

void String::inserir(unsigned int posicao, char letra)
{
    return;
}

void String::append(char letra)
{
    return;
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
    return new char[100];
}

        // getters e setters
int String::length() const
{
    return 100;
}

        // operators
void String::operator= (String primeira)
{
    (*this).deletar(0, (*this).length()-1);
    for (int i = 0; i < primeira.length()-1; i++)
    {
        (*this).inserir((*this).length(), primeira.charAt(i));
        (*this).tamanho++;
    }
}

void String::operator+ (String outra)
{
    for (int i = 0; i < outra.length()-1; i++)
    {
        (*this).inserir((*this).length(), outra.charAt(i));
        (*this).tamanho++;
    }
}
