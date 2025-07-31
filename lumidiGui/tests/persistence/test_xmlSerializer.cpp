#include <gtest/gtest.h>
#include "xmlSerializer.h"
#include "scene.h"
#include "element.h"
#include <filesystem>
#include <fstream>

using namespace LumidiGui;
using namespace LumidiGui::Data;

class DummyElement : public Element
{
public:
  DummyElement(const std::string &name, Vector3 pos, Vector3 size)
      : Element(name, pos, size) {}

  ElementType GetType() const override
  {
    return ElementType::Panel;
  }
};

class XmlSerializerTest : public ::testing::Test
{
protected:
  std::string testPath = "./test_output";
  std::string sceneName = "TestScene";

  void SetUp() override
  {
    // Cleanup vorheriger Testdateien
    std::filesystem::remove_all(testPath);
  }

  std::unique_ptr<Scene> CreateTestScene()
  {
    auto scene = std::make_unique<Scene>("TestScene");

    return scene;
  }
};

TEST_F(XmlSerializerTest, SerializeScene_WritesFileWithCorrectContent)
{
  auto scene = CreateTestScene();

  XmlSerializer serializer;
  serializer.SetFilePath(testPath);

  EXPECT_NO_THROW(serializer.SerializeScene(*scene));

  // Prüfe, ob Datei existiert
  std::string filename = testPath + "/" + sceneName + ".xml";
  EXPECT_TRUE(std::filesystem::exists(filename));

  // Lade XML und prüfe Inhalt
  pugi::xml_document doc;
  auto result = doc.load_file(filename.c_str());
  EXPECT_TRUE(result);

  auto sceneNode = doc.child("Scene");
  ASSERT_TRUE(sceneNode);

  EXPECT_STREQ(sceneNode.attribute("name").value(), sceneName.c_str());

  auto elementNode = sceneNode.child("Element");
  ASSERT_TRUE(elementNode);
  EXPECT_STREQ(elementNode.attribute("name").value(), "root");
  EXPECT_STREQ(elementNode.attribute("size").value(), "0, 0, 0");
  EXPECT_STREQ(elementNode.attribute("position").value(), "0, 0, 0");
  EXPECT_EQ(elementNode.attribute("isEnabled").as_bool(), true);
  EXPECT_EQ(elementNode.attribute("isVisible").as_bool(), true);

  auto anchorsNode = elementNode.child("Anchors");
  ASSERT_TRUE(anchorsNode);
  EXPECT_EQ(anchorsNode.attribute("left").as_bool(), true);
  EXPECT_EQ(anchorsNode.attribute("right").as_bool(), false);
  EXPECT_EQ(anchorsNode.attribute("top").as_bool(), true);
  EXPECT_EQ(anchorsNode.attribute("bottom").as_bool(), false);
}