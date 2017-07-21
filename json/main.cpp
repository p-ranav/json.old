#include "json.h"

int main() {
  json record;

  record["projects"]["json"]["year"] = 2017;                         // value of type int  
  record["projects"]["json"]["url"] = "http://json.org";             // value of type string
  record["projects"]["json"]["commits/day"] = 5.21;                  // value of type double

  auto keys = record["projects"]["json"].keys();                     // ["year", "url", "commits/day"]
  auto query = record["projects"]["json"]["commits/day"].value();    // query = "5.21"

  record.print();
  /*
  {
      "projects" :
      {
          "json" :
          {
              "commits/day" : "5.21",
              "url" : "https://json.org",
              "year" : "2017"
          }
      }
  }
  */
  system("PAUSE");
}