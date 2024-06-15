#pragma once

#include <glm/glm.hpp>

class Camera {
private:
    glm::vec3 pos;
    glm::vec3 target;
    glm::vec3 up;
    glm::mat4 viewMatrix;

    float fov;
    float aspect;
    float nearPlane;
    float farPlane;
    glm::mat4 projectionMatrix;

    float dist;  /* distance to target            */
    float yaw;   /* rotation angle around y axis  */
    float pitch; /* rotation angle around x axis  */

public:
    Camera(
        const glm::vec3& target, float dist, float yaw, float pitch,
        float fov, float aspect, float nearPlane, float farPlane
    );

    ~Camera();

    /* View model */
    glm::vec3 getPos    () const;
    glm::vec3 getTarget () const;
    glm::vec3 getUp     () const;
    glm::vec3 getDir    () const;

    glm::mat4 getViewMatrix () const;

    void setTarget (const glm::vec3& newTarget);

    void updateViewMatrix();


    /* Projection model */
    float     getFov       () const;
    float     getAspect    () const;
    float     getNearPlane () const;
    float     getFarPlane  () const;

    glm::mat4 getProjectionMatrix () const;

    void setFov       ( float newFov       );
    void setAspect    ( float newAspect    );
    void setNearPlane ( float newNearPlane );
    void setFarPlane  ( float newFarPlane  );

    void updateProjectionMatrix();


    /* Rotation model */
    float getDist  () const;
    float getYaw   () const;
    float getPitch () const;

    void setDist  ( float newDist  );
    void setYaw   ( float newYaw   );
    void setPitch ( float newPitch );

    void updatePosition();
};