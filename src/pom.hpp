#include <array>
#include <cstdint>

#include "../external/blake3/blake3.h"
#include "defs.hpp"
#include "consensus.hpp"
#include "wallet.hpp"

#pragma once

class ProofOfMemory : public IConsensusModel {
    private:
        std::array<std::pair<Blake3Hash, Blake3Hash>, (1<<30) / BLAKE3_OUT_LEN> hashes;
        struct Wallet wallet;
    public:
        Blake3Hash solve_hash(Blake3Hash hash, uint32_t difficulty);
        void gen_hashes();
        ProofOfMemory(Wallet wallet);
};
