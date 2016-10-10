#include "Acao.h"
#include "String.h"

Acao::Acao(String &novaPalavra, String &novoTipo, unsigned int novoX, unsigned int novoY) : palavraMudou(novaPalavra), tipo(novoTipo), X(novoX), Y(novoY)
{

}

Acao::Acao(const Acao &original) : palavraMudou(original.palavraMudou), tipo(original.tipo), X(original.X), Y(original.Y)
{
    (*this).palavraMudou = original.palavraMudou;
    (*this).tipo = original.tipo;
    (*this).X = original.X;
    (*this).Y = original.Y;
}

Acao::~Acao()
{
    //dtor
}

Acao* Acao::clone() const
{
    return new Acao(*this);
}
