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

#ifndef TrenchBroom_MapGui_h
#define TrenchBroom_MapGui_h

#include "Gwen/Skins/Simple.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/Renderers/OpenGL_DebugFont.h"
#include "Gwen/Controls/Canvas.h"
#include "Gwen/Controls/TabControl.h"
#include "MapRendererControl.h"
#include "Splitter.h"
#include "Editor.h"
#include "FontManager.h"

using namespace std;

namespace TrenchBroom {
    
    namespace Gui {
        class EditorGui {
        private:
            Controller::Editor& m_editor;
            Gwen::Renderer::OpenGL* m_renderer;
            Gwen::Skin::TexturedBase* m_skin;
            Gwen::Controls::Canvas* m_canvas;
            Splitter* m_splitter;
            MapRendererControl* m_mapRenderer;
            Gwen::Controls::TabControl* m_inspectorTab;
        public:
            EditorGui(Controller::Editor& editor, Renderer::FontManager& fontManager, const string& skinPath);
            ~EditorGui();
            
            void resizeTo(int width, int height);
            void render();
            
            Gwen::Controls::Canvas* canvas();
        };
    }
}

#endif