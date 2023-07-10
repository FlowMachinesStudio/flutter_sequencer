#include <flsPlatform.h>
#include "WinEngine.h"
#include "../Utils/Logging.h"

oboe::DataCallbackResult WinEngine::onAudioReady(oboe::AudioStream *oboeStream, void *audioData, int32_t numFrames) {
    float* outputBuffer = static_cast<float *>(audioData);

    mSchedulerMixer.renderAudio(outputBuffer, numFrames);

    return oboe::DataCallbackResult::Continue;
}

WinEngine::WinEngine(Dart_Port sampleRateCallbackPort) {
    oboe::AudioStreamBuilder builder;

    builder.setSharingMode(oboe::SharingMode::Shared)
            ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
            ->setChannelCount(oboe::ChannelCount::Stereo)
            ->setSampleRate(kSampleRate)
            ->setFormat(oboe::AudioFormat::Float)
            ->setCallback(this)
            ->openManagedStream(mOutStream);

    mSchedulerMixer.setChannelCount(mOutStream->getChannelCount());
    callbackToDartInt32(sampleRateCallbackPort, mOutStream->getSampleRate());

};

WinEngine::~WinEngine() {
    mSchedulerMixer.pause();

    oboe::Result result = mOutStream->close();

    if (result != oboe::Result::OK){
        LOGE("Failed to close stream. Error: %s", convertToText(result));
        return;
    }
}

int32_t WinEngine::getSampleRate() {
    return mOutStream->getSampleRate();
}

int32_t WinEngine::getChannelCount() {
    return mOutStream->getChannelCount();
}

int32_t WinEngine::getBufferSize() {
    return mOutStream->getBufferSizeInFrames();
}

void WinEngine::play() {
    mSchedulerMixer.play();

    auto streamState = mOutStream->getState();

    // Don't request start if stream is already starting or started
    if (streamState != oboe::StreamState(3)
        && streamState != oboe::StreamState(4)) {
        oboe::Result result = mOutStream->requestStart();

        if (result != oboe::Result::OK){
            LOGE("Failed to start stream. Error: %s", convertToText(result));
            return;
        }
    }
}

void WinEngine::pause() {
    mSchedulerMixer.pause();

    oboe::Result result = mOutStream->requestPause();

    if (result != oboe::Result::OK){
        LOGE("Failed to pause stream. Error: %s", convertToText(result));
        return;
    }
}
