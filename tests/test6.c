#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctools/json.h>


int main(int argc, char* argv[]){
    char* str = "{\"a\": 100, \"b\": [true, \"potato\\n\", null, -1e-13]}";

    json_t* json = json_parse(str);

    json_t* tmp = json_getValueByKey(json, "a");
    json_set(tmp, JSON_OBJECT, 0);

    json_set(json_addEntry(tmp, "c"), JSON_STRING, strdup("monkey!"));
    json_t* d = json_addEntry(tmp, "d");
    json_set(d, JSON_ARRAY, 0);

    json_set(json_addItem(d), JSON_BOOL, false);
    json_set(json_addItem(d), JSON_BOOL, true);

    char* str2 = json_stringify(json, 4);
    printf("%s\n\nresult: \n%s", str, str2);

    free(str2);
    json_destroy(json);

    getchar();
    return 0;
}
