# bencode.h: A stb-style header only library for decoding bencoded data

[![patreon](https://img.shields.io/badge/patreon-FF5441?style=for-the-badge&logo=Patreon)](https://www.patreon.com/hughdavenport)
[![youtube](https://img.shields.io/badge/youtube-FF0000?style=for-the-badge&logo=youtube)](https://www.youtube.com/watch?v=dqw7B6eR9P8&list=PL5r5Q39GjMDfetFdGmnhjw1svsALW1HIY)

This repo contains a [stb-style](https://github.com/nothings/stb/blob/master/docs/stb_howto.txt) header only library. All you need is [bencode.h](https://github.com/hughdavenport/bencode.h/raw/refs/heads/main/bencode.h).

[Bencode encoding](https://en.wikipedia.org/wiki/Bencode) is used in the bittorrent protocol, and is defined as part of [BEP3](https://www.bittorrent.org/beps/bep_0003.html).

    - Strings are length-prefixed base ten followed by a colon and the string. For example 4:spam corresponds to
      'spam'.
    - Integers are represented by an 'i' followed by the number in base 10 followed by an 'e'. For example i3e
      corresponds to 3 and i-3e corresponds to -3. Integers have no size limitation. i-0e is invalid. All encodings
      with a leading zero, such as i03e, are invalid, other than i0e, which of course corresponds to 0.
    - Lists are encoded as an 'l' followed by their elements (also bencoded) followed by an 'e'. For example
      l4:spam4:eggse corresponds to ['spam', 'eggs'].
    - Dictionaries are encoded as a 'd' followed by a list of alternating keys and their corresponding values followed
      by an 'e'. For example, d3:cow3:moo4:spam4:eggse corresponds to {'cow': 'moo', 'spam': 'eggs'} and
      d4:spaml1:a1:bee corresponds to {'spam': ['a', 'b']}. Keys must be strings and appear in sorted order (sorted
      as raw strings, not alphanumerics).

This library was developed during a [YouTube series](https://www.youtube.com/watch?v=dqw7B6eR9P8&list=PL5r5Q39GjMDfetFdGmnhjw1svsALW1HIY) where I implement [bittorrent from scratch](https://github.com/hughdavenport/codecrafters-bittorrent-c), which drove me to create the following libraries:
- Bencode decoding in [bencode.h](https://github.com/hughdavenport/bencode.h)
- SHA-1 hashing in [sha1.h](https://github.com/hughdavenport/sha1.h)
- URL parsing in [url.h](https://github.com/hughdavenport/url.h)
- HTTP communication in [http.h](https://github.com/hughdavenport/http.h)

To use the library, add `#define BENCODE_IMPLEMENTATION` exactly once (in your main.c may be a good place). You can `#include` the file as many times as you like.

An example file is shown below.
```c
#define BENCODE_IMPLEMENTATION
#include "bencode.h"

int main() {
    char *encoded = "d8:greetingl5:hello5:worldee";
    BencodedValue *value = decode_bencoded_bytes((uint8_t *)encoded, NULL);
    print_bencoded_value(value, (BencodedPrintConfig){0});
    printf("\n");
    if (value->type == DICT) {
        BencodedValue *greeting = bencoded_dict_value((BencodedDict *)value->data, "greeting");
        if (greeting->type == LIST) {
            printf("greeting keys:\n");
            BencodedList *list = (BencodedList *)greeting->data;
            while (list) {
                printf("- ");
                print_bencoded_value(list->value, (BencodedPrintConfig){0});
                printf("\n");
                list = list->next;
            }
        }
    }
    free_bencoded_value(value);
}
```

Test by saving the above to a file `example.c` and then running this
```sh
cc example.c
./a.out
```

It should give output:
```
{"greeting":["hello","world"]}
greeting keys:
- "hello"
- "world"
```

I don't really guarantee the security of this, yet. Please feel free to try find bugs and report them.

Please leave any comments about what you liked. Feel free to suggest any features or improvements.

You are welcome to support me financially if you would like on my [patreon](https://www.patreon.com/hughdavenport).
