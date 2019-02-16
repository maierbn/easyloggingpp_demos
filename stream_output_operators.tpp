
#include <sstream>

//! output array content to stream
template<typename T, std::size_t N>
std::ostream &operator<<(std::ostream &stream, const std::array<T,N> &vector)
{
  stream << "(" << vector[0];
  for (std::size_t i = 1; i < N; i++)
    stream << "," << vector[i];
  stream << ")";
  return stream;
}

template<std::size_t N>
std::ostream &operator<<(std::ostream &stream, const std::array<std::size_t,N> vector)
{
  stream << "(" << vector[0];
  for (std::size_t i = 1; i < N; i++)
    stream << "," << vector[i];
  stream << ")";
  return stream;
}

template<typename T>
std::ostream &operator<<(std::ostream &stream, const std::vector<T> &values)
{
  if (values.empty())
  {
    stream << "[]";
    return stream;
  }

  stream << "[" << values[0];

  if (VLOG_IS_ON(1))
  {
    // with VLOG output all entries
    for (unsigned long i = 1; i < values.size(); i++)
      stream << "," << values[i];
  }
  else
  {
    // without VLOG only output the first 100 entries
    unsigned long i = 1;
    for (; i < std::min(100ul,values.size()); i++)
      stream << "," << values[i];
    if (i == 100 && i < values.size())
      stream << "... " << values.size() << " entries total, only showing the first 100";
  }

  stream << "]";
  return stream;
}

template<typename T>
std::ostream &operator<<(std::ostream &stream, const std::list<T> &values)
{
  if (values.empty())
  {
    stream << "[]";
    return stream;
  }

  stream << "[" << values.front();
  typename std::list<T>::const_iterator iter = values.begin();
  iter++;

  if (VLOG_IS_ON(1))
  {
    // with VLOG output all entries
    for(;iter != values.end(); iter++)
      stream << "," << *iter;
  }
  else
  {
    // without VLOG only output the first 100 entries
    unsigned long i = 1;
    for (; i < std::min(100ul,values.size()); i++, iter++)
      stream << "," << *iter;
    if (i == 100 && i < values.size())
      stream << "... " << values.size() << " entries total, only showing the first 100";
  }

  stream << "]";
  return stream;
}

//! output operator for pairs of arbitrary type
template<typename T1, typename T2>
std::ostream &operator<<(std::ostream &stream, const std::pair<T1,T2> &pair)
{
  stream << "(" << pair.first << "," << pair.second << ")";
  return stream;
}

//! output operator for maps of arbitrary type
template<typename T1, typename T2>
std::ostream &operator<<(std::ostream &stream, const std::map<T1,T2> &map)
{
  bool first = true;
  for (typename std::map<T1,T2>::const_iterator iter = map.cbegin(); iter != map.cend(); iter++)
  {
    if (!first)
      stream << ", ";
    stream << "\"" << iter->first << "\": " << iter->second;
    first = false;
  }
  return stream;
}

//! output operator for sets of arbitrary type
template<typename T>
std::ostream &operator<<(std::ostream &stream, const std::set<T> &set)
{
  stream << "{";
  bool first = true;
  for (typename std::set<T>::const_iterator iter = set.cbegin(); iter != set.cend(); iter++)
  {
    if (!first)
      stream << ", ";
    stream << (*iter);
    first = false;
  }
  stream << "}";
  return stream;
}

//! output operators for tuples or arbitrary type
template <size_t index, typename... T>
typename std::enable_if<(index >= sizeof...(T))>::type
  getString(std::ostream &stream, const std::tuple<T...> &tuple)
{}

template <size_t index, typename... T>
typename std::enable_if<(index < sizeof...(T))>::type
  getString(std::ostream &stream, const std::tuple<T...> &tuple)
{
  if (index != 0)
  {
    stream << ",";
  }
  stream << std::get<index>(tuple);

  getString<index+1>(stream, tuple);
}

template <typename... T>
std::ostream &operator<<(std::ostream& stream, const std::tuple<T...> &tuple)
{
  stream << "[";
  getString<0>(stream, tuple);
  stream << "]";

  return stream;
}
