#pragma once
template <class Tipo>
class NoLista
{
public:
	NoLista();
	NoLista(Tipo novoDado);
	NoLista(const Tipo &novoDado, NoLista* Proximo, NoLista* Anterior);
	NoLista(const NoLista<Tipo> &novoDado);
	virtual ~NoLista();

	NoLista<Tipo>* getProximo() const;
	Tipo getDado() const;
	NoLista<Tipo>* getAnterior() const;
	void setProximo(NoLista<Tipo> *NovoProx);
	void setDado(Tipo novoDado);
	void setAnterior(NoLista<Tipo> *NovoAnte);
	void setProximo(NoLista<Tipo> NovoProx);
	void setAnterior(NoLista<Tipo> NovoAnte);
	static NoLista<Tipo>* NoListaNull();
protected:
	Tipo dado;
	NoLista<Tipo>* ante;
	NoLista<Tipo>* prox;
private:
};

