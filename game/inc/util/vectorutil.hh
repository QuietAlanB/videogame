#ifndef VECTORUTIL_HH__
#define VECTORUTIL_HH__

#include <vector>
#include <optional>
#include <algorithm>

template<typename T, typename F>
static std::optional<T> get_if_exists(std::vector<T> &v, F const &cmp) {
	for (T &i : v)
		if (cmp(i))
			return std::make_optional(i);
	
	return std::nullopt;
}

template<typename T, typename F>
static std::vector<T> get_all(std::vector<T> &v, F const &cmp) {
	std::vector<T> mat;

	for (T &i : v)
		if (cmp(i))
			mat.push_back(i);

	return mat;
}

template<typename T, typename F>
static void rm_all_by_cmp(std::vector<T> &v, F const &cmp) {
	v.erase(std::remove_if(v.begin(), v.end(), cmp), v.end());
}

template<typename T>
static void rm_by_ptr_cmp(std::vector<std::shared_ptr<T>> &v, T const *ptr) {
	auto cmp = [&](std::shared_ptr<T> const &other_ptr) {
		return ptr == other_ptr.get();
	};

	rm_all_by_cmp(v, cmp);
}

#endif
