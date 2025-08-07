#include <iostream>
#include "externalWindows.h"

int main(int argc, char *argv[])
{
  if (argc > 1 && std::string(argv[2]) == "--type=dialog")
  {
    LumidiGui::CreateDialogWindow(std::string(argv[1]), std::string(argv[3])); // Assuming ShowDialogWindow takes a type as an argumentq
  }
  else if (argc > 1 && std::string(argv[1]) == "--type=main")
  {
  }
  else
  {
    // Default: e.g. normal window
  }

  return 0;
}