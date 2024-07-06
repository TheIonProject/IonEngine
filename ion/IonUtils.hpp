/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
                                __/ |
                               |___/


NAME: IonUtils.hpp

DESCTIPTION: Project-wide utility functions

AUTHOR: Noah de Pischof | @torrra on GitHub


*/


#ifndef __ION_UTILS_H__
#define __ION_UTILS_H__

#include <vector>
#include <list>
#include <string>

namespace ion
{
    // Append a dynamic array to another of the same type
    template <typename TValueType>
    inline std::vector<TValueType>&     operator+=
    (std::vector<TValueType>& lhs, const std::vector<TValueType>& rhs);


    template <typename TValueType>
    inline TValueType GetFromList(std::list<TValueType>& list, size_t index);




// ---- Implementation ----


	template <typename TValueType>
	inline std::vector<TValueType>& operator+=(std::vector<TValueType>& lhs, const std::vector<TValueType>& rhs)
	{
		for (const TValueType& element : rhs)
			lhs.push_back(element);

		return lhs;
	}


	template <typename TValueType>
	inline TValueType GetFromList(std::list<TValueType>& list, size_t index)
	{
		auto iterator = list.cbegin();

		for (size_t value = 0; value < index; ++value)
			++iterator;

		return *iterator;
	}

}




#endif
