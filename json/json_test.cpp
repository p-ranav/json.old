#include "json.h"

int main() {
  json record;

  record["projects"]["json"]["year"] = 2017;                         
  record["projects"]["json"]["url"] = "https://json.org";            
  record["projects"]["json"]["commits/day"] = 5.21;

  record["projects"]["llama"]["language"] = "C++";
  record["projects"]["llama"]["domain"] = "Linear Algebra";

  record["projects"]["rosmod"]["language"] = "C++/Python";
  record["projects"]["rosmod"]["url"] = "https://github.com/rosmod";

  auto keys = record["projects"]["json"].keys();                     // ["year", "url", "commits/day"]
  auto query = record["projects"]["json"]["commits/day"].value();    // query = "5.21"

  std::string record_string = record.to_string();                    // returns a string of the json
  record.print();                                                    // pretty prints json data
  record.write("clone.json");                                        // writes json to file
  
  system("PAUSE");
}