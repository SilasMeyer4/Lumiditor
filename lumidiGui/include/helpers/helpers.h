/**
 * @file helpers.h
 * @brief Utility functions for the LumidiGui framework.
 */

#include "element.h"

namespace LumidiGui
{
  /**
   * @brief Calculates the center point of a given UI element.
   *
   * @param element The element for which to calculate the center.
   * @return The center point as a Vector2.
   */
  inline Vector2 CalculateCenterPoint(const Element &element)
  {
    float xCenter = (element.GetSize().x / 2.f);
    float yCenter = (element.GetSize().y / 2.f);
    return Vector2{xCenter, yCenter};
  }
}