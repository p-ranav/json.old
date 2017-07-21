# JSON Manipulation Library for C++

## User Guide

```cpp
#include <json.h>

int main() {
  json record;
  
  record["projects"]["json"]["year"] = 2017;                                           // value of type int  
  record["projects"]["json"]["url"] = "https://github.com/pranav-srinivas-kumar/json"; // value of type string
  record["projects"]["json"]["commits/day"] = 5.21;                                    // value of type string
  
  auto keys = record["projects"]["json"].keys();                                       // ["year", "url", "commits/day"]
  auto query = record["projects"]["json"]["commits/day"].value();                      // query = "5.21"
  
  record.print();                                                                      // pretty print of JSON
  /*
  {
      "projects" :
      {
          "json" :
          {
              "commits/day" : "5.21",
              "url" : "https://github.com/pranav-srinivas-kumar/json",
              "year" : "2017"
          }
      }
  }
  */
}
```

## LICENSE

Copyright (c) 2017 Pranav Srinivas Kumar <pranav.srinivas.kumar@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
