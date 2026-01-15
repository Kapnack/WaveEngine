#include "Shape.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialManager.h"

Shape::Shape(Renderer* renderer) : Entity2D(renderer)
{
	material = &ServiceProvider::Instance().Get<MaterialManager>()->GetMaterial("basicShapeMaterial");
}

Shape::~Shape()
{
}

void Shape::Draw()
{
	renderer->DrawElement(model, material, indexSize, VAO);
}
