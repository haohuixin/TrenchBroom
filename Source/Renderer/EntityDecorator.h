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

#ifndef TrenchBroom_EntityDecorator_h
#define TrenchBroom_EntityDecorator_h

#include <vector>

namespace TrenchBroom {
    namespace Model {
        class MapDocument;
    }
    
    namespace Renderer {
        class RenderContext;
        class Vbo;
        
        class EntityDecorator {
        private:
            const Model::MapDocument& m_document;
        protected:
            inline const Model::MapDocument& document() const {
                return m_document;
            }
        public:
            typedef std::vector<EntityDecorator*> List;
            
            EntityDecorator(const Model::MapDocument& document) : m_document(document) {}
            virtual ~EntityDecorator() {}

            virtual void invalidate() = 0;
            virtual void render(Vbo& vbo, RenderContext& context) = 0;
        };
    }
}

#endif
