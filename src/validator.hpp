#include <array>
#include <cstdint>
#include <string>
#include <vector>

#include "consensus.hpp"
#include "block.hpp"
#include "defs.hpp"
#include "server.hpp"
#include "transaction.hpp"
#include "wallet.hpp"
#include "defs.hpp"
#include "messages.hpp"

#pragma once

class Validator {
    private:
        void* zmq_ctx;
        std::string blockchain;
        std::string metronome;
        std::string tx_pool;
        IConsensusModel* consensus;
        Wallet wallet;
        Block create_block(BlockHeader bh, uint32_t difficulty, Blake3Hash hash);
        int submit_block(Block block);
        BlockHeader request_block_header();
        uint32_t request_difficulty();
        std::array<Transaction, BLOCK_SIZE> request_txs();
    public:
        Validator(std::string, std::string, std::string, IConsensusModel*, Wallet);
        ~Validator();
        void start(std::string);
};