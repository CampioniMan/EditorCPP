#ifndef PILHA_H
#define PILHA_H
#include <Acao.h>

class Pilha
{
    public:
        // Construtores
        Pilha(int tamanhoMax);
        Pilha(Pilha &original);
        virtual ~Pilha();
        void destroy();

        // Métodos normais
        void empilhar(Acao feita); // remove a base da pilha e empilha o novo
        Acao desempilhar();
        bool ehCheia() const;
        bool ehVazia() const;

        // getters e setters
        Acao espiar() const;
        int length() const;
    protected:
        void empilhar(Acao feita, bool vaiRemoverPrimeiro);
    private:
        Acao* acoes;
        int tamanhoMax;
        int tamanhoAtual;

};

#endif // PILHA_H
