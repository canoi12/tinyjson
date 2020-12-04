# tiny json

tiny json is a small json parser lib, its based on https://craftinginterpreters.com/ chapters about parsing.

```json
{
  "name": "Player",
  "type": "Player",
  "life": 10,
  "image": "image.png",
  "position": {
    "x": 10,
    "y": 10
  },
  "speed": 95.55,
  "items": [15, 25, 55, 90, 1, 2]
}
```

```c
#include "tinyjson.h"

int main(int argc, char **argv) {
  tjson_t *json = tjson_open("teste.json");

  tjson_t *image = tjson_object_get(json, "image");
  printf("image name: %s\n", image->string);

  return 0;
}
```