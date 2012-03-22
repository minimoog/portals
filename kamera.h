#ifndef KAMERA_H
#define KAMERA_H

#include "math/tmat4.h"
#include "math/tvec4.h"

class Kamera
{
public:
    Kamera();
    Kamera(float eyeVec3[], float atVec3[], float upVec3[]);
    Kamera(float eyex, float eyey, float eyez,
           float atx, float aty, float atz,
           float upx, float upy, float upz);
    ~Kamera();

    void lookat(float eyeVec3[], float atVec3[], float upVec3[]);

    void moveForward(float f);
    void moveSide(float s);
    void moveUp(float u);
    void rotateX(float angle);
    void rotateXX(float angle);
    void rotateY(float angle);
    void rotateYY(float angle);

    void setPerspectiveViewFOV(float fovy, float aspect, float zn, float zf);
    void setPerspectiveViewWH(float w, float h, float zn, float zf);

    TVec3& getEyePos();
    TMat4& getViewMatrix();
    float* getProjMatrix();
    float  getWidthNearPlane() const;
    float  getHeightNearPlane() const;
    float  getZNearPlane() const;
    float  getZFarPlane() const;
    TVec3  getDirection() const;
    TVec3  getUp() const;
    TVec3  getRight() const;

private:
    TQuat m_rotQuat;
    TMat4 m_viewMatrix;
    TMat4 m_projMatrix;
    TVec3 m_eyePos;
    float m_wnearplane;
    float m_hnearplane;
    float m_znear;
    float m_zfar;
};

#endif // KAMERA_H
