#include "Shape.h"

#include "ServiceProvider/ServiceProvider.h"
#include "Material/MaterialManager.h"

Shape::Shape() : Entity2D()
{
	materialID = ServiceProvider::Instance().Get<MaterialManager>()->GetMaterial("basicShapeMaterial");
}

Shape::~Shape()
{
}

void Shape::Draw()
{
	GetRenderer()->DrawElement(model, materialID, indexSize, VAO);
}
