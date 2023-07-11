#ifndef OBOE_WIN_H
#define OBOE_WIN_H


namespace oboe
{
    constexpr int32_t kUnspecified = 0;


enum class SharingMode : int32_t
    { // aaudio_sharing_mode_t

        /**
         * This will be the only stream using a particular source or sink.
         * This mode will provide the lowest possible latency.
         * You should close EXCLUSIVE streams immediately when you are not using them.
         *
         * If you do not need the lowest possible latency then we recommend using Shared,
         * which is the default.
         */
        Exclusive = 0, // AAUDIO_SHARING_MODE_EXCLUSIVE,

        /**
         * Multiple applications can share the same device.
         * The data from output streams will be mixed by the audio service.
         * The data for input streams will be distributed by the audio service.
         *
         * This will have higher latency than the EXCLUSIVE mode.
         */
        Shared = 1, // AAUDIO_SHARING_MODE_SHARED,
    };
/**
     * The performance mode of the audio stream.
     */
    enum class PerformanceMode : int32_t
    { // aaudio_performance_mode_t

        /**
         * No particular performance needs. Default.
         */
        None = 10, // AAUDIO_PERFORMANCE_MODE_NONE,

        /**
         * Extending battery life is most important.
         */
        PowerSaving = 11, // AAUDIO_PERFORMANCE_MODE_POWER_SAVING,

        /**
         * Reducing latency is most important.
         */
        LowLatency = 12, // AAUDIO_PERFORMANCE_MODE_LOW_LATENCY
    };

    enum ChannelCount : int32_t
    {
        /**
         * Audio channel count definition, use Mono or Stereo
         */
        Unspecified = kUnspecified,

        /**
         * Use this for mono audio
         */
        Mono = 1,

        /**
         * Use this for stereo audio.
         */
        Stereo = 2,
    };

    enum class DataCallbackResult : int32_t
    {                 // aaudio_data_callback_result_t
                      // Indicates to the caller that the callbacks should continue.
        Continue = 0, // AAUDIO_CALLBACK_RESULT_CONTINUE,

        // Indicates to the caller that the callbacks should stop immediately.
        Stop = 1, // AAUDIO_CALLBACK_RESULT_STOP,
    };

    
    enum class AudioFormat : int32_t
    { // aaudio_format_t
        /**
         * Invalid format.
         */
        Invalid = -1, // AAUDIO_FORMAT_INVALID,

        /**
         * Unspecified format. Format will be decided by Oboe.
         * When calling getHardwareFormat(), this will be returned if
         * the API is not supported.
         */
        Unspecified = 0, // AAUDIO_FORMAT_UNSPECIFIED,

        /**
         * Signed 16-bit integers.
         */
        I16 = 1, // AAUDIO_FORMAT_PCM_I16,

        /**
         * Single precision floating point.
         *
         * This is the recommended format for most applications.
         * But note that the use of Float may prevent the opening of
         * a low-latency input path on OpenSL ES or Legacy AAudio streams.
         */
        Float = 2, // AAUDIO_FORMAT_PCM_FLOAT,

        /**
         * Signed 24-bit integers, packed into 3 bytes.
         *
         * Note that the use of this format does not guarantee that
         * the full precision will be provided.  The underlying device may
         * be using I16 format.
         *
         * Added in API 31 (S).
         */
        I24 = 3, // AAUDIO_FORMAT_PCM_I24_PACKED

        /**
         * Signed 32-bit integers.
         *
         * Note that the use of this format does not guarantee that
         * the full precision will be provided.  The underlying device may
         * be using I16 format.
         *
         * Added in API 31 (S).
         */
        I32 = 4, // AAUDIO_FORMAT_PCM_I32

        /**
         * This format is used for compressed audio wrapped in IEC61937 for HDMI
         * or S/PDIF passthrough.
         *
         * Unlike PCM playback, the Android framework is not able to do format
         * conversion for IEC61937. In that case, when IEC61937 is requested, sampling
         * rate and channel count or channel mask must be specified. Otherwise, it may
         * fail when opening the stream. Apps are able to get the correct configuration
         * for the playback by calling AudioManager#getDevices(int).
         *
         * Available since API 34 (U).
         */
        IEC61937 = 5, // AAUDIO_FORMAT_IEC61937
    };

    template <typename FromType>
    const char *convertToText(FromType input);

    enum class StreamState : int32_t
    {                      // aaudio_stream_state_t
        Uninitialized = 0, // AAUDIO_STREAM_STATE_UNINITIALIZED,
        Unknown = 1,       // AAUDIO_STREAM_STATE_UNKNOWN,
        Open = 2,          // AAUDIO_STREAM_STATE_OPEN,
        Starting = 3,      // AAUDIO_STREAM_STATE_STARTING,
        Started = 4,       // AAUDIO_STREAM_STATE_STARTED,
        Pausing = 5,       // AAUDIO_STREAM_STATE_PAUSING,
        Paused = 6,        // AAUDIO_STREAM_STATE_PAUSED,
        Flushing = 7,      // AAUDIO_STREAM_STATE_FLUSHING,
        Flushed = 8,       // AAUDIO_STREAM_STATE_FLUSHED,
        Stopping = 9,      // AAUDIO_STREAM_STATE_STOPPING,
        Stopped = 10,      // AAUDIO_STREAM_STATE_STOPPED,
        Closing = 11,      // AAUDIO_STREAM_STATE_CLOSING,
        Closed = 12,       // AAUDIO_STREAM_STATE_CLOSED,
        Disconnected = 13, // AAUDIO_STREAM_STATE_DISCONNECTED,
    };

    enum class Result : int32_t
    {                                // aaudio_result_t
        OK = 0,                      // AAUDIO_OK
        ErrorBase = -900,            // AAUDIO_ERROR_BASE,
        ErrorDisconnected = -899,    // AAUDIO_ERROR_DISCONNECTED,
        ErrorIllegalArgument = -898, // AAUDIO_ERROR_ILLEGAL_ARGUMENT,
        ErrorInternal = -896,        // AAUDIO_ERROR_INTERNAL,
        ErrorInvalidState = -895,    // AAUDIO_ERROR_INVALID_STATE,
        ErrorInvalidHandle = -892,   // AAUDIO_ERROR_INVALID_HANDLE,
        ErrorUnimplemented = -890,   // AAUDIO_ERROR_UNIMPLEMENTED,
        ErrorUnavailable = -889,     // AAUDIO_ERROR_UNAVAILABLE,
        ErrorNoFreeHandles = -888,   // AAUDIO_ERROR_NO_FREE_HANDLES,
        ErrorNoMemory = -887,        // AAUDIO_ERROR_NO_MEMORY,
        ErrorNull = -886,            // AAUDIO_ERROR_NULL,
        ErrorTimeout = -885,         // AAUDIO_ERROR_TIMEOUT,
        ErrorWouldBlock = -884,      // AAUDIO_ERROR_WOULD_BLOCK,
        ErrorInvalidFormat = -883,   // AAUDIO_ERROR_INVALID_FORMAT,
        ErrorOutOfRange = -882,      // AAUDIO_ERROR_OUT_OF_RANGE,
        ErrorNoService = -881,       // AAUDIO_ERROR_NO_SERVICE,
        ErrorInvalidRate = -880,     // AAUDIO_ERROR_INVALID_RATE,
                                 // Reserved for future AAudio result types
        Reserved1,
        Reserved2,
        Reserved3,
        Reserved4,
        Reserved5,
        Reserved6,
        Reserved7,
        Reserved8,
        Reserved9,
        Reserved10,
        ErrorClosed = -869,
    };

    enum class ChannelMask : uint32_t
    { // aaudio_channel_mask_t
        Unspecified = kUnspecified,
        FrontLeft = 1 << 0,
        FrontRight = 1 << 1,
        FrontCenter = 1 << 2,
        LowFrequency = 1 << 3,
        BackLeft = 1 << 4,
        BackRight = 1 << 5,
        FrontLeftOfCenter = 1 << 6,
        FrontRightOfCenter = 1 << 7,
        BackCenter = 1 << 8,
        SideLeft = 1 << 9,
        SideRight = 1 << 10,
        TopCenter = 1 << 11,
        TopFrontLeft = 1 << 12,
        TopFrontCenter = 1 << 13,
        TopFrontRight = 1 << 14,
        TopBackLeft = 1 << 15,
        TopBackCenter = 1 << 16,
        TopBackRight = 1 << 17,
        TopSideLeft = 1 << 18,
        TopSideRight = 1 << 19,
        BottomFrontLeft = 1 << 20,
        BottomFrontCenter = 1 << 21,
        BottomFrontRight = 1 << 22,
        LowFrequency2 = 1 << 23,
        FrontWideLeft = 1 << 24,
        FrontWideRight = 1 << 25,

        Mono = FrontLeft,

        Stereo = FrontLeft |
                 FrontRight,

        CM2Point1 = FrontLeft |
                    FrontRight |
                    LowFrequency,

        Tri = FrontLeft |
              FrontRight |
              FrontCenter,

        TriBack = FrontLeft |
                  FrontRight |
                  BackCenter,

        CM3Point1 = FrontLeft |
                    FrontRight |
                    FrontCenter |
                    LowFrequency,

        CM2Point0Point2 = FrontLeft |
                          FrontRight |
                          TopSideLeft |
                          TopSideRight,

        CM2Point1Point2 = CM2Point0Point2 |
                          LowFrequency,

        CM3Point0Point2 = FrontLeft |
                          FrontRight |
                          FrontCenter |
                          TopSideLeft |
                          TopSideRight,

        CM3Point1Point2 = CM3Point0Point2 |
                          LowFrequency,

        Quad = FrontLeft |
               FrontRight |
               BackLeft |
               BackRight,

        QuadSide = FrontLeft |
                   FrontRight |
                   SideLeft |
                   SideRight,

        Surround = FrontLeft |
                   FrontRight |
                   FrontCenter |
                   BackCenter,

        Penta = Quad |
                FrontCenter,

        // aka 5Point1Back
        CM5Point1 = FrontLeft |
                    FrontRight |
                    FrontCenter |
                    LowFrequency |
                    BackLeft |
                    BackRight,

        CM5Point1Side = FrontLeft |
                        FrontRight |
                        FrontCenter |
                        LowFrequency |
                        SideLeft |
                        SideRight,

        CM6Point1 = FrontLeft |
                    FrontRight |
                    FrontCenter |
                    LowFrequency |
                    BackLeft |
                    BackRight |
                    BackCenter,

        CM7Point1 = CM5Point1 |
                    SideLeft |
                    SideRight,

        CM5Point1Point2 = CM5Point1 |
                          TopSideLeft |
                          TopSideRight,

        CM5Point1Point4 = CM5Point1 |
                          TopFrontLeft |
                          TopFrontRight |
                          TopBackLeft |
                          TopBackRight,

        CM7Point1Point2 = CM7Point1 |
                          TopSideLeft |
                          TopSideRight,

        CM7Point1Point4 = CM7Point1 |
                          TopFrontLeft |
                          TopFrontRight |
                          TopBackLeft |
                          TopBackRight,

        CM9Point1Point4 = CM7Point1Point4 |
                          FrontWideLeft |
                          FrontWideRight,

        CM9Point1Point6 = CM9Point1Point4 |
                          TopSideLeft |
                          TopSideRight,

        FrontBack = FrontCenter |
                    BackCenter,
    };

    /**
     * AudioStreamDataCallback defines a callback interface for
     * moving data to/from an audio stream using `onAudioReady`
     * 2) being alerted when a stream has an error using `onError*` methods
     *
     * It is used with AudioStreamBuilder::setDataCallback().
     */
    class AudioStream;
    class AudioStreamDataCallback
    {
    public:
        virtual ~AudioStreamDataCallback() = default;

        /**
         * A buffer is ready for processing.
         *
         * For an output stream, this function should render and write numFrames of data
         * in the stream's current data format to the audioData buffer.
         *
         * For an input stream, this function should read and process numFrames of data
         * from the audioData buffer.
         *
         * The audio data is passed through the buffer. So do NOT call read() or
         * write() on the stream that is making the callback.
         *
         * Note that numFrames can vary unless AudioStreamBuilder::setFramesPerCallback()
         * is called.
         *
         * Also note that this callback function should be considered a "real-time" function.
         * It must not do anything that could cause an unbounded delay because that can cause the
         * audio to glitch or pop.
         *
         * These are things the function should NOT do:
         * <ul>
         * <li>allocate memory using, for example, malloc() or new</li>
         * <li>any file operations such as opening, closing, reading or writing</li>
         * <li>any network operations such as streaming</li>
         * <li>use any mutexes or other synchronization primitives</li>
         * <li>sleep</li>
         * <li>oboeStream->stop(), pause(), flush() or close()</li>
         * <li>oboeStream->read()</li>
         * <li>oboeStream->write()</li>
         * </ul>
         *
         * The following are OK to call from the data callback:
         * <ul>
         * <li>oboeStream->get*()</li>
         * <li>oboe::convertToText()</li>
         * <li>oboeStream->setBufferSizeInFrames()</li>
         * </ul>
         *
         * If you need to move data, eg. MIDI commands, in or out of the callback function then
         * we recommend the use of non-blocking techniques such as an atomic FIFO.
         *
         * @param audioStream pointer to the associated stream
         * @param audioData buffer containing input data or a place to put output data
         * @param numFrames number of frames to be processed
         * @return DataCallbackResult::Continue or DataCallbackResult::Stop
         */
        
        virtual DataCallbackResult onAudioReady(
            AudioStream *audioStream,
            void *audioData,
            int32_t numFrames) = 0;
        
    };
    
    class AudioStreamErrorCallback
    {
    public:
        virtual ~AudioStreamErrorCallback() = default;

        /**
         * This will be called before other `onError` methods when an error occurs on a stream,
         * such as when the stream is disconnected.
         *
         * It can be used to override and customize the normal error processing.
         * Use of this method is considered an advanced technique.
         * It might, for example, be used if an app want to use a high level lock when
         * closing and reopening a stream.
         * Or it might be used when an app want to signal a management thread that handles
         * all of the stream state.
         *
         * If this method returns false it indicates that the stream has *not been stopped and closed
         * by the application. In this case it will be stopped by Oboe in the following way:
         * onErrorBeforeClose() will be called, then the stream will be closed and onErrorAfterClose()
         * will be closed.
         *
         * If this method returns true it indicates that the stream *has* been stopped and closed
         * by the application and Oboe will not do this.
         * In that case, the app MUST stop() and close() the stream.
         *
         * This method will be called on a thread created by Oboe.
         *
         * @param audioStream pointer to the associated stream
         * @param error
         * @return true if the stream has been stopped and closed, false if not
         */
        virtual bool onError(AudioStream* /* audioStream */, Result /* error */)
        {
            return false;
        }

        /**
         * This will be called when an error occurs on a stream,
         * such as when the stream is disconnected,
         * and if onError() returns false (indicating that the error has not already been handled).
         *
         * Note that this will be called on a thread created by Oboe.
         *
         * The underlying stream will already be stopped by Oboe but not yet closed.
         * So the stream can be queried.
         *
         * Do not close or delete the stream in this method because it will be
         * closed after this method returns.
         *
         * @param audioStream pointer to the associated stream
         * @param error
         */
        virtual void onErrorBeforeClose(AudioStream* /* audioStream */, Result /* error */) {}

        /**
         * This will be called when an error occurs on a stream,
         * such as when the stream is disconnected,
         * and if onError() returns false (indicating that the error has not already been handled).
         *
         * The underlying AAudio or OpenSL ES stream will already be stopped AND closed by Oboe.
         * So the underlying stream cannot be referenced.
         * But you can still query most parameters.
         *
         * This callback could be used to reopen a new stream on another device.
         *
         * @param audioStream pointer to the associated stream
         * @param error
         */
        virtual void onErrorAfterClose(AudioStream* /* audioStream */, Result /* error */) {}
    };


    class AudioStreamDataCallback;
    class AudioStreamErrorCallback;

    class AudioStreamBase
    {

    public:
        AudioStreamBase() {}

        virtual ~AudioStreamBase() = default;

        int32_t getChannelCount() const { return mChannelCount; }
        int32_t getSampleRate() const { return mSampleRate; }
        virtual int32_t getBufferSizeInFrames() { return mBufferSizeInFrames; }

    protected:
        AudioStreamDataCallback *mDataCallback = nullptr;
        std::shared_ptr<AudioStreamDataCallback> mSharedDataCallback;

        AudioStreamErrorCallback *mErrorCallback = nullptr;
        std::shared_ptr<AudioStreamErrorCallback> mSharedErrorCallback;
        int32_t mChannelCount = kUnspecified;
        int32_t mBufferSizeInFrames = kUnspecified;
        ChannelMask mChannelMask = ChannelMask::Unspecified;
        AudioFormat mFormat = AudioFormat::Unspecified;
        PerformanceMode mPerformanceMode = PerformanceMode::None;
        int32_t mSampleRate = kUnspecified;
        SharingMode mSharingMode = SharingMode::Shared;
    };

    class AudioStreamCallback;
    class AudioStreamErrorCallback;

    struct StreamDeleterFunctor;
    class AudioStream;
    using ManagedStream = std::unique_ptr<AudioStream, StreamDeleterFunctor>;

    class AudioStreamCallback : public AudioStreamDataCallback,
        public AudioStreamErrorCallback
    {
    public:
        virtual ~AudioStreamCallback() = default;
    };

        class AudioStreamBuilder : public AudioStreamBase
    {
    public:
        AudioStreamBuilder() : AudioStreamBase() {}

        AudioStreamBuilder *setSharingMode(SharingMode sharingMode)
        {
            mSharingMode = sharingMode;
            return this;
        }
        AudioStreamBuilder *setPerformanceMode(PerformanceMode performanceMode)
        {
            mPerformanceMode = performanceMode;
            return this;
        }
        AudioStreamBuilder *setChannelCount(int channelCount)
        {
            mChannelCount = channelCount;
            mChannelMask = ChannelMask::Unspecified;
            return this;
        }
        AudioStreamBuilder *setSampleRate(int32_t sampleRate)
        {
            mSampleRate = sampleRate;
            return this;
        }
        AudioStreamBuilder *setFormat(AudioFormat format)
        {
            mFormat = format;
            return this;
        }
        AudioStreamBuilder *setCallback(AudioStreamCallback *streamCallback)
        {
            // Use the same callback object for both, dual inheritance.
            mDataCallback = streamCallback;
            mErrorCallback = streamCallback;
            return this;
        }
        Result openManagedStream(ManagedStream &stream);
        Result openStream(AudioStream **stream);
        Result AudioStreamBuilder::openStream(std::shared_ptr<AudioStream> &sharedStream);
    };

    class AudioStream;
    class AudioStream : public AudioStreamBase
    {
        friend class AudioStreamBuilder; // allow access to setWeakThis() and lockWeakThis()
    public:
        AudioStream() {}

        /**
         * Construct an `AudioStream` using the given `AudioStreamBuilder`
         *
         * @param builder containing all the stream's attributes
         */
        explicit AudioStream(const AudioStreamBuilder &builder);

        virtual ~AudioStream() = default;

        virtual Result close();

        void setWeakThis(std::shared_ptr<oboe::AudioStream>& sharedStream) {
            mWeakThis = sharedStream;
        }

        virtual StreamState getState() = 0;
         virtual Result requestPause() = 0;
         virtual Result requestStart() = 0;

         std::weak_ptr<AudioStream> mWeakThis; // weak pointer to this object
    };

    struct StreamDeleterFunctor
    {
        void operator()(AudioStream *audioStream)
        {
            if (audioStream)
            {
                audioStream->close();
            }
            delete audioStream;
        }
    };

    class AudioStreamAAudioWin : public AudioStream {
    public:
        AudioStreamAAudioWin();
        explicit AudioStreamAAudioWin(const AudioStreamBuilder &builder);

        virtual ~AudioStreamAAudioWin() = default;

        virtual StreamState getState() override;
        virtual Result requestPause() override;
        virtual Result requestStart() override;
    };

}; // namespace

#endif // OBOE_WIN_H
