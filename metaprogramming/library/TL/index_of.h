#pragma once

#include <cstdint>

#include "is_type_list.h"

#include "type_list.h"

namespace TL {
	/**
	 Gets index of a first ocurrence of typename T in type_list
	 @param type_list Template parameter
	 @param T Template parameter
	 @returns Parameter value, index of a first ocurrence of typename T in type_list, INT32_MIN otherwise
	 */
	template<class type_list, typename T>
	struct IndexOf {
		static_assert(IsTypeList<type_list>::value, "First passed parameter must be a TypeList");
		constexpr static int value = 1 + IndexOf<typename type_list::Tail, T>::value;
	};

	/**
	 * @see IndexOf
	 */
	template<class type_list>
	struct IndexOf<type_list, typename type_list::Head> {
		static_assert(IsTypeList<type_list>::value, "First passed parameter must be a TypeList");
		constexpr static int value = 0;
	};

	/**
	 * @see IndexOf
	 */
	template<typename T>
	struct IndexOf<EmptyTypeList, T> {
		constexpr static int value = INT32_MIN;
	};
}