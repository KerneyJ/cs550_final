#include <array>
#include <cstdint>
#include <ctime>
#include <vector>
#include <string>

#include "address_list.hpp"
#include "consensus.hpp"
#include "defs.hpp"
#include "pow.hpp"
#include "transaction.hpp"
#include "validator.hpp"
#include "wallet.hpp"

Validator::Validator(AddressList _blockchain_peers, AddressList _tx_pools, IConsensusModel* _consensus) {
    blockchain_peers = _blockchain_peers;
    tx_pools = _tx_pools;
    consensus = _consensus;

    difficulty = 1;
    // wallet = load_wallet("./confing/wallet.cfg");
}

Validator::~Validator() {
    delete consensus;
}

void Validator::run() {
    // TODO: error handling
    while(true) {
        auto problem = request_block_header();
        Blake3Hash solution = consensus->solve_hash(problem.hash, problem.difficulty);
        auto block = create_block(problem, solution);
        submit_block(block);

        printf("Submitted block!\n");
    }
}

BlockHeader Validator::request_block_header() {
    Blake3Hash hash, prev_hash;
    hash.fill(255);

    return { nullptr, hash, prev_hash, 25, 0 };
}

Block Validator::create_block(BlockHeader prev_block, Blake3Hash solution) {
    auto txs = request_txs();

    // TODO: add reward to txs
    // TODO: variable difficulty

    Block new_block = {
        {
            nullptr,
            solution,
            prev_block.hash,
            prev_block.difficulty,
            static_cast<uint64_t>(std::time(nullptr))
        },
        txs
    };

    return new_block;
}

std::array<Transaction, BLOCK_SIZE> Validator::request_txs() {
    std::array<Transaction, BLOCK_SIZE> txs;

    std::string pool = tx_pools.get_address();

    return txs;
}

int Validator::submit_block(Block block) {
    // TODO: implement

    return 0;
}

int main() {
    AddressList blockchain_peers;
    AddressList tx_pools;
    IConsensusModel* consensus = new ProofOfWork();

    Validator validator = Validator(blockchain_peers, tx_pools, consensus);
    validator.run();
}