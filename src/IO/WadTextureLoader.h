/*
 Copyright (C) 2010-2013 Kristian Duske
 
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

#ifndef __TrenchBroom__WadTextureLoader__
#define __TrenchBroom__WadTextureLoader__

#include "IO/TextureLoader.h"
#include "Model/Palette.h"
#include "Model/TextureCollection.h"

namespace TrenchBroom {
    namespace IO {
        struct MipData;
        class Path;
        
        class WadTextureLoader : public TextureLoader {
        private:
            const Model::Palette& m_palette;
        public:
            WadTextureLoader(const Model::Palette& palette);
        private:
            static const size_t InitialBufferSize = 3 * 512 * 512;
            
            Model::TextureCollection::Ptr doLoadTextureCollection(const Path& path);
            void doUploadTextureCollection(Model::TextureCollection::Ptr collection);
        };
    }
}

#endif /* defined(__TrenchBroom__WadTextureLoader__) */