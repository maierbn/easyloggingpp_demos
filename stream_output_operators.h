#pragma once

#include <array>
#include <map>
#include <set>
#include <vector>

//! output array content to stream
template<typename T, std::size_t N>
std::ostream &operator<<(std::ostream &stream, const std::array<T,N> &vector);

//! output array content to stream
template<std::size_t N>
std::ostream &operator<<(std::ostream &stream, const std::array<std::size_t,N> vector);

//! output arbitrary vector
template<typename T>
std::ostream &operator<<(std::ostream &stream, const std::vector<T> &vector);

//! output arbitrary list
template<typename T>
std::ostream &operator<<(std::ostream &stream, const std::list<T> &list);

//! output operator for pairs of arbitrary type
template<typename T1, typename T2>
std::ostream &operator<<(std::ostream &stream, const std::pair<T1,T2> &pair);

//! output operator for maps of arbitrary type
template<typename T1, typename T2>
std::ostream &operator<<(std::ostream &stream, const std::map<T1,T2> &map);

//! output operator for sets of arbitrary type
template<typename T>
std::ostream &operator<<(std::ostream &stream, const std::set<T> &set);

//! output operators for tuples or arbitrary type
template <size_t index, typename... T>
typename std::enable_if<(index >= sizeof...(T))>::type
  getString(std::ostream &stream, const std::tuple<T...> &tuple);

template <size_t index, typename... T>
typename std::enable_if<(index < sizeof...(T))>::type
  getString(std::ostream &stream, const std::tuple<T...> &tuple);

template <typename... T>
std::ostream &operator<<(std::ostream& stream, const std::tuple<T...> &tuple);

#include "stream_output_operators.tpp"
