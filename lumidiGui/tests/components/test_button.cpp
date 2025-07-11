#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include "button.h"
#include "uiElement2D.h"
#include "raylib.h"

using namespace LumidiGui;
using ::testing::_;        // Wildcard Matcher
using ::testing::NiceMock; // NiceMock suppresses warnings for uninteresting calls
using ::testing::Return;

// Mock for UICollider (RectangleCollider)
class MockRectangleCollider : public UICollider2D
{
public:
  MOCK_METHOD(bool, Contains, (Vector2), (const override));
  MOCK_METHOD(void, SetPosition, (Vector2), (const override));
  MOCK_METHOD(void, SetSize, (Vector2), (const override));
  MOCK_METHOD(Vector2, GetPosition, (), (const override));
  MOCK_METHOD(Vector2, GetSize, (), (const override));
};

// Mock for Button to intercept DrawChildren call
class MockButton : public Button
{
public:
  MockButton(const std::string &name, Vector2 pos, Vector2 size, const std::string &text = "Button")
      : Button(name, pos, size, text) {}

  MOCK_METHOD(void, DrawChildren, (), (const));

  // Provide method to call original DrawChildren (optional)
  void CallDrawChildren() const { Button::DrawChildren(); }
};

// Stub implementations for raylib draw functions to avoid linker errors
extern "C"
{
  void DrawRectangleV(Vector2 position, Vector2 size, Color color) { /* empty stub */ }
  void DrawText(const char *text, int posX, int posY, int fontSize, Color color) { /* empty stub */ }
}

// 1. Button draws with default parameters without errors
TEST(ButtonTest, DrawsWithDefaultParameters)
{
  Vector2 pos = {10, 20};
  Vector2 size = {100, 40};
  Button btn("btn1", pos, size);
  EXPECT_EQ(btn.text, "Button");
  EXPECT_EQ(btn.color, LIGHTGRAY);
  EXPECT_EQ(btn.hoverColor, DARKGRAY);
  EXPECT_EQ(btn.pressedColor, GRAY);
  EXPECT_EQ(btn.textColor, BLACK);
  EXPECT_EQ(btn.disabledColor, DARKGRAY);
  EXPECT_NO_THROW(btn.Draw());
}

// 2. Button draws with custom text and colors correctly
TEST(ButtonTest, CustomTextAndColors)
{
  Vector2 pos = {5, 5};
  Vector2 size = {50, 25};
  Button btn("btn2", pos, size, "Custom");
  btn.color = RED;
  btn.hoverColor = GREEN;
  btn.pressedColor = BLUE;
  btn.textColor = YELLOW;
  btn.disabledColor = ORANGE;
  EXPECT_EQ(btn.text, "Custom");
  EXPECT_EQ(btn.color, RED);
  EXPECT_EQ(btn.hoverColor, GREEN);
  EXPECT_EQ(btn.pressedColor, BLUE);
  EXPECT_EQ(btn.textColor, YELLOW);
  EXPECT_EQ(btn.disabledColor, ORANGE);
  EXPECT_NO_THROW(btn.Draw());
}

// 3. Draw invokes DrawChildren exactly once
TEST(ButtonTest, DrawInvokesDrawChildren)
{
  Vector2 pos = {0, 0};
  Vector2 size = {10, 10};
  NiceMock<MockButton> btn("btn3", pos, size, "ChildTest");
  EXPECT_CALL(btn, DrawChildren()).Times(1);
  btn.Draw();
}

// 4. Button handles empty string text gracefully
TEST(ButtonTest, EmptyText)
{
  Vector2 pos = {0, 0};
  Vector2 size = {30, 15};
  Button btn("btn4", pos, size, "");
  EXPECT_EQ(btn.text, "");
  EXPECT_NO_THROW(btn.Draw());
}

// 5. Button with zero size does not crash
TEST(ButtonTest, ZeroSize)
{
  Vector2 pos = {0, 0};
  Vector2 size = {0, 0};
  Button btn("btn5", pos, size, "Zero");
  EXPECT_EQ(btn.size.x, 0);
  EXPECT_EQ(btn.size.y, 0);
  EXPECT_NO_THROW(btn.Draw());
}

// 6. Button draws without error when invisible (no rendering expected)
TEST(ButtonTest, DrawWhenInvisible)
{
  Vector2 pos = {0, 0};
  Vector2 size = {20, 10};
  Button btn("btn6", pos, size, "Invisible");
  btn.isVisible = false;
  EXPECT_NO_THROW(btn.Draw());
}

// 7. Button initializes its collider correctly
TEST(ButtonTest, InitializesCollider)
{
  Vector2 pos = {1, 2};
  Vector2 size = {3, 4};
  Button btn("btn7", pos, size, "Collider");
  auto collider = btn.GetCollider();
  ASSERT_NE(collider, nullptr);
  EXPECT_EQ(collider->position.x, pos.x);
  EXPECT_EQ(collider->position.y, pos.y);
  EXPECT_EQ(collider->size.x, size.x);
  EXPECT_EQ(collider->size.y, size.y);
}

// 8. Button handles very long text string without crashing
TEST(ButtonTest, LongTextHandling)
{
  Vector2 pos = {0, 0};
  Vector2 size = {200, 40};
  std::string longText(1000, 'A');
  Button btn("btn8", pos, size, longText);
  EXPECT_EQ(btn.text.size(), 1000);
  EXPECT_NO_THROW(btn.Draw());
}
