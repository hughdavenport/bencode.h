#define BENCODE_IMPLEMENTATION
#include "bencode.h"

int main() {
    char *encoded = "d8:greetingl5:hello5:worldee";
    BencodedValue *value = decode_bencoded_bytes((uint8_t *)encoded, NULL);
    print_bencoded_value(value, (BencodedPrintConfig){0});
    if (value->type == DICT) {
        printf("data %p\n", value->data);
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
