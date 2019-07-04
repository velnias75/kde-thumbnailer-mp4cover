/*
This file is part of mp4coverthumbnailer
Copyright (C) 2019 Heiko Schäfer <heiko@rangun.de>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MP4COVERTHUMBNAILER_H
#define MP4COVERTHUMBNAILER_H

#include <QObject>
#include <kio/thumbcreator.h>

#include <ffmpegthumbnailer/videothumbnailer.h>
#include <ffmpegthumbnailer/filmstripfilter.h>

class MP4CoverThumbnailer : public QObject, public ThumbCreator {

    Q_OBJECT

    public:
        MP4CoverThumbnailer();
        virtual ~MP4CoverThumbnailer();

        QWidget *createConfigurationWidget() override;
        bool create(const QString& path, int width, int, QImage& img) override;
        virtual Flags flags() const override;
        virtual void writeConfiguration(const QWidget *configurationWidget)
        override;

    private:
        ffmpegthumbnailer::VideoThumbnailer m_Thumbnailer;
        ffmpegthumbnailer::FilmStripFilter m_FilmStrip;
};

#endif // MP4COVERTHUMBNAILER_H

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; remove-trailing-space on;
