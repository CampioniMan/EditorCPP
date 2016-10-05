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
    if (indice < 0 || indice > (*this).length()-2)
        return (*this).null;
    return (*this).minhaString[indice];
}

void String::deleteCharAt(unsigned int posicao)
{
    if (posicao < 0) // não pode ser menor que 0
        return;

    for (int i = posicao; i < (*this).length()-2;) // mexendo, de posicao pra frente, 1 para trás
        (*this).minhaString[i] = (*this).minhaString[++i];

    (*this).minhaString[(*this).length()-2] = (*this).null; // deixando o último nulo
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
    (*this).deletar(0, (*this).length()-2);
    for (int i = 0; i < primeira.length()-2; i++)
    {
        (*this).inserir((*this).length(), primeira.charAt(i));
    }
}

void String::operator+ (String outra)
{
    for (int i = 0; i < outra.length()-2; i++)
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

bool operator== (String primeira, String segunda)
{
    return primeira.length() == segunda.length();
}

bool operator!= (String primeira, String segunda)
{
    return primeira.length() != segunda.length();
}

