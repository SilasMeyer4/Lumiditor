
#include <gtest/gtest.h>
#include "element.h"
#include "collider.h"
#include "uiBehavior.h"
#include <memory>

using namespace LumidiGui;

// Minimal concrete Element for testing
class TestElement : public Element
{
public:
  TestElement(std::string name, Vector3 pos, Vector3 size)
      : Element(name, pos, size) {}
  ElementType GetType() const override { return ElementType::Base; }
};

// Minimal concrete Collider for testing
class TestCollider : public Collider
{
public:
  TestCollider(Vector3 pos, Vector3 size) : Collider(pos, size) {}
  bool Contains(const Vector2 &) const override { return false; }
  bool Contains(const Vector3 &) const override { return false; }
};

// Minimal concrete UIBehavior for testing
class TestBehavior : public Events::UIBehavior
{
public:
  TestBehavior(std::weak_ptr<LumidiGui::Element> parent)
      : UIBehavior(parent) {}
  void Update(InputManager &) override {}
};

TEST(ElementTest, ConstructorSetsNameAndPosition)
{
  TestElement elem("Elem1", Vector3{1, 2, 3}, Vector3{4, 5, 6});
  EXPECT_EQ(elem.GetName(), "Elem1");
  EXPECT_EQ(elem.GetAbsolutePosition().x, 1);
  EXPECT_EQ(elem.GetAbsolutePosition().y, 2);
  EXPECT_EQ(elem.GetAbsolutePosition().z, 3);
  EXPECT_EQ(elem.GetSize().x, 4);
  EXPECT_EQ(elem.GetSize().y, 5);
  EXPECT_EQ(elem.GetSize().z, 6);
}

TEST(ElementTest, SetAndGetVisibility)
{
  TestElement elem("Elem1", Vector3{0, 0, 0}, Vector3{1, 1, 1});
  elem.SetVisible(false);
  EXPECT_FALSE(elem.IsVisible());
  elem.SetVisible(true);
  EXPECT_TRUE(elem.IsVisible());
}

TEST(ElementTest, SetAndGetEnabled)
{
  TestElement elem("Elem1", Vector3{0, 0, 0}, Vector3{1, 1, 1});
  elem.SetEnabled(false);
  EXPECT_FALSE(elem.IsEnabled());
  elem.SetEnabled(true);
  EXPECT_TRUE(elem.IsEnabled());
}

TEST(ElementTest, AddAndGetChild)
{
  auto parent = std::make_shared<TestElement>("parent", Vector3{0, 0, 0}, Vector3{1, 1, 1});
  auto child = std::make_shared<TestElement>("child", Vector3{1, 1, 1}, Vector3{2, 2, 2});
  parent->AddChild(child);
  auto found = parent->GetChildByName("child");
  ASSERT_NE(found, nullptr);
  EXPECT_EQ(found->GetName(), "child");
}

TEST(ElementTest, RemoveChild)
{
  auto parent = std::make_shared<TestElement>("parent", Vector3{0, 0, 0}, Vector3{1, 1, 1});
  auto child = std::make_shared<TestElement>("child", Vector3{1, 1, 1}, Vector3{2, 2, 2});
  parent->AddChild(child);
  parent->RemoveChild(child);
  auto found = parent->GetChildByName("child");
  EXPECT_EQ(found, nullptr);
}

TEST(ElementTest, AddAndGetCollider)
{
  TestElement elem("Elem1", Vector3{0, 0, 0}, Vector3{1, 1, 1});
  elem.AddCollider<TestCollider>("main");
  auto collider = elem.GetCollider("main");
  EXPECT_NE(collider, nullptr);
  EXPECT_EQ(dynamic_cast<TestCollider *>(collider.get()) != nullptr, true);
}

TEST(ElementTest, AddMultipleColliders)
{
  TestElement elem("Elem1", Vector3{0, 0, 0}, Vector3{1, 1, 1});
  elem.AddCollider<TestCollider>("main");
  elem.AddCollider<TestCollider>("secondary");
  EXPECT_NE(elem.GetCollider("main"), nullptr);
  EXPECT_NE(elem.GetCollider("secondary"), nullptr);
  EXPECT_EQ(elem.GetCollider("notfound"), nullptr);
}

TEST(ElementTest, AddAndGetBehavior)
{
  TestElement elem("Elem1", Vector3{0, 0, 0}, Vector3{1, 1, 1});
  elem.AddBehavior<TestBehavior>();
  const auto &behaviors = elem.GetBehaviors();
  EXPECT_FALSE(behaviors.empty());
  bool found = false;
  for (const auto &b : behaviors)
  {
    if (dynamic_cast<TestBehavior *>(b.get()) != nullptr)
      found = true;
  }
  EXPECT_TRUE(found);
}

TEST(ElementTest, AddMultipleBehaviors)
{
  TestElement elem("Elem1", Vector3{0, 0, 0}, Vector3{1, 1, 1});
  elem.AddBehavior<TestBehavior>();
  elem.AddBehavior<TestBehavior>();
  EXPECT_GE(elem.GetBehaviors().size(), 2);
}
