/*
 Copyright (C) 2010-2012 Kristian Duske
 
 This file is part of TrenchBroom.
 
 TrenchBroom is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 TrenchBroom is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with TrenchBroom.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TrenchBroom__Palette__
#define __TrenchBroom__Palette__

#include "Color.h"
#include "StringUtils.h"
#include "ByteBuffer.h"
#include "IO/Path.h"

#include <cassert>

namespace TrenchBroom {
    namespace Assets {
        class Palette {
        private:
            char* m_data;
            size_t m_size;
        public:
            Palette(const IO::Path& path);
            Palette(const Palette& other);
            ~Palette();
            
            void operator= (Palette other);
            
            void indexedToRgb(const Buffer<char>& indexedImage, const size_t pixelCount, Buffer<unsigned char>& rgbImage, Color& averageColor) const;
            void indexedToRgb(const char* indexedImage, const size_t pixelCount, Buffer<unsigned char>& rgbImage, Color& averageColor) const;
        };
    }
}

#endif /* defined(__TrenchBroom__Palette__) */