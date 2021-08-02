#ifndef ERROR_CODE_CONFIG_H__
#define ERROR_CODE_CONFIG_H__


#define ERROR_CODE_BASE_NUM      (0x0)       ///< Global error base


#define ERROR_CODE_SUCCESS                     (ERROR_CODE_BASE_NUM + 0)  ///< Successful command
#define ERROR_CODE_SVC_HANDLER_MISSING         (ERROR_CODE_BASE_NUM + 1)  ///< SVC handler is missing
#define ERROR_CODE_SOFTDEVICE_NOT_ENABLED      (ERROR_CODE_BASE_NUM + 2)  ///< SoftDevice has not been enabled
#define ERROR_CODE_INTERNAL                    (ERROR_CODE_BASE_NUM + 3)  ///< Internal Error
#define ERROR_CODE_NO_MEM                      (ERROR_CODE_BASE_NUM + 4)  ///< No Memory for operation
#define ERROR_CODE_NOT_FOUND                   (ERROR_CODE_BASE_NUM + 5)  ///< Not found
#define ERROR_CODE_NOT_SUPPORTED               (ERROR_CODE_BASE_NUM + 6)  ///< Not supported
#define ERROR_CODE_INVALID_PARAM               (ERROR_CODE_BASE_NUM + 7)  ///< Invalid Parameter
#define ERROR_CODE_INVALID_STATE               (ERROR_CODE_BASE_NUM + 8)  ///< Invalid state, operation disallowed in this state
#define ERROR_CODE_INVALID_LENGTH              (ERROR_CODE_BASE_NUM + 9)  ///< Invalid Length
#define ERROR_CODE_INVALID_FLAGS               (ERROR_CODE_BASE_NUM + 10) ///< Invalid Flags
#define ERROR_CODE_INVALID_DATA                (ERROR_CODE_BASE_NUM + 11) ///< Invalid Data
#define ERROR_CODE_DATA_SIZE                   (ERROR_CODE_BASE_NUM + 12) ///< Data size exceeds limit
#define ERROR_CODE_TIMEOUT                     (ERROR_CODE_BASE_NUM + 13) ///< Operation timed out
#define ERROR_CODE_NULL                        (ERROR_CODE_BASE_NUM + 14) ///< Null Pointer
#define ERROR_CODE_FORBIDDEN                   (ERROR_CODE_BASE_NUM + 15) ///< Forbidden Operation
#define ERROR_CODE_INVALID_ADDR                (ERROR_CODE_BASE_NUM + 16) ///< Bad Memory Address
#define ERROR_CODE_BUSY                        (ERROR_CODE_BASE_NUM + 17) ///< Busy

#endif // NRF_ERROR_H__

/**
  @}
*/

