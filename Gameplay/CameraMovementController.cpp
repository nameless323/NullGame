#include "stdafx.h"

#include "CameraMovementController.h"

namespace NullGame
{

CameraMovementController::CameraMovementController(Kioto::TransformComponent* cameraTransform, float32 moveAcceleration, float32 rotationAcceleration, float32 fwdMoveAcceleration)
    : m_cameraTransform(cameraTransform)
    , m_moveAcceleration(moveAcceleration)
    , m_rotationAcceleration(rotationAcceleration)
    , m_fwdMoveAcceleration(fwdMoveAcceleration)
{
}

void CameraMovementController::Update(float32 dt)
{
    Kioto::Vector3 thisFrameOffset;

    Kioto::eMouseWheelScroll scroll = Kioto::Input::GetMouseWheel();
    if (scroll == Kioto::eMouseWheelScroll::ScrollUp)
        thisFrameOffset.z += m_fwdMoveAcceleration;
    else if (scroll == Kioto::eMouseWheelScroll::ScrollDown)
        thisFrameOffset.z -= m_fwdMoveAcceleration;

    Kioto::Vector2i mouseRelativePosition = Kioto::Input::GetMouseRelativePosition();
    if (Kioto::Input::GetMouseHeldDown(Kioto::eMouseCodes::MouseMiddle))
    {
        thisFrameOffset.x = mouseRelativePosition.x * -m_moveAcceleration;
        thisFrameOffset.y = mouseRelativePosition.y * m_moveAcceleration;
    }

    float32 x = 0;
    float32 y = 0;
    if (scroll == Kioto::eMouseWheelScroll::ScrollNone && Kioto::Input::GetMouseHeldDown(Kioto::eMouseCodes::MouseRight))
    {
        x = Kioto::Math::DegToRad(-mouseRelativePosition.x * m_rotationAcceleration);
        y = Kioto::Math::DegToRad(-mouseRelativePosition.y * m_rotationAcceleration);
    }

    Kioto::Vector3 right = m_cameraTransform->Right();
    Kioto::Quaternion upRot({ 0.0f, 1.0f, 0.0f }, x);
    Kioto::Quaternion rightRot(right, y);
    Kioto::Quaternion frameRot = rightRot * upRot;
    Kioto::Quaternion finalRot = m_cameraTransform->GetWorldRotation() * frameRot;

    Kioto::Vector3 worldPos = m_cameraTransform->TransformPointToWorld(thisFrameOffset);

    if (Kioto::Input::GetIsButtonHeldDown(Kioto::eKeyCode::KeyCodeControl) && Kioto::Input::GetMouseHeldDown(Kioto::eMouseCodes::MouseRight))
    {
        x = Kioto::Math::DegToRad(mouseRelativePosition.x * m_rotationAcceleration);
        y = Kioto::Math::DegToRad(mouseRelativePosition.y * m_rotationAcceleration);
        Kioto::Vector3 rotateAround = m_cameraTransform->GetWorldPosition() + m_cameraTransform->Fwd() * 5.0f;
        worldPos = Kioto::Math::TransformHelpers::RotateAround(*m_cameraTransform, rotateAround, x, y);
        Kioto::Vector3 up = Kioto::Vector3::Up;
        Kioto::Matrix4 lookAt = Kioto::Matrix4::BuildLookAt(worldPos, rotateAround, up);
        finalRot = Kioto::Quaternion::FromMatrix(lookAt.Tranposed());
    }

    m_cameraTransform->SetWorldPosition(worldPos);
    m_cameraTransform->SetWorldRotation(finalRot);
}

}