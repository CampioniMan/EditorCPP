#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "NoLista.h"

NoLista::NoLista() : dado()
{

}
NoLista::NoLista(String novoDado) : dado(novoDado)
{

}

NoLista::NoLista(const String &novoDado, NoLista* Proximo, NoLista* Anterior) : dado(novoDado), prox(Proximo), ante(Anterior)
{

}

NoLista::~NoLista()
{

}

NoLista* NoLista::getProximo() const
{
    return prox;
}

String NoLista::getDado() const
{
    return dado;
}

NoLista* NoLista::getAnterior() const
{
    return ante;
}

void NoLista::setProximo(NoLista *NovoProx)
{
    this->prox = NovoProx;
}

void NoLista::setDado(String novoDado)
{
    this->dado = novoDado;
}

void NoLista::setAnterior(NoLista *NovoAnte)
{
    this->ante = NovoAnte;
}

void NoLista::setProximo(NoLista NovoProx)
{
    *this->prox = NovoProx;
}

void NoLista::setAnterior(NoLista NovoAnte)
{
     *this->ante = NovoAnte;
}

NoLista* NoLista::NoListaNull()
{
    NoLista* nulo = NULL;
    return nulo;
}
