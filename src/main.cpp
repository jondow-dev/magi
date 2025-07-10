#include "main.h"
#include "consensus/params.h"
#include "logging.h"

double ConvertBitsToDouble(unsigned int nBits)
{
    int nShift = (nBits >> 24) & 0xff;
    double dDiff = (double)0x0000ffff / (double)(nBits & 0x00ffffff);
    while (nShift < 29) {
        dDiff *= 256.0;
        nShift++;
    }
    while (nShift > 29) {
        dDiff /= 256.0;
        nShift--;
    }
    return dDiff;
}

CAmount GetBlockReward(const CBlock& block, int nHeight, const CBlockIndex* pindex, const Consensus::Params& consensusParams, bool fTestNet)
{
    CAmount nSubsidy = 0;
    if (fTestNet) {
        nSubsidy = (100 * COIN) >> (nHeight / 1051200); // Magi testnet logic
    } else if (block.IsProofOfWork()) {
        // Magi mPoW logic
        double nDiff = GetDifficulty(pindex); // Port from Magi
        if (nHeight <= 10) {
            nSubsidy = 112500 * COIN; // Premine
        } else if (nHeight <= 2700) {
            nSubsidy = 495.05 * pow((5.55243 * (exp_n(-0.3 * nDiff / 15.762) - exp_n(-0.6 * nDiff / 15.762))) * nDiff, 0.5) / 8.61553;
            if (nSubsidy < 5) nSubsidy = 5;
            nSubsidy *= COIN;
        } else if (nHeight <= 32750) {
            nSubsidy = 294.118 * pow((5.55243 * (exp_n(-0.3 * nDiff / 0.39) - exp_n(-0.6 * nDiff / 0.39))) * nDiff, 0.5) / 1.335;
            if (nSubsidy < 5) nSubsidy = 5;
            nSubsidy *= COIN;
        } else {
            nSubsidy = 294.118 * pow((5.55243 * (exp_n(-0.3 * nDiff / 0.39 * M7Mv2_SCALE) - exp_n(-0.6 * nDiff / 0.39 * M7Mv2_SCALE))) * nDiff, 0.5) / 0.8456;
            if (nSubsidy < 5) nSubsidy = 5;
            nSubsidy *= COIN;
        }
        for (int i = 525600; i <= nHeight; i += 525600) nSubsidy *= 0.93; // Yearly decline
    } else if (block.IsProofOfStake() && pindex) {
        // Peercoin PoS reward
        nSubsidy = CalculateProofOfStakeReward(block, pindex, consensusParams);
    }
    if (nSubsidy < MIN_TX_FEE) nSubsidy = MIN_TX_FEE;
    LogPrintf("GetBlockReward: nHeight=%d, nSubsidy=%s\n", nHeight, FormatMoney(nSubsidy));
    return nSubsidy;
}

CAmount CalculateProofOfStakeReward(const CBlock& block, const CBlockIndex* pindex, const Consensus::Params& consensusParams)
{
    CAmount nCoinAge;
    if (!GetCoinAge(block, pindex, nCoinAge)) {
        return 0;
    }
    // Magi mPoS: Limit coin age (e.g., max 90 days)
    CAmount nMaxCoinAge = 90 * 24 * 60 * 60 * consensusParams.nStakeMinAge; // Example
    if (nCoinAge > nMaxCoinAge) nCoinAge = nMaxCoinAge;
    // Peercoin: ~1% annual reward
    CAmount nReward = nCoinAge * 0.01 / 365;
    return nReward;
}