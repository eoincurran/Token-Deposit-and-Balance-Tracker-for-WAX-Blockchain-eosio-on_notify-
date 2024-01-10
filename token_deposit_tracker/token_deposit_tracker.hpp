#include <eosio/eosio.hpp> // Essential EOSIO smart contract header
#include <eosio/asset.hpp> // EOSIO asset type header
#include <string>          // Include the C++ string library

// Declare the eosio namespace which contains core EOSIO classes and functions
using namespace eosio;

// Define the smart contract class
// The eosio::contract("token_deposit_tracker") attribute defines the contract name
class [[eosio::contract("token_deposit_tracker")]] token_deposit_tracker : public contract
{
public:
    // Constructor that uses the base eosio::contract class constructor
    using contract::contract;

    // Notification handler for WAX token transfers
    // The eosio::on_notify attribute specifies that this function should only be called
    // when a transfer action is sent by the "eosio.token" contract
    [[eosio::on_notify("eosio.token::transfer")]] void on_transfer(name from, name to, asset quantity, std::string memo);

    // Structure representing a record in the transfer logs table
    struct [[eosio::table]] transfer_record
    {
        uint64_t id;      // Unique ID for the record
        name from;        // Account name of the sender
        asset quantity;   // Amount and symbol of the asset transferred
        std::string memo; // Memo attached to the transfer

        // Primary key of the table is the unique ID
        uint64_t primary_key() const { return id; }
    };
    // Multi-index table for storing transfer records, indexed by ID
    using transfer_table = multi_index<"transfers"_n, transfer_record>;

    // Structure representing a user's balance record
    struct [[eosio::table]] balance_record
    {
        name user;           // Account name of the user
        asset total_balance; // Total balance of the user

        // Primary key of the table is the account name of the user
        uint64_t primary_key() const { return user.value; }
    };
    // Multi-index table for storing balance records, indexed by user account name
    using balance_table = multi_index<"balances"_n, balance_record>;
};
