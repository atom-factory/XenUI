// Author: Jake Rieger
// Created: 8/2/2024.
//

#pragma once

#include "Context.h"
#include "Dimension.h"
#include "Rectangle.h"

#include <functional>
#include <optional>
#include <queue>
#include <vector>

namespace XenUI {
    class IWidget {
    public:
        IWidget(const Offset& position, const Size<f32>& size)
            : m_Position(position), m_Size(size) {}
        virtual ~IWidget();

        void AddChild(IWidget* component) {
            m_Children.push_back(component);
        }

        std::optional<std::vector<IWidget*>> GetChildren() {
            if (m_Children.empty()) {
                return std::nullopt;
            }

            return m_Children;
        }

        virtual void Draw(Context* context, const Dimension& dim) = 0;

        static void TraverseTree(IWidget* root, const std::function<void(IWidget*)>& callback) {
            if (root) {
                std::queue<IWidget*> queue;
                queue.push(root);

                while (!queue.empty()) {
                    IWidget* widget = queue.front();
                    queue.pop();

                    callback(widget);

                    auto result = widget->GetChildren();
                    if (result.has_value()) {
                        auto children = result.value();
                        for (const auto& child : children) {
                            queue.push(child);
                        }
                    }
                }
            }
        }

    protected:
        std::vector<IWidget*> m_Children;
        Offset m_Position;
        Size<f32> m_Size;

        [[nodiscard]] Rectangle GetRect() const {
            return Rectangle::FromCenter(m_Position, m_Size.Width, m_Size.Height);
        }

    private:
        bool m_Dirty = true;
    };
}  // namespace XenUI
