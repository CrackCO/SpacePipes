#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


Camera::Camera(
    const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& up, 
    float fov, float aspect, float nearPlane, float farPlane
)
    :
    pos ( pos ),
    dir ( dir ),
    up  ( up  ),

    fov       ( fov       ),
    aspect    ( aspect    ),
    nearPlane ( nearPlane ),
    farPlane  ( farPlane  )
{
    updateViewMatrix();
    updateProjectionMatrix();
}

Camera::~Camera() {}


glm::vec3 Camera::getPos        () const { return pos;        }
glm::vec3 Camera::getDir        () const { return dir;        }
glm::vec3 Camera::getUp         () const { return up;         }
glm::mat4 Camera::getViewMatrix () const { return viewMatrix; }

void Camera::setPos ( const glm::vec3& newPos ) { pos = newPos; updateViewMatrix(); }
void Camera::setDir ( const glm::vec3& newDir ) { dir = newDir; updateViewMatrix(); }
void Camera::setUp  ( const glm::vec3& newUp  ) { up  = newUp;  updateViewMatrix(); }

void Camera::updateViewMatrix()
{
    viewMatrix = glm::lookAt(pos, pos + dir, up);
}


float     Camera::getFov              () const { return fov;              }
float     Camera::getAspect           () const { return aspect;           }
float     Camera::getNearPlane        () const { return nearPlane;        }
float     Camera::getFarPlane         () const { return farPlane;         }
glm::mat4 Camera::getProjectionMatrix () const { return projectionMatrix; }

void Camera::setFov       ( float newFov       ) { fov       = newFov;       updateProjectionMatrix(); }
void Camera::setAspect    ( float newAspect    ) { aspect    = newAspect;    updateProjectionMatrix(); }
void Camera::setNearPlane ( float newNearPlane ) { nearPlane = newNearPlane; updateProjectionMatrix(); }
void Camera::setFarPlane  ( float newFarPlane  ) { farPlane  = newFarPlane;  updateProjectionMatrix(); }

void Camera::updateProjectionMatrix()
{
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}