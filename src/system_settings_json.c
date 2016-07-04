
#include <system_settings.h>
#include <system_settings_private.h>
#include <system_settings_json.h>

#include <vconf.h>

//#define VCONFKEY_SETAPPL_CALL_RINGTONE_USER_LIST

static void ss_json_ringtone_save(JsonNode *root)
{
	// write here
	GError *error = NULL;
	JsonGenerator *generator = json_generator_new();
	json_generator_set_root(generator, root);
	g_object_set(generator, "pretty", TRUE, NULL);
#ifdef USE_JSONFILE
	gboolean ret = json_generator_to_file(generator, filename, &error);
#else
	gchar* result = json_generator_to_data(generator, NULL);
	vconf_set_str(VCONFKEY_SETAPPL_CALL_RINGTONE_USER_LIST,(char*)result);
#endif
	g_object_unref(generator);
}


JsonParser* ss_json_ringtone_open_file(char* path)
{
	JsonParser *parser;
	JsonNode *root;
	GError *error;

	parser = json_parser_new ();

	error = NULL;
	json_parser_load_from_file (parser, path, &error);
	if (error)
	{
		SETTING_TRACE("Unable to parse `%s': %s\n", path, error->message);
		g_error_free (error);
		g_object_unref (parser);
		return NULL;
	}

	return parser;
}

JsonParser* ss_json_ringtone_load_from_data()
{
	JsonParser *parser;
	JsonNode *root;
	GError *error;

	parser = json_parser_new ();

	error = NULL;
	char* load_data = vconf_get_str(VCONFKEY_SETAPPL_CALL_RINGTONE_USER_LIST);
	json_parser_load_from_data (parser, load_data, -1, &error);
	if (error)
	{
		SETTING_TRACE("Unable to load data : %s \n", error->message);
		g_error_free (error);
		g_object_unref (parser);
		return NULL;
	}
	return parser;
}

void ss_json_ringtone_add(JsonNode *root, char* filename, char* nameval, char* pathval)
{
	SETTING_TRACE_BEGIN;

	JsonNode* menu_item = json_node_new(JSON_NODE_OBJECT);
	JsonObject *object = json_object_new();
	json_node_take_object(menu_item, object);
	json_object_set_string_member(object, "name", nameval);
	json_object_set_string_member(object, "path", pathval);

	JsonArray* menu = json_node_get_array(root);
	json_array_add_element(menu, menu_item);

	ss_json_ringtone_save(root);
}

void ss_json_ringtone_print(JsonNode *root)
{
	JsonNode *node = root;

	JsonGenerator *generator = json_generator_new();
	g_object_set(generator, "pretty", TRUE, NULL);
	json_generator_set_root(generator, node);
	gchar *data = json_generator_to_data(generator, NULL);
	//SETTING_TRACE("%s", (char * )data);
	SETTING_TRACE("-------------------------------------------------------\n");
	SETTING_TRACE("%s", data);
	SETTING_TRACE("-------------------------------------------------------\n");

	SETTING_TRACE("VCONFKEY_SETAPPL_CALL_RINGTONE_USER_LIST SET !!!!\n");
	vconf_set_str(VCONFKEY_SETAPPL_CALL_RINGTONE_USER_LIST, (char*)data);
	g_free(data);
	g_object_unref(generator);
}

void ss_json_ringtone_remove(JsonNode *root,  char* filename, char* path_to_del)
{
	int size = json_array_get_length(json_node_get_array(root));

	SETTING_TRACE("BBB size : (%d) \n", size);
	int i = 0;
	for (i = 0; i < size ; i++) {
		JsonObject *ringtone = json_array_get_object_element( json_node_get_array(root), i);
		char *nameval = (char *)json_object_get_string_member(ringtone, "name");
		char *pathval = (char *)json_object_get_string_member(ringtone, "path");

		if (pathval && !strcmp(pathval, path_to_del)) {
			json_array_remove_element(json_node_get_array(root), i);
			SETTING_TRACE("remove BBB : (%s) --- (%s) \n", pathval, path_to_del);
		}
	}

	ss_json_ringtone_save(root);
}

bool ss_json_ringtone_contain(JsonNode *root, char* newfile)
{
	int size = json_array_get_length(json_node_get_array(root));

	bool ret = false;

	int i = 0;
	for (i = 0; i < size ; i++) {
		JsonObject *ringtone = json_array_get_object_element( json_node_get_array(root), i);
		char *nameval = (char *)json_object_get_string_member(ringtone, "name");
		char *pathval = (char *)json_object_get_string_member(ringtone, "path");
		//SETTING_TRACE("(%s) --- (%s) \n", name, path);


		if (pathval && !strcmp(pathval, newfile)) {
			//SETTING_TRACE("FOUND\n");
			ret = true;
			break;
		} else {
			//SETTING_TRACE("*NOT* FOUND\n");
			ret = false;
		}
	}

	return ret;
}

void ss_json_ringtone_list(JsonNode *root)
{
	int size = json_array_get_length(json_node_get_array(root));

	int i = 0;
	for (i = 0; i < size ; i++) {
		JsonObject *ringtone = json_array_get_object_element( json_node_get_array(root), i);
		char *name = (char *)json_object_get_string_member(ringtone, "name");
		char *path = (char *)json_object_get_string_member(ringtone, "path");
		SETTING_TRACE("(%s) --- (%s) \n", name, path);
	}
}


