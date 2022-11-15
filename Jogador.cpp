#include "Jogador.h"
using namespace personagens;
Jogador::Jogador(int vidas, float x, float y) : Personagem(vidas, x, y, 11, 1) {
    body->setPosition(0.f, 280.f);
    body->setFillColor(Color::Color(58,238,39));
    velocidadeX = 0;
    imune = 0;
    atacando = 0;
    tiro = new Projetil;
}

Jogador::~Jogador()
{
}

void Jogador::move() {
    velocidadeX*=0.9f;
    if (imune) {
        imune--;
        if (!imune) {
            body->setFillColor(Color::Color(58, 238, 39));
        }
    }
    if (atacando) {
        if (atacando > 0)
            atacando--;
    }
    if (pulo > 1000000) {
        pulo = 10000;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        direcao = 1;
        if (velocidadeX < 0.1f)
            velocidadeX += 0.03f;

    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        direcao = -1;
        if (velocidadeX > -0.1f)
            velocidadeX += -0.03f;

    }
    if (Keyboard::isKeyPressed(Keyboard::Up) && pulo>160) {
            velocidadeY += -0.7f;
            pulo = 0;

    }
    if (Keyboard::isKeyPressed(Keyboard::Z)) {
        if (!atacando) {
            atacando = 100;
        }
    }
    if (Keyboard::isKeyPressed(Keyboard::X)) {
        if (!tiro->getAtivo()) {
            atira();
        }
    }
    y += velocidadeY;
    x += velocidadeX;
    body->setPosition(x,y);
    if(!noChao)
        gravidade();
    if (!vivo) {
        body->setFillColor(Color(200, 114, 185));
    }
    noChao = false;
    id = 1;


}
int Jogador::getAtacando() {
    return atacando;
}

int Jogador::getImune() {
    return imune;
}

int Jogador::getDirecao() {
    return direcao;
}

Projetil* Jogador::getTiro() {
    return tiro;
}

void Jogador::setImune() {
    imune = 3000;
}

void Jogador::atira() {
    if (direcao > 0) {
        tiro->setX(x + largura + 2);
        tiro->setY(y + 20);
        tiro->setVelocidadeX(1.f);
    }
    else {
        tiro->setX(x - (2+tiro->getLargura()));
        tiro->setY(y + 20);
        tiro->setVelocidadeX(-1.f);
    }
    tiro->setVelocidadeY(0);
    tiro->setAtivo(true);
}

void Jogador::setNoChao(bool estado) {
    noChao = estado;
    pulo++;
}