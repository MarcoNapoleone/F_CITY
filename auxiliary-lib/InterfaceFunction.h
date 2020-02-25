
#include <sstream>

/**
 * this template will transform float to string of float with decimal precision \p n
 * @tparam T this ca be any type
 * @param a_value the value to be transformed
 * @param n the precision
 * @return string with \p n decimal precisiom
 */
template <typename T> std::string to_string_with_precision(const T a_value, const int n) {

    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();

}