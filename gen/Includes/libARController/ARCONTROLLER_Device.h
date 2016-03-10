/**********************************************************
 *            AUTOGENERATED FILE                          *
 *             DO NOT MODIFY IT                           *
 *                                                        *
 * To add new commands :                                  *
 *  - Modify ../Xml/commands.xml file                     *
 *  - Re-run generateDeviceControllers.py script          *
 *                                                        *
 **********************************************************/

/**
* @file ARCONTROLLER_Device.h
* @brief Device controller allow to drive a device.
*/

#ifndef _ARCONTROLLER_DEVICE_H_
#define _ARCONTROLLER_DEVICE_H_

#include <stdlib.h>

#include <libARSAL/ARSAL_Print.h>
#include <libARSAL/ARSAL_Mutex.h>
#include <uthash/uthash.h>

#include <libARController/ARCONTROLLER_Error.h>
#include <libARController/ARCONTROLLER_Dictionary.h>
#include <libARController/ARCONTROLLER_Feature.h>
#include <libARController/ARCONTROLLER_Stream.h>

/**
 * Enum characterizing the states of the device controller
 */
typedef enum
{
    ARCONTROLLER_DEVICE_STATE_STOPPED = 0, /**< device controller is stopped */
    ARCONTROLLER_DEVICE_STATE_STARTING, /**< device controller is starting */
    ARCONTROLLER_DEVICE_STATE_RUNNING, /**< device controller is running */
    ARCONTROLLER_DEVICE_STATE_PAUSED, /**< device controller is paused */
    ARCONTROLLER_DEVICE_STATE_STOPPING, /**< device controller is stopping */
    
    ARCONTROLLER_DEVICE_STATE_MAX /**< Max of the enumeration */
}eARCONTROLLER_DEVICE_STATE;

/**
 * @brief Callback used when the state of the device Controller is changed.
 * @param[in] newState The new state of the Device Contoller
 * @param[in] error Error causing this new state.
 * @param[in] customData Custom Data set by the register
 */
typedef void (*ARCONTROLLER_Device_StateChangedCallback_t) (eARCONTROLLER_DEVICE_STATE newState, eARCONTROLLER_ERROR error, void *customData);

/**
 * @brief Callback used when the extension state of the device Controller is changed.
 * @param[in] newState The new state of the extension of the Device Contoller
 * @param[in] product the type of the extension.
 * @param[in] name the name of the extension.
 * @param[in] error Error causing this new state.
 * @param[in] customData Custom Data set by the register
 */
typedef void (*ARCONTROLLER_Device_ExtensionStateChangedCallback_t) (eARCONTROLLER_DEVICE_STATE newState, eARDISCOVERY_PRODUCT product, const char *name, eARCONTROLLER_ERROR error, void *customData);

/**
 * @brief Private part of the Device controller.
 */
typedef struct ARCONTROLLER_Device_Private_t ARCONTROLLER_Device_Private_t;

/**
 * @brief Device controller allow to drive a device.
 */
typedef struct
{
    ARCONTROLLER_FEATURE_Generic_t *generic; /**< */
    ARCONTROLLER_FEATURE_Pro_t *pro; /**< */
    ARCONTROLLER_FEATURE_ARDrone3_t *aRDrone3; /**< */
    ARCONTROLLER_FEATURE_UnknownFeature_1_t *unknown_feature_1; /**< */
    ARCONTROLLER_FEATURE_MiniDrone_t *miniDrone; /**< */
    ARCONTROLLER_FEATURE_CommonDebug_t *commonDebug; /**< */
    ARCONTROLLER_FEATURE_JumpingSumo_t *jumpingSumo; /**< */
    ARCONTROLLER_FEATURE_Wifi_t *wifi; /**< */
    ARCONTROLLER_FEATURE_SkyController_t *skyController; /**< */
    ARCONTROLLER_FEATURE_Common_t *common; /**< */
    ARCONTROLLER_Device_Private_t *privatePart; /**< private part of the deviceController */
}ARCONTROLLER_Device_t;

/**
 * @brief Create a new Device Controller
 * @warning This function allocate memory
 * @post ARCONTROLLER_Device_Delete() must be called to delete the Device Controller and free the memory allocated.
 * @param[in] discoveryDevice The device to drive ; must be not NULL.
 * @param[out] error executing error.
 * @return the new Device Controller
 * @see ARCONTROLLER_Device_Delete
 */
ARCONTROLLER_Device_t *ARCONTROLLER_Device_New (ARDISCOVERY_Device_t *discoveryDevice, eARCONTROLLER_ERROR *error);

/**
 * @brief Delete the Device Controller
 * @warning This function free memory
 * @param device The device controller to delete
 * @see ARCONTROLLER_Device_New
 */
void ARCONTROLLER_Device_Delete (ARCONTROLLER_Device_t **deviceController);

/**
 * @brief Start the Device Controller.
 * @post ARCONTROLLER_Device_Stop() must be called to stop the Device Controller.
 * @param deviceController The device controller to start.
 * @return executing error.
 * @see ARCONTROLLER_Device_Stop
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_Start (ARCONTROLLER_Device_t *deviceController);

/**
 * @brief Stop the Device Controller.
 * @param deviceController The device controller to Stop.
 * @return executing error.
 * @see ARCONTROLLER_Device_Start
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_Stop (ARCONTROLLER_Device_t *deviceController);

/**
 * @brief Set callback to receive the video stream.
 * @param deviceController The device controller.
 * @param decoderConfigCallback callback to configure the stream decoder.
 * @param receiveFrameCallback The callback when a frame is received.
 * @param timeoutFrameCallback The callback when timeout on receive.
 * @param[in] customData custom data given as parameter to the callback.
 * @return executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_SetVideoStreamCallbacks (ARCONTROLLER_Device_t *deviceController, ARCONTROLLER_Stream_DecoderConfigCallback_t decoderConfigCallback, ARCONTROLLER_Stream_DidReceiveFrameCallback_t receiveFrameCallback, ARCONTROLLER_Stream_TimeoutFrameCallback_t timeoutFrameCallback, void *customData);

/**
 * @brief Set video stream compliant with the mp4 format.
 * @note Must be set for decoding H264 stream by the iOS hardware decoder.
 * @param deviceController The device controller.
 * @param isMP4Compliant 1 if the video stream must be compliant with mp4 format ; otherwide 0.
 * @return Executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_SetVideoStreamMP4Compliant (ARCONTROLLER_Device_t *deviceController, int isMP4Compliant);

/**
 * @brief Add callback to be informed when a commands is received.
 * @param deviceController The device controller.
 * @param commandReceivedCallback The callback when a commands is received.
 * @param[in] customData custom data given as parameter to the callback.
 * @return executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_AddCommandReceivedCallback (ARCONTROLLER_Device_t *deviceController, ARCONTROLLER_DICTIONARY_CALLBACK_t commandReceivedCallback, void *customData);

/**
 * @brief Remove callback of command received information.
 * @param deviceController The device controller.
 * @param commandReceivedCallback The callback to remove.
 * @param[in] customData custom data associated to the callback.
 * @return executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_RemoveCommandReceivedCallback (ARCONTROLLER_Device_t *deviceController, ARCONTROLLER_DICTIONARY_CALLBACK_t commandReceivedCallback, void *customData);

/**
 * @brief Add callback of Device Controller state changed information.
 * @param deviceController The device controller.
 * @param StateChangedCallback The callback to add.
 * @param[in] customData custom data given as parameter to the callback.
 * @return executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_AddStateChangedCallback (ARCONTROLLER_Device_t *deviceController, ARCONTROLLER_Device_StateChangedCallback_t stateChangedCallback, void *customData);

/**
 * @brief Add callback of Device Controller extension state changed information.
 * @param deviceController The device controller.
 * @param extensionStateChangedCallback The callback to add.
 * @param[in] customData custom data given as parameter to the callback.
 * @return executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_AddExtensionStateChangedCallback (ARCONTROLLER_Device_t *deviceController, ARCONTROLLER_Device_ExtensionStateChangedCallback_t extensionStateChangedCallback, void *customData);

/**
 * @brief Remove callback of Device Controller state changed information.
 * @param deviceController The device controller.
 * @param StateChangedCallback The callback to remove.
 * @param[in] customData custom data associated to the callback.
 * @return executing error.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Device_RemoveStateChangedCallback (ARCONTROLLER_Device_t *deviceController, ARCONTROLLER_Device_StateChangedCallback_t stateChangedCallback, void *customData);

/**
 * @brief Get Element of a command received.
 * @param deviceController The device controller.
 * @param[in] commandKey The key of the command.
 * @param[out] error Executing error.
 * @return Element dictionary of the command
 */
ARCONTROLLER_DICTIONARY_ELEMENT_t *ARCONTROLLER_Device_GetCommandElements (ARCONTROLLER_Device_t *deviceController, eARCONTROLLER_DICTIONARY_KEY commandKey, eARCONTROLLER_ERROR *error);

/**
 * @brief Get the Device Controller state.
 * @param deviceController The device controller.
 * @return The state of the Device Controller.
 */
eARCONTROLLER_DEVICE_STATE ARCONTROLLER_Device_GetState (ARCONTROLLER_Device_t *deviceController, eARCONTROLLER_ERROR *error);

/**
 * @brief Get the Device Controller extension state.
 * @param deviceController The device controller.
 * @return The extension state of the Device Controller.
 */
eARCONTROLLER_DEVICE_STATE ARCONTROLLER_Device_GetExtensionState (ARCONTROLLER_Device_t *deviceController, eARCONTROLLER_ERROR *error);

/**
 * @brief Get the Device Controller extension name.
 * @param deviceController The device controller.
 * @param[out] buffer The buffer to receive the name.
 * @param[in] bufferSize The allocated size of the given buffer.
 */
void ARCONTROLLER_Device_GetExtensionName (ARCONTROLLER_Device_t *deviceController, char *buffer, int bufferSize, eARCONTROLLER_ERROR *error);

/**
 * @brief Get the Device Controller extension product type.
 * @param deviceController The device controller.
 * @return The product of the extension of the Device Controller.
 */
eARDISCOVERY_PRODUCT ARCONTROLLER_Device_GetExtensionProduct (ARCONTROLLER_Device_t *deviceController, eARCONTROLLER_ERROR *error);

#endif /* _ARCONTROLLER_DEVICE_H_ */

// END GENERATED CODE
