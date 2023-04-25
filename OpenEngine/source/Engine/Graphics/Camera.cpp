#include "Engine/Graphics/Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Engine/Game.h"
#include "Engine/Collision/Collision.h"

Camera::Camera()
{
	UpdateDirectionVectors();

	Transform.Location += -Directions.Forward * 2.0f;

	//@param1 - position of collision
	//@param2 - offset of the location
	//@param3 - size of the camera collision
	CameraCollision = make_shared<BoxCollision>(Transform.Location, Vector3(0.0f), Vector3(1.0f));
}

void Camera::Translate(Vector3 Location)
{
	Transform.Location = Location;

	UpdateDirectionVectors();
}

void Camera::AddMovementInput(Vector3 Direction)
{
	//ignore the rest of the function if no direction is given
	if (glm::length(Direction) == 0)
		return;

	//divide the vector by its length
	//dont normalize if the direction is 0
	Direction = glm::normalize(Direction);

	//set the velocity of the camera using speed and input direction
	Vector3 Vel = Direction * (CameraData.Speed * Game::GetGameInstance().GetFDeltaTime());

	//create a new location from the camera based on its position and the current velocity
	Vector3 NewPosition = Transform.Location + Vel;

	//make sure the camera has actually been told to move
	if (Transform.Location != NewPosition) {
		//move camera to the new position
		Translate(NewPosition);
	}
}

glm::mat4 Camera::GetViewMatrix() const
{
	//eye - view position of the camera
	//center - what the eye is looking at (eye's position + forward direction normalized to max of 1)
	//up - local up direction
	return glm::lookAt(Transform.Location, Transform.Location + Directions.Forward, Directions.Up);
}

void Camera::RotatePitch(float Amount)
{
	//rotating -89 or +89 will result in yaw flip and flip the cam
	Transform.Rotation.x += Amount * CameraData.LookSensitivity;
	
	//clamp the result between two max values to avoid the flip
	if (Transform.Rotation.x > 89.0f)
		Transform.Rotation.x = 89.0f;

	if (Transform.Rotation.x < -89.0f)
		Transform.Rotation.x = -89.0f;
	UpdateDirectionVectors();
}

void Camera::RotateYaw(float Amount)
{
	//can currently increase to a max number
	Transform.Rotation.y += Amount * CameraData.LookSensitivity;

	//when the yaw gets to 360 change it to 0
	Transform.Rotation.y = glm::mod(Transform.Rotation.y, 360.0f);
	
	UpdateDirectionVectors();
}

void Camera::Update()
{
	if (CameraCollision != nullptr) {
		CameraCollision->SetLocation(Transform.Location);
	}
}

void Camera::UpdateDirectionVectors()
{
	//create a vector3 to initialilze a 0 direction
	Vector3 ForwardDirection;

	//cosine of the Yaw * cosine of the Pitch
	ForwardDirection.x = cos(glm::radians(Transform.Rotation.y)) * cos(glm::radians(Transform.Rotation.x));
	//sine of the pitch
	ForwardDirection.y = sin(glm::radians(Transform.Rotation.x));
	//sine of the Yaw and cosine of the pitch
	ForwardDirection.z = sin(glm::radians(Transform.Rotation.y)) * cos(glm::radians(Transform.Rotation.x));

	//normalize the direction to update hte values to be between 0 and 1
	ForwardDirection = glm::normalize(ForwardDirection);

	//set the forward direction
	Directions.Forward = ForwardDirection;
	//cross product - will allow us to get our right and up vectors from the forward vector
	//Cross product is the axis that is perpendicular to two other axis
	//set the right direction to alwasy be perpendicular to the world up axis
	//this means we strafe on the world x and z
	Directions.Right = glm::normalize(glm::cross(Directions.Forward, Vector3(0.0f, 1.0f, 0.0f)));
	//up direction is based on the local rotation of the forward and right directions
	Directions.Up = glm::normalize(glm::cross(Directions.Right, Directions.Forward));
}
