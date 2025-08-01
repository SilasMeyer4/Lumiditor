#ifndef LUMIDI_GUI_HELPERS_OPERATOR_OVERLOADS_H
#define LUMIDI_GUI_HELPERS_OPERATOR_OVERLOADS_H

#include "raylib.h"

inline Vector2 operator+(const Vector2 &a, const Vector2 &b)
{
  return {a.x + b.x, a.y + b.y};
}

inline Vector2 operator-(const Vector2 &a, const Vector2 &b)
{
  return {a.x - b.x, a.y - b.y};
}

inline Vector2 &operator+=(Vector2 &a, const Vector2 &b)
{
  a.x += b.x;
  a.y += b.y;
  return a;
}

inline Vector2 &operator-=(Vector2 &a, const Vector2 &b)
{
  a.x -= b.x;
  a.y -= b.y;
  return a;
}

inline Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

inline Vector3 &operator+=(Vector3 &a, const Vector3 &b)
{
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  return a;
}

inline Vector3 &operator-=(Vector3 &a, const Vector3 &b)
{
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  return a;
}

#endif