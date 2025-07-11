#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include "uiManager.h"

// Mock für UIElement2D
class MockUIElement2D : public LumidiGui::UIElement2D
{
public:
  MockUIElement2D(const std::string &n, Vector2 pos = {0, 0}, Vector2 size = {0, 0})
      : UIElement2D(n, pos, size) {}

  MOCK_METHOD(void, Draw, (), (const, override));
  MOCK_METHOD(void, Update, (Vector2, bool), (override));
};

using namespace LumidiGui;
using ::testing::_;        // Matcher für beliebige Argumente
using ::testing::NiceMock; // Für "ruhige" Mocks ohne Warnungen

class UIManagerTest : public ::testing::Test
{
protected:
  UIManager manager;
};

class DerivedMockElement : public MockUIElement2D
{
public:
  using MockUIElement2D::MockUIElement2D;
};

TEST_F(UIManagerTest, CreateUniqueElement_Succeeds)
{
  auto elementWeak = manager.Create<DerivedMockElement>("unique");
  ASSERT_FALSE(elementWeak.expired());

  auto element = elementWeak.lock();
  ASSERT_NE(element, nullptr);
  EXPECT_EQ(element->name, "unique");

  auto foundWeak = manager.GetElementByName("unique");
  auto found = foundWeak.lock();
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found, element);
}

TEST_F(UIManagerTest, CreateDuplicateElementName_FailsWhenNotAllowed)
{
  manager.allowDuplicateNames = false;

  auto e1Weak = manager.Create<DerivedMockElement>("dup");
  ASSERT_FALSE(e1Weak.expired());

  auto e2Weak = manager.Create<DerivedMockElement>("dup");
  EXPECT_TRUE(e2Weak.expired());
}

TEST_F(UIManagerTest, RemoveElementByName_ElementIsRemoved)
{
  auto elementWeak = manager.Create<DerivedMockElement>("toremove");
  ASSERT_FALSE(elementWeak.expired());

  bool removed = manager.RemoveElement("toremove");
  EXPECT_TRUE(removed);

  auto foundWeak = manager.GetElementByName("toremove");
  EXPECT_TRUE(foundWeak.expired());
}

TEST_F(UIManagerTest, RemoveNonExistentElementByName_ReturnsFalse)
{
  bool removed = manager.RemoveElement("doesnotexist");
  EXPECT_FALSE(removed);
}

TEST_F(UIManagerTest, GetElementByName_ReturnsNullIfNotFound)
{
  auto elementWeak = manager.GetElementByName("missing");
  EXPECT_TRUE(elementWeak.expired());
}

TEST_F(UIManagerTest, CreateChild_AttachesToParentCorrectly)
{
  auto parentWeak = manager.Create<DerivedMockElement>("parent");
  ASSERT_FALSE(parentWeak.expired());
  auto parent = parentWeak.lock();

  auto childWeak = manager.CreateChild<DerivedMockElement>("child", "parent");
  ASSERT_FALSE(childWeak.expired());
  auto child = childWeak.lock();
  auto children = parent->GetChildren();
  // parent->children ist vector<shared_ptr<UIElement2D>>
  ASSERT_EQ(children.size(), 1);
  EXPECT_EQ(children[0], child);
}

TEST_F(UIManagerTest, CreateChild_WithMissingParentFails)
{
  auto childWeak = manager.CreateChild<DerivedMockElement>("child", "nonexistent");
  EXPECT_TRUE(childWeak.expired());
}

TEST_F(UIManagerTest, MoveChildToAnotherParent_Succeeds)
{
  auto parent1Weak = manager.Create<DerivedMockElement>("parent1");
  auto parent2Weak = manager.Create<DerivedMockElement>("parent2");
  ASSERT_FALSE(parent1Weak.expired());
  ASSERT_FALSE(parent2Weak.expired());
  auto parent1 = parent1Weak.lock();
  auto parent2 = parent2Weak.lock();

  auto childWeak = manager.CreateChild<DerivedMockElement>("child", "parent1");
  ASSERT_FALSE(childWeak.expired());
  auto child = childWeak.lock();

  bool moved = manager.MoveChildToParent("child", "parent2");
  EXPECT_TRUE(moved);
  auto children1 = parent1->GetChildren();
  auto children2 = parent2->GetChildren();
  // Check child is removed from parent1 and added to parent2
  EXPECT_EQ(children1.size(), 0);
  ASSERT_EQ(children2.size(), 1);
  EXPECT_EQ(children2[0]->name, "child");
}

TEST_F(UIManagerTest, MoveChildToMissingParent_Fails)
{
  auto parent1Weak = manager.Create<DerivedMockElement>("parent1");
  ASSERT_FALSE(parent1Weak.expired());

  auto childWeak = manager.CreateChild<DerivedMockElement>("child", "parent1");
  ASSERT_FALSE(childWeak.expired());

  bool moved = manager.MoveChildToParent("child", "nonexistent");
  EXPECT_FALSE(moved);
}

TEST_F(UIManagerTest, Update_CallsUpdateOnEnabledElements)
{
  auto elementWeak = manager.Create<DerivedMockElement>("mock");
  ASSERT_FALSE(elementWeak.expired());

  auto element = elementWeak.lock();
  // Aktivieren (Standard ist true, aber sicherheitshalber)
  element->isEnabled = true;

  // Downcast zu Mock für EXPECT_CALL
  auto mockPtr = static_cast<MockUIElement2D *>(element.get());
  EXPECT_CALL(*mockPtr, Update(_, _)).Times(1);

  manager.Update({10, 10}, true);
}

TEST_F(UIManagerTest, Draw_CallsDrawOnVisibleElements)
{
  auto elementWeak = manager.Create<DerivedMockElement>("mock");
  ASSERT_FALSE(elementWeak.expired());

  auto element = elementWeak.lock();
  element->isVisible = true;

  auto mockPtr = static_cast<MockUIElement2D *>(element.get());
  EXPECT_CALL(*mockPtr, Draw()).Times(1);

  manager.Draw();
}
