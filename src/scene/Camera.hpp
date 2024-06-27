#pragma once

#include <glm/glm.hpp>

#include <app/Definitions.hpp>


class Camera {
public:
    Camera(
        const glm::vec3& target, float dist, float yaw, float pitch,
        float fov, float aspect, float nearPlane, float farPlane
    );

    /* View model */
    SP_NODISCARD glm::vec3 GetPos() const;
    SP_NODISCARD glm::vec3 GetTarget() const;
    SP_NODISCARD glm::vec3 GetUp() const;
    SP_NODISCARD glm::vec3 GetDir() const;
    SP_NODISCARD glm::mat4 GetViewMatrix() const;

    void SetTarget(const glm::vec3& newTarget);

    void UpdateViewMatrix();


    /* Projection model */
    SP_NODISCARD float GetFov() const;
    SP_NODISCARD float GetAspect() const;
    SP_NODISCARD float GetNearPlane() const;
    SP_NODISCARD float GetFarPlane() const;
    SP_NODISCARD glm::mat4 GetProjectionMatrix() const;

    void SetFov(float newFov);
    void SetAspect(float newAspect);
    void SetNearPlane(float newNearPlane);
    void SetFarPlane(float newFarPlane);

    void UpdateProjectionMatrix();


    /* Rotation model */
    SP_NODISCARD float GetDist() const;
    SP_NODISCARD float GetYaw() const;
    SP_NODISCARD float GetPitch() const;

    void SetDist(float newDist);
    void SetYaw(float newYaw);
    void SetPitch(float newPitch);

    void UpdatePosition();

    ~Camera() = default;

private:
    glm::vec3 pos;
    glm::vec3 target;
    glm::vec3 up;
    glm::mat4 viewMatrix;

    float fov = 0.0f;
    float aspect = 0.0f;
    float nearPlane = 0.0f;
    float farPlane = 0.0f;
    glm::mat4 projectionMatrix;

    float dist = 0.0f;  /* distance to target */
    float yaw = 0.0f;   /* rotation angle around y axis */
    float pitch = 0.0f; /* rotation angle around x axis */
};