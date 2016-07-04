#ifndef __SYSTEM_SETTINGS_RINGTONES_H__
#define __SYSTEM_SETTINGS_RINGTONES_H__

#include <sys/types.h>
#include <dirent.h>
#include <metadata_extractor.h>
#include <Elementary.h>

typedef struct _ugFsNodeInfo fileNodeInfo;
struct _ugFsNodeInfo {
	char *path;
	char *name;
	char *media_name;
};

int get_filelist_from_dir_path(char *path, Eina_List **file_list);
char *get_filename_from_fullname(const char *fullname);
inline char *strlower(char *str);

#if 0
void ringtone_play_sound(const char *sound_file, player_h **mp_handle);
void ringtone_stop_sound(void *data);
#endif

#endif /* __SYSTEM_SETTINGS_RINGTONES_H__ */
