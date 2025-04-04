// Copyright (c) 2012-2020 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_VERSION_H
#define BITCOIN_VERSION_H

/**
 * network protocol versioning
 */

static const int PROTOCOL_VERSION = 71066;
static const int OLD_VERSION = 71065; // peercoin: used to communicate with clients that don't know how to send PoS information in headers

//! initial proto version, to be increased after version/verack negotiation
static const int INIT_PROTO_VERSION = 209;

//! disconnect from peers older than this proto version
static const int MIN_PEER_PROTO_VERSION = 71064;

//! BIP 0031, pong message, is enabled for all versions AFTER this one
static const int BIP0031_VERSION = 60000;

//! "filter*" commands are disabled without NODE_BLOOM after and including this version
static const int NO_BLOOM_VERSION = 71066;

//! "sendheaders" command and announcing blocks with headers starts with this version
static const int SENDHEADERS_VERSION = 71066;

//! "feefilter" tells peers to filter invs to you by fee starts with this version
static const int FEEFILTER_VERSION = 71066;

//! short-id-based block download starts with this version
static const int SHORT_IDS_BLOCKS_VERSION = 71066;

//! not banning for invalid compact blocks starts with this version
static const int INVALID_CB_NO_BAN_VERSION = 71066;

//! "wtxidrelay" command for wtxid-based relay starts with this version
static const int WTXID_RELAY_VERSION = 71066;

// Make sure that none of the values above collide with
// `SERIALIZE_TRANSACTION_NO_WITNESS` or `ADDRV2_FORMAT`.

#endif // BITCOIN_VERSION_H
