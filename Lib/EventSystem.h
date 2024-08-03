// Author: Jake Rieger
// Created: 8/2/2024.
//

#pragma once

#include <functional>
#include <map>
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace XenUI {
    class EventDispatcher;

    class IEvent {
    public:
        virtual ~IEvent() = default;
    };

    class IEventListener {
    public:
        virtual ~IEventListener()                 = default;
        virtual void OnEvent(const IEvent& event) = 0;
    };

    template<typename EventType>
    class SpecificEventListener final : public IEventListener {
    public:
        using Callback = std::function<void(const EventType&)>;
        explicit SpecificEventListener(Callback cb) : m_Callback(cb) {}

        void OnEvent(const IEvent& event) override {
            m_Callback(static_cast<const EventType&>(event));
        }

    private:
        Callback m_Callback;
    };

    class EventDispatcher {
    public:
        template<typename EventType>
        void RegisterListener(std::function<void(const EventType&)> callback) {
            const std::type_index typeIndex(typeid(EventType));
            m_Listeners[typeIndex].emplace_back(
              std::make_shared<SpecificEventListener<EventType>>(callback));
        }

        void Dispatch(const IEvent& event) {
            const std::type_index typeIndex(typeid(event));
            const auto it = m_Listeners.find(typeIndex);
            if (it != m_Listeners.end()) {
                for (const auto& listener : it->second) {
                    listener->OnEvent(event);
                }
            }
        }

    private:
        std::map<std::type_index, std::vector<std::shared_ptr<IEventListener>>> m_Listeners;
    };
}  // namespace XenUI
