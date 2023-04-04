#include "Engine/Graphics/Mesh.h"
#include "Engine/Graphics/ShaderProgram.h"
#include "Engine/Graphics/Texture.h"
#include "Engine/Graphics/Material.h"
#include "Engine/Graphics/VertexArrayObject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Engine/Game.h"
#include "Engine/Graphics/GraphicsEngine.h"

Mesh::Mesh()
{
	cout << "Mesh | Initialised Mesh." << endl;

	//Transform.Location.x = 0.5f;
	//Transform.Scale.y = 0.5f;
}

Mesh::~Mesh()
{
	MeshShader = nullptr;
	MeshVAO = nullptr;

	cout << "Mesh | Mesh Destroyed." << endl;
}

bool Mesh::CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, UNint MaterialSlot)
{
	cout << "Creating Mesh." << endl;

	//Create the VAO
	MeshVAO = make_shared<VAO>(Shape);

	//validate the mesh was created
	if (MeshVAO == nullptr) {
		cout << "Mesh | Failed to create Mesh." << endl;
		return false;
	}

	//assign the shader and textures
	this->MeshShader = MeshShader;
	this->MaterialSlot = MaterialSlot;

	cout << "Mesh | Mesh created successfully." << endl;

	return true;
}

bool Mesh::CreateMesh(vector<Vertex> Vertices, vector<UNint> Indices, ShaderPtr MeshShader, UNint MaterialSlot)
{
	cout << "Creating Mesh." << endl;

	//Create the VAO
	MeshVAO = make_shared<VAO>(Vertices, Indices);

	//validate the mesh was created
	if (MeshVAO == nullptr) {
		cout << "Mesh | Failed to create Mesh." << endl;
		return false;
	}

	//assign the shader and textures
	this->MeshShader = MeshShader;
	this->MaterialSlot = MaterialSlot;

	cout << "Mesh | Mesh created successfully." << endl;

	return true;
}

void Mesh::Draw(MaterialPtr MeshMaterial)
{
	//Activate the shader that this mesh uses
	MeshShader->RunShader();

	//run the material for this mesh
	//activate all required textures in the material
	if (MeshMaterial != nullptr) {
		MeshMaterial->Draw(MeshShader);
	}

	//initialise a static variable to check if any changes to transform
	static CTransform OldTransform;

	if (Transform != OldTransform) {
		OldTransform = Transform;

		glm::mat4 MatTransform = glm::mat4(1.0f);

		//translate - rotate - scale --- in this order
		//translate
		MatTransform = glm::translate(MatTransform, Transform.Location);
		//rotate
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.x), Vector3(1.0f, 0.0f, 0.0f));
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.y), Vector3(0.0f, 1.0f, 0.0f));
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.z), Vector3(0.0f, 0.0f, 1.0f));
		//scale
		MatTransform = glm::scale(MatTransform, Transform.Scale);

		//update the shader with the new transforms
		MeshShader->SetMat4("model", MatTransform);
	}

	//create the world and screen positions for this object
	Game::GetGameInstance().GetGraphics()->ApplyScreenTransformations(MeshShader);

	//draw the VAO
	MeshVAO->Draw();
}
