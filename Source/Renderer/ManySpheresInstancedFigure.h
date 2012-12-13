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

#ifndef __TrenchBroom__ManySpheresInstancedFigure__
#define __TrenchBroom__ManySpheresInstancedFigure__

#include "Renderer/SphereFigure.h"
#include "Renderer/RenderTypes.h"
#include "Utility/VecMath.h"

using namespace TrenchBroom::Math;

namespace TrenchBroom {
    namespace Renderer {
        class Vbo;
        
        class ManySpheresInstancedFigure : public SphereFigure {
        protected:
            Vec3f::List m_positions;
            InstancedVertexArrayPtr m_vertexArray;
            bool m_valid;
            Color m_color;
        public:
            ManySpheresInstancedFigure(float radius, unsigned int iterations);

            inline const Color& color() const {
                return m_color;
            }
            
            inline void setColor(const Color& color) {
                m_color = color;
            }
            
            void add(const Vec3f& position);
            void clear();

            void render(Vbo& vbo, RenderContext& context);
        };
    }
}

#endif /* defined(__TrenchBroom__ManySpheresInstancedFigure__) */
