project(kde-thumbnailer-mp4cover)
cmake_minimum_required(VERSION 2.8.12)
set(QT_MIN_VERSION "5.2.0")

include(FindPkgConfig)
if(NOT PKG_CONFIG_FOUND)
  message(FATAL_ERROR "pkg-config not found!" )
endif()

find_package(ECM 1.0.0 REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(FeatureSummary)
include(WriteBasicConfigVersionFile)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)

pkg_check_modules(taglib REQUIRED IMPORTED_TARGET taglib)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Gui)
find_package(KF5 REQUIRED COMPONENTS KIO)

set(mp4coverthumbnail_SRCS mp4coverthumbnailer.cpp)

add_library(mp4coverthumbnail MODULE ${mp4coverthumbnail_SRCS})
target_link_libraries(mp4coverthumbnail KF5::KIOWidgets PkgConfig::taglib)

install(TARGETS mp4coverthumbnail DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES mp4coverthumbnail.desktop DESTINATION ${SERVICES_INSTALL_DIR})
