#pragma once
#include "Engine/Math/Transformations.h"
#include "Engine/CoreMinimal.h"

struct STCameraData {
	//how fast the camera can move
	float Speed = 25.0f;

	//How much of the view space the camera can see - in degrees (zoom)
	//peripheral vision
	float FOV = 70.0f;

	//how close can models get to the camera before disappearing
	float NearClip = 0.01f;
	//opposite of near clip
	float FarClip = 1000.0f;

	//speed at which the camera is turn is multiplied
	float LookSensitivity = 0.2f;
};

class Camera {
public:
	Camera();

	//move the camera in 3D space to a location
	void Translate(Vector3 Location);

	void AddMovementInput(Vector3 Direction);

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

	//update camera logic
	void Update();

	//get the collision for the camera
	CollisionPtr GetCameraCollision() const { return CameraCollision; }
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

	//add a camera collision
	CollisionPtr CameraCollision;
};