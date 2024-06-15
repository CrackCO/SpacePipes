#include "Camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(
    const glm::vec3& target, float dist, float yaw, float pitch,
    float fov, float aspect, float nearPlane, float farPlane
)
    :
    target ( target ),
    dist   ( dist   ),
    yaw    ( yaw    ),
    pitch  ( pitch  ),

    fov       ( fov       ),
    aspect    ( aspect    ),
    nearPlane ( nearPlane ),
    farPlane  ( farPlane  ) 

{
    updatePosition         ();
    updateViewMatrix       ();
    updateProjectionMatrix ();
}

Camera::~Camera() {}


/* View model */
glm::vec3 Camera::getPos    () const { return pos;    }
glm::vec3 Camera::getTarget () const { return target; }
glm::vec3 Camera::getUp     () const { return up;     }

glm::vec3 Camera::getDir () const { return glm::normalize(target - pos); }

glm::mat4 Camera::getViewMatrix () const { return viewMatrix; }

void Camera::setTarget(const glm::vec3& newTarget)
{
    glm::vec3 newDir = newTarget - pos;
    dist = glm::length(newDir);

    yaw = glm::degrees(glm::atan(newDir.z, newDir.x));
    pitch = glm::degrees(glm::asin(newDir.y / dist));

    target = newTarget;

    updatePosition();
}

void Camera::updateViewMatrix()
{
    viewMatrix = glm::lookAt(pos, target, up);
}


/* Projection model */
float Camera::getFov       () const { return fov;       }
float Camera::getAspect    () const { return aspect;    }
float Camera::getNearPlane () const { return nearPlane; }
float Camera::getFarPlane  () const { return farPlane;  }

glm::mat4 Camera::getProjectionMatrix () const { return projectionMatrix; }


void Camera::setFov       ( float newFov       ) { fov       = newFov;       updateProjectionMatrix(); }
void Camera::setAspect    ( float newAspect    ) { aspect    = newAspect;    updateProjectionMatrix(); }
void Camera::setNearPlane ( float newNearPlane ) { nearPlane = newNearPlane; updateProjectionMatrix(); }
void Camera::setFarPlane  ( float newFarPlane  ) { farPlane  = newFarPlane;  updateProjectionMatrix(); }

void Camera::updateProjectionMatrix()
{
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}


/* Rotation model */
float Camera::getDist  () const { return dist;  }
float Camera::getYaw   () const { return yaw;   }
float Camera::getPitch () const { return pitch; }


void Camera::setDist  ( float newDist  ) { dist  = newDist;  updatePosition(); }
void Camera::setYaw   ( float newYaw   ) { yaw   = newYaw;   updatePosition(); }
void Camera::setPitch ( float newPitch ) { pitch = newPitch; updatePosition(); }

void Camera::updatePosition()
{
    pos.x = target.x + dist * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    pos.y = target.y + dist * sin(glm::radians(pitch));
    pos.z = target.z + dist * cos(glm::radians(pitch)) * sin(glm::radians(yaw));

    glm::vec3 front = glm::normalize(target - pos);
    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));

    updateViewMatrix();
}