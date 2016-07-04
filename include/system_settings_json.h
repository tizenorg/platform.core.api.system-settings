/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the License);
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef __TIZEN_SYSTEM_SETTING_JSON_H__
#define __TIZEN_SYSTEM_SETTING_JSON_H__

#include <stdlib.h>
#include <string.h>
#include <glib-object.h>
#include <json-glib/json-glib.h>


#ifdef __cplusplus
extern "C"
{
#endif

JsonParser* ss_json_ringtone_open_file(char* path);

void ss_json_ringtone_add(JsonNode *root, char* filename, char* nameval, char* pathval);

void ss_json_ringtone_print(JsonNode *root);

void ss_json_ringtone_remove(JsonNode *root,  char* filename, char* path_to_del);

int ss_json_ringtone_contain(JsonNode *root, char* newfile);

void ss_json_ringtone_list(JsonNode *root);

/*// */
#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_SYSTEM_SETTING_JSON_H__ */



