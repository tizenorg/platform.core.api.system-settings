#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <regex.h>

#include <dlog.h>
#include <vconf.h>

#include <glib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#include <fontconfig/fontconfig.h>

#include <Elementary.h>
#include <Evas.h>
#include <Ecore_Evas.h>

#include <pkgmgr-info.h>

#include <system_settings.h>
#include <system_settings_private.h>

#include <tzplatform_config.h>
#include <system_settings_util.h>

#ifdef TIZEN_WEARABLE
#define SMALL_FONT_DPI						(-90)
#endif
#ifdef TIZEN_MOBILE
#define SMALL_FONT_DPI						(-80)
#endif
#define MIDDLE_FONT_DPI						(-100)
#ifdef TIZEN_WEARABLE
#define LARGE_FONT_DPI						(-110)
#endif
#ifdef TIZEN_MOBILE
#define LARGE_FONT_DPI						(-150)
#endif
#define HUGE_FONT_DPI						(-190)
#define GIANT_FONT_DPI						(-250)

#define SETTING_FONT_PRELOAD_FONT_PATH _TZ_SYS_RO_SHARE"/fonts"
#define SETTING_FONT_DOWNLOADED_FONT_PATH _TZ_SYS_RO_SHARE"/fonts"

#define SETTING_FONT_CONF_FILE _TZ_SYS_ETC"/fonts/conf.avail/99-tizen.conf"
#define SETTING_DEFAULT_FONT_CONF_FILE _TZ_SYS_ETC"/fonts/conf.avail/99-tizen.conf"

static int __font_size_get();

/*  LCOV_EXCL_START */
bool __is_supported_image_type_load(char *path)
{
	SETTING_TRACE_BEGIN;
	evas_init();
	Ecore_Evas	*ee;
	Evas		*evas;

	ee = ecore_evas_new(NULL, 0, 0, 100, 100, NULL);
	evas = ecore_evas_get(ee);

	Evas_Object *img = evas_object_image_add(evas);
	evas_object_image_file_set(img, path, NULL);
	Evas_Load_Error ret = evas_object_image_load_error_get(img);

	bool result = false;
	if (ret == EVAS_LOAD_ERROR_NONE) {
		SETTING_TRACE("%s - OK", path);
		result = true;
	} else {
		SETTING_TRACE("%s - NO", path);
		result = false;
	}
	ecore_evas_free(ee);
	evas_shutdown();
	return result;
}
/*  LCOV_EXCL_STOP */

char *_get_cur_font()
{
	SETTING_TRACE_BEGIN;
	xmlDocPtr doc = NULL;
	xmlNodePtr cur = NULL;
	xmlNodePtr cur2 = NULL;
	xmlNodePtr cur3 = NULL;
	xmlChar *key = NULL;

	char *font_name = NULL;

	doc = xmlParseFile(SETTING_FONT_CONF_FILE);

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		xmlFreeDoc(doc);
		doc = NULL;
		return NULL;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *)"fontconfig")) {
		xmlFreeDoc(doc);
		doc = NULL;
		return NULL;
	}

	cur = cur->xmlChildrenNode;

	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"match"))) {
			cur2 = cur->xmlChildrenNode;
			while (cur2 != NULL) {
				if ((!xmlStrcmp(cur2->name, (const xmlChar *)"edit"))) {
					cur3 = cur2->xmlChildrenNode;
					while (cur3 != NULL) {
						if ((!xmlStrcmp(cur3->name, (const xmlChar *)"string"))) {
							key = xmlNodeListGetString(doc, cur3->xmlChildrenNode, 1);

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

/*  LCOV_EXCL_START */
void font_config_set_notification()
{
	SETTING_TRACE_BEGIN;
#if 0
	/* notification */
	Ecore_X_Window ecore_win = ecore_x_window_root_first_get();
	Ecore_X_Atom atom = ecore_x_atom_get("FONT_TYPE_change");
	ecore_x_window_prop_string_set(ecore_win, atom, "tizen");
#endif
}
/*  LCOV_EXCL_STOP */

/*  LCOV_EXCL_START */
int __is_available_font(char *font_name)
{
	SETTING_TRACE_BEGIN;
	FcObjectSet *os = NULL;
	FcFontSet *fs = NULL;
	FcPattern *pat = NULL;
	FcConfig *font_config = NULL;

	int ret = 0;

	if (font_name == NULL)
		return -1;

	font_config = FcInitLoadConfigAndFonts();

	/*setting_retvm_if(font_config == NULL, NULL, "Failed: FcInitLoadConfigAndFonts"); */

	char *locale = setlocale(0, NULL);

	pat = FcPatternCreate();

	os = FcObjectSetBuild(FC_FAMILY, FC_FILE, FC_FAMILYLANG, (char *) 0);

	if (os) {
		fs = FcFontList(font_config, pat, os);
		FcObjectSetDestroy(os);
		os = NULL;
	}

	if (pat) {
		FcPatternDestroy(pat);
		pat = NULL;
	}

	if (fs)	{
		int j;
		SETTING_TRACE("fs->nfont = %d", fs->nfont);

		for (j = 0; j < fs->nfont; j++)	{
			FcChar8 *family = NULL;
			FcChar8 *file = NULL;

			if (FcPatternGetString(fs->fonts[j], FC_FILE, 0, &file) == FcResultMatch) {
				int preload_path_len = strlen(SETTING_FONT_PRELOAD_FONT_PATH);
				int download_path_len = strlen(SETTING_FONT_DOWNLOADED_FONT_PATH);

				if (file && (!strncmp((const char *)file, SETTING_FONT_PRELOAD_FONT_PATH, preload_path_len)
						|| !strncmp((const char *)file, SETTING_FONT_DOWNLOADED_FONT_PATH, download_path_len))) {
					char *family_result = NULL;
					FcChar8 *lang = NULL;
					int id = 0;
					if (FcPatternGetString(fs->fonts[j], FC_FAMILY, id, &family) != FcResultMatch) {
						break;
					}
					if (FcPatternGetString(fs->fonts[j], FC_FAMILYLANG, id, &lang) != FcResultMatch) {
						break;
					}
					family_result = (char *)family;

					/* Find proper family name for current locale. */
					while (locale && family && lang) {
						if (!strncmp(locale, (char *)lang, strlen((char *)lang))) {
							family_result = (char *)family;
							break;
						}

						/* I will set english as default family language. */
						/* If there is no proper family language for current locale, */
						/* we have to show the english family name. */
						if (!strcmp((char *)lang, (char *)"en")) {
							family_result = (char *)family;
						}
						id++;
						if (FcPatternGetString(fs->fonts[j], FC_FAMILY, id, &family) != FcResultMatch) {
							break;
						}
						if (FcPatternGetString(fs->fonts[j], FC_FAMILYLANG, id, &lang) != FcResultMatch) {
							break;
						}
					}

					if (family_result) {
						SETTING_TRACE("-------- FONT - family_result = %s", (char *)family_result);
						if (strcmp(family_result, font_name) == 0) {
							ret = 1;
							break;
						}
					}
				}
			}
		}
		FcFontSetDestroy(fs);
		fs = NULL;
	}
	FcConfigDestroy(font_config);
	font_config = NULL;
	return ret;
}
/*  LCOV_EXCL_STOP */


char *_get_default_font()
{
	SETTING_TRACE_BEGIN;
	xmlDocPtr doc = NULL;
	xmlNodePtr cur = NULL;
	xmlNodePtr cur2 = NULL;
	xmlNodePtr cur3 = NULL;
	xmlChar *key = NULL;
	struct _xmlAttr *properties = NULL;
	char *default_font_name = NULL;

	doc = xmlParseFile(SETTING_DEFAULT_FONT_CONF_FILE);

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		xmlFreeDoc(doc);
		doc = NULL;
		return NULL;
	}

	if (xmlStrcmp(cur->name, (const xmlChar *)"fontconfig")) {
		xmlFreeDoc(doc);
		doc = NULL;
		return NULL;
	}

	cur = cur->xmlChildrenNode;

	while (cur != NULL) {
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"match"))) {
			cur2 = cur->xmlChildrenNode;
			while (cur2 != NULL) {
				if ((!xmlStrcmp(cur2->name, (const xmlChar *)"edit"))) {
					properties = cur2->properties;
					/*find the "name" property*/
					while (NULL != properties) {
						if (!xmlStrcmp(properties->name, (const xmlChar *)"name")) {
							break;
						}
						properties = properties->next;
					}

					/*If the value of "name" property is "family", then get the child node string,
					it shall be the default font type*/
					if (NULL != properties && !xmlStrcmp(properties->children->content, (const xmlChar *)"family")) {
						cur3 = cur2->xmlChildrenNode;
						while (cur3 != NULL) {
							if ((!xmlStrcmp(cur3->name, (const xmlChar *)"string"))) {
								key = xmlNodeListGetString(doc, cur3->xmlChildrenNode, 1);
								default_font_name = g_strdup((char *)key);
								xmlFree(key);
								key = NULL;
								xmlFreeDoc(doc);
								doc = NULL;
								return default_font_name;
							}
							cur3 = cur3->next;
						}
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

/*  LCOV_EXCL_START */
bool font_config_set(char *font_name)
{
	SETTING_TRACE_BEGIN;
	Eina_List *text_classes = NULL;
	Elm_Text_Class *etc = NULL;
	const Eina_List *l = NULL;
	Eina_List *fo_list = NULL;
	Elm_Font_Overlay *efo = NULL;

	int font_size = __font_size_get();
	int size = 0;

	text_classes = elm_config_text_classes_list_get();

	fo_list = (Eina_List *)elm_config_font_overlay_list_get();

	Eina_List *ll = NULL;
	Eina_List *l_next = NULL;

	Eina_Bool slp_medium_exist = EINA_FALSE;
	Eina_Bool slp_roman_exist = EINA_FALSE;
	Eina_Bool slp_bold_exist = EINA_FALSE;
	Eina_Bool slp_regular_exist = EINA_FALSE;

	/* Tizen */
	Eina_Bool tizen_exist = EINA_FALSE;

	EINA_LIST_FOREACH_SAFE(fo_list, ll, l_next, efo) {
		if (!strcmp(efo->text_class, "tizen_medium")) {
			elm_config_font_overlay_set(efo->text_class, (const char *)font_name, efo->size);
			slp_medium_exist = EINA_TRUE;
		} else if (!strcmp(efo->text_class, "tizen_roman")) {
			elm_config_font_overlay_set(efo->text_class, (const char *)font_name, efo->size);
			slp_roman_exist = EINA_TRUE;
		} else if (!strcmp(efo->text_class, "tizen_bold")) {
			elm_config_font_overlay_set(efo->text_class, (const char *)font_name, efo->size);
			slp_bold_exist = EINA_TRUE;
		} else if (!strcmp(efo->text_class, "tizen_regular")) {
			elm_config_font_overlay_set(efo->text_class, (const char *)font_name, efo->size);
			slp_regular_exist = EINA_TRUE;
		}

		/* Tizen */
		if (!strcmp(efo->text_class, "tizen")) {
			elm_config_font_overlay_set(efo->text_class, (const char *)font_name, efo->size);
			tizen_exist = EINA_TRUE;
		}

	}

	/* if slp_XX do not exist, need to set them, font size is -100(100%) */
	if (slp_medium_exist == EINA_FALSE) {
		elm_config_font_overlay_set("tizen_medium", (const char *)font_name,  MIDDLE_FONT_DPI);
	}
	if (slp_roman_exist == EINA_FALSE) {
		elm_config_font_overlay_set("tizen_roman", (const char *)font_name,	 MIDDLE_FONT_DPI);
	}
	if (slp_bold_exist == EINA_FALSE) {
		elm_config_font_overlay_set("tizen_bold", (const char *)font_name,	MIDDLE_FONT_DPI);
	}
	if (slp_regular_exist == EINA_FALSE) {
		elm_config_font_overlay_set("tizen_regular", (const char *)font_name,  MIDDLE_FONT_DPI);
	}

	/* Tizen */
	if (tizen_exist == EINA_FALSE) {
		elm_config_font_overlay_set("tizen", (const char *)font_name,  MIDDLE_FONT_DPI);
	}

	elm_config_font_overlay_set("tizen", (const char *)font_name,  MIDDLE_FONT_DPI);

	/* Tizen */
	elm_config_font_overlay_set("tizen", (const char *)font_name,  MIDDLE_FONT_DPI);

	EINA_LIST_FOREACH(text_classes, l, etc) {
		ll = NULL;

		size = font_size;
		EINA_LIST_FOREACH(fo_list, ll, efo) {
			if (!strcmp(etc->name, efo->text_class)) {
				size = efo->size;
			}
		}
		elm_config_font_overlay_set(etc->name, (const char *)font_name, size);
	}
	elm_config_text_classes_list_free(text_classes);
	text_classes = NULL;

	/* add new function */
#ifdef USE_EFL_ASSIST
	ea_theme_system_font_set(font_name, font_size);
	ea_theme_system_fonts_apply();
#endif

	elm_config_font_overlay_apply();
	elm_config_all_flush();
	elm_config_save();
	return 1;
}
/*  LCOV_EXCL_STOP */

/*  LCOV_EXCL_START */
void __font_size_set()
{
	SETTING_TRACE_BEGIN;
	Eina_List *text_classes = NULL;
	Elm_Text_Class *etc = NULL;
	const Eina_List *l = NULL;
	int font_size = __font_size_get();
	char *font_name = _get_cur_font();

	if (font_size == -1) {
		return;
	}

	text_classes = elm_config_text_classes_list_get();

	EINA_LIST_FOREACH(text_classes, l, etc) {
		elm_config_font_overlay_set(etc->name, font_name, font_size);
	}

	elm_config_text_classes_list_free(text_classes);

#ifdef USE_EFL_ASSIST
	ea_theme_system_font_set(font_name, font_size);
	ea_theme_system_fonts_apply();
#endif

	elm_config_font_overlay_apply();
	elm_config_all_flush();
	elm_config_save();

	text_classes = NULL;
	g_free(font_name);
}
/*  LCOV_EXCL_STOP */

/*  LCOV_EXCL_START */
static int __font_size_get()
{
	SETTING_TRACE_BEGIN;
	int font_size = -1;

	int vconf_value = -1;
	if (vconf_get_int(VCONFKEY_SETAPPL_ACCESSIBILITY_FONT_SIZE, &vconf_value)) {
		return -1;
	}

	switch (vconf_value) {
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
/*  LCOV_EXCL_STOP */
