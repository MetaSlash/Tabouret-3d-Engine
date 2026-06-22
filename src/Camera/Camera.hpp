/**
 * @file Camera.hpp
 * @details src\Camera\Camera.hpp
 *
 * @author Tabouret
 * @date 14/06/2026
 */

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
  private:
    /// @brief 3D World coords of the camera (x, y, z)
    double xCoord, yCoord, zCoord;

    /// @brief horizontal rotation (like `no` with the head)
    double yawRot;

    /// @brief vertical rotation (like `yes` with the head)
    double pitchRot;

    /// @brief The field of view of the camera
    double feldOfView;

  public:
    double x(), y(), z();
    double pitch(), yaw();
    double fov();

    void setFov(double fov);
    void setCoords(double x, double y, double z);
    void setX(double x), setY(double y), setZ(double z);
    void setRotation(double yaw, double pitch);
    void setYaw(double yaw), setPitch(double pitch);

    Camera();
    Camera(double x, double y, double z);
    Camera(double x, double y, double z, double fov);
    Camera(double x, double y, double z, double yaw, double pitch);
};

#endif  // CAMERA_H