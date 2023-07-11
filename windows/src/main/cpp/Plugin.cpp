#include<flsPlatform.h>
#include <thread>
#ifdef USE_SFIZZ
#include "SharedInstruments/SfizzSamplerInstrument.h"
#endif // #ifdef USE_SFIZZ
#include "WinEngine/WinEngine.h"
#include "WinInstruments/SoundFontInstrument.h"
#include "Utils/OptionArray.h"

std::unique_ptr<WinEngine> engine;

void check_engine() {
    if (engine == nullptr) {
        throw std::runtime_error("Engine is not set up. Ensure that setup_engine() is called before calling this method.");
    }
}

void setInstrumentOutputFormat(IInstrument* instrument) {
    auto sampleRate = engine->getSampleRate();
    auto channelCount = engine->getChannelCount();
    auto isStereo = channelCount > 1;

    instrument->setOutputFormat(sampleRate, isStereo);
}

void __log_print(const char* level,
    const char* appName, const char* messageFormat, ...) {
    // FIXME:...
    /*
    std::cout << "[" << level << "] " << appName << ": ";
    va_list args;
    va_start(args, messageFormat);
    vprintf(messageFormat, args);
    va_end(args);

    std::cout << std::endl;
    */
}


extern "C" {
    DLL_EXPORT
    void setup_engine(Dart_Port sampleRateCallbackPort) {
        engine = std::make_unique<WinEngine>(sampleRateCallbackPort);
    }

    DLL_EXPORT
    void destroy_engine() {
        engine.reset();
    }

    DLL_EXPORT
    void add_track_sf2(const char* filename, bool isAsset, int32_t presetIndex, Dart_Port callbackPort) {
        check_engine();

        std::thread([=]() {
            auto sf2Instrument = new SoundFontInstrument();
            setInstrumentOutputFormat(sf2Instrument);

            auto didLoad = sf2Instrument->loadSf2File(filename, isAsset, presetIndex);

            if (didLoad) {
                auto trackIndex = engine->mSchedulerMixer.addTrack(sf2Instrument);

                callbackToDartInt32(callbackPort, trackIndex);
            } else {
                callbackToDartInt32(callbackPort, -1);
            }

        }).detach();
    }

    DLL_EXPORT
    void add_track_sfz(const char* filename, const char* tuningFilename, Dart_Port callbackPort) {
#ifdef USE_SZIFF
        check_engine();

        std::thread([=]() {
            auto sfzInstrument = new SfizzSamplerInstrument();
            setInstrumentOutputFormat(sfzInstrument);

            auto didLoad = sfzInstrument->loadSfzFile(filename, tuningFilename);

            if (didLoad) {
                auto bufferSize = engine->getBufferSize();
                sfzInstrument->setSamplesPerBlock(bufferSize);
                auto trackIndex = engine->mSchedulerMixer.addTrack(sfzInstrument);

                callbackToDartInt32(callbackPort, trackIndex);
            } else {
                callbackToDartInt32(callbackPort, -1);
            }
        }).detach();
#else // USE_SFIZZ
        LOGE("sfizz: disabled");
#endif // USE_SFIZZ
    }

    DLL_EXPORT
    void add_track_sfz_string(const char* sampleRoot, const char* sfzString, const char* tuningString, Dart_Port callbackPort) {
        check_engine();
#ifdef USE_SZIFF
        std::thread([=]() {
            auto sfzInstrument = new SfizzSamplerInstrument();
            setInstrumentOutputFormat(sfzInstrument);

            auto didLoad = sfzInstrument->loadSfzString(sampleRoot, sfzString, tuningString);

            if (didLoad) {
                auto bufferSize = engine->getBufferSize();
                sfzInstrument->setSamplesPerBlock(bufferSize);
                auto trackIndex = engine->mSchedulerMixer.addTrack(sfzInstrument);

                callbackToDartInt32(callbackPort, trackIndex);
            } else {
                callbackToDartInt32(callbackPort, -1);
            }
        }).detach();
#else // USE_SFIZZ
        LOGE("sfizz: disabled");
#endif // USE_SFIZZ
    }

DLL_EXPORT
    void remove_track(track_index_t trackIndex) {
        check_engine();

        engine->mSchedulerMixer.removeTrack(trackIndex);
    }

    DLL_EXPORT
    void reset_track(track_index_t trackIndex) {
        check_engine();

        engine->mSchedulerMixer.resetTrack(trackIndex);
    }

    DLL_EXPORT
    float get_track_volume(track_index_t trackIndex) {
        check_engine();

        return engine->mSchedulerMixer.getLevel(trackIndex);
    }

    DLL_EXPORT
    int32_t get_position() {
        check_engine();

        return engine->mSchedulerMixer.getPosition();
    }

    DLL_EXPORT
    uint64_t get_last_render_time_us() {
        check_engine();

        return engine->mSchedulerMixer.getLastRenderTimeUs();
    }

    DLL_EXPORT
    uint32_t get_buffer_available_count(track_index_t trackIndex) {
        return engine->mSchedulerMixer.getBufferAvailableCount(trackIndex);
    }

    DLL_EXPORT
    void handle_events_now(track_index_t trackIndex, const uint8_t* eventData, int32_t eventsCount) {
        check_engine();

        SchedulerEvent *events= new SchedulerEvent[eventsCount];

        rawEventDataToEvents(eventData, eventsCount, events);

        engine->mSchedulerMixer.handleEventsNow(trackIndex, events, eventsCount);
        delete[] events;
    }

    DLL_EXPORT
    int32_t schedule_events(track_index_t trackIndex, const uint8_t* eventData, int32_t eventsCount) {
        check_engine();

        SchedulerEvent *events = new SchedulerEvent[eventsCount];

        rawEventDataToEvents(eventData, eventsCount, events);

        uint32_t ret = engine->mSchedulerMixer.scheduleEvents(trackIndex, events, eventsCount);
        delete[] events;
        return ret;
    }

    DLL_EXPORT
    void clear_events(track_index_t trackIndex, position_frame_t fromFrame) {
        check_engine();

        return engine->mSchedulerMixer.clearEvents(trackIndex, fromFrame);
    }

    DLL_EXPORT
    void engine_play() {
        check_engine();

        engine->play();
    }

    DLL_EXPORT
    void engine_pause() {
        check_engine();

        engine->pause();
    }
}
