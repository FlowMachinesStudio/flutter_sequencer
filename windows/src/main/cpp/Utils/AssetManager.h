#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
/*
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
*/
#include <flsPlatform.h>
#include <string>
#include <regex>

#include "./Logging.h"

class AAssetManager {

};

struct AAsset {
    const void* buffer;
    int size;
};

#define AASSET_MODE_BUFFER 0

AAsset* AAssetManager_open(AAssetManager* assetManager, const char* path, int mode) {
    // FIXME: read path and fill AAsset?
    return 0;
}

const void* AAsset_getBuffer(AAsset* aasset) {
    return aasset->buffer;
}

int AAsset_getLength(AAsset* aasset) {
    return aasset->size;
}


void AAsset_close(AAsset* aasset) {
    if (!aasset) {
        return;
    }
    delete aasset;
}

AAssetManager *assetManager;

std::string appendToAssetDir(const char* path) {
    auto assetDirStr = std::string("flutter_assets/");
    auto pathStr = std::string(path);

    return assetDirStr.append(pathStr);
}

AAsset* openAssetBuffer(const char* path) {
    auto pathWithAssetDirStr = appendToAssetDir(path);
    return AAssetManager_open(assetManager, pathWithAssetDirStr.c_str(), AASSET_MODE_BUFFER);
}

/*
extern "C" __attribute__((visibility("default"))) __attribute__((used))
void JNICALL Java_com_michaeljperri_flutter_1sequencer_FlutterSequencerPlugin_setupAssetManager(
    JNIEnv *env, jobject instance, jobject jAssetManager) {

    assetManager = AAssetManager_fromJava(env, jAssetManager);

    if (assetManager == nullptr) {
    LOGE("Could not load assetManager");
    return;
    }

    LOGI("Successfully set asset manager in native module");
}
*/

#endif //ASSET_MANAGER_H
