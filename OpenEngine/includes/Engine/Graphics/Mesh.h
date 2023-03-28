#pragma once
#include "Engine/CoreMinimal.h"
#include "Engine/Math/Transformations.h"

class Mesh {
public:
	Mesh();
	~Mesh();

	//Create the mesh out of VAO, a shader and textures
	bool CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, MaterialPtr MeshMaterial);

	//handle the drawing of all the required classes
	void Draw();

	//this holds the position, rotation and scale of the mesh
	CTransform Transform;

private:
	//Store the shader this mesh requires
	ShaderPtr MeshShader;
	
	//Assign a material to the mesh
	MaterialPtr MeshMaterial;

	//Create a new VAO for the mesh
	VAOPtr MeshVAO;

};