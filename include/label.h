#ifndef LUMIDITOR_LABEL_H
#define LUMIDITOR_LABEL_H

#include "raylib.h"
#include "uiElement2D.h"

namespace Lumiditor
{
  class Label : public UIElement2D
  {
  private:
    /* data */
  public:
    Label(/* args */);
    ~Label();
  };
}

#endif // LUMIDITOR_LABEL_H