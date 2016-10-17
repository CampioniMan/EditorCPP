#include "iostream"
#include "stdlib.h"
#include "stdio.h"
#include "NoLista.h"
#include "String.h"
#include "stdafx.h"
template <class Tipo>
NoLista<Tipo>::NoLista() : dado()
{

}

template <class Tipo>
NoLista<Tipo>::NoLista(Tipo novoDado) : dado(novoDado)
{

}

template <class Tipo>
NoLista<Tipo>::NoLista(const Tipo &novoDado, NoLista* Proximo, NoLista* Anterior) : dado(novoDado), prox(Proximo), ante(Anterior)
{

}

template <class Tipo>
NoLista<Tipo>::NoLista(const NoLista<Tipo> &novoDado) : dado(novoDado.getDado()), prox(novoDado.getProximo()), ante(novoDado.getAnterior())
{

}

template <class Tipo>
NoLista<Tipo>::~NoLista()
{

}

template <class Tipo>
NoLista<Tipo>* NoLista<Tipo>::getProximo() const
{
    return prox;
}

template <class Tipo>
Tipo NoLista<Tipo>::getDado() const
{
    return dado;
}

template <class Tipo>
NoLista<Tipo>* NoLista<Tipo>::getAnterior() const
{
    return ante;
}

template <class Tipo>
void NoLista<Tipo>::setProximo(NoLista *NovoProx)
{
    this->prox = NovoProx;
}

template <class Tipo>
void NoLista<Tipo>::setDado(Tipo novoDado)
{
    this->dado = novoDado;
}

template <class Tipo>
void NoLista<Tipo>::setAnterior(NoLista *NovoAnte)
{
    this->ante = NovoAnte;
}

template <class Tipo>
void NoLista<Tipo>::setProximo(NoLista NovoProx)
{
    *this->prox = NovoProx;
}

template <class Tipo>
void NoLista<Tipo>::setAnterior(NoLista NovoAnte)
{
     *this->ante = NovoAnte;
}

template <class Tipo>
NoLista<Tipo>* NoLista<Tipo>::NoListaNull()
{
    NoLista* nulo = NULL;
    return nulo;
}

template class NoLista<String>;
