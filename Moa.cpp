#include "Moa.h"

using namespace entidades;
using namespace personagens;

Moa::Moa(int vidas, Vector2f p) :
	Inimigo(vidas, Vector2f(50., 50.), p, 22)
{
	textura.loadFromFile("sprites/moa1.png");
	body->setTexture(&textura);
	body->setFillColor(Color::Red);
	velocidade = Vector2f(0.088, 0.);
	invisivel = -4000;
}

Moa::~Moa()
{
}

void Moa::move() {
	invisivel--;
	if (invisivel < 0) {
		body->setFillColor(Color::Red);
	}
	if (invisivel <= -8000) {
		body->setFillColor(Color::Transparent);
		invisivel = 2000;
	}
	posicao.x += velocidade.x;
	posicao.y += velocidade.y;
	body->setPosition(posicao);
	velocidade.y -= 0.001f;
	gravidade();
}

void Moa::gravar() {
	ofstream gravador("save/moa.dat", ios::app);

	if (!gravador)
	{
		return;
	}
	gravador << endl<< numVidas << ' '
			 << posicao.x << ' '
			 << posicao.y << ' '
			 << velocidade.x << ' '
			 << velocidade.y ;
	gravador.close();
}

Lista<Moa>* Moa::recuperar() {
	ifstream recuperador("save/moa.dat", ios::in);
	Lista<Moa>* l = new Lista<Moa>;
	int vidas;
	Vector2f p;
	Vector2f v;
	if (!recuperador) {
		return nullptr;
	}
	while (!recuperador.eof()) {
		recuperador >> vidas >> p.x >> p.y >> v.x >> v.y;

		Moa* temp = new Moa(vidas, p);
		temp->setVelocidade(v);
		l->push(temp);
	}
	recuperador.close();
	return l;


}