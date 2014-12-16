/*
 Copyright (C) 2010-2014 Kristian Duske
 
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
 along with TrenchBroom. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TrenchBroom__CyclingMapView__
#define __TrenchBroom__CyclingMapView__

#include "TrenchBroom.h"
#include "VecMath.h"
#include "View/MapViewContainer.h"
#include "View/ViewTypes.h"

#include <wx/panel.h>

#include <vector>

namespace TrenchBroom {
    class Logger;
    
    namespace Renderer {
        class MapRenderer;
    }
    
    namespace View {
        class GLContextManager;
        class MapViewBase;
        class MapViewToolBox;
        
        class CyclingMapView : public MapViewContainer {
        public:
            typedef enum {
                View_3D  = 1,
                View_XY  = 2,
                View_XZ  = 4,
                View_YZ  = 8,
                View_ZZ  = View_XZ | View_YZ,
                View_2D  = View_XY | View_ZZ,
                View_ALL = View_3D | View_2D
            } View;
        private:
            Logger* m_logger;
            MapDocumentWPtr m_document;
            
            typedef std::vector<MapViewBase*> MapViewList;
            MapViewList m_mapViews;
            MapViewBase* m_currentMapView;
        public:
            CyclingMapView(wxWindow* parent, Logger* logger, MapDocumentWPtr document, MapViewToolBox& toolBox, Renderer::MapRenderer& mapRenderer, GLContextManager& contextManager, View views);
        private:
            void createGui(MapViewToolBox& toolBox, Renderer::MapRenderer& mapRenderer, GLContextManager& contextManager, View views);
        private:
            void bindEvents();
            void OnCycleMapView(wxCommandEvent& event);
        private:
            void switchToMapView(MapViewBase* mapView);
        private: // implement MapViewContainer interface
            void doSetToolBoxDropTarget();
            void doClearDropTarget();
        private: // implement MapView interface
            Vec3 doGetPasteObjectsDelta(const BBox3& bounds) const;
            
            void doCenterCameraOnSelection();
            void doMoveCameraToPosition(const Vec3& position);
            
            void doMoveCameraToCurrentTracePoint();
        };
    }
}

#endif /* defined(__TrenchBroom__CyclingMapView__) */