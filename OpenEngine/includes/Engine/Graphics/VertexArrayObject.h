#pragma once

#include "Engine/CoreMinimal.h"

const PositionMatrix TrianglePositions{
	//x		//y		//z		//Colour
	-0.5f,	-0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	//bottom left
	 0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	//bottom right
	 0.0f,	 0.5f,	0.0f,	0.0f, 0.0f, 1.0f	//top
};

const IndicesMatrix TriangleIndices{
	0, 1, 2
};

const PositionMatrix PolyPositions{
	//x		//y		//z		//Colour
	-0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	//bottom left
	 0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	//bottom right
	 0.5f,	 0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	//top right
	-0.5f,	 0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	//top left
};

const IndicesMatrix PolyIndices{
	0, 3, 1,				//triangle 1
	3, 2, 1					//triangle 2
};

const PositionMatrix CirclePositions{
	//x		//y		//z
	 0.0f,   0.0f,  0.0f,		//center
	-0.5f,	 0.0f,	0.0f,		//left
	-0.35f,  0.35f,	0.0f,		//top left
	 0.0f,	 0.5f,	0.0f,		//top center
	 0.35f,	 0.35f,	0.0f,		//top right
	 0.5f,	 0.0f,	0.0f,		//right
	 0.35f,	-0.35f,	0.0f,		//bottom right
	 0.0f,	-0.5f,	0.0f,		//bottom center
	-0.35f,	-0.35f,	0.0f,		//bottom left	 
};

const IndicesMatrix CircleIndices{
	1, 2, 0,				//triangle 1
	2, 3, 0,				//triangle 2
	3, 4, 0,				//triangle 3
	4, 5, 0,				//triangle 4
	5, 6, 0,				//triangle 5
	6, 7, 0,				//triangle 6
	7, 8, 0,				//triangle 7
	8, 1, 0					//triangle 8
};

class VertexArrayObject {
public:
	VertexArrayObject(GeometricShapes ChosenShape);
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