#pragma once

#include <memory>

#include <hawtk/renderer.hpp>

namespace hawtk {
	class context final {
		template <typename T, typename... Args>
		friend context make_context(Args&&...);

	private:
		template <typename T>
		struct type {};

		std::unique_ptr<renderer> _renderer;

		template <typename T, typename... Args>
		context(const type<T>&, Args&&... args) {
			_renderer = std::make_unique<T>(std::forward<Args>(args)...);
		}

	public:
		void draw();
		void update();
	};

	template <typename T, typename... Args>
	context make_context(Args&&... args) {
		return context(context::type<T>{}, std::forward<Args>(args)...);
	}
}
