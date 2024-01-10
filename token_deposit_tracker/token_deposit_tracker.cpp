#include "token_deposit_tracker.hpp"
#include <string> // Include the string library for std::string

// Implementation of the on_transfer function
void token_deposit_tracker::on_transfer(name from, name to, asset quantity, std::string memo)
{

    // Check if the transfer is intended for this contract and if the token is WAX
    // to: the recipient of the transfer (should be this contract)
    // quantity.symbol: the symbol of the asset being transferred (should be WAX)
    if (to != get_self() || quantity.symbol != symbol("WAX", 8))
        return; // If not, exit the function

    // A table to log the transfers received by this contract
    // get_self(): gets the account name of the contract
    // get_self().value: scopes the table uniquely to this contract
    transfer_table transfers(get_self(), get_self().value);
    transfers.emplace(get_self(), [&](auto &record)
                      {
                          // Lambda function to set the fields of a new transfer record
                          record.id = transfers.available_primary_key(); // Auto-incrementing ID
                          record.from = from;                            // Sender of the transfer
                          record.quantity = quantity;                    // Amount and symbol of the asset transferred
                          record.memo = memo;                            // Memo attached to the transfer
                      });

    // A table to keep track of balances for each user who sent tokens to this contract
    balance_table balances(get_self(), get_self().value);
    auto iterator = balances.find(from.value); // Find the balance record for the sender

    // Check if this is the first transfer from the sender
    if (iterator == balances.end())
    {
        // If it is, create a new balance record
        balances.emplace(get_self(), [&](auto &record)
                         {
                             record.user = from;              // Set the user to the sender of the transfer
                             record.total_balance = quantity; // Initialize the balance to the transferred amount
                         });
    }
    else
    {
        // If the sender already has a balance record, update it
        balances.modify(iterator, get_self(), [&](auto &record)
                        {
                            record.total_balance += quantity; // Add the transferred amount to the existing balance
                        });
    }
}
