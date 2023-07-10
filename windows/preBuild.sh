#!/bin/bash

if [ "$1" = "clean" ]; then
  rm -rf "./third_party"
  exit
fi

cloneAndBuildThirdPartyRepo() {
  REPO_NAME=$1
  REPO_URL=$2
  REPO_TAG=$3
  DEST_DIR=$4

  git clone ${REPO_URL} ${DEST_DIR}

  pushd ${DEST_DIR}
  git checkout ${REPO_TAG}
  pwd
  git status
  git submodule update --init --recursive
  popd
}

if [ ! -d "./third_party" ]; then
  mkdir "./third_party"

  cloneAndBuildThirdPartyRepo "TinySoundFont" "https://github.com/schellingb/TinySoundFont.git" "bf574519e601202c3a9d27a74f345921277eed39" "./third_party/TinySoundFont"
  cloneAndBuildThirdPartyRepo "sfizz" "https://github.com/sfztools/sfizz.git" "fc1f0451cebd8996992cbc4f983fcf76b03295c5" "./third_party/sfizz"

  if [ "$1" = "nobuild" ]; then
    exit
  fi

  pushd ./third_party/sfizz
  cmake -DCMAKE_BUILD_TYPE=sfizz_static \
    -DSFIZZ_JACK=OFF \
    -DSFIZZ_RENDER=OFF \
    -DSFIZZ_LV2=OFF \
    -DSFIZZ_LV2_UI=OFF \
    -DSFIZZ_VST=OFF \
    -DSFIZZ_AU=OFF \
    -DSFIZZ_SHARED=OFF \
    -B build -S .

  cmake --build build -j
fi
