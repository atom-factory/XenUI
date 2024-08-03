// Author: Jake Rieger
// Created: 8/2/2024.
//

#include "Widget.h"

namespace XenUI {
    IWidget::~IWidget() {
        for (const auto child : m_Children) {
            delete child;
        }
    }
}  // namespace XenUI