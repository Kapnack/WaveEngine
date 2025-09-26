#include "Shape.h"

Shape::Shape(Renderer* renderer, Vector3 position) : Entity2D(renderer, position)
{
}

Shape::~Shape()
{
}

void Shape::Draw()
{
	renderer->DrawElement(model, indexSize, VAO);
}