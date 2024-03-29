#pragma once

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int UNint;

//class/type definitions
class GraphicsEngine;		//forward declaring for circular dependency
typedef shared_ptr<GraphicsEngine> GraphicsEnginePtr;

class VertexArrayObject;
typedef VertexArrayObject VAO;
typedef shared_ptr<VAO> VAOPtr;

class Texture;
typedef shared_ptr<Texture> TexturePtr;
typedef vector<TexturePtr> TexturePtrStack;

class ShaderProgram;
typedef shared_ptr<ShaderProgram> ShaderPtr;

class Mesh;
typedef shared_ptr<Mesh> MeshPtr;
typedef vector<MeshPtr> MeshPtrStack;

class Model;
typedef shared_ptr<Model> ModelPtr;
typedef vector<ModelPtr> ModelPtrStack;

class Material;
typedef shared_ptr<Material> MaterialPtr;
typedef vector<MaterialPtr> MaterialPtrStack;

class Camera;
typedef shared_ptr<Camera> CameraPtr;

class Collision;
typedef shared_ptr<Collision> CollisionPtr;
typedef vector<CollisionPtr> CollisionPtrStack;

class BoxCollision;
typedef shared_ptr<BoxCollision> BoxCollisionPtr;

//useful for shape data and VAOs
typedef vector<float>  PositionMatrix;
typedef vector<UNint> IndicesMatrix;

//structure to handle matrices VAOs
struct ShapeData {
	vector<float> PositionMatrix;
	vector<UNint> IndicesMatrix;
};

//list of the geometric shapes in VAO
enum class GeometricShapes {
	Triangle = 0,
	Polygon,
	Circle,
	Cube
};

//store the parameters required to create a shader program
struct VFShaderParams {
	const wchar_t* VertexShaderPath;
	const wchar_t* FragmentShaderPath;
};

//types of shader acceptable in our program
enum class ShaderTypes {
	Vertex = 0,
	Fragment
};