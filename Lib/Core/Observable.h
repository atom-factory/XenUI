// Author: Jake Rieger
// Created: 8/4/2024.
//

#pragma once

namespace XenUI {
    class IObserver {
    public:
        virtual ~IObserver()  = default;
        virtual void Update() = 0;
    };

    class Observable {};
}  // namespace XenUI
