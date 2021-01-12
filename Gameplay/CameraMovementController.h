#include <Kioto.h>

namespace NullGame
{
class CameraMovementController
{
public:
    CameraMovementController(Kioto::TransformComponent* cameraTransform, float32 moveAcceleration, float32 rotationAcceleration, float32 fwdMoveAcceleration, float32 keyboardAcceleration);

    void Update(float32 dt);
    void SetCameraTransform(Kioto::TransformComponent* cameraTransform);
    Kioto::TransformComponent* GetCameraTransform() const;

private:
    Kioto::TransformComponent* m_cameraTransform = nullptr;
    float32 m_moveAcceleration = 0.0f;
    float32 m_rotationAcceleration = 0.0f;
    float32 m_fwdMoveAcceleration = 0.0f;
    float32 m_keyboardAcceleration = 0.0f;
};

inline void CameraMovementController::SetCameraTransform(Kioto::TransformComponent* cameraTransform)
{
    m_cameraTransform = cameraTransform;
}

inline Kioto::TransformComponent* CameraMovementController::GetCameraTransform() const
{
    return m_cameraTransform;
}

}