#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include "uiManager.h"

// Mock für UIElement2D
class MockUIElement2D : public LumidiGui::UIElement2D
{
public:
  // Konstruktor ruft den Basisklassen-Konstruktor mit Standard-Position und -Größe auf
  MockUIElement2D(const std::string &n, Vector2 pos = {0, 0}, Vector2 size = {0, 0})
      : LumidiGui::UIElement2D(n, pos, size) {}

  // Draw() ist const in der Basisklasse
  MOCK_METHOD(void, Draw, (), (const, override));

  // Update() mit Parametern Vector2 und bool
  MOCK_METHOD(void, Update, (Vector2, bool), (override));
};

using ::testing::_;
using ::testing::NiceMock;

class UIManagerTest : public ::testing::Test
{
protected:
  LumidiGui::UIManager manager;
};

TEST_F(UIManagerTest, AddUniqueElement_Succeeds)
{
  auto element = std::make_shared<NiceMock<MockUIElement2D>>("unique");
  bool result = manager.AddElement(element);
  EXPECT_TRUE(result);

  auto retrieved = manager.GetElementByName("unique");
  EXPECT_EQ(retrieved, element);
}

TEST_F(UIManagerTest, GetElementByName_ReturnsCorrectElement)
{
  auto element = std::make_shared<NiceMock<MockUIElement2D>>("findme");
  manager.AddElement(element);

  auto found = manager.GetElementByName("findme");
  EXPECT_EQ(found, element);
}

TEST_F(UIManagerTest, RemoveElementByName_ElementIsRemoved)
{
  auto element = std::make_shared<NiceMock<MockUIElement2D>>("toremove");
  manager.AddElement(element);

  bool removed = manager.RemoveElement("toremove");
  EXPECT_TRUE(removed);

  auto found = manager.GetElementByName("toremove");
  EXPECT_EQ(found, nullptr);
}

TEST_F(UIManagerTest, AddDuplicateElementName_FailsWhenNotAllowed)
{
  auto element1 = std::make_shared<NiceMock<MockUIElement2D>>("dup");
  auto element2 = std::make_shared<NiceMock<MockUIElement2D>>("dup");
  manager.allowDuplicateNames = false;

  EXPECT_TRUE(manager.AddElement(element1));
  EXPECT_FALSE(manager.AddElement(element2));
}

TEST_F(UIManagerTest, RemoveNonExistentElementByName_ReturnsFalse)
{
  bool removed = manager.RemoveElement("doesnotexist");
  EXPECT_FALSE(removed);
}

TEST_F(UIManagerTest, GetElementByName_ReturnsNullptrIfNotFound)
{
  auto found = manager.GetElementByName("missing");
  EXPECT_EQ(found, nullptr);
}

TEST_F(UIManagerTest, AddElements_MultipleUniqueElementsAdded)
{
  auto e1 = std::make_shared<NiceMock<MockUIElement2D>>("a");
  auto e2 = std::make_shared<NiceMock<MockUIElement2D>>("b");
  auto e3 = std::make_shared<NiceMock<MockUIElement2D>>("c");

  bool result = manager.AddElements(e1, e2, e3);
  EXPECT_TRUE(result);

  EXPECT_EQ(manager.GetElementByName("a"), e1);
  EXPECT_EQ(manager.GetElementByName("b"), e2);
  EXPECT_EQ(manager.GetElementByName("c"), e3);
}

TEST_F(UIManagerTest, RemoveElementByPointer_ElementNotManaged_ReturnsFalse)
{
  auto notManaged = std::make_shared<NiceMock<MockUIElement2D>>("notmanaged");
  bool removed = manager.RemoveElement(notManaged);
  EXPECT_FALSE(removed);
}