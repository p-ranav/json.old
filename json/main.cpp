#include "json.h"

int main() {
  json output;
  output["structures"] = json();
  output["structures"]["properties"]["beds"] = "0";                   // value of type string
  output["structures"]["properties"]["doctors"] = 1;                  // value of type integer
  output["structures"]["properties"]["nurses"] = 2.47326874;          // value of type double
  auto keys = output["structures"]["properties"].keys();              // keys = ["beds", "doctors", "nurses"]
  auto query = output["structures"]["properties"]["nurses"].value();  // query = "2.47326874"
  output.print();
  system("PAUSE");
}