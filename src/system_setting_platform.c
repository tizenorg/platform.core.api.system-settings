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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <dlog.h>
#include <vconf.h>

#include <glib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include <Ecore_X.h>
#include <Elementary.h>

#include <system_settings.h>
#include <system_settings_private.h>


#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define SMALL_FONT_DPI                      (-80)
#define MIDDLE_FONT_DPI                     (-100)
#define LARGE_FONT_DPI                      (-150)
#define HUGE_FONT_DPI                       (-190)
#define GIANT_FONT_DPI                      (-250)

#define SETTING_FONT_CONF_FILE "/opt/etc/fonts/conf.avail/99-slp.conf"
#define SETTING_STR_SLP_LEN  256

static char* _get_cur_font();
static void font_size_set();
static int __font_size_get();

static void font_config_set(char *font_name);
static void font_config_set_notification();

int system_setting_get_incoming_call_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	char* vconf_value;
	if (system_setting_vconf_get_value_string(VCONFKEY_SETAPPL_CALL_RINGTONE_PATH_STR, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	*value = vconf_value;
	return SYSTEM_SETTINGS_ERROR_NONE;
}


int system_setting_get_wallpaper_home_screen(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	char* vconf_value;
	if (system_setting_vconf_get_value_string(VCONFKEY_BGSET, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	*value = vconf_value;
	return SYSTEM_SETTINGS_ERROR_NONE;
}


int system_setting_get_wallpaper_lock_screen(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	char* vconf_value;

	if (system_setting_vconf_get_value_string(VCONFKEY_IDLE_LOCK_BGSET, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	*value = vconf_value;

	return SYSTEM_SETTINGS_ERROR_NONE;
}


// [int] vconf GET
int system_setting_get_font_size(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	printf("system_setting_get_font_size \n");
	int vconf_value;

	if (system_setting_vconf_get_value_int(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	*value = (void*)vconf_value;

	return SYSTEM_SETTINGS_ERROR_NONE;
}


// [int] vconf GET
int system_setting_get_font_type(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	printf("system_setting_get_font_type\n");
	//int vconf_value;

	char* font_name = _get_cur_font();
	#if 0
	if (system_setting_vconf_get_value_int(VCONFKEY_SETAPPL_FONT_TYPE_INT, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	//*value = (void*)vconf_value;
	#endif
	*value = (void*)font_name;

	return SYSTEM_SETTINGS_ERROR_NONE;
}


int system_setting_get_motion_activation(system_settings_key_e key, system_setting_data_type_e data_type, void** value)
{
	bool vconf_value;

	if (system_setting_vconf_get_value_bool(VCONFKEY_SETAPPL_MOTION_ACTIVATION, &vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	*value = (void*)vconf_value;

	return SYSTEM_SETTINGS_ERROR_NONE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int system_setting_set_incoming_call_ringtone(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	printf(" mock --> real system_setting_set_incoming_call_ringtone \n");
	char* vconf_value;
	vconf_value = (char*)value;
	if (system_setting_vconf_set_value_string(VCONFKEY_SETAPPL_CALL_RINGTONE_PATH_STR, vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	return SYSTEM_SETTINGS_ERROR_NONE;
}

int system_setting_set_wallpaper_home_screen(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	printf(" mock --> real system_setting_set_wallpaper_home_screen \n");

	char* vconf_value;
	vconf_value = (char*)value;
	if (system_setting_vconf_set_value_string(VCONFKEY_BGSET, vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	return SYSTEM_SETTINGS_ERROR_NONE;
}

int system_setting_set_wallpaper_lock_screen(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	printf(" mock --> real system_setting_set_wallpaper_lock_screen \n");

	char* vconf_value;
	vconf_value = (char*)value;
	if (system_setting_vconf_set_value_string(VCONFKEY_IDLE_LOCK_BGSET, vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}

	return SYSTEM_SETTINGS_ERROR_NONE;
}

int system_setting_set_font_size(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	printf(" real system_setting_set_font_size \n");
	int* vconf_value;
	vconf_value = (int*)value;

	if (*vconf_value < 0 || *vconf_value > SYSTEM_SETTINGS_FONT_SIZE_GIANT) {
		return SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER;
	}

	if (system_setting_vconf_set_value_int(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE, *vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	font_size_set();

	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>. system_setting_set_font_size called \n");

	return SYSTEM_SETTINGS_ERROR_NONE;
}

int system_setting_set_font_type(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	printf(" real system_setting_set_font_type \n");
	char* font_name = NULL;
	font_name = (char*)value;

	printf(">>>>>>>>>>>>> font name = %s \n", font_name);
	font_config_set(font_name);
	font_config_set_notification();

	char* vconf_value;
	vconf_value = (char*)value;
	if (system_setting_vconf_set_value_string(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_NAME, vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	return SYSTEM_SETTINGS_ERROR_NONE;
}

int system_setting_set_motion_activation(system_settings_key_e key, system_setting_data_type_e data_type, void* value)
{
	printf(" mock --> real system_setting_set_motion_activation \n");

	bool* vconf_value;
	vconf_value = (bool*)value;
	if (system_setting_vconf_set_value_bool(VCONFKEY_SETAPPL_MOTION_ACTIVATION, *vconf_value)) {
		return SYSTEM_SETTINGS_ERROR_IO_ERROR;
	}
	return SYSTEM_SETTINGS_ERROR_NONE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//

int system_setting_set_changed_callback_incoming_call_ringtone(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_SETAPPL_CALL_RINGTONE_PATH_STR, SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE, 0);
}

int system_setting_unset_changed_callback_incoming_call_ringtone(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_SETAPPL_CALL_RINGTONE_PATH_STR, 0);
}

int system_setting_set_changed_callback_wallpaper_home_screen(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_BGSET, SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN, 0);
}

int system_setting_unset_changed_callback_wallpaper_home_screen(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_BGSET, 0);
}

int system_setting_set_changed_callback_wallpaper_lock_screen(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_IDLE_LOCK_BGSET,SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN, 0);
}

int system_setting_unset_changed_callback_wallpaper_lock_screen(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_IDLE_LOCK_BGSET, 0);
}

int system_setting_set_changed_callback_font_size(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE,SYSTEM_SETTINGS_KEY_FONT_SIZE, 1);
}

int system_setting_unset_changed_callback_font_size(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE, 1);
}

/**
 * @todo need to add custom event notification method
 */
int system_setting_set_changed_callback_font_type(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	return system_setting_vconf_set_changed_cb(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_NAME,SYSTEM_SETTINGS_KEY_FONT_TYPE, 2);
}

int system_setting_unset_changed_callback_font_type(system_settings_key_e key)
{
	return system_setting_vconf_unset_changed_cb(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_NAME,2);
}

// TODO : 2th argument, callback, is not in use.
int system_setting_set_changed_callback_motion_activation(system_settings_key_e key, system_settings_changed_cb callback, void *user_data)
{
	printf("system_setting_set_changed_callback_motion_activation \n");
	return system_setting_vconf_set_changed_cb(VCONFKEY_SETAPPL_MOTION_ACTIVATION, SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, 3);
}

int system_setting_unset_changed_callback_motion_activation(system_settings_key_e key)
{
	printf("system_setting_unset_changed_callback_motion_activation \n");
	return system_setting_vconf_unset_changed_cb(VCONFKEY_SETAPPL_MOTION_ACTIVATION, 3);
}

static char* _get_cur_font()
{
    printf("get current font \n");

    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    xmlNodePtr cur2 = NULL;
    xmlNodePtr cur3 = NULL;
    xmlChar *key = NULL;

    char *font_name = NULL;

    doc = xmlParseFile(SETTING_FONT_CONF_FILE);

    cur = xmlDocGetRootElement(doc);

    if(cur == NULL) {
        printf("empty document");
        xmlFreeDoc(doc);
        doc = NULL;
        return NULL;
    }

    if(xmlStrcmp(cur->name, (const xmlChar *)"fontconfig")) {
        printf("document of the wrong type, root node != fontconfig");
        xmlFreeDoc(doc);
        doc = NULL;
        return NULL;
    }

    cur = cur->xmlChildrenNode;

    while(cur != NULL)
    {
        if((!xmlStrcmp(cur->name, (const xmlChar *)"match")))
        {
            cur2 = cur->xmlChildrenNode;
            while(cur2 != NULL)
            {
                if((!xmlStrcmp(cur2->name, (const xmlChar *)"edit")))
                {
                    cur3 = cur2->xmlChildrenNode;
                    while(cur3 != NULL)
                    {
                        if((!xmlStrcmp(cur3->name, (const xmlChar *)"string")))
                        {
                            key = xmlNodeListGetString(doc, cur3->xmlChildrenNode, 1);
                            //printf("string is: %s", key);

                            font_name = g_strdup((char *)key);
                            xmlFree(key);
                            key = NULL;
                            xmlFreeDoc(doc);
                            doc = NULL;
                            return font_name;
                        }
                       cur3 = cur3->next;
                    }
                }
                cur2 = cur2->next;
            }
        }
        cur = cur->next;
    }

    xmlFreeDoc(doc);
    doc = NULL;
    return NULL;
}

static void font_config_set_notification()
{
    /* notification */
	Ecore_X_Window ecore_win = ecore_x_window_root_first_get();
	printf("FONT CHANGE NOTIFICATION >>>>>>>>>> : %d  \n", (unsigned int)ecore_win);
	Ecore_X_Atom atom = ecore_x_atom_get("FONT_TYPE_change");
	ecore_x_window_prop_string_set(ecore_win, atom, "slp");
}

static void font_config_set(char *font_name)
{
    Eina_List *text_classes = NULL;
    Elm_Text_Class *etc = NULL;
    const Eina_List *l = NULL;
    Eina_List *fo_list = NULL;
    Elm_Font_Overlay *efo = NULL;
    int font_size = __font_size_get();
    int size = 0;

    text_classes = elm_config_text_classes_list_get();

    fo_list = elm_config_font_overlay_list_get();

    Eina_List *ll = NULL;
    Eina_List *l_next = NULL;

    Eina_Bool slp_medium_exist = EINA_FALSE;
    Eina_Bool slp_roman_exist = EINA_FALSE;
    Eina_Bool slp_bold_exist = EINA_FALSE;
    Eina_Bool slp_regular_exist = EINA_FALSE;

    EINA_LIST_FOREACH_SAFE(fo_list, ll, l_next, efo)
    {
        if (!strcmp(efo->text_class, "slp_medium")) {
            elm_config_font_overlay_set(efo->text_class, (const char*)font_name, efo->size);
            slp_medium_exist = EINA_TRUE;
        } else if (!strcmp(efo->text_class, "slp_roman")) {
            elm_config_font_overlay_set(efo->text_class, (const char*)font_name, efo->size);
            slp_roman_exist = EINA_TRUE;
        } else if (!strcmp(efo->text_class, "slp_bold")) {
            elm_config_font_overlay_set(efo->text_class, (const char*)font_name, efo->size);
            slp_bold_exist = EINA_TRUE;
        } else if (!strcmp(efo->text_class, "slp_regular")) {
            elm_config_font_overlay_set(efo->text_class, (const char*)font_name, efo->size);
            slp_regular_exist = EINA_TRUE;
        }
    }

    /* if slp_XX do not exist, need to set them, font size is -100(100%) */
    if (slp_medium_exist == EINA_FALSE) {
        elm_config_font_overlay_set("slp_medium", (const char*)font_name,  MIDDLE_FONT_DPI);
    }
    if (slp_roman_exist == EINA_FALSE) {
        elm_config_font_overlay_set("slp_roman", (const char*)font_name,  MIDDLE_FONT_DPI);
    }
    if (slp_bold_exist == EINA_FALSE) {
        elm_config_font_overlay_set("slp_bold", (const char*)font_name,  MIDDLE_FONT_DPI);
    }
    if (slp_regular_exist == EINA_FALSE) {
        elm_config_font_overlay_set("slp_regular", (const char*)font_name,  MIDDLE_FONT_DPI);
    }

    EINA_LIST_FOREACH(text_classes, l, etc)
    {
        ll = NULL;

        size = font_size;
        EINA_LIST_FOREACH(fo_list, ll, efo)
        {
            if (!strcmp(etc->name, efo->text_class)) {
                size = efo->size;
            }
        }
        elm_config_font_overlay_set(etc->name, (const char*)font_name, size);
    }

    elm_config_font_overlay_apply();
    elm_config_all_flush();
    elm_config_save();
    elm_config_text_classes_list_free(text_classes);
    text_classes = NULL;
}

static void font_size_set()
{
    Eina_List *text_classes = NULL;
    Elm_Text_Class *etc = NULL;
    const Eina_List *l = NULL;
    int font_size = __font_size_get();
    char *font_name = _get_cur_font();

    if (font_size == -1) {
        //SETTING_TRACE_DEBUG("failed to call font_size_get");
        return;
    } else {
		printf(">> font name = %s, font size = %d \n", font_name, font_size);
	}

    text_classes = elm_config_text_classes_list_get();

    EINA_LIST_FOREACH(text_classes, l, etc)
    {
        elm_config_font_overlay_set(etc->name, font_name, font_size);
    }

	elm_config_font_overlay_apply();
    elm_config_all_flush();
    elm_config_save();
    elm_config_text_classes_list_free(text_classes);
    text_classes = NULL;
    //G_FREE(font_name);
    g_free(font_name);
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>. font_size_set called \n");
}

static int __font_size_get()
{
    int font_size = -1;
    int err = -1;

	int vconf_value = -1;
	if (system_setting_vconf_get_value_int(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE, &vconf_value)) {
		return -1;
	}

    switch(vconf_value) {
    case SYSTEM_SETTINGS_FONT_SIZE_SMALL:
        font_size = SMALL_FONT_DPI;
        break;
    case SYSTEM_SETTINGS_FONT_SIZE_NORMAL:
        font_size = MIDDLE_FONT_DPI;
        break;
    case SYSTEM_SETTINGS_FONT_SIZE_LARGE:
        font_size = LARGE_FONT_DPI;
        break;
    case SYSTEM_SETTINGS_FONT_SIZE_HUGE:
        font_size = HUGE_FONT_DPI;
        break;
    case SYSTEM_SETTINGS_FONT_SIZE_GIANT:
        font_size = GIANT_FONT_DPI;
        break;
    default:
        font_size = MIDDLE_FONT_DPI;
        break;
    }
    return font_size;
}
