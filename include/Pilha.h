#ifndef PILHA_H
#define PILHA_H
#include <Acao.h>
#include <cstddef>
#include <iostream>

class Pilha
{
    public:
        // Construtores
        Pilha(unsigned int tamanhoMax);
        Pilha(const Pilha &original);
        virtual ~Pilha();
        Pilha* clone() const;

        // Métodos normais
        Acao empilhar(Acao feita); // remove a base da pilha e empilha o novo
        Acao desempilhar();
        bool ehCheia() const;
        bool ehVazia() const;

        // getters e setters
        Acao getTopo() const;
        int length() const;

        void operator= (Pilha *primeira) const;
    protected:
        Acao valorDe(const int &indice) const;
    private:
        Acao* acoes;
        int tamanhoMax;
        int tamanhoAtual;

};

#endif // PILHA_H
