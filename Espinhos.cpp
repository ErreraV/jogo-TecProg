#include "Espinhos.h"

Espinhos::Espinhos(float X, float Y, float l, float a, int id) :
	Obstaculo(X, Y, l, a, id)
{
	body->setFillColor(Color::Cyan);
}

Espinhos::~Espinhos()
{
}
