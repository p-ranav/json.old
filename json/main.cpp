#include "json.h"

int main() {
  json record;

  record["projects"]["json"]["year"] = 2017;                                             // value of type int  
  record["projects"]["json"]["url"] = "https://github.com/pranav-srinivas-kumar/json";   // value of type string
  record["projects"]["json"]["commits/day"] = 5.21;                                      // value of type string

  auto keys = record["projects"]["json"].keys();                                         // ["year", "url", "commits/day"]
  auto query = record["projects"]["json"]["commits/day"].value();                        // query = "5.21"

  record.print();
  /*

  */
  system("PAUSE");
}