// Author: Jake Rieger
// Created: 8/2/2024.
//

#include "Canvas.h"

namespace XenUI {
    Canvas::Canvas(HWND window) {
        ThrowIfFailed(
          D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, IID_PPV_ARGS(&m_pFactory)));

        RECT rc;
        ::GetClientRect(window, &rc);
        ThrowIfFailed(m_pFactory->CreateHwndRenderTarget(
          D2D1::RenderTargetProperties(),
          D2D1::HwndRenderTargetProperties(window, D2D1::SizeU(rc.right, rc.bottom)),
          &m_pRenderTarget));
    }

    Canvas::~Canvas() {
        if (m_pRenderTarget) {
            m_pRenderTarget.Reset();
        }

        if (m_pFactory) {
            m_pFactory.Reset();
        }
    }

    void Canvas::Draw(IWidget* root) const {
        const auto rt = m_pRenderTarget.Get();
        if (rt) {
            rt->BeginDraw();
            rt->Clear(D2D1::ColorF(D2D1::ColorF::Black));

            // Render widget tree

            ThrowIfFailed(rt->EndDraw());
        }
    }
}  // namespace XenUI