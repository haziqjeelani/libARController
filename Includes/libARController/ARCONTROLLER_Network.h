/*
    Copyright (C) 2014 Parrot SA

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in
      the documentation and/or other materials provided with the 
      distribution.
    * Neither the name of Parrot nor the names
      of its contributors may be used to endorse or promote products
      derived from this software without specific prior written
      permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
    COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
    BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
    OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED 
    AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
    OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*/
/**
 * @file ARNETWORK_Network.h
 * @brief ARCONTROLLER_Network allow to operate an ARNETWORK_Manager for send and receive commands.
 * @date 02/03/2015
 * @author maxime.maitre@parrot.com
 */

#ifndef _ARCONTROLLER_NETWORK_H_
#define _ARCONTROLLER_NETWORK_H_

#include <libARSAL/ARSAL_Thread.h>
#include <libARNetwork/ARNETWORK_Manager.h>
#include <libARController/ARCONTROLLER_Error.h>

/**
 * Enum characterizing the type of data to send
 */
typedef enum
{
    ARCONTROLLER_NETWORK_SENDING_DATA_TYPE_NOT_ACK = 0,
    ARCONTROLLER_NETWORK_SENDING_DATA_TYPE_ACK,
    ARCONTROLLER_NETWORK_SENDING_DATA_TYPE_HIGHT_PRIORITY,
    ARCONTROLLER_NETWORK_SENDING_DATA_TYPE_STREAM,
    
    ARCONTROLLER_NETWORK_SENDING_DATA_TYPE_MAX
}
eARCONTROLLER_NETWORK_SENDING_DATA_TYPE;

/**
 * Enum characterizing the states of the network controller
 */
typedef enum
{
    ARCONTROLLER_NETWORK_STATE_STOPPED = 0, /**< network controller stopped */
    ARCONTROLLER_NETWORK_STATE_RUNNING, /**< network controller running */
    ARCONTROLLER_NETWORK_STATE_PAUSE, /**< network controller in pause */
    
    ARCONTROLLER_NETWORK_STATE_MAX /**< Max of the enumeration */
}
eARCONTROLLER_NETWORK_STATE;

/**
 * @brief Network controller allow to operate an ARNETWORK_Manager for send and receive commands.
 */
typedef struct ARCONTROLLER_Network_t ARCONTROLLER_Network_t;

typedef struct
{
    eARNETWORK_MANAGER_CALLBACK_RETURN timeoutPolicy;
    //ARNETWORK_Manager_Callback_t customCallback;
    void *customData;
}ARCONTROLLER_NETWORK_SendingConfiguration_t;

/**
 * @brief Create a new Network Controller
 * @warning This function allocate memory
 * @post ARCONTROLLER_Network_New() must be called to delete the Network Controller and free the memory allocated.
 * @param[in] discoveryDevice The device to drive ; must be not NULL.
 * @param[out] error error output.
 * @return the new Network Controller
 * @see ARCONTROLLER_Network_Delete()
 */
ARCONTROLLER_Network_t *ARCONTROLLER_Network_New (ARDISCOVERY_DiscoveryDevice_t discoveryDevice, eARCONTROLLER_ERROR *error);

/**
 * @brief Delete the Network Controller
 * @warning This function free memory
 * @param networkController address of the pointer on the network controller
 * @see ARCONTROLLER_Network_New()
 */
void ARCONTROLLER_Network_Delete (ARCONTROLLER_Network_t **networkController);

/**
 * @brief Pauses the Network Controller
 * @note Network Controller state must be ARCONTROLLER_NETWORK_STATE_RUNNING ; nothing will be done in others cases
 * @param[in] networkController The network Controller ; must be not NULL.
 * @see ARCONTROLLER_Network_Resume()
 */
eARCONTROLLER_ERROR ARCONTROLLER_Network_Pause (ARCONTROLLER_Network_t *networkController);

/**
 * @brief Resumes the Network Controller
 * @note Network Controller state must be ARCONTROLLER_NETWORK_STATE_PAUSE ; nothing will be done in ARCONTROLLER_NETWORK_STATE_RUNNING case ; in case ARCONTROLLER_NETWORK_STATE_STOPPED an error ARCONTROLLER_ERROR_STATE will be returned.
 * @param[in] networkController The network Controller ; must be not NULL.
 * @see ARCONTROLLER_Network_Pause()
 */
eARCONTROLLER_ERROR ARCONTROLLER_Network_Resume (ARCONTROLLER_Network_t *networkController);

/**
 * @brief stop the threads of sending and reception
 * @param[in] networkController The network Controller ; must be not NULL.
 */
eARCONTROLLER_ERROR ARCONTROLLER_Network_Stop (ARCONTROLLER_Network_t *networkController);


//eARCONTROLLER_ERROR ARCONTROLLER_Network_SendData (ARCONTROLLER_Network_t *networkController, void *data, int dataSize, int bufferID, ARCONTROLLER_NETWORK_SendingConfiguration_t sendingConfig);
eARCONTROLLER_ERROR ARCONTROLLER_Network_SendData (ARCONTROLLER_Network_t *networkController, void *data, int dataSize, eARCONTROLLER_NETWORK_SENDING_DATA_TYPE dataType, eARNETWORK_MANAGER_CALLBACK_RETURN timeoutPolicy, eARNETWORK_ERROR *netError);




#endif /* _ARCONTROLLER_NETWORK_H_ */
