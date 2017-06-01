#pragma once

#include <memory>
#include <vector>

#include <hawtk/vec.hpp>

namespace hawtk {
	class context;

	class widget {
		friend class context;

	protected:
		using widget_pointer = std::shared_ptr<widget>;
		bool _dirty = true;
		vec2 _bounds;
		std::vector<widget_pointer> _children;

	public:
		using size_type = std::vector<widget_pointer>::size_type;
		using iterator = std::vector<widget_pointer>::iterator;
		using const_iterator = std::vector<widget_pointer>::const_iterator;
		widget() = default;
		explicit widget(const vec2& bounds) noexcept : _bounds{bounds} {}
		virtual ~widget() = default;

		auto& at(size_type pos) {
			return _children.at(pos);
		}

		auto& at(size_type pos) const {
			return _children.at(pos);
		}

		auto& operator[](size_type pos) {
			return _children[pos];
		}

		auto& operator[](size_type pos) const {
			return _children[pos];
		}

		auto& front() {
			return _children.front();
		}

		auto& front() const {
			return _children.front();
		}

		auto& back() {
			return _children.back();
		}

		auto& back() const {
			return _children.back();
		}

		auto size() const noexcept {
			return _children.size();
		}

		auto begin() noexcept {
			return _children.begin();
		}

		auto begin() const noexcept {
			return _children.begin();
		}

		auto end() noexcept {
			return _children.end();
		}

		auto end() const noexcept {
			return _children.end();
		}

		void clear() {
			_children.clear();
		}

		void insert(iterator pos, const widget_pointer& widget) {
			_children.insert(pos, widget);
		}

		auto erase(iterator pos) {
			return _children.erase(pos);
		}

		auto erase(const_iterator pos) {
			return _children.erase(pos);
		}

		auto erase(iterator first, iterator last) {
			return _children.erase(first, last);
		}

		auto erase(const_iterator first, const_iterator last) {
			return _children.erase(first, last);
		}

		void push_back(const widget_pointer& widget) {
			_children.push_back(widget);
		}

		template <typename T, typename... Args>
		T& emplace_back(Args&&... args) {
			_children.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
			return _children.back();
		}

	private:
		virtual void draw(context& context) = 0;
	};
}
