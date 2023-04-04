#pragma once
#include "Engine/CoreMinimal.h"
#include "Engine/Math/Transformations.h"

struct Vertex;

class Mesh {
public:
	Mesh();
	~Mesh();

	//Create the mesh out of VAO, a shader and textures
	bool CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, UNint MaterialSlot);

	//create a mesh VAO that has a predefined model
	bool CreateMesh(vector<Vertex> Vertices, vector<UNint> Indices, ShaderPtr Shader, UNint MaterialSlot);

	//handle the drawing of all the required classes
	void Draw(MaterialPtr MeshMaterial);

	//return material slot assigned by the model to the mesh
	UNint GetMaterialSlot() const { return MaterialSlot; }

public:
	//this holds the position, rotation and scale of the mesh
	CTransform Transform;

private:
	//Store the shader this mesh requires
	ShaderPtr MeshShader;
	
	//Assign a material slot relevant to the model class
	UNint MaterialSlot;

	//Create a new VAO for the mesh
	VAOPtr MeshVAO;

};