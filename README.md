# bstd::json

Integrate JSON with C++.

## Usage

### Clone and build

1. ```git clone git@github.com:benagin/bstd_json.git```
2. ```cd bstd_json```
3. ```make bstd_json```

##### Available build targets
1. Build everything: ```make``` or ```make all```
2. Build bstd_json: ```make bstd_json```
3. Build examples: ```make examples```
4. Build tests: ```make tests```
5. Build and install the library to ```/usr/local/lib```: ```make install```

More specific build commands in their relavent directories.

### Include public headers

Assuming the path to `bstd_json` is included with ```-I<path-to-bstd_json>``` or something similar:

* bstd::json public headers: ```#include "bstd/include/json/bstd_json.hpp"```

Alternatively, include ```bstd_json/include``` in gcc or equivalent:
* ```-Ibstd_json/include```

Then use (depending on which headers you need):
* ```#include <bstd_json.hpp>```

## Documentation

See https://benagin.github.io/bstd_json for documentation.
