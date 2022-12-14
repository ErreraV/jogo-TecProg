#include "Octorok.h"

using namespace entidades;
using namespace personagens;

Octorok::Octorok(int vidas, Vector2f p) :
	Inimigo(vidas, Vector2f(50.,50.), p, 22)
{
	textura.loadFromFile("sprites/octorok.png");
	body->setTexture(&textura);

	pedra = new Projetil();

	velocidade = Vector2f(0.088, 0.);

	direcao = +1;
}

Octorok::~Octorok()
{
	delete pedra;
}

void Octorok::move() {
	posicao.x += velocidade.x;
	posicao.y += velocidade.y;
	body->setPosition(posicao);
	if (!pedra->getAtivo() && recarga<=0 ) {
		atira();
		recarga = 1000;
	}
	recarga--;
	velocidade.y -= 0.001f;
	gravidade();
}
void Octorok::atira() {
	if (direcao > 0){		
		pedra->setX(posicao.x + tamanho.x+ 2);
		pedra->setY(posicao.y + 20);
		pedra->setVelocidadeX(1.f);
	}
	else {
		pedra->setX(posicao.x - (2 + pedra->getLargura()));
		pedra->setY(posicao.y + 20);
		pedra->setVelocidadeX(-1.f);
	}
	pedra->setVelocidadeY(0);
	pedra->setAtivo(true);
}

void Octorok::setProjetil(Projetil* p) {
	
	pedra = p;
}

Projetil* Octorok::getProjetil() {
	return pedra;
}

void Octorok::setRecarga(int rec)
{
	recarga = rec;
}

void Octorok::gravar() {
	ofstream gravador("save/octorok.dat", ios::app);

	if (!gravador)
	{
		return;
	}
	gravador  << endl<< numVidas << ' '
			 << posicao.x << ' '
			 << posicao.y << ' '
			 << velocidade.x << ' '
			 << velocidade.y << ' '
			 << recarga;
	gravador.close();
	pedra->gravar();

}


Lista<Octorok>* Octorok::recuperar() {
	ifstream recuperador("save/octorok.dat", ios::in);
	Lista<Octorok>* l = new Lista<Octorok>;
	int vidas;
	Vector2f p;
	Vector2f v;
	int rec;
	if (!recuperador) {
		return nullptr;
	}
	while (!recuperador.eof()) {
		recuperador >> vidas >> p.x >> p.y >> v.x >> v.y >> rec;

		Octorok* temp = new Octorok(vidas, p);
		temp->setVelocidade(v);
		temp->setRecarga(rec);
		l->push(temp);
	}
	recuperador.close();
	return l;


}












