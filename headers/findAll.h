#pragma once
#include "../headers/collection.h"

template<typename T, typename Condition>
std::vector<T> findAll(const Collection<T>& c, Condition con) 
{
	std::vector<T> result;

	for (const auto& it : c) 
		if (con(it))
			result.push_back(it);

	return result;
}