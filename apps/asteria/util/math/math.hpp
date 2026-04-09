
struct Vec2 {
    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}
    float x, y;
};

struct Vec3 {
    Vec3() : x(0), y(0), z(0) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
    float x, y, z;
};

struct QAngle_t {
    QAngle_t() : pitch(0), yaw(0), roll(0) {}
    QAngle_t(float pitch, float yaw, float roll) : pitch(pitch), yaw(yaw), roll(roll) {}
    float pitch, yaw, roll;
};
