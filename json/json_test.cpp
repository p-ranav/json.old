#include "json.h"

int main() {
  json record;

  record["projects"]["json"]["year"] = 2017;                         // value of type int  
  record["projects"]["json"]["url"] = "https://json.org";            // value of type string
  record["projects"]["json"]["commits/day"] = 5.21;                  // value of type double

  record["projects"]["llama"]["language"] = "C++";
  record["projects"]["llama"]["domain"] = "Linear Algebra";

  record["projects"]["opengl"]["language"] = "C";
  record["projects"]["opengl"]["url"] = "http://opengl.org";

  auto keys = record["projects"]["json"].keys();                     // ["year", "url", "commits/day"]
  auto query = record["projects"]["json"]["commits/day"].value();    // query = "5.21"

  record.print();                                                    // pretty prints json data
  system("PAUSE");
}