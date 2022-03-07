#pragma once

namespace glr {

	template<typename T>
	using Uniq = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Uniq<T> getUniq(Args&& ... args) { return std::make_unique<T>(std::forward<Args>(args)...); }

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> getRef(Args&& ... args) { return std::make_shared<T>(std::forward<Args>(args)...); }

}