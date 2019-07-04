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
include(KDECompilerSettings NO_POLICY_SCOPE)

pkg_check_modules(taglib REQUIRED IMPORTED_TARGET taglib)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Gui)
find_package(KF5 REQUIRED COMPONENTS KIO I18n Config)
find_package(FFmpeg COMPONENTS AVCODEC AVFILTER AVFORMAT SWSCALE)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PC_AVCODEC_INCLUDEDIR}
    ${PC_AVFORMAT_INCLUDEDIR}
    ${FFMPEG_INCLUDE_DIR}
)

# Certain versions of FFMPEG need this to be defined
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D __STDC_CONSTANT_MACROS")

add_definitions(-DTRANSLATION_DOMAIN=\"mp4coverthumbnail\")

set(mp4coverthumbnail_SRCS 
    mp4coverthumbnailer.cpp
    ffmpegthumbnailer/filmstripfilter.cpp
    ffmpegthumbnailer/moviedecoder.cpp
    ffmpegthumbnailer/imagewriter.cpp
    ffmpegthumbnailer/videothumbnailer.cpp
)

kconfig_add_kcfg_files(mp4coverthumbnail_SRCS mp4coverthumbnailsettings5.kcfgc)
add_library(mp4coverthumbnail MODULE ${mp4coverthumbnail_SRCS})
target_link_libraries(mp4coverthumbnail 
    KF5::KIOWidgets 
    KF5::I18n 
    KF5::ConfigCore 
    KF5::ConfigGui 
    ${AVUTIL_LIBRARIES}
    ${AVFILTER_LIBRARIES}
    ${AVFORMAT_LIBRARIES}
    ${AVCODEC_LIBRARIES}
    ${SWSCALE_LIBRARIES}
    PkgConfig::taglib)

install(FILES mp4coverthumbnailsettings5.kcfg DESTINATION ${KCFG_INSTALL_DIR})
install(TARGETS mp4coverthumbnail DESTINATION ${PLUGIN_INSTALL_DIR})
install(FILES mp4coverthumbnail.desktop DESTINATION ${SERVICES_INSTALL_DIR})

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_CONTACT "Heiko Schäfer <heiko@rangun.de>")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TXZ")
set(CPACK_SOURCE_IGNORE_FILES
	  "/\\\\.kdev.*/"
	  "/\\\\.git/"
	  "/\\\\.gitattributes$"
	  "/\\\\.gitignore$"
	  "/\\\\build/"
	  "\\\\.kdev.$"
	  "\\\\.swp$"
	  "\\\\.#"
	  "/#"
	  "~$"
	  )

include(CPack)
