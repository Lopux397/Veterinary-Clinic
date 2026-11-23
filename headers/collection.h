#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <ranges>

#include"../exception/outOfRangeException.h"


template<typename T>
class Collection 
{
private:
	std::vector<T> items;
public:
	void add(const T& item) 
	{
		items.push_back(item);
	}

	template<typename Condition>
	bool removeIf(Condition con) 
	{
		auto it = std::ranges::find_if(items, con);

		if (it == items.end())
			return false;

		items.erase(it);
		return true;
	}

	template<typename Condition>
	T* findIf(Condition con) 
	{
		auto it = std::ranges::find_if(items, con);

		if (it == items.end())
			return nullptr;
		return &(*it);
	}

	T& operator[](std::size_t index)
	{
		if (index >= items.size() || index < 0)
			throw OutOfRangeException("Going beyond the bounds of a collection");
		return	items[index];
	}

	const T& operator[](std::size_t index) const
	{
		if (index >= items.size() || index < 0)
			throw OutOfRangeException("Going beyond the bounds of a collection");
		return items[index];
	}

	auto begin() 
	{
		return items.begin();
	}
	auto end() 
	{
		return items.end();
	}

	auto begin() const
	{
		return items.begin();
	}
	auto end() const
	{
		return items.end();
	}

	std::size_t size() const 
	{
		return items.size();
	}

	bool empty() const
	{
		return items.empty();
	}

	void clear() 
	{
		items.clear();
	}

	void print(std::ostream& os) const
	{
		for (const auto& item : items)
			os << item << std::endl;
		os.flush(); //принудительно сбрасывает буфер потока на вывод
	}
};