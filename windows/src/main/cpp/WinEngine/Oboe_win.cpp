#include <flsPlatform.h>
#include "Oboe_win.h"

///////////////////////////////////////////////////////////////



namespace oboe {

    Result AudioStreamBuilder::openManagedStream(oboe::ManagedStream& stream) {
        stream.reset();
        AudioStream* streamptr;
        auto result = openStream(&streamptr);
        stream.reset(streamptr);
        return result;
    }

    Result AudioStreamBuilder::openStream(AudioStream **streamPP) {
        auto result = Result::OK;
        // FIXME: create concrete stream.
        // what is stream?
        *streamPP = new AudioStreamAAudioWin(*this);
        return result;
    }

    Result AudioStreamBuilder::openStream(std::shared_ptr<AudioStream>& sharedStream) {
        sharedStream.reset();
        AudioStream* streamptr;
        auto result = openStream(&streamptr);
        if (result == Result::OK) {
            sharedStream.reset(streamptr);
            // Save a weak_ptr in the stream for use with callbacks.
            streamptr->setWeakThis(sharedStream);
        }
        return result;
    }

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

    AudioStream::AudioStream(const AudioStreamBuilder &builder)
        : AudioStreamBase(builder) {
    }

    Result AudioStream::close() {
        // FIXME.
        return Result::OK;
    }



    AudioStreamAAudioWin::AudioStreamAAudioWin(const AudioStreamBuilder &builder)
        : AudioStream(builder)
        /*
        , mAAudioStream(nullptr)
        */
       {
        //mCallbackThreadEnabled.store(false);
        //mLibLoader = AAudioLoader::getInstance();
    }

    StreamState AudioStreamAAudioWin::getState() {
        return StreamState::Closed;
    }
    Result AudioStreamAAudioWin::requestPause() {
        return Result::OK;
    }
    Result AudioStreamAAudioWin::requestStart() {
        return Result::OK;
    }


}; // namespace oboe