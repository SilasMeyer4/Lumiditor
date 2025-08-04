/**
 * @file colors.h
 * @brief Defines color utilities and macros for the LumidiGui namespace using raylib's Color struct.
 *
 * This header provides functions and macros to facilitate the creation and manipulation
 * of RGBA color values within the LumidiGui namespace. It includes a utility function
 * for constructing Color structs from individual RGBA components and a macro for
 * creating color literals.
 *
 * Dependencies:
 * - raylib.h: Provides the Color struct definition.
 *
 * Macros:
 * - LUMIDIGUI_COLOR(r, g, b, a): Creates a Color literal with the specified RGBA values.
 */
#ifndef LUMIDI_GUI_COLORS_H
#define LUMIDI_GUI_COLORS_H

#include "raylib.h"

namespace LumidiGui
{
  /**
   * @brief Creates a Color struct from individual RGBA components.
   *
   * @param r Red component (0-255).
   * @param g Green component (0-255).
   * @param b Blue component (0-255).
   * @param a Alpha (opacity) component (0-255).
   * @return Color The resulting color with the specified RGBA values.
   */
  Color CreateColorRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
  {
    return Color{r, g, b, a}; // Default color: black with full opacity
  }

}

#define LUMIDIGUI_COLOR(r, g, b, a) \
  CLITERAL(Color) { r, g, b, a }

#endif // LUMIDI_GUI_COLORS_H