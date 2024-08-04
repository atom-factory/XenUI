// Author: Jake Rieger
// Created: 8/4/2024.
//

#pragma once

namespace XenUI {
    class IInteractive {
    public:
        virtual ~IInteractive() = default;

        virtual void OnPressed() {};
        virtual void OnReleased() {};
        virtual void OnEnter() {};
        virtual void OnExit() {};
    };
}  // namespace XenUI