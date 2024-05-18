#pragma once

#include <glm/glm.hpp>

class Camera {
private:
    glm::vec3 pos;
    glm::vec3 dir;
    glm::vec3 up;
    glm::mat4 viewMatrix;

    float fov;
    float aspect;
    float nearPlane;
    float farPlane;
    glm::mat4 projectionMatrix;

public:
    Camera::Camera(
        const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& up, 
        float fov, float aspect, float nearPlane, float farPlane
    );

    ~Camera();

    glm::vec3 getPos    () const;
    glm::vec3 getDir    () const;
    glm::vec3 getUp     () const;
    glm::mat4 getMatrix () const;


    float     getFov              () const;
    float     getAspect           () const;
    float     getNearPlane        () const;
    float     getFarPlane         () const;
    glm::mat4 getProjectionMatrix () const;


    void setPos ( const glm::vec3& newPos );
    void setDir ( const glm::vec3& newDir );
    void setUp  ( const glm::vec3& newUp  );

    void updateViewMatrix();


    void setFov       ( float newFov       );
    void setAspect    ( float newAspect    );
    void setNearPlane ( float newNearPlane );
    void setFarPlane  ( float newFarPlane  );

    void updateProjectionMatrix();
};