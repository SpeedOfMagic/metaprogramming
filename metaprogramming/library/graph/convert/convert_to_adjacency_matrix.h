#pragma once

#include "../../TL/fill_type_list_with_object.h"
#include "../../TL/index_of.h"

#include "../class.h"
#include "../graphs/adjacency_matrix_graph.h"
#include "../objects.h"

/**
 * @see ConvertGraph
 */
template<class graph>
struct ConvertGraph<EDGE_LIST, ADJACENCY_MATRIX, graph> {
	static_assert(EDGE_LIST == graph::TYPE, "Type of a graph must be equal to passed argument");
	using vertexes = typename graph::vertexes_;
	
	template<class cur_edges>
	struct IterateThroughEdges {
		using cur_edge = typename cur_edges::Head;

		using from = typename cur_edge::from;
		using to = typename cur_edge::to;
		static_assert(TL::Contains<vertexes, from>::value, "Every vertex must be in graph");
		static_assert(TL::Contains<vertexes, to>::value, "Every vertex must be in graph");

		constexpr static size_t from_ind = TL::IndexOf<vertexes, typename cur_edge::from>::value;
		constexpr static size_t to_ind = TL::IndexOf<vertexes, typename cur_edge::to>::value;

		using new_weight = std::conditional_t<
			std::is_same_v<NullType, typename cur_edge::weight>,  // If weight is NullType
			Objects::Boolean<true>,  // Then it becomes Boolean<true>
			std::conditional_t<
				std::is_same_v<Objects::Boolean<false>, typename cur_edge::weight>,  // If weight is Boolean
				Class<Objects::Boolean<false>>,  // Then it's a Class<Boolean>
				std::conditional_t<
					std::is_same_v<Objects::Boolean<true>, typename cur_edge::weight>,
					Class<Objects::Boolean<true>>,
					typename cur_edge::weight
				>
			>
		>;

		using tail_result = typename IterateThroughEdges<typename cur_edges::Tail>::result;
		using result = typename TL::Replace<
			typename TL::Replace<
				new_weight,
				to_ind,
				typename TL::TypeAt<tail_result, from_ind>::value
			>::result,
			from_ind,
			tail_result
		>::result;
	};

	template<>
	struct IterateThroughEdges<EmptyTypeList> {
		using result = typename TL::FillTypeListWithObject<
			typename TL::FillTypeListWithObject<
				Objects::Boolean<false>,
				TL::Size<vertexes>::size
			>::result,
			TL::Size<vertexes>::size
		>::result;
	};

	using matrix = typename IterateThroughEdges<typename graph::edge_list_>::result;
	using result = AdjacencyMatrixGraph<vertexes, matrix>;
};
