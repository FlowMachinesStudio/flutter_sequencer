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
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "./Logging.h"

class AAssetManager {

};

struct AAsset {
    std::vector<char> vec;
    const void* buffer;
    int size;
};

#define AASSET_MODE_BUFFER 0


AAsset* AAssetManager_open(AAssetManager* assetManager, const char* path, int mode) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }

    file.seekg(0, std::ios::end);
    int size = static_cast<int>(file.tellg());
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    file.read(buffer.data(), size);

    AAsset* asset = new AAsset();
    asset->vec = std::move(buffer);
    asset->buffer = asset->vec.data();
    asset->size = size;

    return asset;
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

std::string GetEntryPointDirectory() {
    wchar_t buffer[MAX_PATH];
    DWORD length = GetModuleFileName(nullptr, buffer, MAX_PATH);
    if (length == 0) {
        return "";
    }

    std::wstring path(buffer);
    size_t lastSlash = path.find_last_of(L"\\/");
    if (lastSlash != std::wstring::npos) {
        path = path.substr(0, lastSlash);
    }

    int requiredSize = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, nullptr, 0, nullptr, nullptr);
    if (requiredSize == 0) {
        return "";
    }
    std::string convertedPath(requiredSize, '\0');
    WideCharToMultiByte(CP_UTF8, 0, buffer, -1, convertedPath.data(), requiredSize, nullptr, nullptr);

    std::replace(convertedPath.begin(), convertedPath.end(), '\\', '/');

    size_t lastDirPos = convertedPath.find_last_of("/");
    if (lastDirPos != std::string::npos) {
        convertedPath = convertedPath.substr(0, lastDirPos);
    }

    return convertedPath;
}
std::string appendToAssetDir(const char* path) {
    std::string basePath = GetEntryPointDirectory();
    std::string assetDirStr = basePath + "/data/flutter_assets/";
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
