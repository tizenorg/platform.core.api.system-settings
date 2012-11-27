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


#ifndef __TIZEN_SYSTEM_SETTING_PRIVATE_H__
#define __TIZEN_SYSTEM_SETTING_PRIVATE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_NAME  "db/setting/accessibility/font_name"

typedef enum {
	SYSTEM_SETTING_DATA_TYPE_STRING,
	SYSTEM_SETTING_DATA_TYPE_INT,
	SYSTEM_SETTING_DATA_TYPE_DOUBLE,
	SYSTEM_SETTING_DATA_TYPE_BOOL,
} system_setting_data_type_e;


typedef int (*system_setting_get_value_cb) (system_settings_key_e key, system_setting_data_type_e data_type, void** value);
typedef int (*system_setting_set_value_cb) (system_settings_key_e key, system_setting_data_type_e data_type, void* value);

typedef int (*system_setting_set_changed_callback_cb)(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
typedef int (*system_setting_unset_changed_callback_cb)(system_settings_key_e key);


typedef struct {
	system_settings_key_e key;										/* key */
	system_setting_data_type_e data_type;
	system_setting_get_value_cb get_value_cb;						/* get value */
	system_setting_set_value_cb set_value_cb;						/* set value */

	system_setting_set_changed_callback_cb set_changed_cb;
	system_setting_unset_changed_callback_cb unset_changed_cb ;

	system_settings_changed_cb changed_cb;							/* registered by user application */
} system_setting_s;

typedef system_setting_s* system_setting_h;


int system_settings_get_item(system_settings_key_e key, system_setting_h *item);


// get
int system_setting_vconf_get_value_int(const char *vconf_key, int *value);
int system_setting_vconf_get_value_bool(const char *vconf_key, bool *value);
int system_setting_vconf_get_value_double(const char *vconf_key, double *value);
int system_setting_vconf_get_value_string(const char *vconf_key, char **value);

// set
int system_setting_vconf_set_value_int(const char *vconf_key, int value);
int system_setting_vconf_set_value_bool(const char *vconf_key, bool value);
int system_setting_vconf_set_value_double(const char *vconf_key, double value);
int system_setting_vconf_set_value_string(const char *vconf_key, char *value);


int system_setting_vconf_set_changed_cb(const char *vconf_key, system_settings_key_e system_setting_key, int slot);
int system_setting_vconf_unset_changed_cb(const char *vconf_key, int slot);

int system_setting_get_incoming_call_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_email_alert_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_wallpaper_home_screen(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_wallpaper_lock_screen(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_font_size(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_font_type(system_settings_key_e key, system_setting_data_type_e data_type, void** value);
int system_setting_get_motion_activation(system_settings_key_e key, system_setting_data_type_e data_type, void** value);

int system_setting_set_incoming_call_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_email_alert_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_wallpaper_home_screen(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_wallpaper_lock_screen(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_font_size(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_font_type(system_settings_key_e key, system_setting_data_type_e data_type, void* value);
int system_setting_set_motion_activation(system_settings_key_e key, system_setting_data_type_e data_type, void* value);

int system_setting_set_changed_callback_incoming_call_ringtone(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_incoming_call_ringtone(system_settings_key_e key);

int system_setting_set_changed_callback_email_alert_ringtone(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_email_alert_ringtone(system_settings_key_e key);

int system_setting_set_changed_callback_wallpaper_home_screen(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_wallpaper_home_screen(system_settings_key_e key);

int system_setting_set_changed_callback_wallpaper_lock_screen(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_wallpaper_lock_screen(system_settings_key_e key);

int system_setting_set_changed_callback_font_size(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_font_size(system_settings_key_e key);

int system_setting_set_changed_callback_font_type(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_font_type(system_settings_key_e key);

int system_setting_set_changed_callback_motion_activation(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);
int system_setting_unset_changed_callback_motion_activation(system_settings_key_e key);



#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_SYSTEM_SETTING_PRIVATE_H__ */



