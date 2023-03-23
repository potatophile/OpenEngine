#include "Engine/Graphics/Camera.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
{
	UpdateDirectionVectors();

	Transform.Location += -Directions.Forward * 2.0f;
}

void Camera::Translate(Vector3 Location)
{
	Transform.Location = Location;

	UpdateDirectionVectors();
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
	Transform.Rotation.x += Amount;
	
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
	Transform.Rotation.y += Amount;

	//when the yaw gets to 360 change it to 0
	Transform.Rotation.y = glm::mod(Transform.Rotation.y, 360.0f);
	
	UpdateDirectionVectors();
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
