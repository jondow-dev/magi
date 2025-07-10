#ifndef BITCOIN_MAIN_H
#define BITCOIN_MAIN_H

#include <amount.h> // For CAmount
#include <math.h>   // For pow and exp

// Constants from m-pays/magi/src/main.h
static const int BLOCK_REWARD_ADJT = 2700;
static const int BLOCK_REWARD_ADJT_M7M_V2 = 32750;
static const double M7Mv2_SCALE = 1.0;
static const CAmount MIN_TX_FEE = 10000; // Minimum transaction fee

// Mathematical functions from magimath.h
inline double exp_n(double x)
{
    return exp(x);
}

// Function declarations
double ConvertBitsToDouble(unsigned int nBits);
CAmount GetBlockSubsidy(int nHeight, double nDiff, bool fTestNet);

#endif // BITCOIN_MAIN_H