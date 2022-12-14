#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ente.h"
#include "GerenciadorGrafico.h"
#include "Jogador.h"
#include "Inimigo.h"
#include "ListaEntidades.h"
#include "Fase.h"
#include "PrimeiraFase.h"
#include "SegundaFase.h"
#include "Menu.h"
#include "MenuGameOver.h"
#include "Ranking.h"

using namespace std;
using namespace sf;
using namespace gerenciadores;
using namespace entidades;
using namespace personagens;
using namespace obstaculos;
using namespace listas;
using namespace fases;

class Jogo{
private:
	GerenciadorGrafico* grafico;
	Jogador* link1;
	Jogador* link2;
	ListaEntidades* LEs;
	Menu* menu;
	MenuGameOver* end;
	Ranking* ranking;
	int numFase;
	bool fim;

	float time;
	Fase* fase;
	int estado;
	static int pontuacao;
public:
	Jogo();
	~Jogo();
	void Executar();

	static void addPontos(int valor);
	void resetarJogo();
	void trocaFase();
	void continuar();
	void fimDeJogo(int pontos);
	int getPontos();
};

