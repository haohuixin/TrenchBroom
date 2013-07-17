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

#ifndef TrenchBroom_CommandListener_h
#define TrenchBroom_CommandListener_h

#include "Controller/Command.h"

#include <vector>

namespace TrenchBroom {
    namespace Controller {
        class CommandListener {
        public:
            typedef CommandListener* Ptr;
            typedef std::vector<Ptr> List;
            
            virtual void commandDo(Command::Ptr command) = 0;
            virtual void commandDone(Command::Ptr command) = 0;
            virtual void commandDoFailed(Command::Ptr command) = 0;
            virtual void commandUndo(Command::Ptr command) = 0;
            virtual void commandUndone(Command::Ptr command) = 0;
            virtual void commandUndoFailed(Command::Ptr command) = 0;
        };
    }
}

#endif