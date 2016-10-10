#include "String.h"
#ifndef ACAO_H
#define ACAO_H

class Acao
{
    public:
        Acao(String &novaPalavra, String &novoTipo, unsigned int novoX, unsigned int novoY);
        Acao(const Acao &original);
        virtual ~Acao();

        Acao* clone() const;
        void operator= (Acao primeira);

        String getPalavra() const;
        String getTipo() const;
        unsigned int getX() const;
        unsigned int getY() const;

        void setPalavra(String palavra);
        void setTipo(String tipo);
        void setX(unsigned int posX);
        void setY(unsigned int posX);
    protected:
        String palavraMudou, tipo;
        unsigned int X, Y;
    private:
};
#endif // ACAO_H
