#include "Engine\Graphics\VertexArrayObject.h"
#include "GLEW/glew.h"

VertexArrayObject::VertexArrayObject(GeometricShapes ChosenShape)
{
	ID = EAB = VAB = 0;

	//localised version of chosen matrices
	PositionMatrix ChosenPositions = PositionMatrix();
	IndicesMatrix ChosenIndices = IndicesMatrix();

	//switch current geometric shape
	switch (ChosenShape) {
	case GeometricShapes::Triangle:
		ChosenPositions = TrianglePositions;
		ChosenIndices = TriangleIndices;
		break;
	case GeometricShapes::Polygon:
		ChosenPositions = PolyPositions;
		ChosenIndices = PolyIndices;
		break;
	case GeometricShapes::Circle:
		ChosenPositions = CirclePositions;
		ChosenIndices = CircleIndices;
		break;
	case GeometricShapes::Cube:
		ChosenPositions = CubePositions;
		ChosenIndices = CubeIndicies;
		break;
	default:
		break;
	}

	Shape.PositionMatrix = ChosenPositions;
	Shape.IndicesMatrix = ChosenIndices;

	//create the ID for our VAO
	glGenVertexArrays(1, &ID);
	//bind the data to this vertex array
	glBindVertexArray(ID);

	//	Handle the positions
	//Create an ID for our array buffer
	glGenBuffers(1, &VAB);
	//Bind the above IDs to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VAB);
	//Run through the data and attach the vertices to VAB
	glBufferData(
		GL_ARRAY_BUFFER,
		Shape.PositionMatrix.size() * sizeof(float),
		&Shape.PositionMatrix[0],
		GL_STATIC_DRAW
	);

	//	Handle the indices
	//Create an ID for our element array buffer
	glGenBuffers(1, &EAB);
	//Bind the above ID to OpenGL as element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EAB);
	//Run through the data and attach the indices to the EAB
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		Shape.IndicesMatrix.size() * sizeof(UNint),
		&Shape.IndicesMatrix[0],
		GL_STATIC_DRAW
	);

	//Assign the vertices and indices to the VAO
	glVertexAttribPointer(
		0,					//Data set - 0 = first data set in the array
		3,					//How many numbers in our matrix to make a triangle
		GL_FLOAT, GL_FALSE, //Data type of matrix, whether you want to normalize the values
		sizeof(float) * 8,	//stride - length it takes to get to each number
		(void*)0			//offset of how many numbers to skip in the matrix
	);

	//enable the vertex array
	glEnableVertexAttribArray(0);

	//assign the colour to the shader
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT, GL_FALSE,
		sizeof(float) * 8,
		(void*)(3 * sizeof(float))
		);

	//enable the colour array
	glEnableVertexAttribArray(1);

	//assign the texture coordinates to the shader
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT, GL_FALSE,
		sizeof(float) * 8,
		(void*)(6 * sizeof(float))
	);

	//enable the texture coordinate array
	glEnableVertexAttribArray(2);

	//clear the bufferr
	glBindVertexArray(0);

}

VertexArrayObject::VertexArrayObject(vector<Vertex> Vertices, vector<UNint> Indices)
{
	ID = EAB = VAB = 0;

	//assign the vertices and indices to the class
	this->Vertices = Vertices;
	this->Indices = Indices;

	//create the ID for our VAO
	glGenVertexArrays(1, &ID);
	//bind the data to this vertex array
	glBindVertexArray(ID);

	//	Handle the positions
	//Create an ID for our array buffer
	glGenBuffers(1, &VAB);
	//Bind the above IDs to OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VAB);
	//Run through the data and attach the vertices to VAB
	glBufferData(
		GL_ARRAY_BUFFER,
		Vertices.size() * sizeof(Vertex),
		&Vertices[0],
		GL_STATIC_DRAW
	);

	//	Handle the indices
	//Create an ID for our element array buffer
	glGenBuffers(1, &EAB);
	//Bind the above ID to OpenGL as element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EAB);
	//Run through the data and attach the indices to the EAB
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		Indices.size() * sizeof(UNint),
		&Indices[0],
		GL_STATIC_DRAW
	);

	//Assign the vertices and indices to the VAO
	glVertexAttribPointer(
		0,					//Data set - 0 = first data set in the array
		3,					//How many numbers in our matrix to make a triangle
		GL_FLOAT, GL_FALSE, //Data type of matrix, whether you want to normalize the values
		sizeof(float) * 8,	//stride - length it takes to get to each number
		(void*)0			//offset of how many numbers to skip in the matrix
	);

	//enable the vertex array
	glEnableVertexAttribArray(0);

	//assign the normals of the mesh vertices to the shader
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT, GL_FALSE,
		sizeof(float) * 8,
		(void*)(3 * sizeof(float))
	);

	//enable the colour array
	glEnableVertexAttribArray(1);

	//assign the texture coordinates to the shader
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT, GL_FALSE,
		sizeof(float) * 8,
		(void*)(6 * sizeof(float))
	);

	//enable the texture coordinate array
	glEnableVertexAttribArray(2);

	//clear the bufferr
	glBindVertexArray(0);

}

VertexArrayObject::~VertexArrayObject()
{
	//clean up the VAO in OpenGL
	glDeleteVertexArrays(1, &ID);

	//Clean up the vectors
	Vertices.clear();
	Indices.clear();

	cout << "Deleted VAO..." << endl;
}

void VertexArrayObject::Draw()
{
	vector<UNint> IndicesToUse;
	
	//decide which indices to use based on whats assigned
	if (Vertices.size() > 0)
		IndicesToUse = Indices;

	else 
		IndicesToUse = Shape.IndicesMatrix;

	//bind our VAO to the current buffer
	glBindVertexArray(ID);
	//Draw the 3d object/VAO
	glDrawElements(
		GL_TRIANGLES,					//type of object we are drawing
		IndicesToUse.size(),		//how many vertices do we draw
		GL_UNSIGNED_INT,				//what is the type of data that's being input
		(void*)0						//how many should  we skip
	);
	//clear the VAO from the current array to allow for the next object
	glBindVertexArray(0);
}
