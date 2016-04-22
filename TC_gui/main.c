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
#include "main.h"
#include <system_settings.h>
#include <system_settings_private.h>
#include <tzplatform_config.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static void _quit_cb(void *data, Evas_Object *obj, void *event_info)
{
	Evas_Object *win = (Evas_Object *) data;
	elm_win_lower(win);
}

static Evas_Object *create_win(const char *name)
{
	Evas_Object *eo;
	int w, h;

	eo = elm_win_add(NULL, name, ELM_WIN_BASIC);
	if (!eo) return NULL;

	elm_win_title_set(eo, name);
	elm_win_borderless_set(eo, EINA_TRUE);
	elm_win_autodel_set(eo, EINA_TRUE);
	evas_object_smart_callback_add(eo, "delete,request", _quit_cb, NULL);
	/*ecore_x_window_size_get(ecore_x_window_root_first_get(), &w, &h); */
	/*evas_object_resize(eo, w, h); */

	return eo;
}

static Evas_Object *_create_bg(Evas_Object *parent)
{
	Evas_Object *bg;

	bg = elm_bg_add(parent);
	evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(parent, bg);
	evas_object_show(bg);

	return bg;
}

static Evas_Object *_create_layout_main(Evas_Object *parent)
{
	Evas_Object *layout;

	layout = elm_layout_add(parent);

	elm_layout_theme_set(layout, "layout", "application", "default");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_win_resize_object_add(parent, layout);

	evas_object_show(layout);

	return layout;
}

static Evas_Object *_create_naviframe_layout(Evas_Object *parent)
{
	Evas_Object *navi;

	navi = elm_naviframe_add(parent);
	elm_object_part_content_set(parent, "elm.swallow.content", navi);

	evas_object_show(navi);

	return navi;
}


static void _create_view_layout(struct appdata *ad)
{
	Evas_Object *list;
	Evas_Object *btn;

	list = _create_list_winset(ad->win_main, ad);
	btn = elm_button_add(ad->navi);
	elm_object_style_set(btn, "naviframe/end_btn/default");
	evas_object_smart_callback_add(btn, "clicked", _quit_cb, ad->win_main);
	elm_naviframe_item_push(ad->navi, _("Tizen UI"), btn, NULL, list, NULL);
}

void list_item_touch_handler_exit(void *data, Evas_Object *obj, void *event_info)
{
	elm_exit();
}

/**
 * Huge
 */
void list_item_touch_handler1(void *data, Evas_Object *obj, void *event_info)
{
	char *font_name = "HelveticaNeue";
	int ret;
	ret = system_settings_set_value_int(SYSTEM_SETTINGS_KEY_FONT_SIZE, SYSTEM_SETTINGS_FONT_SIZE_HUGE);
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, font_name);

	char *ret_font = NULL;
	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, &ret_font);
	if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE(" %s  --------------- %s ", font_name, ret_font);
	} else {
		SETTING_TRACE(" %s  --------------- ", font_name);
	}
}

/**
 * Normal
 */
void list_item_touch_handler2(void *data, Evas_Object *obj, void *event_info)
{
	char *font_name = "HelveticaNeue";
	int ret;

	ret = system_settings_set_value_int(SYSTEM_SETTINGS_KEY_FONT_SIZE, SYSTEM_SETTINGS_FONT_SIZE_NORMAL);
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, font_name);

	char *ret_font = NULL;
	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, &ret_font);
	if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE(" %s  --------------- %s ", font_name, ret_font);
	} else {
		SETTING_TRACE(" %s  --------------- ", font_name);
	}
}

void list_item_touch_handler17(void *data, Evas_Object *obj, void *event_info)
{
	char *font_name = "aaaaaaa";
	int ret;
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, font_name);


	char *ret_font = NULL;
	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, &ret_font);
	if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE(" %s  --------------- %s ", font_name, ret_font);
	} else {
		SETTING_TRACE(" %s  --------------- ", font_name);
	}
}

void list_item_touch_handler18(void *data, Evas_Object *obj, void *event_info)
{
	char *font_name = "bbbbbbb";
	int ret;
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, font_name);

	char *ret_font = NULL;
	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, &ret_font);
	if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE(" %s  --------------- %s ", font_name, ret_font);
	} else {
		SETTING_TRACE(" %s  --------------- ", font_name);
	}

}

void list_item_touch_handler19(void *data, Evas_Object *obj, void *event_info)
{
	char *font_name = "Samsung Sans";
	int ret;
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, font_name);

	char *ret_font = NULL;
	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, &ret_font);
	if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE(" %s  --------------- %s ", font_name, ret_font);
	} else {
		SETTING_TRACE(" %s  --------------- ", font_name);
	}

}

void list_item_touch_handler20(void *data, Evas_Object *obj, void *event_info)
{
	char *font_name = "Choco cooky";
	int ret;
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, font_name);

	char *ret_font = NULL;
	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, &ret_font);
	if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE(" %s  --------------- %s ", font_name, ret_font);
	} else {
		SETTING_TRACE(" %s  --------------- ", font_name);
	}

}



void list_item_touch_handler3(void *data, Evas_Object *obj, void *event_info)
{
	int ret;
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, "HelveticaNeue");
}

void list_item_touch_handler4(void *data, Evas_Object *obj, void *event_info)
{
	int ret;
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_FONT_TYPE, "HelveticaNeue");
}

void list_item_touch_handler5(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> motion activation ON (SET)");

	bool enableMotion = false;;
	int errorcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, &enableMotion);
	SETTING_TRACE(">>>>>>>> motion activation (GET TEST  1) -- %d - errorcode : %d", enableMotion, errorcode);

	SETTING_TRACE(">>>>>>>> motion activation ON (SET)");
	system_settings_set_value_bool(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, true);
}

void list_item_touch_handler6(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> motion activation OFF ");
	system_settings_set_value_bool(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, false);
}

void system_settings_changed_font_size(system_settings_key_e key, void *user_data)
{
	struct appdata *ad = (struct appdata *)user_data;
	SETTING_TRACE(" font size -- %s ", ad->pkgname);
	SETTING_TRACE(">>>>>>>> system_settings_changed_font_size key = %d ", key);
	SETTING_TRACE("---------------------------------CALLED BY USER APPLICATION -FONT SIZE ");
}

void system_settings_changed_font_type(system_settings_key_e key, void *user_data)
{
	struct appdata *ad = (struct appdata *)user_data;
	SETTING_TRACE(" font type -- %s ", ad->pkgname);
	SETTING_TRACE(">>>>>>>> system_settings_changed_font_type key = %d ", key);
	SETTING_TRACE("---------------------------------CALLED BY USER APPLICATION -FONT TYPE ");
}

void system_settings_changed_motion_activation(system_settings_key_e key, void *user_data)
{
	struct appdata *ad = (struct appdata *)user_data;
	SETTING_TRACE(" motion type -- %s ", ad->pkgname);
	SETTING_TRACE(">>>>>>>> system_settings_changed_motion_activation key = %d ", key);
	SETTING_TRACE("---------------------------------CALLED BY USER APPLICATION-MOTION ACTIVIATION ");
}

void system_settings_changed_time(system_settings_key_e key, void *user_data)
{
	SETTING_TRACE(">>>>>>>> notify change time ");
	int ret;
	char *timezone = NULL;
	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_TIMEZONE, &timezone);
	SETTING_TRACE(" timezone : (%s) ", timezone);
	/*SETTING_TRACE("---------------------------------CALLED BY USER APPLICATION-MOTION ACTIVIATION "); */
}

void list_item_touch_handler7_1(void *data, Evas_Object *obj, void *event_info)
{
	char *path = NULL;
	int ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN, &path);
	SETTING_TRACE(">>>>>>>> home screen - error case :: %d ------ %s ", ret, path);
}

void list_item_touch_handler8_1(void *data, Evas_Object *obj, void *event_info)
{
	char *path = NULL;
	int ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN, &path);
	SETTING_TRACE(">>>>>>>> home screen - error case :: %d ------ %s ", ret, path);
}

void list_item_touch_handler7(void *data, Evas_Object *obj, void *event_info)
{
	char path[512];
	snprintf(path, 512, "%s/Images/image16.jpg", tzplatform_getenv(TZ_USER_CONTENT));
	int ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN, "/aaa.png");
	SETTING_TRACE(">>>>>>>> home screen - error case :: %d ", ret);

	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN, path);
	SETTING_TRACE(">>>>>>>> home screen - error case :: %d ", ret);

}

void list_item_touch_handler8(void *data, Evas_Object *obj, void *event_info)
{
	char path[512];
	snprintf(path, 512, "%s/Images/image16.jpg", tzplatform_getenv(TZ_USER_CONTENT));
	int ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN, "aaa.png");
	SETTING_TRACE(">>>>>>>> lock screen - error case  : %d ", ret);

	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN, path);
	SETTING_TRACE(">>>>>>>> lock screen - error case  : %d ", ret);
}

/*	SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED,  /**< Indicates whether the usb debugging is enabled * / */
/* get 3g data network */
void list_item_touch_handler9(void *data, Evas_Object *obj, void *event_info)
{
	bool state = false;;
	int errorcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED, &state);
	SETTING_TRACE(">>>>>>>> 3G data network (GET TEST) -- %d - errorcode : %d ", state, errorcode);
}

/* set 3g data network to ON */
void list_item_touch_handler10(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> set 3G data network to ON ");
	system_settings_set_value_bool(SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED, 1/*ON*/);
}

/* set 3g data network to OFF */
void list_item_touch_handler11(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> set 3G data network to OFF ");
	system_settings_set_value_bool(SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED, 0/*OFF*/);
}

/* get usg debugging */
void list_item_touch_handler12(void *data, Evas_Object *obj, void *event_info)
{
	bool state = false;;
	int errorcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED, &state);
	SETTING_TRACE(">>>>>>>> USB Debugging (GET TEST) -- %d - errorcode : %d ", state, errorcode);
}

/* set USB debugging to ON */
void list_item_touch_handler13(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> set USB debugging to ON ");
	system_settings_set_value_bool(SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED, 1/*ON*/);
}

/* set USB debugging to OFF */
void list_item_touch_handler14(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> set USB debugging to OFF ");
	system_settings_set_value_bool(SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED, 0/*OFF*/);
}

/* get ringtone path */
void list_item_touch_handler15(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> get ringtone path ");
	char *ringtonepath = NULL;
	int ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE, &ringtonepath);
	SETTING_TRACE("current ringtone path : (%s) ", ringtonepath);

}

/* get ringtone path - exception case */
void list_item_touch_handler16(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> get ringtone path - exception case ");
	int ret;
	char *ringtonepath = NULL;
	/*opt/share/settings/Ringtones/Over the horizon.mp3 */
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE, _TZ_SYS_SHARE"/settings/Ringtones/Over the horizon.mp3");
	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE, &ringtonepath);
	SETTING_TRACE(" 1 current ringtone path : (%s) ", ringtonepath);
	/* set the key to the wrong value */
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE, "aaa.wav");

	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE, &ringtonepath);
	SETTING_TRACE("2 current ringtone path : (%s) ", ringtonepath);
}

void list_item_touch_handler21(void *data, Evas_Object *obj, void *event_info)
{
	char *path1 = _TZ_SYS_SHARE"/settings/Alerts/Over the horizon.mp3";
	char *path2 = _TZ_SYS_SHARE"/settings/Alerts/Over the horizon.mp3.bak";

	SETTING_TRACE(">>>>>>>> get ringtone path ");
	char *ringtonepath = NULL;
	int ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE, &ringtonepath);
	SETTING_TRACE("current ringtone path : (%s) -- return : %d ", ringtonepath, ret);


	rename(path1, path2);
	SETTING_TRACE("after rename ");

	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE, &ringtonepath);
	SETTING_TRACE("current ringtone path : (%s) -- return : %d ", ringtonepath, ret);

	rename(path2, path1);

}

void list_item_touch_handler22(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> get email ringtone path - exception case ");
	int ret;
	char *ringtonepath = NULL;
	/*opt/share/settings/Ringtones/Over the horizon.mp3 */
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE, _TZ_SYS_SHARE"/settings/Ringtones/Over the horizon.mp3");
	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE, &ringtonepath);
	SETTING_TRACE(" 1 current ringtone path : (%s) ", ringtonepath);
	/* set the key to the wrong value */
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE, "aaa.wav");
	SETTING_TRACE(" wrong path name of email alert path : (%s) ", "aaa.wav");

	SETTING_TRACE(" 1 current ringtone path return = %d ", ret);


	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE, &ringtonepath);
	SETTING_TRACE("2 current ringtone path : (%s) -- return : %d ", ringtonepath, ret);

}

/* get notification sound */
void list_item_touch_handler15_1(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> get notification ringtone path ");
	char *ringtonepath = NULL;
	int ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION, &ringtonepath);
	SETTING_TRACE("current notification ringtone path : (%s) ", ringtonepath);

}

void list_item_touch_handler15_2(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> get notification ringtone path - exception case ");
	int ret;
	char *ringtonepath = NULL;
	/*opt/share/settings/ringtones/ringtone_sdk.mp3 */
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION, _TZ_SYS_SHARE"/settings/Ringtones/ringtone_sdk.mp3");
	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION, &ringtonepath);
	SETTING_TRACE(" 1 current ringtone path : (%s) ", ringtonepath);
	/* set the key to the wrong value */
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION, "aaa.wav");
	SETTING_TRACE(" wrong path name of notification ringtone path : (%s) ", "aaa.wav");

	SETTING_TRACE(" 1 current ringtone path return = %d ", ret);

	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_SOUND_NOTIFICATION, &ringtonepath);
	SETTING_TRACE("2 current ringtone path : (%s) -- return : %d ", ringtonepath, ret);

}

void list_item_touch_handler23(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> GET tap and hold delay ");
	int ret;
	int delay;
	ret = system_settings_get_value_int(SYSTEM_SETTINGS_KEY_TAP_AND_HOLD_DELAY, &delay);
	SETTING_TRACE(" tap and delay = %d ", delay);
}

void list_item_touch_handler24(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> SET tap and hold delay ");
	int ret;
	int delay;
	ret = system_settings_get_value_int(SYSTEM_SETTINGS_KEY_TAP_AND_HOLD_DELAY, &delay);

	ret = system_settings_set_value_int(SYSTEM_SETTINGS_KEY_TAP_AND_HOLD_DELAY, SYSTEM_SETTINGS_TAP_AND_HOLD_DELAY_LONG);
	ret = system_settings_get_value_int(SYSTEM_SETTINGS_KEY_TAP_AND_HOLD_DELAY, &delay);
	SETTING_TRACE(" tap and delay = %d ", delay);

	ret = system_settings_set_value_int(SYSTEM_SETTINGS_KEY_TAP_AND_HOLD_DELAY, SYSTEM_SETTINGS_TAP_AND_HOLD_DELAY_MEDIUM);
	ret = system_settings_get_value_int(SYSTEM_SETTINGS_KEY_TAP_AND_HOLD_DELAY, &delay);
	SETTING_TRACE(" tap and delay = %d ", delay);

	ret = system_settings_set_value_int(SYSTEM_SETTINGS_KEY_TAP_AND_HOLD_DELAY, SYSTEM_SETTINGS_TAP_AND_HOLD_DELAY_SHORT);
	ret = system_settings_get_value_int(SYSTEM_SETTINGS_KEY_TAP_AND_HOLD_DELAY, &delay);
	SETTING_TRACE(" tap and delay = %d ", delay);

}

void list_item_touch_handler25(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> Lock screen extension Test ");
	int ret;
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_LOCKSCREEN_APP, "com.samsung.lockscreen");
	SETTING_TRACE("ret = %d", ret);
}

void list_item_touch_handler26(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> Get default font ");
	char *ret_font = NULL;
	int ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE, &ret_font);
	if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE(" %s ----------------  ", ret_font);
	} else {
		SETTING_TRACE(" %s ----------------  ", ret_font);
	}
}

/*"get locale language " */
void list_item_touch_handler27(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> get locale language ");
	int ret;
	char *language = NULL;
	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &language);
	SETTING_TRACE(" lnaguage : (%s) ", language);
}

/* "get locale country " */
void list_item_touch_handler28(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> get locale country ");
	int ret;
	char *country = NULL;
	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY, &country);
	SETTING_TRACE(" country : (%s) ", country);

}

/*"get locale language " */
void list_item_touch_handler30(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> set locale language ");
	int ret;
	char *language = NULL;
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, "en_GB");
	SETTING_TRACE(">>>>>>>> set locale language - DONE ");
}

/* "get locale country " */
void list_item_touch_handler31(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> set locale country ");
	int ret;
	char *country = NULL;
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY, "en_GB");
	SETTING_TRACE(">>>>>>>> set locale country - DONE ");
}

/* "get locale formformat 1224 " */
void list_item_touch_handler29(void *data, Evas_Object *obj, void *event_info)
{
	bool is_24hour = false;;
	int errorcode = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_LOCALE_TIMEFORMAT_24HOUR, &is_24hour);
	SETTING_TRACE(">>>>>>>> get locale formformat 1224 -- %d - errorcode : %d", is_24hour, errorcode);
}

/* "get timezone " */
void list_item_touch_handler32(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> get timezone ");
	int ret;
	char *timezone = NULL;
	ret = system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_TIMEZONE, &timezone);
	SETTING_TRACE(" timezone : (%s) ", timezone);
}

/* "get flight mode " */
void list_item_touch_handler33(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE(">>>>>>>> get flight mode");
	int ret;
	bool mode;
	ret = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE, &mode);
	SETTING_TRACE(" flight mode : (%d) ", mode);
}

static void system_settings_changed_locale(system_settings_key_e key, void *user_data)
{
	struct appdata *ad = (struct appdata *)user_data;
	SETTING_TRACE(" font size -- %s ", ad->pkgname);
	SETTING_TRACE(">>>>>>>> system_settings_changed_locale key = %d ", key);
	SETTING_TRACE("---------------------------------CALLED BY USER APPLICATION -locale ");
}

static void system_settings_changed_locale_country(system_settings_key_e key, void *user_data)
{
	struct appdata *ad = (struct appdata *)user_data;
	SETTING_TRACE(" font size -- %s ", ad->pkgname);
	SETTING_TRACE(">>>>>>>> system_settings_changed_locale key = %d ", key);
	SETTING_TRACE("---------------------------------CALLED BY USER APPLICATION -locale ");
}


void list_item_touch_handler34(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE("start");
	int ret = 0;

	int test_key = SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE;

	ret = system_settings_set_changed_cb(test_key, system_settings_changed_locale, NULL);
	if (ret == SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER");
	} else if (ret == SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER");
	} else if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_NONE");
	} else {
		SETTING_TRACE("UNKNOW_ERROR :%d ", ret);
	}

	sleep(3);

	ret = system_settings_unset_changed_cb(test_key);
	SETTING_TRACE("system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE) = %d, . ", ret);
	if (ret == SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER");
	} else if (ret == SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER");
	} else if (ret == SYSTEM_SETTINGS_ERROR_IO_ERROR) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_IO_ERROR");
	} else if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_NONE");
	} else {
		SETTING_TRACE("UNKNOW_ERROR :%d ", ret);
	}

	sleep(3);

	ret = system_settings_set_changed_cb(test_key, system_settings_changed_locale, NULL);
	if (ret == SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER");
	} else if (ret == SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER");
	} else if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_NONE");
	} else if (ret == SYSTEM_SETTINGS_ERROR_IO_ERROR) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_IO_ERROR");
	} else {
		SETTING_TRACE("UNKNOW_ERROR : %d", ret);
	}
	SETTING_TRACE("end");
}

void list_item_touch_handler37(void *data, Evas_Object *obj, void *event_info)
{
	SETTING_TRACE("start");
	int ret = 0;

	int test_key = SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY;

	ret = system_settings_set_changed_cb(test_key, system_settings_changed_locale_country, NULL);
	if (ret == SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER");
	} else if (ret == SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER");
	} else if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_NONE");
	} else {
		SETTING_TRACE("system_settings_set_changed_cb --- UNKNOW_ERROR :%d ", ret);
	}

	sleep(3);

	ret = system_settings_unset_changed_cb(test_key);
	SETTING_TRACE("system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_LOCALE_COUNTRY) = %d, . ", ret);
	if (ret == SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER");
	} else if (ret == SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER");
	} else if (ret == SYSTEM_SETTINGS_ERROR_IO_ERROR) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_IO_ERROR");
	} else if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_NONE");
	} else {
		SETTING_TRACE("1st system_settings_unset_changed_cb --- UNKNOW_ERROR :%d ", ret);
	}

	sleep(3);

	ret = system_settings_set_changed_cb(test_key, system_settings_changed_locale_country, NULL);
	if (ret == SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER");
	} else if (ret == SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER");
	} else if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_NONE");
	} else if (ret == SYSTEM_SETTINGS_ERROR_IO_ERROR) {
		SETTING_TRACE("SYSTEM_SETTINGS_ERROR_IO_ERROR");
	} else {
		/*SETTING_TRACE("UNKNOW_ERROR : %d", ret); */
		SETTING_TRACE("2nd system_settings_unset_changed_cb --- UNKNOW_ERROR :%d ", ret);
	}
	SETTING_TRACE("end");
}

void list_item_touch_handler35(void *data, Evas_Object *obj, void *event_info)
{
	bool flag = false;;
	int ret = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_SOUND_LOCK, &flag);
	if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE(" %d ---------------- ret: %d  ", flag, ret);
	} else {
		SETTING_TRACE(" %d ---------------- ret: %d  ", flag, ret);
	}
}

void list_item_touch_handler36(void *data, Evas_Object *obj, void *event_info)
{
	bool flag = false;;
	int ret = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_SOUND_TOUCH, &flag);
	if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE(" %d ---------------- ret: %d  ", flag, ret);
	} else {
		SETTING_TRACE(" %d ---------------- ret: %d  ", flag, ret);
	}
}

void list_item_touch_handler38(void *data, Evas_Object *obj, void *event_info)
{
	bool flag = false;;
	int ret = system_settings_get_value_bool(SYSTEM_SETTINGS_KEY_DISPLAY_SCREEN_ROTATION_AUTO, &flag);
	if (ret == SYSTEM_SETTINGS_ERROR_NONE) {
		SETTING_TRACE(" %d ---------------- ret: %d  ", flag, ret);
	} else {
		SETTING_TRACE(" %d ---------------- ret: %d  ", flag, ret);
	}
}

void system_settings_changed_flight_mode(system_settings_key_e key, void *user_data)
{
	struct appdata *ad = (struct appdata *)user_data;
	SETTING_TRACE(">>>>>>>> system_settings_changed_flight_mode key = %d ", key);
}

/*flight mode - error code test - return zero, it's OK. */
void list_item_touch_handler39(void *data, Evas_Object *obj, void *event_info)
{
	int ret;
	struct appdata *ad = (struct appdata *)data;
	ret = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE, system_settings_changed_flight_mode, ad);
	SETTING_TRACE("system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE) = %d, . ", ret);

	ret = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE);
	SETTING_TRACE("system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_NETWORK_FLIGHT_MODE) = %d, . ", ret);

}

/*motion activation - set_value_string - error code test */
void list_item_touch_handler40(void *data, Evas_Object *obj, void *event_info)
{
	int ret;
	ret = system_settings_set_value_string(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, "hello");
	SETTING_TRACE("system_settings_set_value_string(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION) = %d, . ", ret);
}

/*motion activation - get_value_int -  error code test */
void list_item_touch_handler41(void *data, Evas_Object *obj, void *event_info)
{
	int ret;
	int val;
	ret = system_settings_get_value_int(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, &val);
	SETTING_TRACE("system_settings_get_value_int(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION) = %d, val =%d ", ret, val);
}



static Evas_Object *_create_list_winset(Evas_Object *parent, struct appdata *ad)
{
	Evas_Object *li;
	int idx = 0;
	/*struct _menu_item *menu_its; */
	int ret;
	ret = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_FONT_SIZE, system_settings_changed_font_size, ad);

	ret = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_FONT_TYPE, system_settings_changed_font_type, ad);
	if (ret < 0) {
		SETTING_TRACE("SYSTEM_SETTINGS_KEY_FONT_TYPE returns negative values = %d ", ret);
	} else {
		SETTING_TRACE("SYSTEM_SETTINGS_KEY_FONT_TYPE returns positive values = %d, means successful return. ", ret);
	}

	/* callback registration */
	ret = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, system_settings_changed_motion_activation, ad);
	if (ret < 0) {
		SETTING_TRACE("SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION returns negative values = %d ", ret);
	} else {
		SETTING_TRACE("SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION returns positive values = %d, means successful return. ", ret);
	}

	/* callback registration */
	ret = system_settings_set_changed_cb(SYSTEM_SETTINGS_KEY_TIME_CHANGED, system_settings_changed_time, ad);
	if (ret < 0) {
		SETTING_TRACE("SYSTEM_SETTINGS_KEY_TIME_CHANGED returns negative values = %d ", ret);
	} else {
		SETTING_TRACE("SYSTEM_SETTINGS_KEY_TIME_CHANGED returns positive values = %d, means successful return. ", ret);
	}

	li = elm_list_add(parent);
	elm_list_mode_set(li, ELM_LIST_COMPRESS);

	elm_list_item_append(li, "QUIT", NULL, NULL, list_item_touch_handler_exit, ad);
	elm_list_item_append(li, "font size - bigger ", NULL, NULL, list_item_touch_handler1, ad);
	elm_list_item_append(li, "font size - normal ", NULL, NULL, list_item_touch_handler2, ad);
	elm_list_item_append(li, "font type - choose Helvetica 1 ", NULL, NULL, list_item_touch_handler3, ad);
	elm_list_item_append(li, "font type - choose Helvetica 2 ", NULL, NULL, list_item_touch_handler4, ad);
	elm_list_item_append(li, "font type - choose unexisited font ", NULL, NULL, list_item_touch_handler17, ad);
	elm_list_item_append(li, "font type - choose unexisited font ", NULL, NULL, list_item_touch_handler18, ad);
	elm_list_item_append(li, "font type - choose Samsung Sens ", NULL, NULL, list_item_touch_handler19, ad);
	elm_list_item_append(li, "font type - choose Choco cooky ", NULL, NULL, list_item_touch_handler20, ad);
	elm_list_item_append(li, "motion activation ON ", NULL, NULL, list_item_touch_handler5, ad);
	elm_list_item_append(li, "motion activation OFF ", NULL, NULL, list_item_touch_handler6, ad);
	elm_list_item_append(li, "homescreen - get ", NULL, NULL, list_item_touch_handler7_1, ad);
	elm_list_item_append(li, "homescreen - set ", NULL, NULL, list_item_touch_handler7, ad);
	elm_list_item_append(li, "lockscreen - get ", NULL, NULL, list_item_touch_handler8_1, ad);
	elm_list_item_append(li, "lockscreen - set ", NULL, NULL, list_item_touch_handler8, ad);

	elm_list_item_append(li, "3g data network GET ", NULL, NULL, list_item_touch_handler9, ad);
	elm_list_item_append(li, "3g data network SET - ON ", NULL, NULL, list_item_touch_handler10, ad);
	elm_list_item_append(li, "3g data network SET - OFF ", NULL, NULL, list_item_touch_handler11, ad);

	elm_list_item_append(li, "usb debugging GET ", NULL, NULL, list_item_touch_handler12, ad);
	elm_list_item_append(li, "usb debugging SET - ON ", NULL, NULL, list_item_touch_handler13, ad);
	elm_list_item_append(li, "usb debugging SET - OFF ", NULL, NULL, list_item_touch_handler14, ad);

	elm_list_item_append(li, "get call ringtone ", NULL, NULL, list_item_touch_handler15, ad);
	elm_list_item_append(li, "get call ringtone - exception ", NULL, NULL, list_item_touch_handler16, ad);

	elm_list_item_append(li, "get email ringtone ", NULL, NULL, list_item_touch_handler21, ad);
	elm_list_item_append(li, "get email ringtone - exception ", NULL, NULL, list_item_touch_handler22, ad);

	elm_list_item_append(li, "get notification ringtone ", NULL, NULL, list_item_touch_handler15_1, ad);
	elm_list_item_append(li, "get notification ringtone - exception ", NULL, NULL, list_item_touch_handler15_2, ad);

	elm_list_item_append(li, "get - tap and hold delay ", NULL, NULL, list_item_touch_handler23, ad);
	elm_list_item_append(li, "set - tap and hold delay ", NULL, NULL, list_item_touch_handler24, ad);

	elm_list_item_append(li, "lockscreen - extention test ", NULL, NULL, list_item_touch_handler25, ad);
	elm_list_item_append(li, "get default font ", NULL, NULL, list_item_touch_handler26, ad);

	elm_list_item_append(li, "get locale language ", NULL, NULL, list_item_touch_handler27, ad);
	elm_list_item_append(li, "get locale country ", NULL, NULL, list_item_touch_handler28, ad);

	elm_list_item_append(li, "get locale formformat 1224 ", NULL, NULL, list_item_touch_handler29, ad);

	elm_list_item_append(li, "set locale language ", NULL, NULL, list_item_touch_handler30, ad);
	elm_list_item_append(li, "set locale country ", NULL, NULL, list_item_touch_handler31, ad);


	elm_list_item_append(li, "Get Timezone ", NULL, NULL, list_item_touch_handler32, ad);
	elm_list_item_append(li, "Get Flight mode ", NULL, NULL, list_item_touch_handler33, ad);
	elm_list_item_append(li, "cb TEST ", NULL, NULL, list_item_touch_handler34, ad);
	elm_list_item_append(li, "SYSTEM_SETTINGS_KEY_SOUND_LOCK - get test ", NULL, NULL, list_item_touch_handler35, ad);
	elm_list_item_append(li, "SYSTEM_SETTINGS_KEY_SOUND_TOUCH - get test ", NULL, NULL, list_item_touch_handler36, ad);
	elm_list_item_append(li, "cb TEST - locale_language ", NULL, NULL, list_item_touch_handler37, ad);
	elm_list_item_append(li, "auto rotation ", NULL, NULL, list_item_touch_handler38, ad);

	elm_list_item_append(li, "flight mode - error code test ", NULL, NULL, list_item_touch_handler39, ad);
	elm_list_item_append(li, "motion activation - set_value_string - error code test ", NULL, NULL, list_item_touch_handler40, ad);
	elm_list_item_append(li, "motion activation - get_value_int -  error code test ", NULL, NULL, list_item_touch_handler41, ad);

	elm_list_go(li);
	return li;
}

static void _mouse_down_cb(void *data, Evas *evas, Evas_Object *obj, void *event_info)
{
	/*struct appdata *ad = (struct appdata *)data; */
	/*Evas_Event_Mouse_Down *ev = event_info; */

}

static void _mouse_up_cb(void *data, Evas *evas, Evas_Object *obj, void *event_info)
{
	/*struct appdata *ad = (struct appdata *)data; */

}

static void _mouse_move_cb(void *data, Evas *evas, Evas_Object *obj, void *event_info)
{
	/*struct appdata *ad = (struct appdata *)data; */
}

static void _window_resize_cb(void *data, Evas *e, Evas_Object *obj, void *event_info)
{
	struct appdata *ad = (struct appdata *)data;
	evas_object_geometry_get(ad->win_main, NULL, NULL, &ad->root_w, &ad->root_h);
}

static int _rotation_cb(enum appcore_rm mode, void *data)
{
	struct appdata *ad = (struct appdata *)data;
	int angle;

	switch (mode) {
	case APPCORE_RM_LANDSCAPE_NORMAL:
		angle = -90;
		break;

	case APPCORE_RM_LANDSCAPE_REVERSE:
		angle = 90;
		break;

	case APPCORE_RM_PORTRAIT_REVERSE:
		angle = 180;
		break;

	case APPCORE_RM_UNKNOWN:
	case APPCORE_RM_PORTRAIT_NORMAL:
	default:
		angle = 0;
		break;
	}

	elm_win_rotation_with_resize_set(ad->win_main, angle);
	/* set_rotation_degree(angle); */

	/* This is need for customized rotation process. */
	/* rotate_for_winset(mode); */

	return 0;
}

int app_create(void *data)
{
	struct appdata *ad = (struct appdata *) data;

	/* Set the engine to opengl_x11 */
	/*elm_config_engine_set("opengl_x11"); */

	ad->win_main = create_win(PACKAGE);

	evas_object_event_callback_add(ad->win_main, EVAS_CALLBACK_RESIZE, _window_resize_cb, ad);
	evas_object_show(ad->win_main);
	ad->evas = evas_object_evas_get(ad->win_main);
	appcore_set_rotation_cb(_rotation_cb, ad);

	/* set_edj_name(NULL); */

	ad->bg = _create_bg(ad->win_main);
	ad->layout_main = _create_layout_main(ad->win_main);
	elm_win_indicator_mode_set(ad->win_main, ELM_WIN_INDICATOR_SHOW);

	ad->navi = _create_naviframe_layout(ad->layout_main);

	_create_view_layout(ad);

	evas_object_event_callback_add(ad->navi, EVAS_CALLBACK_MOUSE_DOWN, _mouse_down_cb, ad);
	evas_object_event_callback_add(ad->navi, EVAS_CALLBACK_MOUSE_UP, _mouse_up_cb,  ad);
	evas_object_event_callback_add(ad->navi, EVAS_CALLBACK_MOUSE_MOVE, _mouse_move_cb, ad);

	return 0;
}

int app_terminate(void *data)
{
	/*struct appdata *ad = data; */

	int ret;
	/* unregistration */
	ret = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_FONT_SIZE);
	SETTING_TRACE("system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_FONT_SIZE) = %d, . ", ret);

	ret = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_FONT_TYPE);
	SETTING_TRACE("system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_FONT_TYPE) = %d, . ", ret);

	ret = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION);
	SETTING_TRACE("system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION) = %d, . ", ret);

	ret = system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_TIME_CHANGED);
	SETTING_TRACE("system_settings_unset_changed_cb(SYSTEM_SETTINGS_KEY_TIME_CHANGED) = %d, . ", ret);

	return 0;
}

int app_pause(void *data)
{
	/*struct appdata *ad = data; */

	return 0;
}

int app_resume(void *data)
{
	/*struct appdata *ad = data; */

	return 0;
}

int app_reset(bundle *b, void *data)
{
	struct appdata *ad = data;

	if (ad->win_main)
		elm_win_activate(ad->win_main);

	return 0;
}


int main(int argc, char *argv[])
{
	struct appdata ad;

	ad.pkgname = "ARGUMENTATION SUCCESS *********************************";

	struct appcore_ops ops = {
		.create = app_create,
		.terminate = app_terminate,
		.pause = app_pause,
		.resume = app_resume,
		.reset = app_reset
	};

	ops.data = &ad;

	return appcore_efl_main(PACKAGE, &argc, &argv, &ops);
}
