#include "GerenciadorColisoes.h"

using namespace gerenciadores;

GerenciadorColisoes::GerenciadorColisoes(Jogador* player1,Jogador* player2){
	jogador1 = player1;
	jogador2 = player2;
}
GerenciadorColisoes::~GerenciadorColisoes() {
	jogador1 = NULL;
	jogador2 = NULL;
	LIs.clear();
	LOs.clear();
}
void GerenciadorColisoes::executar() {
	list<Inimigo*>::iterator itI;
	list<Projetil*>::iterator itP;
	itI = LIs.begin();
	int i = 0, j=0;
	int tipoColi;
	Inimigo* obj;
	while (i<LIs.size()) {
		
		obj = *itI;
		if ((*itI)->getVivo()) {
			if (jogador1 != NULL) {

				if (testaColisao((Entidade*)jogador1, (Entidade*)obj)) {
					if (jogador1->getAtacando() > 0) {
						colidirAtaque(*itI, jogador1);
					}
					else if (!jogador1->getImune()) {
						colidirInimigo(jogador1, *itI);
					}
				}
			}
			if (jogador2 != NULL) {

				if (testaColisao((Entidade*)jogador2, (Entidade*)obj)) {
					if (jogador2->getAtacando() > 0) {
						colidirAtaque(*itI, jogador2);
					}
					else if (!jogador2->getImune()) {
						colidirInimigo(jogador2, *itI);
					}
				}
			}
		}
		i++;
		itI++;
	}
	vector<Obstaculo*>::iterator itO;
	itO = LOs.begin();
	i = 0;
	while (i < LOs.size()) {
		if (jogador1 != NULL) {
			int tipo = testaColisao((Entidade*)jogador1, (Entidade*)*itO);
			if (tipo) {
				colidirObstaculo(tipo, jogador1, *itO);
			}
		}
		if (jogador2 != NULL) {
			int tipo = testaColisao((Entidade*)jogador2, (Entidade*)*itO);
			if (tipo) {
				colidirObstaculo(tipo, jogador2, *itO);
			}
		}
		itI = LIs.begin();
		j = 0;
		while (j < LIs.size()) {
			int tipo = testaColisao((Entidade*)*itI, (Entidade*)*itO);
			if ((*itO)->getAtivo() && tipo)
				colidirObstaculo(tipo, *itI, *itO);
			j++;
			itI++;
		}
		itP = LPs.begin();
		j = 0;
		while (j < LPs.size()) {
			if (testaColisao((Entidade*)*itP, (Entidade*)*itO))
				colidirObstaculo(*itP, *itO);
			j++;
			itP++;
		}
		i++;
		itO++;
	}
	i = 0;
	itP = LPs.begin();
	while (i < LPs.size()) {
		if ((*itP)->getAtivo()) {

			if (jogador1 != NULL) {
				
				if (testaColisao((Entidade*)jogador1, (Entidade*)*itP)) {
					if (jogador1->getAtacando() > 0)
						colidirAtaque(*itP, jogador1);

					else if (jogador1->getImune()) {
						(*itP)->setAtivo(false);
					}

					else {
						colidirProjetil(jogador1, *itP);
					}
				}
			}
			if (jogador2 != NULL) {

				if (testaColisao((Entidade*)jogador2, (Entidade*)*itP)) {
					if (jogador2->getAtacando() > 0)
						colidirAtaque(*itP, jogador2);

					else if (jogador2->getImune()) {
						(*itP)->setAtivo(false);
					}

					else {
						colidirProjetil(jogador2, *itP);
					}
				}
			}
		}
		i++;
		itP++;
	} 
}
void GerenciadorColisoes::addObstaculo(Obstaculo* obst) {
	LOs.push_back(obst);
}
void GerenciadorColisoes::addInimigo(Inimigo* Inim) {
	LIs.push_back(Inim);
}
void GerenciadorColisoes::addProjetil(Projetil* tiro) {
	LPs.push_back(tiro);
}
void GerenciadorColisoes::removeObstaculo(int posicao) {
	vector<Obstaculo*>::iterator it = LOs.begin();
	for (int i = 0; i < posicao; i++) {
		it++;
	}
	LOs.erase(it);
}
void GerenciadorColisoes::removeInimigo(int posicao) {
	list<Inimigo*>::iterator it = LIs.begin();
	for (int i = 0; i < posicao; i++) {
		it++;
	}
	LIs.erase(it);
}

int GerenciadorColisoes::testaColisao(Entidade* obj1, Entidade* obj2){
	if (obj1->getX() + obj1->getLargura() > obj2->getX()-1 && obj1->getX() < obj2->getX() + obj2->getLargura() && obj1->getY() + obj1->getAltura() > obj2->getY() - 2 && obj1->getY() < obj2->getY() + obj2->getAltura() + 2) {

		if (obj1->getY() + obj1->getAltura() < obj2->getY() + 2 ) {
			return 1;
		}

		if (obj1->getY() > obj2->getY() + obj2->getAltura() - 2 && obj1->getVelocidadeY() < 0 ) {
			return 2;
		}

		if (obj1->getX() + obj1->getLargura() < obj2->getX() + 2 ){
			return 3;
		}
		if (obj1->getX() > obj2->getX() + obj2->getLargura() - 1) {
			return 4;
		}
	}
	return 0;	
}

void GerenciadorColisoes::colidirObstaculo(int direcao, Jogador* obj1, Obstaculo* obj2) {
	/*if (obj2->getId() == 31) {
		if (direcao == 1 && !obj1->getNoChao()) {
			obj1->setVelocidadeY(0);
			obj1->setNoChao(true);
		}

		else if (direcao == 2) {
			obj1->setVelocidadeY(0);
		}

		else if (direcao == 3) {
			obj1->setVelocidadeX(0);
			obj1->setX(obj2->getX() - (float)(obj1->getLargura()+2));
		}
		else if (direcao == 4) {
			obj1->setVelocidadeX(0);
			obj1->setX(obj2->getX() +(float) (obj2->getLargura()+2));
		}
	}
	else if (obj2->getId() == 32) {
		if (!obj1->getImune()) {
			obj1->removeVidas(obj2->getDano());
			obj1->setImune();
			obj1->getBody()->setFillColor(Color::Color(20, 34, 184));
		}
		if (direcao == 1 && !obj1->getNoChao()) {
			obj1->setVelocidadeY(0);
			obj1->setNoChao(true);
		}

		else if (direcao == 2) {
			obj1->setVelocidadeY(obj1->getVelocidadeY() * -0.5f);
		}

		else if (direcao == 3) {
			obj1->setVelocidadeX(0);
			obj1->setX(obj2->getX() - (float)(obj1->getLargura() + 2));
		}
		else if (direcao == 4) {
			obj1->setVelocidadeX(0);
			obj1->setX(obj2->getX() + (float)(obj2->getLargura() + 2));
		}
		
	}
	else if (obj2->getId() == 33) {
		obj1->removeVidas(obj2->getDano());
		
	}
	else if (obj2->getId() == 34) {
		if (obj2->getAtivo()) {
			if (direcao == 1 ) {
				obj1->setVelocidadeY(0);
				obj1->setNoChao(true);
				obj2->reduzAtivo();
			}

			else if (direcao == 2) {
				obj1->setVelocidadeY(obj1->getVelocidadeY() * -0.5f);
			}

			else if (direcao == 3) {
				obj1->setVelocidadeX(0);
				obj1->setX(obj2->getX() - (float)(obj1->getLargura() + 2));
			}
			else if (direcao == 4) {
				obj1->setVelocidadeX(0);
				obj1->setX(obj2->getX() + (float)(obj2->getLargura() + 2));
			}
		}
	}*/
	if (obj2->getSolido()) {
		if (direcao == 1 && !obj1->getNoChao() && obj2->getAtivo()) {
			obj1->setVelocidadeY(0);
			obj1->setNoChao(true);
			obj2->reduzAtivo();
		}

		else if (direcao == 2) {
			obj1->setVelocidadeY(0);
		}

		else if (direcao == 3) {
			obj1->setVelocidadeX(0);
			obj1->setX(obj2->getX() - (float)(obj1->getLargura() + 2));
		}
		else if (direcao == 4) {
			obj1->setVelocidadeX(0);
			obj1->setX(obj2->getX() + (float)(obj2->getLargura() + 2));
		}
	}
	if (obj2->getDanoso()) {
		if (!obj1->getImune() || obj2->getId()==33) {
			obj1->removeVidas(obj2->getDano());
			obj1->setImune();
			obj1->getBody()->setFillColor(Color::Color(20, 34, 184));
		}
	}
}
void GerenciadorColisoes::colidirObstaculo(int direcao, Inimigo* obj1, Obstaculo* obj2) {
	if (obj2->getId() == 31 || obj2->getId()==32 || (obj2->getId() == 34 && obj2->getAtivo())) {
		if (direcao == 1 && !obj1->getNoChao()) {
			obj1->setVelocidadeY(0);
			obj1->setNoChao(true);
		}

		else if (direcao == 2) {
			obj1->setVelocidadeY(obj1->getVelocidadeY() * -0.5f);
		}

		else if (direcao == 3) {
			obj1->setX(obj2->getX() - (float)(obj1->getLargura() + 2));
			obj1->setVelocidadeX(obj1->getVelocidadeX() * -1);
			obj1->setDirecao(obj1->getDirecao() * -1);
		}
		else if (direcao == 4) {
			obj1->setX(obj2->getX() + (float)(obj2->getLargura() + 2));
			obj1->setVelocidadeX(obj1->getVelocidadeX() * -1);
			obj1->setDirecao(obj1->getDirecao() * -1);
		}
	}
	else if (obj2->getId() == 33) {
		obj1->removeVidas(100);

	}
}
void GerenciadorColisoes::colidirObstaculo(Projetil* obj1, Obstaculo* obj2) {
	obj1->setAtivo(false);
}

void GerenciadorColisoes::colidirInimigo( Jogador* obj1, Inimigo* obj2){
	if (!obj1->getImune()) {
		obj1->removeVidas(obj2->getDano());
		obj1->setImune();
		obj1->getBody()->setFillColor(Color::Color(20, 34, 184));
	}
}

void GerenciadorColisoes::colidirAtaque(Inimigo* obj1, Jogador* obj2) {
	obj1->removeVidas(1);
}
void GerenciadorColisoes::colidirAtaque(Projetil* obj1, Jogador* obj2) {
	obj1->setAtivo(false);
}
void GerenciadorColisoes::colidirProjetil(Jogador* obj1, Projetil* obj2) {
	obj1->removeVidas(1);
	obj1->setImune();
	obj2->setAtivo(false);
	obj1->getBody()->setFillColor(Color::Color(20, 34, 184));
}


int GerenciadorColisoes::getQuantInimigos() {
	return LIs.size();
}


bool GerenciadorColisoes::testaListaInimigo() {
	list<Inimigo*>::iterator itI = LIs.begin();
	while (itI != LIs.end()) {
		if ((*itI)->getVivo()) {
			return false;
		}
		itI++;
	}
	return true;
}

void GerenciadorColisoes::limpaListaInimigo() {
	LIs.clear();
}