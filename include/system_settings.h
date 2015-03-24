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

#ifndef __TIZEN_SYSTEM_SYSTEM_SETTINGS_H__
#define __TIZEN_SYSTEM_SYSTEM_SETTINGS_H__

#include <tizen.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @file system_settings.h
 */

/**
 * @addtogroup CAPI_SYSTEM_SYSTEM_SETTINGS_MODULE
 * @{
 */


/**
 * @brief Enumeration for system settings error.
 */
typedef enum
{
	SYSTEM_SETTINGS_ERROR_NONE = TIZEN_ERROR_NONE, /**< Successful */
	SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER, /**< Invalid parameter */
	SYSTEM_SETTINGS_ERROR_OUT_OF_MEMORY = TIZEN_ERROR_OUT_OF_MEMORY, /**< Out of memory */
	SYSTEM_SETTINGS_ERROR_IO_ERROR =  TIZEN_ERROR_IO_ERROR, /**< Internal I/O error */
	SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED =  TIZEN_ERROR_PERMISSION_DENIED, /**< Permition denied */
	SYSTEM_SETTINGS_ERROR_CALL_UNSUPPORTED_API =  TIZEN_ERROR_INVALID_PARAMETER, /**< Permition denied */

	// lock screen app error code
	SYSTEM_SETTINGS_ERROR_LOCKSCREEN_APP_PASSWORD_MODE = TIZEN_ERROR_SYSTEM_SETTING|0x01, /**< Current lock screen app set 'password' type */
} system_settings_error_e;


/**
 * @brief Enumeration for System Settings Key.
 */
typedef enum
{
	SYSTEM_SETTINGS_KEY_INCOMING_CALL_RINGTONE, /**< The file path of the current ringtone */
	SYSTEM_SETTINGS_KEY_WALLPAPER_HOME_SCREEN, /**< The file path of the current home screen wallpaper */
	SYSTEM_SETTINGS_KEY_WALLPAPER_LOCK_SCREEN, /**< The file path of the current lock screen wallpaper */
	SYSTEM_SETTINGS_KEY_FONT_SIZE, /**< The current system font size */
	SYSTEM_SETTINGS_KEY_FONT_TYPE, /**< The current system font type */
	SYSTEM_SETTINGS_KEY_MOTION_ACTIVATION, /**< Indicates whether the motion service is activated */
	SYSTEM_SETTINGS_KEY_EMAIL_ALERT_RINGTONE,  /**< The file path of the current email alert ringtone */
	SYSTEM_SETTINGS_KEY_USB_DEBUGGING_ENABLED,  /**< Indicates whether the usb debugging is enabled */
	SYSTEM_SETTINGS_KEY_3G_DATA_NETWORK_ENABLED,  /**< Indicates whether the 3G data network is enabled */
} system_settings_key_e;


/**
 * @brief Enumeration for font size.
 */
typedef enum
{
	SYSTEM_SETTINGS_FONT_SIZE_SMALL = 0, /**< A small size */
	SYSTEM_SETTINGS_FONT_SIZE_NORMAL, /**< A normal size */
	SYSTEM_SETTINGS_FONT_SIZE_LARGE, /**< A large size */
	SYSTEM_SETTINGS_FONT_SIZE_HUGE, /**< A huge size */
	SYSTEM_SETTINGS_FONT_SIZE_GIANT, /**< A giant size */
} system_settings_font_size_e;


/**
 * @brief Called when the system settings changes.
 * @since_tizen 2.3
 * @param[in] key The key name of the system settings changed system settings
 * @param[in] user_data The user data passed from the callback registration function
 * @pre system_settings_set_changed_cb() will invoke this callback function.
 * @see system_settings_set_changed_cb()
 * @see system_settings_unset_changed_cb()
 */
typedef void (*system_settings_changed_cb)(system_settings_key_e key, void *user_data);

/**
 * @internal
 * @brief Sets the system settings value associated with the given key as an integer.
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/systemsettings.admin
 * @param[in] key The key name of the system settings changed
 * @param[in] key The key name of the system settings
 * @param[out] value The new system settings value of the given key
 * @return @c 0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_settings_set_value_int(system_settings_key_e key, int value);

/**
 * @brief Gets the system settings value associated with the given key as an integer.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/systemsettings
 * @param[in] key The key name of the system settings
 * @param[out] value The current system settings value of the given key
 * @return @c 0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_settings_get_value_int(system_settings_key_e key, int *value);


/**
 * @internal
 * @brief Sets the system settings value associated with the given key as a boolean.
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/systemsettings.admin
 * @param[in] key The key name of the system settings
 * @param[out] value The new system settings value of the given key
 * @return @c 0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_settings_set_value_bool(system_settings_key_e key, bool value);

/**
 * @brief Gets the system settings value associated with the given key as a boolean.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/systemsettings
 * @param[in] key The key name of the system settings
 * @param[out] value The current system settings value of the given key
 * @return @c 0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_settings_get_value_bool(system_settings_key_e key, bool *value);

/**
 * @internal
 * @brief Sets the system settings value associated with the given key as a string.
 * @since_tizen 2.3
 * @privlevel platform
 * @privilege %http://tizen.org/privilege/systemsettings.admin
 * @remarks #SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE is not available for setting.
 * @param[in] key The key name of the system settings
 * @param[out] value The new system settings value of the given key
 * @return @c 0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_settings_set_value_string(system_settings_key_e key, const char *value);

/**
 * @brief Gets the system settings value associated with the given key as a string.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/systemsettings
 * @remarks You must release @a value using free().
 * @param[in] key The key name of the system settings
 * @param[out] value The current system settings value of the given key
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_IO_ERROR Internal I/O error
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 */
int system_settings_get_value_string(system_settings_key_e key, char **value);

/**
 * @brief Registers a change event callback for the given system settings key.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/systemsettings
 * @remarks #SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE is not available for set_changed_cb.
 * @param[in] key The key name of the system settings
 * @param[in] callback The callback function to invoke
 * @param[in] user_data The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 * @post system_settings_changed_cb() will be invoked.
 *
 * @see system_settings_unset_changed_cb()
 * @see system_settings_changed_cb()
 *
*/
int system_settings_set_changed_cb(system_settings_key_e key, system_settings_changed_cb callback, void *user_data);

/**
 * @brief Unregisters the callback function.
 * @since_tizen 2.3
 * @privlevel public
 * @privilege %http://tizen.org/privilege/systemsettings
 * @remarks #SYSTEM_SETTINGS_KEY_DEFAULT_FONT_TYPE is not available for set_changed_cb.
 * @param[in] key The key name of the system settings
 * @return  0 on success, otherwise a negative error value
 * @retval  #SYSTEM_SETTINGS_ERROR_NONE Successful
 * @retval  #SYSTEM_SETTINGS_ERROR_INVALID_PARAMETER Invalid parameter
 * @retval  #SYSTEM_SETTINGS_ERROR_PERMISSION_DENIED Permission violation error
 *
 * @see system_settings_set_changed_cb()
 */
int system_settings_unset_changed_cb(system_settings_key_e key);


/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_SYSTEM_SYSTEM_SETTINGS_H__ */
