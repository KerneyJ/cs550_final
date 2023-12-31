#include "block.hpp"
#include "keys.hpp"

void display_block_header(BlockHeader header) {
    printf("Block header:\n");
    printf("\thash: %s\n", base58_encode_key(header.hash).c_str());
    printf("\tprev_hash: %s\n", base58_encode_key(header.prev_hash).c_str());
    printf("\tdifficulty: %d\n", header.difficulty);
    printf("\ttimestamp: %lu\n", header.timestamp);
    printf("\tid: %d\n", header.id);
}

void display_block(Block block) {
    display_block_header(block.header);

    for(auto tx : block.transactions)
        display_transaction(tx);
}