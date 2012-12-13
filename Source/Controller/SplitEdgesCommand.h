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

#ifndef __TrenchBroom__SplitEdgesCommand__
#define __TrenchBroom__SplitEdgesCommand__

#include "Controller/SnapshotCommand.h"
#include "Model/BrushGeometryTypes.h"
#include "Model/BrushTypes.h"
#include "Utility/VecMath.h"

#include <map>

using namespace TrenchBroom::Math;

namespace TrenchBroom {
    namespace Controller {
        class SplitEdgesCommand : public SnapshotCommand {
        protected:
            Model::EdgeList m_edges;
            Model::BrushList m_brushes;
            Vec3f::Set m_vertices;
            Vec3f m_delta;
            
            bool performDo();
            bool performUndo();

            SplitEdgesCommand(Model::MapDocument& document, const wxString& name, const Model::EdgeList& edges, const Vec3f& delta);
        public:
            static SplitEdgesCommand* splitEdges(Model::MapDocument& document, const Model::EdgeList& edges, const Vec3f& delta);
            
            inline const Model::BrushList& brushes() const {
                return m_brushes;
            }
            
            inline const Vec3f::Set& vertices() const {
                return m_vertices;
            }
        };
    }
}

#endif /* defined(__TrenchBroom__SplitEdgesCommand__) */
