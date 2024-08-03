// Author: Jake Rieger
// Created: 8/2/2024.
//

#pragma once
#include <d2d1.h>
#include <optional>
#include <vector>

namespace XenUI {
    class IWidget {
    public:
        virtual ~IWidget();
        virtual void Draw(ID2D1RenderTarget* context) = 0;

        void AddChild(IWidget* component) {
            m_Children.push_back(component);
        }

        std::optional<std::vector<IWidget*>> GetChildren() {
            if (m_Children.empty()) {
                return std::nullopt;
            }

            return m_Children;
        }

    protected:
        std::vector<IWidget*> m_Children;
    };
}  // namespace XenUI
