#ifndef WIN_ENGINE_H
#define WIN_ENGINE_H

#include "./Oboe_win.h"
#include "CallbackManager.h"
#include "IInstrument.h"
#include "../WinInstruments/Mixer.h"

class WinEngine : public oboe::AudioStreamCallback {
public:
    explicit WinEngine(Dart_Port sampleRateCallbackPort);
    ~WinEngine();

    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) override;

    int32_t getSampleRate();
    int32_t getChannelCount();
    int32_t getBufferSize();
    void play();
    void pause();

    Mixer mSchedulerMixer;
private:
    oboe::ManagedStream mOutStream;

    static int constexpr kSampleRate = 44100;
};

#endif //WIN_ENGINE_H
