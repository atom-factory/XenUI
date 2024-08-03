// Author: Jake Rieger
// Created: 8/2/2024.
//

#pragma once

#include "Context.h"
#include "Dimension.h"
#include "Rectangle.h"

#include <optional>
#include <vector>

namespace XenUI {
    class IWidget {
    public:
        IWidget(const Offset& position, const Size<f32>& size)
            : m_Position(position), m_Size(size) {}
        virtual ~IWidget();
        virtual void Draw(Context* context, const Dimension& dim) = 0;

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
        Offset m_Position;
        Size<f32> m_Size;

        [[nodiscard]] Rectangle GetRect() const {
            return Rectangle::FromCenter(m_Position, m_Size.Width, m_Size.Height);
        }
    };
}  // namespace XenUI
