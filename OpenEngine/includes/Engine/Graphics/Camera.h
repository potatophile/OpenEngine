#pragma once
#include "Engine/Math/Transformations.h"

struct STCameraData {
	//how fast the camera can move
	float Speed = 5.0f;

	//How much of the view space the camera can see - in degrees (zoom)
	//peripheral vision
	float FOV = 70.0f;

	//how close can models get to the camera before disappearing
	float NearClip = 0.01f;
	//opposite of near clip
	float FarClip = 1000.0f;
};

class Camera {
public:
	Camera();

	//move the camera in 3D space to a location
	void Translate(Vector3 Location);

	//return the transform data
	CTransform GetTransforms() const { return Transform; }

	//return the current facing directions
	CDirections GetDirections() const { return Directions; }

	//return the extra camera info - Speed, FOV, NearClip, FarClip
	STCameraData GetCameraData() const { return CameraData; }

	//return a view matrix that considers positions and rotations
	glm::mat4 GetViewMatrix() const;
	
	//rotate the camera based on yaw
	void RotatePitch(float Amount);

	//rotate the camera based on pitch
	void RotateYaw(float Amount);

	//set the camera FOV based on mouse wheel scroll
	void SetFOV(float Amount);
	//set the camera FOV to default (70.0f)
	void DefaultFOV();

private:
	//Find the current direction vectors based on the rotation of YAW and PITCH of the camera
	void UpdateDirectionVectors();

private:
	//transforms of the camera
	//location, rotation, scale
	CTransform Transform;

	//forward, right and up directions
	CDirections Directions;

	//hold the extra camera info
	STCameraData CameraData;
};