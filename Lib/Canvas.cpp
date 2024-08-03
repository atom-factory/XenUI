// Author: Jake Rieger
// Created: 8/2/2024.
//

#include "Canvas.h"

#include "Events.h"

#include <queue>

namespace XenUI {
    Canvas::Canvas(const Window* window, const std::shared_ptr<EventDispatcher>& dispatcher)
        : m_pDispatcher(dispatcher) {
        ThrowIfFailed(
          D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, IID_PPV_ARGS(&m_pFactory)));

        RECT rc;
        ::GetClientRect(window->GetHandle(), &rc);
        ThrowIfFailed(m_pFactory->CreateHwndRenderTarget(
          D2D1::RenderTargetProperties(),
          D2D1::HwndRenderTargetProperties(window->GetHandle(), D2D1::SizeU(rc.right, rc.bottom)),
          &m_pRenderTarget));

        // Register our event handlers with the app's event dispatcher
        dispatcher->RegisterListener<ResizeEvent>(
          [this](const ResizeEvent& event) { Resize(event.Width, event.Height); });

        // Since the canvas gets initialized *after the first WM_PAINT is called, we
        // manually trigger a redraw to capture the event in the canvas class. If not,
        // the window will stay blank until the next redraw is triggered via resizing
        // or rect invalidation.
        window->TriggerRedraw();
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
            if (root) {
                std::queue<IWidget*> queue;
                queue.push(root);

                while (!queue.empty()) {
                    IWidget* widget = queue.front();
                    queue.pop();

                    widget->Draw(m_pRenderTarget.Get());

                    auto result = widget->GetChildren();
                    if (result.has_value()) {
                        auto children = result.value();
                        for (const auto& child : children) {
                            queue.push(child);
                        }
                    }
                }
            }

            ThrowIfFailed(rt->EndDraw());
        }
    }

    void Canvas::Resize(int width, int height) {
        if (m_pRenderTarget) {
            ThrowIfFailed(m_pRenderTarget->Resize(D2D1_SIZE_U(width, height)));
        }
    }
}  // namespace XenUI