#include <flsPlatform.h>
#include "Oboe_win.h"


oboe::Result oboe::AudioStreamBuilder::openManagedStream(ManagedStream& stream)
{
    return oboe::Result();
}

///////////////////////////////////////////////////////////////
namespace oboe {
    template<>
    const char* convertToText<Result>(Result returnCode) {
        switch (returnCode) {
        case Result::OK:                    return "OK";
        case Result::ErrorDisconnected:     return "ErrorDisconnected";
        case Result::ErrorIllegalArgument:  return "ErrorIllegalArgument";
        case Result::ErrorInternal:         return "ErrorInternal";
        case Result::ErrorInvalidState:     return "ErrorInvalidState";
        case Result::ErrorInvalidHandle:    return "ErrorInvalidHandle";
        case Result::ErrorUnimplemented:    return "ErrorUnimplemented";
        case Result::ErrorUnavailable:      return "ErrorUnavailable";
        case Result::ErrorNoFreeHandles:    return "ErrorNoFreeHandles";
        case Result::ErrorNoMemory:         return "ErrorNoMemory";
        case Result::ErrorNull:             return "ErrorNull";
        case Result::ErrorTimeout:          return "ErrorTimeout";
        case Result::ErrorWouldBlock:       return "ErrorWouldBlock";
        case Result::ErrorInvalidFormat:    return "ErrorInvalidFormat";
        case Result::ErrorOutOfRange:       return "ErrorOutOfRange";
        case Result::ErrorNoService:        return "ErrorNoService";
        case Result::ErrorInvalidRate:      return "ErrorInvalidRate";
        case Result::ErrorClosed:           return "ErrorClosed";
        default:                            return "Unrecognized result";
        }
    }

}; // namespace oboe