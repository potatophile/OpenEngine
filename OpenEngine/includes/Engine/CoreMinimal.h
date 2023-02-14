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
typedef vector<VAOPtr> VAOStack;


//useful for shape data and VAOs
typedef vector<float>  PositionMatrix;
typedef vector<UNint> IndicesMatrix;

//structure to handle matrices VAOs
struct ShapeData {
	vector<float> PositionMatrix;
	vector<UNint> IndicesMatrix;
};