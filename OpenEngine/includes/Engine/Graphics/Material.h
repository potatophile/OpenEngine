#pragma once
#include "Engine/CoreMinimal.h"

class Material {
public:
	Material();
	~Material();

	TexturePtr BaseColour;

	void Draw(ShaderPtr Shader);
};