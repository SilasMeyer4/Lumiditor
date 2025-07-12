#include "shapes.h"

#include "operatorOverloads.h"

void LumidiGui::Shapes::DrawCross(Vector2 position, Vector2 size, float lineWidth, Color color)
{
  DrawLineEx(position, position + Vector2{size.x, size.y}, lineWidth, color);
  DrawLineEx(position + Vector2{0.f, size.y}, position + Vector2{size.x, 0.f}, lineWidth, color);
}