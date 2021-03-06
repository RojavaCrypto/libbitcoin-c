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
#ifndef LIBBITCOIN_C_CHAIN_TRANSACTION_H
#define LIBBITCOIN_C_CHAIN_TRANSACTION_H

#include <bitcoin/bitcoin/c/chain/chain_state.h>
#include <bitcoin/bitcoin/c/chain/input.h>
#include <bitcoin/bitcoin/c/chain/output.h>
#include <bitcoin/bitcoin/c/error.h>
#include <bitcoin/bitcoin/c/math/hash.h>
#include <bitcoin/bitcoin/c/utility/data.h>
#include <bitcoin/bitcoin/c/utility/string.h>
#include <bitcoin/bitcoin/c/utility/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bc_transaction_t bc_transaction_t;
BC_DECLARE_VECTOR(transaction_list, bc_transaction_t);

// Static functions
bc_transaction_t* bc_transaction__factory_from_data(
    const bc_data_chunk_t* data);
bc_transaction_t* bc_transaction__factory_from_data_nosatoshi(
    const bc_data_chunk_t* data);

// Constructor
bc_transaction_t* bc_create_transaction();
bc_transaction_t* bc_create_transaction_copy(const bc_transaction_t* other);
bc_transaction_t* bc_create_transaction_Parts(
    uint32_t version, uint32_t locktime,
    const bc_input_list_t* inputs, const bc_output_list_t* outputs);

// Destructor
void bc_destroy_transaction(bc_transaction_t* self);

// Member functions
bool bc_transaction__from_data(bc_transaction_t* self,
    const bc_data_chunk_t* data);
bc_data_chunk_t* bc_transaction__to_data(const bc_transaction_t* self);
bc_string_t* bc_transaction__to_string(const bc_transaction_t* self,
    uint32_t flags);

bool bc_transaction__is_valid(const bc_transaction_t* self);
bool bc_transaction__is_coinbase(const bc_transaction_t* self);
bool bc_transaction__is_invalid_coinbase(const bc_transaction_t* self);
bool bc_transaction__is_invalid_non_coinbase(const bc_transaction_t* self);
bool bc_transaction__is_overspent(const bc_transaction_t* self);
bool bc_transaction__is_final(const bc_transaction_t* self,
    uint64_t block_height, uint32_t block_time);
bool bc_transaction__is_locktime_conflict(const bc_transaction_t* self);
bool bc_transaction__is_missing_inputs(const bc_transaction_t* self);
bool bc_transaction__is_immature(const bc_transaction_t* self,
    size_t target_height);
bool bc_transaction__is_double_spend(const bc_transaction_t* self,
    bool include_unconfirmed);

void bc_transaction__reset(bc_transaction_t* self);
bc_error_code_t* bc_transaction__check(const bc_transaction_t* self);
bc_error_code_t* bc_transaction__check_notransaction_pool(
    const bc_transaction_t* self);
bc_error_code_t* bc_transaction__accept(
    const bc_transaction_t* self, const bc_chain_state_t* state);
bc_error_code_t* bc_transaction__accept_notransaction_pool(
    const bc_transaction_t* self, const bc_chain_state_t* state);
bc_error_code_t* bc_transaction__connect(
    const bc_transaction_t* self, const bc_chain_state_t* state);
bc_error_code_t* bc_transaction__connect_input(
    const bc_transaction_t* self, const bc_chain_state_t* state,
    uint32_t input_index);

uint64_t bc_transaction__serialized_size(const bc_transaction_t* self);
uint64_t bc_transaction__total_input_value(const bc_transaction_t* self);
uint64_t bc_transaction__total_output_value(const bc_transaction_t* self);
bc_point_indexes_t* bc_transaction__missing_inputs(
    const bc_transaction_t* self);
bc_point_indexes_t* bc_transaction__immature_inputs(
    const bc_transaction_t* self, size_t target_height);
bc_point_indexes_t* bc_transaction__double_spends(
    const bc_transaction_t* self, bool include_unconfirmed);
size_t bc_transaction__signature_operations(
    const bc_transaction_t* self, bool bip16_active);
bc_hash_digest_t* bc_transaction__hash_Sighash(const bc_transaction_t* self,
    uint32_t sighash_type);
bc_hash_digest_t* bc_transaction__hash(const bc_transaction_t* self);
uint64_t bc_transaction__fees(const bc_transaction_t* self);

/// The transaction duplicates another in the blockchain.
/// This does not exclude the two excepted transactions (see BIP30).
bool bc_transaction__duplicate(const bc_transaction_t* self);
void bc_transaction__set_duplicate(bc_transaction_t* self);

// Member variables
uint32_t bc_transaction__version(const bc_transaction_t* self);
void bc_transaction__set_version(bc_transaction_t* self, uint32_t version);
uint32_t bc_transaction__locktime(const bc_transaction_t* self);
void bc_transaction__set_locktime(bc_transaction_t* self, uint32_t locktime);
bc_input_list_t* bc_transaction__inputs(const bc_transaction_t* self);
void bc_transaction__set_inputs(bc_transaction_t* self,
    const bc_input_list_t* inputs);
bc_output_list_t* bc_transaction__outputs(const bc_transaction_t* self);
void bc_transaction__set_outputs(bc_transaction_t* self,
    const bc_output_list_t* outputs);

#ifdef __cplusplus
}
#endif

#endif

