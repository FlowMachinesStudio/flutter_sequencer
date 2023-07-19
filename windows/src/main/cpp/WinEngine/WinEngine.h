#ifndef WIN_ENGINE_H
#define WIN_ENGINE_H

#include "CallbackManager.h"
#include "IInstrument.h"
#include "../WinInstruments/Mixer.h"
#include "minisdl_audio.h"

class WinEngine {
public:
    explicit WinEngine(Dart_Port sampleRateCallbackPort);
    ~WinEngine();

    void audioCallback(Uint8 *stream, int len);

    int32_t getSampleRate();
    int32_t getChannelCount();
    int32_t getBufferSize();
    void play();
    void pause();

    Mixer mSchedulerMixer;
private:
    SDL_AudioSpec mOutputAudioSpec;
    SDL_mutex* mSdlMutex;

    static int constexpr kSampleRate = 44100;
};

#endif //WIN_ENGINE_H
