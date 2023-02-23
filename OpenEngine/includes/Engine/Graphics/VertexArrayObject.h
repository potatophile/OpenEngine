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
	//x		//y		//z		//Colour - Yellow
	-0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	//bottom left
	 0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	//bottom right
	 0.5f,	 0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	//top right
	-0.5f,	 0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	//top left
};

const IndicesMatrix PolyIndices{
	0, 3, 1,				//triangle 1
	3, 2, 1					//triangle 2
};

const PositionMatrix CirclePositions{
	//x		//y		//z
	 0.0f,   0.0f,  0.0f,	1.0f, 1.0f, 1.0f,		//center, color -White
	-0.5f,	 0.0f,	0.0f,	1.0f, 1.0f, 0.0f,		//left, color - yellow

	 //calculating x using pythagoras theorem (h^2 = p^2 + b^2)
	 //top-left quadrant									//colour - Red
	-sqrt((0.5f * 0.5f) - (0.1f * 0.1f)),	0.1f,	0.0f,	1.0f, 0.0f, 0.0f,
	-sqrt((0.5f * 0.5f) - (0.15f * 0.15f)), 0.15f,	0.0f,	1.0f, 0.0f, 0.0f,
	-sqrt((0.5f * 0.5f) - (0.2f * 0.2f)),	0.2f,	0.0f,	1.0f, 0.0f, 0.0f,
	-sqrt((0.5f * 0.5f) - (0.25f * 0.25f)), 0.25f,	0.0f,	1.0f, 0.0f, 0.0f,
	-sqrt((0.5f * 0.5f) - (0.3f * 0.3f)),	0.3f,	0.0f,	1.0f, 0.0f, 0.0f,
	-sqrt((0.5f * 0.5f) - (0.38f * 0.38f)), 0.38f,	0.0f,	1.0f, 0.0f, 0.0f,
	-sqrt((0.5f * 0.5f) - (0.44f * 0.44f)), 0.44,	0.0f,	1.0f, 0.0f, 0.0f,
	-sqrt((0.5f * 0.5f) - (0.47f * 0.47f)), 0.47f,	0.0f,	1.0f, 0.0f, 0.0f,
	-sqrt((0.5f * 0.5f) - (0.49f * 0.49f)), 0.49f,	0.0f,	1.0f, 0.0f, 0.0f,
	 0.0f,	 0.5f,	0.0f,	1.0f, 0.0f, 0.0f,		//top center

	 //top-right quadrant									//colour - Green
	 //calculating y using pythagoras theorem (h^2 = p^2 + b^2)
	 0.1f,	 sqrt((0.5f * 0.5f) - (0.1f * 0.1f)),	0.0f,	0.0f, 1.0f, 0.0f,
	 0.15f,	 sqrt((0.5f * 0.5f) - (0.15f * 0.15f)),	0.0f,	0.0f, 1.0f, 0.0f,
	 0.2f,	 sqrt((0.5f * 0.5f) - (0.2f * 0.2f)),	0.0f,	0.0f, 1.0f, 0.0f,
	 0.25f,	 sqrt((0.5f * 0.5f) - (0.25f * 0.25f)),	0.0f,	0.0f, 1.0f, 0.0f,
	 0.3f,	 sqrt((0.5f * 0.5f) - (0.3f * 0.3f)),	0.0f,	0.0f, 1.0f, 0.0f,
	 0.38f,	 sqrt((0.5f * 0.5f) - (0.38f * 0.38f)),	0.0f,	0.0f, 1.0f, 0.0f,
	 0.44f,	 sqrt((0.5f * 0.5f) - (0.44f * 0.44f)),	0.0f,	0.0f, 1.0f, 0.0f,
	 0.47f,	 sqrt((0.5f * 0.5f) - (0.47f * 0.47f)),	0.0f,	0.0f, 1.0f, 0.0f,
	 0.49f,	 sqrt((0.5f * 0.5f) - (0.49f * 0.49f)),	0.0f,	0.0f, 1.0f, 0.0f,
	 0.5f,	 0.0f,	0.0f,	0.0f, 1.0f, 0.0f,		//right

	 //bottom-right quadrant								//colour - Blue
	 0.49f,	-sqrt((0.5f * 0.5f) - (0.49f * 0.49f)),	0.0f,	0.0f, 0.0f, 1.0f,
	 0.47f,	-sqrt((0.5f * 0.5f) - (0.47f * 0.47f)),	0.0f,	0.0f, 0.0f, 1.0f,
	 0.44f,	-sqrt((0.5f * 0.5f) - (0.44f * 0.44f)),	0.0f,	0.0f, 0.0f, 1.0f,
	 0.38f,	-sqrt((0.5f * 0.5f) - (0.38f * 0.38f)),	0.0f,	0.0f, 0.0f, 1.0f,
	 0.3f,	-sqrt((0.5f * 0.5f) - (0.3f * 0.3f)),	0.0f,	0.0f, 0.0f, 1.0f,
	 0.25f,	-sqrt((0.5f * 0.5f) - (0.25f * 0.25f)),	0.0f,	0.0f, 0.0f, 1.0f,
	 0.2f,	-sqrt((0.5f * 0.5f) - (0.2f * 0.2f)),	0.0f,	0.0f, 0.0f, 1.0f,
	 0.15f,	-sqrt((0.5f * 0.5f) - (0.15f * 0.15f)),	0.0f,	0.0f, 0.0f, 1.0f,
	 0.1f,	-sqrt((0.5f * 0.5f) - (0.1f * 0.1f)),	0.0f,	0.0f, 0.0f, 1.0f,
	 0.0f,	-0.5f,	0.0f,	0.0f, 0.0f, 1.0f,		//bottom center

	 //bottom-left quadrant									//colour - Yellow
	-0.1f,	-sqrt((0.5f * 0.5f) - (0.1f * 0.1f)),	0.0f,	1.0f, 1.0f, 0.0f,
	-0.15f,	-sqrt((0.5f * 0.5f) - (0.15f * 0.15f)),	0.0f,	1.0f, 1.0f, 0.0f,
	-0.2f,	-sqrt((0.5f * 0.5f) - (0.2f * 0.2f)),	0.0f,	1.0f, 1.0f, 0.0f,
	-0.25f,	-sqrt((0.5f * 0.5f) - (0.25f * 0.25f)),	0.0f,	1.0f, 1.0f, 0.0f,
	-0.3f,	-sqrt((0.5f * 0.5f) - (0.3f * 0.3f)),	0.0f,	1.0f, 1.0f, 0.0f,
	-0.38f,	-sqrt((0.5f * 0.5f) - (0.38f * 0.38f)),	0.0f,	1.0f, 1.0f, 0.0f,
	-0.44f,	-sqrt((0.5f * 0.5f) - (0.44f * 0.44f)),	0.0f,	1.0f, 1.0f, 0.0f,
	-0.47f,	-sqrt((0.5f * 0.5f) - (0.47f * 0.47f)),	0.0f,	1.0f, 1.0f, 0.0f,
	-0.49f,	-sqrt((0.5f * 0.5f) - (0.49f * 0.49f)),	0.0f,	1.0f, 1.0f, 0.0f,
	-0.5f,	 0.0f,	0.0f,	1.0f, 1.0f, 0.0f
};

const IndicesMatrix CircleIndices{
	//joining all vertex to the center
	1, 2, 0,
	2, 3, 0,
	3, 4, 0,
	4, 5, 0,
	5, 6, 0,
	6, 7, 0,
	7, 8, 0,
	8, 9, 0,
	9, 10, 0,
	10, 11, 0,
	11, 12, 0,
	12, 13, 0,
	13, 14, 0,
	14, 15, 0,
	15, 16, 0,
	16, 17, 0,
	17, 18, 0,
	18, 19, 0,
	19, 20, 0,
	20, 21, 0,
	21, 22, 0,
	22, 23, 0,
	23, 24, 0,
	24, 25, 0,
	25, 26, 0,
	26, 27, 0,
	27, 28, 0,
	28, 29, 0,
	29, 30, 0,
	30, 31, 0,
	31, 32, 0,
	32, 33, 0,
	33, 34, 0,
	34, 35, 0,
	35, 36, 0,
	36, 37, 0,
	37, 38, 0,
	38, 39, 0,
	39, 40, 0,
	40, 41, 0
};

const PositionMatrix StarPositions{
	//x		//y		//z		//Colour - Green
	 0.0f,	 0.3f,	0.0f,	0.0f, 1.0f, 0.0f,	//top
	-0.3f,	 0.1f,	0.0f,	0.0f, 1.0f, 0.0f,	//top left
	 0.3f,	 0.1f,	0.0f,	0.0f, 1.0f, 0.0f,	//top right
	-0.05f,	 0.1f,	0.0f,	0.0f, 1.0f, 0.0f,	//top mid left
	 0.05f,	 0.1f,	0.0f,	0.0f, 1.0f, 0.0f,	//top mid right
	-0.2f,	-0.2f,	0.0f,	0.0f, 1.0f, 0.0f,	//bottom left
	 0.2f,	-0.2f,	0.0f,	0.0f, 1.0f, 0.0f,	//bottom right
	-0.1f,	 0.0f,	0.0f,	0.0f, 1.0f, 0.0f,	//bottom mid left
	 0.1f,	 0.0f,	0.0f,	0.0f, 1.0f, 0.0f,	//bottom mid right
};

const IndicesMatrix StarIndices{
	//made of three triangles
	3, 5, 2,
	4, 6, 1,
	0, 7, 8
};

const PositionMatrix CrossPositions{
	//x		//y		//z		//Colour - Blue
	-0.1f,	 0.5f,	0.0f,	0.0f, 0.0f, 1.0f,	//verticle top left
	 0.1f,	 0.5f,	0.0f,	0.0f, 0.0f, 1.0f,	//verticle top right
	-0.1f,	-0.5f,	0.0f,	0.0f, 0.0f, 1.0f,	//verticle bottom left
	 0.1f,	-0.5f,	0.0f,	0.0f, 0.0f, 1.0f,	//verticle bottom right
	-0.5f,	 0.1f,	0.0f,	0.0f, 0.0f, 1.0f,	//horizontal top left
	 0.5f,	 0.1f,	0.0f,	0.0f, 0.0f, 1.0f,	//horizontal top right
	-0.5f,	-0.1f,	0.0f,	0.0f, 0.0f, 1.0f,	//horizontal bottom left
	 0.5f,	-0.1f,	0.0f,	0.0f, 0.0f, 1.0f	//horizontal bottom right
};

const IndicesMatrix CrossIndices{
	// 2 vertical and 2 horizontal triangles
	0, 1, 2,
	1, 2, 3,
	4, 5, 7,
	6, 7, 4
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