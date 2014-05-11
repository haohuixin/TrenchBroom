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

#ifndef __TrenchBroom__FaceInspector__
#define __TrenchBroom__FaceInspector__

#include "Controller/Command.h"
#include "View/GLContextHolder.h"
#include "View/ViewTypes.h"

#include <wx/panel.h>

class wxCollapsiblePaneEvent;
class wxSplitterWindow;
class wxWindow;

namespace TrenchBroom {
    namespace Model {
        class BrushFace;
        class Object;
        class SelectionResult;
    }
    
    namespace View {
        class FaceAttribsEditor;
        class TextureBrowser;
        class TextureCollectionEditor;
        class TextureSelectedCommand;
        
        class FaceInspector : public wxPanel {
        private:
            MapDocumentWPtr m_document;
            ControllerWPtr m_controller;
            
            wxSplitterWindow* m_splitter;
            FaceAttribsEditor* m_faceAttribsEditor;
            TextureBrowser* m_textureBrowser;
            TextureCollectionEditor* m_textureCollectionEditor;
        public:
            FaceInspector(wxWindow* parent, GLContextHolder::Ptr sharedContext, MapDocumentWPtr document, ControllerWPtr controller);

            void OnTextureSelected(TextureSelectedCommand& event);
            void OnTextureCollectionEditorPaneChanged(wxCollapsiblePaneEvent& event);
        private:
            void createGui(GLContextHolder::Ptr sharedContext);
            wxWindow* createFaceAttribsEditor(wxWindow* parent, GLContextHolder::Ptr sharedContext);
            wxWindow* createTexturePanel(wxWindow* parent, GLContextHolder::Ptr sharedContext);
            wxWindow* createTextureBrowser(wxWindow* parent, GLContextHolder::Ptr sharedContext);
            wxWindow* createTextureCollectionEditor(wxWindow* parent);
            
            void bindEvents();
        };
    }
}

#endif /* defined(__TrenchBroom__FaceInspector__) */
