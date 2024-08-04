// Author: Jake Rieger
// Created: 8/2/2024.
//

#include "Canvas.h"

#include "Events.h"

#include <queue>

namespace XenUI {
    Canvas::Canvas(const Window* window,
                   const std::shared_ptr<EventDispatcher>& dispatcher,
                   const Color& backgroundColor)
        : m_Size({0, 0}), m_BackgroundColor(backgroundColor), m_pDispatcher(dispatcher) {
        m_Context = std::make_unique<Context>(window->GetHandle());

        // Update our canvas size
        RECT rc;
        ::GetClientRect(window->GetHandle(), &rc);
        m_Size = {CAST<f32>(rc.right), CAST<f32>(rc.bottom)};

        // Register our event handlers with the app's event dispatcher
        dispatcher->RegisterListener<ResizeEvent>(
          [this](const ResizeEvent& event) { Resize(event.Width, event.Height); });

        // Since the canvas gets initialized *after the first WM_PAINT is called, we
        // manually trigger a redraw to capture the event in the canvas class. If not,
        // the window will stay blank until the next redraw is triggered via resizing
        // or rect invalidation.
        window->TriggerRedraw();
    }

    // TODO: See if anything actually needs to be cleaned up
    Canvas::~Canvas() = default;

    void Canvas::Draw(IWidget* root) const {
        const auto rt = m_Context->GetD2DRenderTarget();
        if (rt) {
            const auto dim = Dimension(m_Size);

            rt->BeginDraw();
            rt->Clear(m_BackgroundColor.GetD2DColor());

            // Render widget tree
            IWidget::TraverseTree(root,
                                  [&](IWidget* widget) { widget->Draw(m_Context.get(), dim); });

            ThrowIfFailed(rt->EndDraw());
        }
    }

    void Canvas::Resize(int width, int height) {
        m_Context->Resize(width, height);
        m_Size = {CAST<f32>(width), CAST<f32>(height)};
    }
}  // namespace XenUI