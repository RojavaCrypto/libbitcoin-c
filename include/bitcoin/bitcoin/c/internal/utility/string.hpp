/**
 * Copyright (c) 2011-2016 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LIBBITCOIN_C_INTERNAL_STRING_HPP
#define LIBBITCOIN_C_INTERNAL_STRING_HPP

#include <bitcoin/bitcoin/utility/string.hpp>
#include <bitcoin/bitcoin/c/internal/utility/vector.hpp>

BC_DECLARE_VECTOR_INTERNAL(string_list, bc_string_t, libbitcoin::string_list);

extern "C" {

struct bc_string_t
{
    std::string* obj;
};

} // extern C

// C++ convenience function
bc_string_t* bc_create_string_StdString(const std::string& string);

#endif

