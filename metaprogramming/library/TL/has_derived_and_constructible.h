#pragma once

#include <type_traits>

#include "type_list.h"

namespace TL {
	/**
	 * Checks if type_list contains derived and constructible child of T
	 * @param type_list Template parameter
	 * @param T Template parameter
	 * @returns Parameter result, true if type_list ccontains derived and constructible child of T, false otherwise
	 */
	template<class type_list, typename T>
	struct HasDerivedAndConstructible;
}

template<class type_list, typename T, bool is_head_parent_of_T>
struct CheckHasDerivedAndConstructible {};

template<class type_list, typename T>
struct CheckHasDerivedAndConstructible<type_list, T, true> {
	constexpr static bool result = true;
};

template<class type_list, typename T>
struct CheckHasDerivedAndConstructible<type_list, T, false> {
	constexpr static bool result = TL::HasDerivedAndConstructible<typename type_list::Tail, T>::result;
};

namespace TL {
	template<class type_list, typename T>
	struct HasDerivedAndConstructible {
		constexpr static bool result = CheckHasDerivedAndConstructible<
			type_list,
			T,
			std::is_base_of<T, typename type_list::Head>::value&&
			std::is_constructible<typename type_list::Head>::value
		>::result;
	};

	/**
	 * @see HasDerivedAndConstructible
	 */
	template<typename T>
	struct HasDerivedAndConstructible<EmptyTypeList, T> {
		constexpr static bool result = false;
	};
};