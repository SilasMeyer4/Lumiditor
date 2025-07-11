
#ifndef LUMIDI_GUI_INPUT_INPUT_MANAGER_H
#define LUMIDI_GUI_INPUT_INPUT_MANAGER_H

#include "raylib.h"
#include <iostream>
#include <vector>

namespace LumidiGui
{
  struct MouseInput
  {
    Vector2 position;                 // Position of the mouse
    bool leftButtonPressed = false;   // Left mouse button pressed state
    bool rightButtonPressed = false;  // Right mouse button pressed state
    bool middleButtonPressed = false; // Middle mouse button pressed state

    MouseInput() : position{0, 0} {} // Default constructor initializing position to (0, 0)
  };

  class InputManager
  {

  private:
    InputManager() = default; // Private constructor for singleton pattern

    static int exitKey_;                           // Default exit key
    static std::vector<int> pressedKeysThisFrame_; // Vector to store pressed keys
    static MouseInput mouseInput_;                 // Mouse input state

  public:
    // Delete copy constructor and assignment operator to prevent copying
    InputManager(const InputManager &) = delete;
    InputManager &operator=(const InputManager &) = delete;

    // Method to get the singleton instance
    static InputManager &GetInstance()
    {
      static InputManager instance; // Guaranteed to be destroyed, instantiated on first use
      return instance;
    }

    // Add input handling methods here
    void HandleInput()
    {
      pressedKeysThisFrame_.clear();
      int key;
      while (key = GetKeyPressed())
      {
        pressedKeysThisFrame_.push_back(key); // Store the pressed key
      }

      mouseInput_.position = GetMousePosition();                                   // Update mouse position
      mouseInput_.leftButtonPressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);     //
      mouseInput_.rightButtonPressed = IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);   // Update right button state
      mouseInput_.middleButtonPressed = IsMouseButtonPressed(MOUSE_MIDDLE_BUTTON); //
    }

    static void SetExitKey(int key)
    {
      exitKey_ = key; // Set the key used to exit the application
      ::SetExitKey(key);
    }

    static int GetExitKey()
    {
      return exitKey_; // Get the currently set exit key
    }

    static std::vector<int> GetPressedKeys()
    {
      return GetInstance().pressedKeysThisFrame_; // Return the keys pressed this frame
    }

    static MouseInput GetMouseInput()
    {
      return GetInstance().mouseInput_; // Return the current mouse input state
    }
  };

}

#endif // LUMIDI_GUI_INPUT_INPUT_MANAGER_H