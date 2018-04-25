project (sampleinlinenotes)

cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)
set (QT_MIN_VERSION "5.4.0")
set(KF5_DEP_VERSION "5.13.0")

find_package (ECM 1.1.0 REQUIRED NO_MODULE)
set (CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(KDEInstallDirs)
include(KDECMakeSettings)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED Core Widgets)

find_package(KF5 "${KF5_DEP_VERSION}" REQUIRED COMPONENTS
  Parts
  TextEditor
  IconThemes
)

add_definitions(-DTRANSLATION_DOMAIN=\"sampleinlinenotes\")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(sampleinlinenotes_PART_SRCS
    plugin_sampleinlinenotes.cpp
    sampleinlinecolorbox.cpp
    sampleinlineicon.cpp
    sampleinlinetextnote.cpp
)

add_library(sampleinlinenotes MODULE ${sampleinlinenotes_PART_SRCS})
kcoreaddons_desktop_to_json (sampleinlinenotes sampleinlinenotes.desktop)

target_link_libraries(sampleinlinenotes KF5::TextEditor KF5::I18n KF5::IconThemes)

install(TARGETS sampleinlinenotes DESTINATION ${PLUGIN_INSTALL_DIR}/ktexteditor)
