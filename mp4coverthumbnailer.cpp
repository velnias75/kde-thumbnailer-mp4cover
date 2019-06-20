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

#include <QtGui/QImage>
#include <taglib/mp4file.h>

extern "C" {
    Q_DECL_EXPORT ThumbCreator *new_creator() {
        return new MP4CoverThumbnailer();
    }
}

bool MP4CoverThumbnailer::create(const QString &path, int, int, QImage &img) {

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
            return true;
        }
    }

    return false;
}

ThumbCreator::Flags MP4CoverThumbnailer::flags() const {
    return ThumbCreator::BlendIcon;
}

// kate: indent-mode cstyle; indent-width 4; replace-tabs on; remove-trailing-space on;
