#include "Ganondorf.h"
using namespace personagens;
Ganondorf::Ganondorf(int vidas, float x, float y) :
	Inimigo(vidas, x, y, 33)
{
	body->setFillColor(Color::Yellow);
}

Ganondorf::~Ganondorf()
{
}