#pragma once
#include <list>
#include <vector>
#include "Inimigo.h"
#include "Obstaculo.h"
#include "Jogador.h"
using namespace std;
using namespace personagens;
class GerenciadorColisoes{
private:
	list <Inimigo*> LIs;
	vector <Obstaculo*> LOs;
	Jogador* jogador1=NULL;
	Jogador* jogador2=NULL;

public:
	GerenciadorColisoes(Jogador* player1, Jogador* player2 = NULL);
	~GerenciadorColisoes();
	void executar();
	void addObstaculo(Obstaculo* obst);
	void addInimigo(Inimigo* Inim);
	void removeObstaculo(int posicao);
	void removeInimigo(int posicao);
	int testaColisao(Entidade* obj1, Entidade* obj2);
	void colidirObstaculo(int diracao, Jogador* obj1, Obstaculo* obj2);
	void colidirObstaculo(int diracao, Inimigo* obj1, Obstaculo* obj2);
	void colidirInimigo(Jogador* obj1, Inimigo* obj2);
};

