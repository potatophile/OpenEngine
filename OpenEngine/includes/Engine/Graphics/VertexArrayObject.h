#pragma once

#include "Engine/CoreMinimal.h"

const PositionMatrix TrianglePositions{
	//x		//y		//z
	-0.5f,	-0.5f,	0.0f,		//bottom left
	 0.5f,	-0.5f,	0.0f,		//bottom right
	 0.0f,	 0.5f,	0.0f		//top
};

const IndicesMatrix TriangleIndices{
	0, 1, 2
};

const PositionMatrix PolyPositions{
	//x		//y		//z
	-0.5f,	-0.5f,	0.0f,		//bottom left
	 0.5f,	-0.5f,	0.0f,		//bottom right
	 0.5f,	 0.5f,	0.0f,		//top right
	-0.5f,	 0.5f,	0.0f		//top left
};

const IndicesMatrix PolyIndices{
	0, 3, 1,				//triangle 1
	3, 2, 1					//triangle 2
};

class VertexArrayObject {
public:
	VertexArrayObject();
	~VertexArrayObject();

	void Draw();

private:
	ShapeData Shape;

	//unsigned int type definition
	//ID - ID for VAO
	//VAB - ID for vertices
	//EAB - ID for indices
	UNint ID, VAB, EAB;
};