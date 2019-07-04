kde-thumbnailer-mp4cover
========================

A KDE thumbnail generator for embedded MP4 video cover art.

Requirements
------------------------

    * taglib
    * FFMpeg

Installation from source (KF5)
------------------------

    mkdir build
    cd build
    cmake -DKDE_INSTALL_USE_QT_SYS_PATHS=ON -DCMAKE_INSTALL_PREFIX=`kf5-config --prefix` ..
    make
    sudo make install
    kbuildsycoca5
