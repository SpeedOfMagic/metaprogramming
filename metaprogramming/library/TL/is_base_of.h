#pragma once

#include <type_traits>

#include "contains_parent.h"
#include "type_list.h"

namespace TL {
	/**
	 * Checks if TypeList "parent" is in fact parent of another TypeList "derived"
	 * "parent" is parent of "derived" if and only if for every class C in "derived", "parent" has parent of C
	 * @param parent Template parameter
	 * @param derived Template parameter
	 * @returns true if TypeList "parent" is in fact parent of another TypeList "derived", false otherwise
	 */
	template<class parent, class derived>
	struct IsBaseOf;
}

template<bool has_parent, class parent, class derived>
struct CheckIsBaseOf {};

template<class parent, class derived>
struct CheckIsBaseOf<false, parent, derived> {
	constexpr static bool result = false;
};

template<class parent, class derived>
struct CheckIsBaseOf<true, parent, derived> {
	constexpr static bool result = TL::IsBaseOf<
		parent,
		typename derived::Tail
	>::result;
};

namespace TL {
	template<class parent, class derived>
	struct IsBaseOf {
		constexpr static bool result = CheckIsBaseOf<
			ContainsParent<parent, typename derived::Head>::result,
			parent,
			derived
		>::result;
	};

	template<class parent>
	struct IsBaseOf<parent, EmptyTypeList> {
		constexpr static bool result = true;
	};

	template<class derived>
	struct IsBaseOf<EmptyTypeList, derived> {
		constexpr static bool result = false;
	};

	template<>
	struct IsBaseOf<EmptyTypeList, EmptyTypeList> {
		constexpr static bool result = true;
	};
}