#include <optional>

namespace LumidiGui
{
  /**
   * @struct Anchors
   * @brief Specifies which sides of a UI element are anchored.
   *
   * Used to determine how a UI element is positioned and resized relative to its parent.
   */
  struct Anchors
  {
    /** @brief If true, the element is anchored to the left side. */
    bool left = true;
    /** @brief If true, the element is anchored to the right side. */
    bool right = false;
    /** @brief If true, the element is anchored to the top side. */
    bool top = true;
    /** @brief If true, the element is anchored to the bottom side. */
    bool bottom = false;
  };

  /**
   * @struct Offsets
   * @brief Specifies the offset values for each side of a UI element.
   *
   * Used to define the distance from each anchored side.
   */
  struct Offsets
  {
    /** @brief Offset from the left side. */
    float left = 0.f;
    /** @brief Offset from the right side. */
    float right = 0.f;
    /** @brief Offset from the top side. */
    float top = 0.f;
    /** @brief Offset from the bottom side. */
    float bottom = 0.f;
  };
}