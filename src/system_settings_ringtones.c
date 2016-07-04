/*
 * system_settings_ringtones.c
 *
 * Copyright (c) 2000 - 2011 Samsung Electronics Co., Ltd.
 *
 * Contact: MyoungJune Park <mj2004.park@samsung.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <system_settings.h>
#include <system_settings_private.h>
#include "system_settings_ringtones.h"
#include "system_settings_json.h"

inline char *strlower(char *str)
{
	if (!str) return NULL;
	char *orig = str;
	for (; *str != '\0'; str++)
		*str = tolower(*str);
	return orig;
};

/*remove ext name */
char *get_filename_from_fullname(const char *fullname)
{
	//retvm_if(fullname == NULL, NULL, "fullname == NULL");
	if (fullname == NULL) return NULL;

	char tmp[512];
	snprintf(tmp, sizeof(tmp), "%s", fullname);

	char *name = strrchr(tmp, '.');
	if (name != NULL)
		*name = '\0';

	return strdup((char*)tmp);
}

char *get_media_basename(const char *dir_path, const char *name)
{
	//retv_if(isEmptyStr(dir_path) || isEmptyStr(name), NULL);
	if (dir_path == NULL) return NULL;

	char path[512] = {0, };
	snprintf(path, sizeof(path), "%s/%s", dir_path, name);

	metadata_extractor_h metadata = NULL;
	char *title = NULL;
	int ret = metadata_extractor_create(&metadata);
	if (ret == METADATA_EXTRACTOR_ERROR_NONE && metadata) {
		ret = metadata_extractor_set_path(metadata, path);
		if (ret == METADATA_EXTRACTOR_ERROR_NONE) {
			ret = metadata_extractor_get_metadata(
					metadata, METADATA_TITLE, &title);
			metadata_extractor_destroy(metadata);
			if (title)
				/*return (char *)g_strdup(title);*/
				return (char *)title;
			else
				return strdup(name);
		} else {
			metadata_extractor_destroy(metadata);
			return strdup(name);
		}
	} else {
		return strdup(name);
	}
}

int get_filelist_from_dir_path(char *path, Eina_List **file_list)
{
	SETTING_TRACE_BEGIN;
	DIR *pDir = NULL;
	struct dirent ent, *result;

	if (path == NULL)
	{
		SETTING_TRACE("dir path is null");
		return -1;
	}

	if (file_list == NULL)
	{
		SETTING_TRACE("file_list is null");
		return -1;
	}

	pDir = opendir(path);

	if (pDir == NULL)
		return -2;

	while (readdir_r(pDir, &ent, &result) == 0) {
		if (result == NULL)
			break;

		fileNodeInfo *pNode = NULL;

		if (strncmp(ent.d_name, ".", 1) == 0
				|| strcmp(ent.d_name, "..") == 0)
			continue;

		if ((ent.d_type & DT_REG) == 0)
			continue;

		pNode = (fileNodeInfo *) malloc(sizeof(fileNodeInfo));
		if (pNode == NULL)
			continue;

		memset(pNode, 0, sizeof(fileNodeInfo));

		pNode->path = strdup(path);
		pNode->name = strdup(ent.d_name);
		pNode->media_name = get_media_basename(
				pNode->path, pNode->name);

		*file_list = eina_list_append(*file_list, pNode);
	}
	closedir(pDir);
	//SETTING_TRACE_END;

	return 0;
}

