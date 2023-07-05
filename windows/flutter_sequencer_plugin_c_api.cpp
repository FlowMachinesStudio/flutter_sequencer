#include "include/flutter_sequencer/flutter_sequencer_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "flutter_sequencer_plugin.h"

void FlutterSequencerPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  flutter_sequencer::FlutterSequencerPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
