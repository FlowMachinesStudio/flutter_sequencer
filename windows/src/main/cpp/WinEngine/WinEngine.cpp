#include <flsPlatform.h>
#include "WinEngine.h"
#include "../Utils/Logging.h"

static void AudioCallback(void* data, Uint8 *stream, int len) {
    WinEngine* pWinEngine = static_cast<WinEngine*>(data);
    if (!pWinEngine) {
        return;
    }
    pWinEngine->audioCallback(stream, len);
}
void WinEngine::audioCallback(Uint8 *stream, int len) {
    float* outputBuffer = reinterpret_cast<float *>(stream);
    int32_t numFrames = (len / (2 * sizeof(float))); //2 output channels
    SDL_LockMutex(mSdlMutex); // really need?
    mSchedulerMixer.renderAudio(outputBuffer, numFrames);
    SDL_UnlockMutex(mSdlMutex);
}

WinEngine::WinEngine(Dart_Port sampleRateCallbackPort) {
    mSdlMutex = 0;
    mOutputAudioSpec.freq = 44100;
    mOutputAudioSpec.format = AUDIO_F32;
    mOutputAudioSpec.channels = 2;
    mOutputAudioSpec.samples = 4096;
    mOutputAudioSpec.callback = AudioCallback;
    mOutputAudioSpec.userdata = this;

  	if (SDL_AudioInit(0) < 0) {
        LOGE("Could not initialize audio hardware or driver\n");
		return;
	}

	mSdlMutex = SDL_CreateMutex();
	if (SDL_OpenAudio(&mOutputAudioSpec, 0) < 0)
	{
		LOGE("Could not open the audio hardware or the desired audio output format\n");
		return;
	}

    mSchedulerMixer.setChannelCount(mOutputAudioSpec.channels);
    callbackToDartInt32(sampleRateCallbackPort, mOutputAudioSpec.freq);
};

WinEngine::~WinEngine() {
    mSchedulerMixer.pause();
    SDL_PauseAudio(1);
    SDL_CloseAudio();
}

int32_t WinEngine::getSampleRate() {
    return mOutputAudioSpec.freq;
}

int32_t WinEngine::getChannelCount() {
    return mOutputAudioSpec.channels;
}

int32_t WinEngine::getBufferSize() {
    // FIXME:
    return mOutputAudioSpec.size;
}

void WinEngine::play() {
    mSchedulerMixer.play();
    SDL_PauseAudio(0);
}

void WinEngine::pause() {
    mSchedulerMixer.pause();
    SDL_PauseAudio(1);
}
