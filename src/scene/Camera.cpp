#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(
    const glm::vec3& target, float dist, float yaw, float pitch,
    float fov, float aspect, float nearPlane, float farPlane
)
    : target(target),
    dist(dist),
    yaw(yaw),
    pitch(pitch),
    fov(fov),
    aspect(aspect),
    nearPlane(nearPlane),
    farPlane(farPlane)

{
    UpdatePosition();
    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

/* View model */
glm::vec3 Camera::GetPos() const
{ return pos; }

glm::vec3 Camera::GetTarget() const
{ return target; }

glm::vec3 Camera::GetUp() const
{ return up; }

glm::vec3 Camera::GetDir() const
{ return glm::normalize(target - pos); }

glm::mat4 Camera::GetViewMatrix() const
{ return viewMatrix; }

void Camera::SetTarget(const glm::vec3& newTarget)
{
    glm::vec3 newDir = newTarget - pos;
    dist = glm::length(newDir);

    yaw = glm::degrees(glm::atan(newDir.z, newDir.x));
    pitch = glm::degrees(glm::asin(newDir.y / dist));

    target = newTarget;

    UpdatePosition();
}

void Camera::UpdateViewMatrix()
{ viewMatrix = glm::lookAt(pos, target, up); }


/* Projection model */
float Camera::GetFov() const
{ return fov; }

float Camera::GetAspect() const
{ return aspect; }

float Camera::GetNearPlane() const
{ return nearPlane; }

float Camera::GetFarPlane() const
{ return farPlane;  }

glm::mat4 Camera::GetProjectionMatrix() const
{ return projectionMatrix; }


void Camera::SetFov(float newFov)
{
    fov = newFov;
    UpdateProjectionMatrix();
}

void Camera::SetAspect(float newAspect)
{
    aspect = newAspect;
    UpdateProjectionMatrix();
}

void Camera::SetNearPlane(float newNearPlane)
{
    nearPlane = newNearPlane;
    UpdateProjectionMatrix();
}

void Camera::SetFarPlane(float newFarPlane)
{
    farPlane  = newFarPlane;
    UpdateProjectionMatrix();
}

void Camera::UpdateProjectionMatrix()
{ projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane); }


/* Rotation model */
float Camera::GetDist() const
{ return dist;  }

float Camera::GetYaw() const
{ return yaw;   }

float Camera::GetPitch() const
{ return pitch; }


void Camera::SetDist(float newDist)
{
    dist = newDist;
    UpdatePosition();
}

void Camera::SetYaw(float newYaw)
{
    yaw = newYaw;
    UpdatePosition();
}

void Camera::SetPitch(float newPitch)
{
    pitch = newPitch;
    UpdatePosition();
}

void Camera::UpdatePosition()
{
    pos.x = target.x + dist * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    pos.y = target.y + dist * sin(glm::radians(pitch));
    pos.z = target.z + dist * cos(glm::radians(pitch)) * sin(glm::radians(yaw));

    glm::vec3 front = glm::normalize(target - pos);
    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));

    UpdateViewMatrix();
}