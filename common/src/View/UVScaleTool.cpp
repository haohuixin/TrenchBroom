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

#include "UVScaleTool.h"
#include "Assets/Texture.h"
#include "Model/BrushFace.h"
#include "Model/BrushVertex.h"
#include "Model/ChangeBrushFaceAttributesRequest.h"
#include "Model/ModelTypes.h"
#include "Renderer/Renderable.h"
#include "Renderer/RenderBatch.h"
#include "Renderer/EdgeRenderer.h"
#include "Renderer/RenderContext.h"
#include "Renderer/VertexSpec.h"
#include "View/MapDocument.h"
#include "View/InputState.h"
#include "View/UVViewHelper.h"
#include "View/UVOriginTool.h"

namespace TrenchBroom {
    namespace View {
        const Hit::HitType UVScaleTool::XHandleHit = Hit::freeHitType();
        const Hit::HitType UVScaleTool::YHandleHit = Hit::freeHitType();
        
        UVScaleTool::UVScaleTool(MapDocumentWPtr document, UVViewHelper& helper) :
        ToolImpl(document),
        m_helper(helper) {}

        void UVScaleTool::doPick(const InputState& inputState, Hits& hits) {
            static const Hit::HitType HitTypes[] = { XHandleHit, YHandleHit };
            if (m_helper.valid())
                m_helper.pickTextureGrid(inputState.pickRay(), HitTypes, hits);
        }

        Vec2i UVScaleTool::getScaleHandle(const Hit& xHit, const Hit& yHit) const {
            const int x = xHit.isMatch() ? xHit.target<int>() : 0;
            const int y = yHit.isMatch() ? yHit.target<int>() : 0;
            return Vec2i(x, y);
        }
        
        Vec2f UVScaleTool::getHitPoint(const Ray3& pickRay) const {
            const Model::BrushFace* face = m_helper.face();
            const Plane3& boundary = face->boundary();
            const FloatType facePointDist = boundary.intersectWithRay(pickRay);
            const Vec3 facePoint = pickRay.pointAtDistance(facePointDist);
            
            const Mat4x4 toTex = face->toTexCoordSystemMatrix(Vec2f::Null, Vec2f::One, true);
            return toTex * facePoint;
        }

        bool UVScaleTool::doStartMouseDrag(const InputState& inputState) {
            assert(m_helper.valid());
            
            if (!inputState.modifierKeysPressed(ModifierKeys::MKNone) ||
                !inputState.mouseButtonsPressed(MouseButtons::MBLeft))
                return false;
            
            const Hits& hits = inputState.hits();
            const Hit& xHit = hits.findFirst(XHandleHit, true);
            const Hit& yHit = hits.findFirst(YHandleHit, true);
            
            if (!xHit.isMatch() && !yHit.isMatch())
                return false;
            
            m_handle = getScaleHandle(xHit, yHit);
            m_selector = Vec2b(xHit.isMatch(), yHit.isMatch());
            m_lastHitPoint = getHitPoint(inputState.pickRay());
            
            document()->beginTransaction("Scale Texture");
            return true;
        }
        
        bool UVScaleTool::doMouseDrag(const InputState& inputState) {
            const Vec2f curPoint = getHitPoint(inputState.pickRay());
            const Vec2f dragDeltaFaceCoords = curPoint - m_lastHitPoint;
            
            const Vec2f curHandlePosTexCoords  = getScaledTranslatedHandlePos();
            const Vec2f newHandlePosFaceCoords = getHandlePos() + dragDeltaFaceCoords;
            const Vec2f newHandlePosSnapped    = snap(newHandlePosFaceCoords);
            
            const Vec2f originHandlePosFaceCoords = m_helper.originInFaceCoords();
            const Vec2f originHandlePosTexCoords  = m_helper.originInTexCoords();
            
            const Vec2f newHandleDistFaceCoords = newHandlePosSnapped    - originHandlePosFaceCoords;
            const Vec2f curHandleDistTexCoords  = curHandlePosTexCoords  - originHandlePosTexCoords;
            
            Model::BrushFace* face = m_helper.face();
            Vec2f newScale = face->scale();
            for (size_t i = 0; i < 2; ++i)
                if (m_selector[i])
                    newScale[i] = newHandleDistFaceCoords[i] / curHandleDistTexCoords[i];
            newScale.correct(4, 0.0f);

            Model::ChangeBrushFaceAttributesRequest request;
            request.setScale(newScale);
            
            document()->setFaceAttributes(request);
            
            const Vec2f newOriginInTexCoords = m_helper.originInTexCoords().corrected(4, 0.0f);
            const Vec2f originDelta = originHandlePosTexCoords - newOriginInTexCoords;
            
            request.clear();
            request.addOffset(originDelta);
            document()->setFaceAttributes(request);
            
            m_lastHitPoint += (dragDeltaFaceCoords - newHandlePosFaceCoords + newHandlePosSnapped);
            return true;
        }
        
        void UVScaleTool::doEndMouseDrag(const InputState& inputState) {
            document()->endTransaction();
        }
        
        void UVScaleTool::doCancelMouseDrag() {
            document()->rollbackTransaction();
            document()->endTransaction();
        }

        Vec2f UVScaleTool::getScaledTranslatedHandlePos() const {
            return Vec2f(m_handle * m_helper.stripeSize());
        }

        Vec2f UVScaleTool::getHandlePos() const {
            const Model::BrushFace* face = m_helper.face();
            const Mat4x4 toWorld = face->fromTexCoordSystemMatrix(face->offset(), face->scale(), true);
            const Mat4x4 toTex   = face->toTexCoordSystemMatrix(Vec2f::Null, Vec2f::One, true);
            
            return Vec2f(toTex * toWorld * Vec3(getScaledTranslatedHandlePos()));
        }

        Vec2f UVScaleTool::snap(const Vec2f& position) const {
            const Model::BrushFace* face = m_helper.face();
            const Mat4x4 toTex = face->toTexCoordSystemMatrix(Vec2f::Null, Vec2f::One, true);
            
            Vec2f distance = Vec2f::Max;
            
            const Model::BrushVertexList& vertices = face->vertices();
            for (size_t i = 0; i < vertices.size(); ++i) {
                const Vec2f vertex(toTex * vertices[i]->position);
                distance = absMin(distance, position - vertex);
            }
            
            for (size_t i = 0; i < 2; ++i) {
                if (Math::abs(distance[i]) > 4.0f / m_helper.cameraZoom())
                    distance[i] = 0.0f;
            }
            return position - distance;
        }
        
        class UVScaleTool::Render : public Renderer::Renderable {
        private:
            void doPrepare(Renderer::Vbo& vbo) {
            }
            
            void doRender(Renderer::RenderContext& renderContext) {
            }
        };
        
        void UVScaleTool::doRender(const InputState& inputState, Renderer::RenderContext& renderContext, Renderer::RenderBatch& renderBatch) {
            if (!m_helper.valid())
                return;
            
            // don't overdraw the origin handles
            const Hits& hits = inputState.hits();
            if (hits.findFirst(UVOriginTool::XHandleHit, true).isMatch() ||
                hits.findFirst(UVOriginTool::YHandleHit, true).isMatch())
                return;
                
            EdgeVertex::List vertices = getHandleVertices(hits);
            const Color color(1.0f, 1.0f, 0.0f);
            
            Renderer::EdgeRenderer edgeRenderer(Renderer::VertexArray::swap(GL_LINES, vertices));
            Renderer::RenderEdges* renderEdges = new Renderer::RenderOccludedEdges(edgeRenderer, true, color);
            renderEdges->setWidth(2.0f);
            
            renderBatch.addOneShot(renderEdges);
        }

        UVScaleTool::EdgeVertex::List UVScaleTool::getHandleVertices(const Hits& hits) const {
            const Hit& xHandleHit = hits.findFirst(XHandleHit, true);
            const Hit& yHandleHit = hits.findFirst(YHandleHit, true);
            const Vec2 stripeSize = m_helper.stripeSize();

            const int xIndex = xHandleHit.target<int>();
            const int yIndex = yHandleHit.target<int>();
            const Vec2 pos = stripeSize * Vec2(xIndex, yIndex);

            Vec3 h1, h2, v1, v2;
            m_helper.computeScaleHandleVertices(pos, v1, v2, h1, h2);

            EdgeVertex::List vertices;
            vertices.reserve(4);
            
            if (xHandleHit.isMatch()) {
                vertices.push_back(EdgeVertex(Vec3f(v1)));
                vertices.push_back(EdgeVertex(Vec3f(v2)));
            }
            
            if (yHandleHit.isMatch()) {
                vertices.push_back(EdgeVertex(Vec3f(h1)));
                vertices.push_back(EdgeVertex(Vec3f(h2)));
            }
            
            return vertices;
        }
    }
}