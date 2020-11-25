#include "type_list.h"

namespace TL {
	/* Get index of first ocurrence of class in TypeList */

	template<class type_list, typename T>
	struct IndexOf {
		constexpr static int value = 1 + IndexOf<typename type_list::Tail, T>::value;
	};

	template<class type_list>
	struct IndexOf<type_list, typename type_list::Head> {
		constexpr static int value = 0;
	};

	template<typename T>
	struct IndexOf<EmptyTypeList, T> {
		constexpr static int value = INT32_MIN;
	};
}