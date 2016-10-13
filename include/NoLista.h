#ifndef NOLISTA_H
#define NOLISTA_H
#include "String.h"

class NoLista
{
    public:
        NoLista();
        NoLista(String novoDado);
        NoLista(const String &novoDado, NoLista* Proximo, NoLista* Anterior);
        virtual ~NoLista();

        NoLista* getProximo() const;
        String getDado() const;
        NoLista* getAnterior() const;
        void setProximo(NoLista *NovoProx);
        void setDado(String novoDado);
        void setAnterior(NoLista *NovoAnte);
        void setProximo(NoLista NovoProx);
        void setAnterior(NoLista NovoAnte);
        static NoLista* NoListaNull();
    protected:
        String dado;
        NoLista* ante;
        NoLista* prox;
    private:
};

#endif // NOLISTA_H
