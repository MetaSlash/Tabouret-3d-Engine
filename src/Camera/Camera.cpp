#include "Camera.hpp"

// Getters
double Camera::x() { return xCoord; }
double Camera::y() { return yCoord; }
double Camera::z() { return zCoord; }

double Camera::yaw() { return yawRot; }
double Camera::pitch() { return pitchRot; }

double Camera::fov() { return feldOfView; }

// Setters
void Camera::setFov(double fov) { feldOfView = fov; }
void Camera::setCoords(double x, double y, double z) {
    xCoord = x;
    yCoord = y;
    zCoord = z;
}
void Camera::setX(double x) { xCoord = x; }
void Camera::setY(double y) { yCoord = y; }
void Camera::setZ(double z) { zCoord = z; }
void Camera::setYaw(double yaw) { yawRot = yaw; }
void Camera::setPitch(double pitch) { pitchRot = pitch; }
void Camera::setRotation(double yaw, double pitch) {
    yawRot = yaw;
    pitchRot = pitch;
}

// Constructors
Camera::Camera() {
    xCoord = 0;
    yCoord = 0;
    zCoord = 0;
    yawRot = 0;
    pitchRot = 0;
    feldOfView = 90.0;
}

Camera::Camera(double x, double y, double z) {
    xCoord = x;
    yCoord = y;
    zCoord = z;
    yawRot = 0;
    pitchRot = 0;
    feldOfView = 90.0;
}

Camera::Camera(double x, double y, double z, double fov) {
    xCoord = x;
    yCoord = y;
    zCoord = z;
    yawRot = 0;
    pitchRot = 0;
    feldOfView = fov;
}

Camera::Camera(double x, double y, double z, double yaw, double pitch) {
    xCoord = x;
    yCoord = y;
    zCoord = z;
    yawRot = yaw;
    pitchRot = pitch;
    feldOfView = 90.0;
}
