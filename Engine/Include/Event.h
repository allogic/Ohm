#pragma once

namespace Ohm {
	enum class TEventCategory : unsigned int {
		None = 0,
		WindowEvent,
		MouseEvent,
		KeyEvent,
	};

	enum class TEventType : unsigned int {
		None = 0,
		WindowResize,
		WindowClose,
		MousePressed,
		MouseHeld,
		MouseReleased,
		KeyPressed,
		KeyHeld,
		KeyReleased,
	};

	struct SEvent {
		TEventCategory category = TEventCategory::None;
		TEventType type = TEventType::None;
	};

	class CEventDispatcher final {
	public:
		CEventDispatcher(const SEvent& event) : mEvent(event) {}
		CEventDispatcher(const CEventDispatcher&) = delete;
		CEventDispatcher(CEventDispatcher&&) = delete;

	public:
		auto& operator =(const CEventDispatcher&) = delete;

	public:
		template<typename TEventType, typename TEventClbFuncPtr>
		bool Dispatch(const TEventClbFuncPtr func) {
			if (mEvent.type == TEventType::GetStaticType()) {
				func(static_cast<TEventType>(mEvent));

				return true;
			}

			return false;
		}

	private:
		SEvent mEvent;
	};
}