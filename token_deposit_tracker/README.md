Auto-Token-Deposit-and-Balance-Tracker for WAX Blockchain (eosio::on_notify)
Overview
The Auto-Token-Deposit-and-Balance-Tracker is an EOSIO smart contract specifically tailored for the WAX blockchain. It leverages the eosio::on_notify attribute to automatically track token deposits (specifically WAX tokens) and manage user balances.
Key Features

- Automated Transfer Tracking: Captures and logs all incoming WAX token transfers to the contract.
- User Balance Management: Keeps an updated ledger of WAX token balances for each user who transfers tokens to the contract.
  Contract Mechanics
  on_transfer (eosio::on_notify Handler)
- This action handler is automatically invoked in response to transfer actions from the eosio.token contract.
  _ Parameters:
  _ from: The account sending the transfer.
  _ to: The intended recipient (must be this contract for processing).
  _ quantity: The amount and symbol of the asset transferred. \* memo: An optional memo attached with the transfer.
  Data Structures
  Table: transfers
- A log of each transfer received by the contract.
  _ Fields:
  _ id: Unique identifier.
  _ from: Sender of the transfer.
  _ quantity: The transferred asset amount and symbol. \* memo: Text of the memo attached to the transfer.
  Table: balances
- A ledger of accumulated balances for users who have sent tokens.
  - Fields:
  - user: Account name of the user.
  - total_balance: Aggregate balance of WAX tokens held by the user.

Testing and Validation
Perform thorough testing on the WAX testnet prior to mainnet deployment. Validate all aspects of the contract, including transfer recording and balance accuracy.
License
This project is distributed under the MIT License.
