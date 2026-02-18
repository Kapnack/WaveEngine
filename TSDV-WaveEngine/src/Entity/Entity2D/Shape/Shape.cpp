#include "Shape.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialManager.h"

Shape::Shape(const unsigned int& ID) : Entity2D(ID), Drawable(ID)
{
	materialID = ServiceProvider::Instance().Get<MaterialManager>()->GetMaterial("basicShapeMaterial");
}

Shape::~Shape()
{
}

void Shape::Draw()
{
	if (!GetIsActive())
		return;

	GetRenderer()->DrawElement(model, materialID, indexSize, VAO);
}
