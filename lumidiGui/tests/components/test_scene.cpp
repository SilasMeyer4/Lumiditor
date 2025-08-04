#include <gtest/gtest.h>
#include "scene.h"
#include "element.h"
#include <memory>

using namespace LumidiGui;

// Dummy Element implementation for testing
class DummyElement : public Element
{
public:
  DummyElement(std::string name, Vector3 pos, Vector3 size)
      : Element(name, pos, size) {}
  ElementType GetType() const override { return ElementType::Base; }
};

TEST(SceneTest, ConstructorSetsNameAndRoot)
{
  Scene scene("TestScene", "RootElement");
  EXPECT_EQ(scene.GetName(), "TestScene");
  auto root = scene.GetRootElement().lock();
  ASSERT_NE(root, nullptr);
  EXPECT_EQ(root->GetName(), "RootElement");
}

TEST(SceneTest, DefaultRootName)
{
  Scene scene("TestScene");
  auto root = scene.GetRootElement().lock();
  ASSERT_NE(root, nullptr);
  EXPECT_EQ(root->GetName(), "root");
}

TEST(SceneTest, SetAndGetName)
{
  Scene scene("TestScene");
  scene.SetName("NewName");
  EXPECT_EQ(scene.GetName(), "NewName");
}

TEST(SceneTest, AddAndRetrieveElement)
{
  Scene scene("TestScene");
  auto dummy = std::make_shared<DummyElement>("child", Vector3{1, 2, 3}, Vector3{4, 5, 6});
  scene.GetElementsMap()["child"] = dummy;
  auto found = scene.GetElementsMap().find("child");
  ASSERT_NE(found, scene.GetElementsMap().end());
  EXPECT_EQ(found->second.lock()->GetName(), "child");
}

TEST(SceneTest, RemoveElement)
{
  Scene scene("TestScene");
  auto dummy = std::make_shared<DummyElement>("child", Vector3{1, 2, 3}, Vector3{4, 5, 6});
  scene.GetElementsMap()["child"] = dummy;
  scene.GetElementsMap().erase("child");
  auto found = scene.GetElementsMap().find("child");
  EXPECT_EQ(found, scene.GetElementsMap().end());
}
