#include "flutter_sequencer_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

namespace flutter_sequencer {

// static
void FlutterSequencerPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "flutter_sequencer",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<FlutterSequencerPlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

FlutterSequencerPlugin::FlutterSequencerPlugin() {}

FlutterSequencerPlugin::~FlutterSequencerPlugin() {}

void FlutterSequencerPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  auto method_name = method_call.method_name();
  if (method_name.compare("getPlatformVersion") == 0) {
    std::ostringstream version_stream;
    version_stream << "Windows ";
    if (IsWindows10OrGreater()) {
      version_stream << "10+";
    } else if (IsWindows8OrGreater()) {
      version_stream << "8";
    } else if (IsWindows7OrGreater()) {
      version_stream << "7";
    }
    result->Success(flutter::EncodableValue(version_stream.str()));
  } else if  (method_name.compare("setupAssetManager") == 0) {
    result->Success(0);
  } else {
    OutputDebugStringA(method_name.c_str());
    result->NotImplemented();
  }
}

}  // namespace flutter_sequencer

////////////////////////////////////
#define EXPORT __declspec(dllexport)
typedef void* Dart_PostCObjectType;
typedef void* Dart_Port;

Dart_PostCObjectType dartPostCObject = NULL;
Dart_Port callbackPort;

#if defined(__cplusplus)
extern "C" {
#endif

EXPORT void RegisterDart_PostCObject(Dart_PostCObjectType _dartPostCObject) {
    dartPostCObject = _dartPostCObject;
}


#if defined(__cplusplus)
}  // extern "C"
#endif
