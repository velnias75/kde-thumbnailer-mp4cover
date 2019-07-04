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

#include "mp4coverthumbnailer.h"
#include "mp4coverthumbnailsettings5.h"

#include <taglib/mp4file.h>

#include <QtGui/QImage>
#include <QtWidgets/QCheckBox>

#include <KLocalizedString>

extern "C" {
    Q_DECL_EXPORT ThumbCreator *new_creator() {
        return new MP4CoverThumbnailer();
    }
}

MP4CoverThumbnailer::MP4CoverThumbnailer() {

    MP4CoverThumbnailerSettings *settings =
        MP4CoverThumbnailerSettings::self();

    if(settings->filmstrip()) {
        m_Thumbnailer.addFilter(&m_FilmStrip);
    }
}

MP4CoverThumbnailer::~MP4CoverThumbnailer() {}

bool MP4CoverThumbnailer::create(const QString &path, int width, int,
                                 QImage &img) {

    TagLib::MP4::File f(path.toStdString().c_str(), false);

    if(f.isValid()) {

        TagLib::MP4::Tag* tag = f.tag();
        TagLib::MP4::ItemListMap itemsListMap = tag->itemListMap();
        TagLib::MP4::Item coverItem = itemsListMap["covr"];
        TagLib::MP4::CoverArtList coverArtList = coverItem.toCoverArtList();

        if(!coverArtList.isEmpty()) {
            TagLib::MP4::CoverArt coverArt = coverArtList.front();
            img.loadFromData((const uchar *)coverArt.data().data(),
                         coverArt.data().size());

            if(!img.isNull()) return true;
        }
    }

    m_Thumbnailer.setThumbnailSize(width);
    m_Thumbnailer.setSeekPercentage(20);
    m_Thumbnailer.generateThumbnail(path, img);

    return !img.isNull();
}

QWidget *MP4CoverThumbnailer::createConfigurationWidget() {

    QCheckBox *filmstripCheckBox =
        new QCheckBox(i18nc("@option:check", "Embed filmstrip effect"));

    filmstripCheckBox->setChecked(MP4CoverThumbnailerSettings::filmstrip());

    return filmstripCheckBox;
}

void
MP4CoverThumbnailer::writeConfiguration(const QWidget *configurationWidget) {

    const QCheckBox *filmstripCheckBox =
        qobject_cast<const QCheckBox *>(configurationWidget);

    if(filmstripCheckBox) {

        MP4CoverThumbnailerSettings *settings =
        MP4CoverThumbnailerSettings::self();

        settings->setFilmstrip(filmstripCheckBox->isChecked());
        settings->save();
    }
}

ThumbCreator::Flags MP4CoverThumbnailer::flags() const {
    return ThumbCreator::BlendIcon;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; remove-trailing-space on;
