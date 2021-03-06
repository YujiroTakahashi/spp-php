#ifndef PHP_SPP_API_H
#define PHP_SPP_API_H

#include <string.h>
#include <stdint.h>

#ifdef __cplusplus

#include <sentencepiece_processor.h>
#include "json.hpp"

extern "C" {

#endif /* __cplusplus */

#ifndef SPP_API
#   if defined(_WIN32) || defined(_WIN64)
#       define SPP_API __declspec(dllimport)
#   else
#       define SPP_API extern
#   endif /* defined(_WIN32) || defined(_WIN64) */
#endif /* SPP_API */

#ifndef SPP_VERSION
#    define SPP_VERSION 12
#endif /* SPP_VERSION */

#define SPP_TRUE           (1)
#define SPP_FALSE          (0)

struct _SPStr {
    size_t len;
    char *buff;
};

typedef void *SppHandle;
typedef struct _SPStr *SPStr;

SPP_API int SppVersion();
SPP_API int SppSize();
SPP_API SppHandle SppCreate();
SPP_API void SppFree(SppHandle handle);
SPP_API void SppStrFree(SPStr str);
SPP_API int SppLoad(SppHandle handle, const char* path);
SPP_API SPStr SppEncode(SppHandle handle, const char* word);
SPP_API SPStr SppWakati(SppHandle handle, const char* word);
SPP_API SPStr SppDecode(SppHandle handle, const char* json, size_t len);
SPP_API SPStr SppSampleEncode(SppHandle handle, const char* word, int size, float alpha);
SPP_API int SppGetPieceSize(SppHandle handle);
SPP_API int SppPieceToId(SppHandle handle, const char* word);
SPP_API SPStr SppIdToPiece(SppHandle handle, int id);
SPP_API int SppIsUnknown(SppHandle handle, int id);
SPP_API int SppIsControl(SppHandle handle, int id);
SPP_API int SppSetEncodeExtraOptions(SppHandle handle, const char* option);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PHP_SPP_API_H */
