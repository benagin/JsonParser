# bstd

A library of tools for use in my other projects.

## Tools

### bstd::json

Integrate JSON with C++.

### bstd::test

Unit testing framework.

## Usage

### Clone and build

1. ```git clone git@github.com:benagin/bstd.git```
2. ```cd bstd```
3. ```make bstd```

##### Available build targets
1. Build everything: ```make``` or ```make all```
2. Build all tools (excludes tests): ```make bstd```
2. Build a single tool: ```make json```, or ```make test```
3. Build examples: ```make examples```
4. Build tests: ```make tests```

More specific build commands in their relavent directories.

### Include public headers

Assuming the path to `bstd` is included with ```-I<path-to-bstd>``` or something similar:

* All public headers: ```#include "bstd/include/bstd.hpp"```
* bstd::json public headers: ```#include "bstd/include/json/bstd_json.hpp"```
* bstd::test public headers: ```#include "bstd/include/test/bstd_test.hpp"```

Alternatively, include ```bstd/include``` or ```bstd/include/<tool>``` in gcc or equivalent:
* ```-Ibstd/include```

Then use (depending on which headers you need):
* ```#include <bstd.hpp>```
* ```#include <bstd_json.hpp>```
* ```#include <bstd_test.hpp>```
