#include <vector>
#include <mutex>

#include "keys.hpp"
#include "server.hpp"
#include "block.hpp"

#pragma once

class BlockChain {
    private:
        Server server;
        std::string txpool_address;
        std::vector<Block> blocks;
        std::mutex blockmutex;
        std::unordered_map<Ed25519Key, uint32_t, Ed25519KeyHash> ledger;
        void sync_bal(Block b);
        void add_block(void* receiver, MessageBuffer data);
        void get_balance(void* receiver, MessageBuffer data);
        void last_block(void* receiver, MessageBuffer data);
        void tx_status(void *receiver, MessageBuffer data);
        void get_num_addr(void* receiver, MessageBuffer data);
        void request_handler(void* receiver, Message<MessageBuffer> request);
        void get_total_coins(void* receiver, MessageBuffer data);
        void load_genesis();
    public:
        BlockChain(std::string txpaddr);
        void start(std::string address);
};
