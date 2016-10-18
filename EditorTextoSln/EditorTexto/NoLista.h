#pragma once
template <class Tipo>
class NoLista
{
public:
	NoLista();
	NoLista(const Tipo &novoDado);
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

template <class Tipo>
NoLista<Tipo>::NoLista() : dado()
{

}

template <class Tipo>
NoLista<Tipo>::NoLista(const Tipo &novoDado) : dado(novoDado)
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
