/**
 * @file operatorOverloads.h
 * @brief Operator overloads for Vector2 and Vector3 arithmetic.
 */

#ifndef LUMIDI_GUI_HELPERS_OPERATOR_OVERLOADS_H
#define LUMIDI_GUI_HELPERS_OPERATOR_OVERLOADS_H

#include "raylib.h"

/**
 * @brief Adds two Vector2 values component-wise.
 * @param a The first vector.
 * @param b The second vector.
 * @return The sum of the two vectors.
 */
inline Vector2 operator+(const Vector2 &a, const Vector2 &b)
{
  return {a.x + b.x, a.y + b.y};
}

/**
 * @brief Subtracts two Vector2 values component-wise.
 * @param a The first vector.
 * @param b The second vector.
 * @return The difference of the two vectors.
 */
inline Vector2 operator-(const Vector2 &a, const Vector2 &b)
{
  return {a.x - b.x, a.y - b.y};
}

/**
 * @brief Adds another Vector2 to this Vector2 in-place.
 * @param a The vector to modify.
 * @param b The vector to add.
 * @return Reference to the modified vector.
 */
inline Vector2 &operator+=(Vector2 &a, const Vector2 &b)
{
  a.x += b.x;
  a.y += b.y;
  return a;
}

/**
 * @brief Subtracts another Vector2 from this Vector2 in-place.
 * @param a The vector to modify.
 * @param b The vector to subtract.
 * @return Reference to the modified vector.
 */
inline Vector2 &operator-=(Vector2 &a, const Vector2 &b)
{
  a.x -= b.x;
  a.y -= b.y;
  return a;
}

/**
 * @brief Adds two Vector3 values component-wise.
 * @param a The first vector.
 * @param b The second vector.
 * @return The sum of the two vectors.
 */
inline Vector3 operator+(const Vector3 &a, const Vector3 &b)
{
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

/**
 * @brief Subtracts two Vector3 values component-wise.
 * @param a The first vector.
 * @param b The second vector.
 * @return The difference of the two vectors.
 */
inline Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

/**
 * @brief Adds another Vector3 to this Vector3 in-place.
 * @param a The vector to modify.
 * @param b The vector to add.
 * @return Reference to the modified vector.
 */
inline Vector3 &operator+=(Vector3 &a, const Vector3 &b)
{
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
  return a;
}

/**
 * @brief Subtracts another Vector3 from this Vector3 in-place.
 * @param a The vector to modify.
 * @param b The vector to subtract.
 * @return Reference to the modified vector.
 */
inline Vector3 &operator-=(Vector3 &a, const Vector3 &b)
{
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
  return a;
}

#endif