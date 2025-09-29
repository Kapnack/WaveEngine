#include "Shape.h"

Shape::Shape(Renderer* renderer) : Entity2D(renderer)
{
}

Shape::~Shape()
{
}

void Shape::Draw()
{
	renderer->DrawElement(model, indexSize, VAO);
}