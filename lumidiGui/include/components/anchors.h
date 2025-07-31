#include <optional>

namespace LumidiGui
{
  struct Anchors
  {
    bool left = true;
    bool right = false;
    bool top = true;
    bool bottom = false;
  };

  struct Offsets
  {
    float left = 0.f;
    float right = 0.f;
    float top = 0.f;
    float bottom = 0.f;
  };
}