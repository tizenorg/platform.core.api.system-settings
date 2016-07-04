
#include <system_settings.h>
#include <system_settings_private.h>
#include <system_settings_json.h>


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

	// write here
	GError *error = NULL;
	JsonGenerator *generator = json_generator_new();
	json_generator_set_root(generator, root);
	g_object_set(generator, "pretty", TRUE, NULL);
	gboolean ret = json_generator_to_file(generator, filename, &error);
	if (error)
	{
		SETTING_TRACE("error : `%s': %s\n", filename, error->message);
		g_error_free (error);
		//g_object_unref (parser);
	}
	g_object_unref(generator);
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


	// write here
	GError *error = NULL;
	JsonGenerator *generator = json_generator_new();
	json_generator_set_root(generator, root);
	g_object_set(generator, "pretty", TRUE, NULL);
	gboolean ret = json_generator_to_file(generator, filename, &error);
	g_object_unref(generator);

}

int ss_json_ringtone_contain(JsonNode *root, char* newfile)
{
	int size = json_array_get_length(json_node_get_array(root));

	int ret = 0;

	int i = 0;
	for (i = 0; i < size ; i++) {
		JsonObject *ringtone = json_array_get_object_element( json_node_get_array(root), i);
		char *nameval = (char *)json_object_get_string_member(ringtone, "name");
		char *pathval = (char *)json_object_get_string_member(ringtone, "path");
		//SETTING_TRACE("(%s) --- (%s) \n", name, path);


		if (pathval && !strcmp(pathval, newfile)) {
			//SETTING_TRACE("FOUND\n");
			ret = 1;
			break;
		} else {
			//SETTING_TRACE("*NOT* FOUND\n");
			ret = 0;
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


