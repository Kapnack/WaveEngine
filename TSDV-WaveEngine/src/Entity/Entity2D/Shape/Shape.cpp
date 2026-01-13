#include "Shape.h"

#include "Material/MaterialManager.h"

Shape::Shape(Renderer* renderer) : Entity2D(renderer)
{
	material = &MaterialManager::GetMaterial("basicShapeMaterial");
}

Shape::~Shape()
{
}

void Shape::Draw()
{
	renderer->DrawElement(model, material, indexSize, VAO);
}
