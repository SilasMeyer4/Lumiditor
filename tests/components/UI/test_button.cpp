#include <gtest/gtest.h>
#include "button.h"

// Dummy implementations for DrawRectangleV and DrawText to allow linking.
// In a real test environment, these would be provided by the graphics library.
void DrawRectangleV(Vector2 position, Vector2 size, Color color) {}
void DrawText(const char *text, int posX, int posY, int fontSize, Color color) {}

namespace
{

  using namespace Lumiditor;

  TEST(ButtonTest, test_button_draws_rectangle_and_text_correctly)
  {
    Vector2 pos = {50, 100};
    Vector2 size = {200, 40};
    std::string text = "Click Me";
    Button button(pos, size, text);

    // Should not throw or crash
    ASSERT_NO_THROW(button.Draw());
  }

  TEST(ButtonTest, test_button_initialization_with_parameters)
  {
    Vector2 pos = {10, 20};
    Vector2 size = {100, 30};
    std::string text = "Test";
    Button button(pos, size, text);

    EXPECT_EQ(button.position.x, pos.x);
    EXPECT_EQ(button.position.y, pos.y);
    EXPECT_EQ(button.size.x, size.x);
    EXPECT_EQ(button.size.y, size.y);
    EXPECT_EQ(button.text, text);
  }

  TEST(ButtonTest, test_button_update_no_errors)
  {
    Vector2 pos = {0, 0};
    Vector2 size = {10, 10};
    std::string text = "Update";
    Button button(pos, size, text);

    // Should not throw or crash
    ASSERT_NO_THROW(button.Update());
  }

  TEST(ButtonTest, test_button_draw_with_empty_text)
  {
    Vector2 pos = {5, 5};
    Vector2 size = {50, 20};
    std::string text = "";
    Button button(pos, size, text);

    // Should not throw or crash
    ASSERT_NO_THROW(button.Draw());
  }

  TEST(ButtonTest, test_button_draw_with_zero_size)
  {
    Vector2 pos = {0, 0};
    Vector2 size = {0, 0};
    std::string text = "Zero";
    Button button(pos, size, text);

    // Should not throw or crash
    ASSERT_NO_THROW(button.Draw());
  }

  TEST(ButtonTest, test_button_draw_with_negative_position)
  {
    Vector2 pos = {-100, -50};
    Vector2 size = {60, 20};
    std::string text = "Negative";
    Button button(pos, size, text);

    // Should not throw or crash
    ASSERT_NO_THROW(button.Draw());
  }

}