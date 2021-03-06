/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *  (C) 2006 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 *
 *  Portions of this code were written by Intel Corporation.
 *  Copyright (C) 2011-2016 Intel Corporation.  Intel provides this material
 *  to Argonne National Laboratory subject to Software Grant and Corporate
 *  Contributor License Agreement dated February 8, 2012.
 */
#ifndef NETMOD_OFI_CAPABILITY_SETS_H_INCLUDED
#define NETMOD_OFI_CAPABILITY_SETS_H_INCLUDED

#define MPIDI_OFI_OFF     0
#define MPIDI_OFI_ON      1

enum {
    MPIDI_OFI_SET_NUMBER_PSM = 0,
    MPIDI_OFI_SET_NUMBER_PSM2,
    MPIDI_OFI_SET_NUMBER_GNI,
    MPIDI_OFI_SET_NUMBER_SOCKETS,
    MPIDI_OFI_SET_NUMBER_BGQ,
    MPIDI_OFI_SET_NUMBER_VERBS,
    MPIDI_OFI_NUM_SETS
};

#define MPIDI_OFI_MAX_ENDPOINTS_SCALABLE        256
#define MPIDI_OFI_MAX_ENDPOINTS_BITS_SCALABLE   8
#define MPIDI_OFI_MAX_ENDPOINTS_REGULAR         1
#define MPIDI_OFI_MAX_ENDPOINTS_BITS_REGULAR    0

/* This needs to be kept in sync with the order in globals.c */
MPL_STATIC_INLINE_PREFIX int MPIDI_OFI_get_set_number(char *set_name)
{
    if (!strcmp("psm", set_name)) {
        return MPIDI_OFI_SET_NUMBER_PSM;
    } else if (!strcmp("psm2", set_name)) {
        return MPIDI_OFI_SET_NUMBER_PSM2;
    } else if (!strcmp("gni", set_name)) {
        return MPIDI_OFI_SET_NUMBER_GNI;
    } else if (!strcmp("sockets", set_name)) {
        return MPIDI_OFI_SET_NUMBER_SOCKETS;
    } else if (!strcmp("bgq", set_name)) {
        return MPIDI_OFI_SET_NUMBER_BGQ;
    } else if (!strcmp("verbs", set_name)) {
        return MPIDI_OFI_SET_NUMBER_VERBS;
    } else {
        return -1;
    }
}

/*
 * The definitions map to these capability sets:
 *
 * MPIDI_OFI_ENABLE_DATA               fi_tsenddata (and other functions with immediate data)
 *                                     Uses FI_REMOTE_CQ_DATA, FI_DIRECTED_RECV
 * MPIDI_OFI_ENABLE_AV_TABLE           Use FI_AV_TABLE instead of FI_AV_MAP
 * MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS fi_scalable_ep instead of fi_ep
 *                                     domain_attr.max_ep_tx_ctx > 1
 * MPIDI_OFI_ENABLE_STX_RMA            Use shared transmit contexts for RMA
 *                                     Uses FI_SHARED_CONTEXT
 * MPIDI_OFI_ENABLE_MR_SCALABLE        Use FI_MR_SCALABLE instead of FI_MR_BASIC
 *                                     If using runtime mode, this will be set to FI_MR_UNSPEC
 * MPIDI_OFI_ENABLE_TAGGED             Use FI_TAGGED interface instead of FI_MSG
 * MPIDI_OFI_ENABLE_AM                 Use FI_MSG and FI_MULTI_RECV for active messages
 * MPIDI_OFI_ENABLE_RMA                Use FI_ATOMICS and FI_RMA interfaces
 * MPIDI_OFI_FETCH_ATOMIC_IOVECS       The maximum number of iovecs that can be used for fetch_atomic operations
 * MPIDI_OFI_CONTEXT_MASK_CAPSET       The bitmask used to extract the context ID from the match_bits in an OFI message
 * MPIDI_OFI_SOURCE_MASK_CAPSET        The bitmask used to extract the source rank from the match_bits in an OFI message
 * MPIDI_OFI_TAG_MASK_CAPSET           The bitmask used to extract the tag from the match_bits in an OFI message
 * MPIDI_OFI_CONTEXT_BITS              The number of bits used for the context ID in an OFI message
 * MPIDI_OFI_SOURCE_BITS               The number of bits used for the source rank in an OFI message
 * MPIDI_OFI_TAG_BITS                  The number of bits used for the tag in an OFI message
 */

#define MPIDI_OFI_ENABLE_DATA_PSM               MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_AV_TABLE_PSM           MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS_PSM MPIDI_OFI_OFF
#define MPIDI_OFI_MAX_ENDPOINTS_PSM             MPIDI_OFI_MAX_ENDPOINTS_REGULAR
#define MPIDI_OFI_MAX_ENDPOINTS_BITS_PSM        MPIDI_OFI_MAX_ENDPOINTS_BITS_REGULAR
#define MPIDI_OFI_ENABLE_STX_RMA_PSM            MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_MR_SCALABLE_PSM        MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_TAGGED_PSM             MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_AM_PSM                 MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_RMA_PSM                MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_ATOMICS_PSM            MPIDI_OFI_ENABLE_RMA_PSM
#define MPIDI_OFI_FETCH_ATOMIC_IOVECS_PSM       1
#define MPIDI_OFI_CONTEXT_MASK_PSM              (0x0FFFF00000000000ULL)
#define MPIDI_OFI_SOURCE_MASK_PSM               (0x00000FFFFFF00000ULL) /* PSM does not support immediate data
                                                                         * so this field needs to be available */
#define MPIDI_OFI_TAG_MASK_PSM                  (0x00000000000FFFFFULL)
#define MPIDI_OFI_CONTEXT_BITS_PSM              (16)
#define MPIDI_OFI_SOURCE_BITS_PSM               (24)
#define MPIDI_OFI_TAG_BITS_PSM                  (20)

#ifdef MPIDI_CH4_OFI_USE_SET_PSM
#define MPIDI_OFI_ENABLE_RUNTIME_CHECKS     MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_DATA               MPIDI_OFI_ENABLE_DATA_PSM
#define MPIDI_OFI_ENABLE_AV_TABLE           MPIDI_OFI_ENABLE_AV_TABLE_PSM
#define MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS_PSM
#define MPIDI_OFI_MAX_ENDPOINTS             MPIDI_OFI_MAX_ENDPOINTS_PSM
#define MPIDI_OFI_MAX_ENDPOINTS_BITS        MPIDI_OFI_MAX_ENDPOINTS_BITS_PSM
#define MPIDI_OFI_ENABLE_STX_RMA            MPIDI_OFI_ENABLE_STX_RMA_PSM
#define MPIDI_OFI_ENABLE_MR_SCALABLE        MPIDI_OFI_ENABLE_MR_SCALABLE_PSM
#define MPIDI_OFI_ENABLE_TAGGED             MPIDI_OFI_ENABLE_TAGGED_PSM
#define MPIDI_OFI_ENABLE_AM                 MPIDI_OFI_ENABLE_AM_PSM
#define MPIDI_OFI_ENABLE_RMA                MPIDI_OFI_ENABLE_RMA_PSM
#define MPIDI_OFI_ENABLE_ATOMICS            MPIDI_OFI_ENABLE_ATOMICS_PSM
#define MPIDI_OFI_FETCH_ATOMIC_IOVECS       MPIDI_OFI_FETCH_ATOMIC_IOVECS_PSM
#define MPIDI_OFI_CONTEXT_MASK_CAPSET       MPIDI_OFI_CONTEXT_MASK_PSM
#define MPIDI_OFI_SOURCE_MASK_CAPSET        MPIDI_OFI_SOURCE_MASK_PSM
#define MPIDI_OFI_TAG_MASK_CAPSET           MPIDI_OFI_TAG_MASK_PSM
#define MPIDI_OFI_CONTEXT_BITS              MPIDI_OFI_CONTEXT_BITS_PSM
#define MPIDI_OFI_SOURCE_BITS               MPIDI_OFI_SOURCE_BITS_PSM
#define MPIDI_OFI_TAG_BITS                  MPIDI_OFI_TAG_BITS_PSM
#endif

#define MPIDI_OFI_ENABLE_DATA_PSM2               MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_AV_TABLE_PSM2           MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS_PSM2 MPIDI_OFI_OFF
#define MPIDI_OFI_MAX_ENDPOINTS_PSM2             MPIDI_OFI_MAX_ENDPOINTS_REGULAR
#define MPIDI_OFI_MAX_ENDPOINTS_BITS_PSM2        MPIDI_OFI_MAX_ENDPOINTS_BITS_REGULAR
#define MPIDI_OFI_ENABLE_STX_RMA_PSM2            MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_MR_SCALABLE_PSM2        MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_TAGGED_PSM2             MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_AM_PSM2                 MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_RMA_PSM2                MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_ATOMICS_PSM2            MPIDI_OFI_ENABLE_RMA_PSM2
#define MPIDI_OFI_FETCH_ATOMIC_IOVECS_PSM2       1
#define MPIDI_OFI_CONTEXT_MASK_PSM2              (0x0FFFF00000000000ULL)
#define MPIDI_OFI_SOURCE_MASK_PSM2               (0x00000FFFFFF00000ULL) /* PSM2 does not support immediate data
                                                                          * so this field needs to be available */
#define MPIDI_OFI_TAG_MASK_PSM2                  (0x00000000000FFFFFULL)
#define MPIDI_OFI_CONTEXT_BITS_PSM2              (16)
#define MPIDI_OFI_SOURCE_BITS_PSM2               (24)
#define MPIDI_OFI_TAG_BITS_PSM2                  (20)

#ifdef MPIDI_CH4_OFI_USE_SET_PSM2
#define MPIDI_OFI_ENABLE_RUNTIME_CHECKS     MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_DATA               MPIDI_OFI_ENABLE_DATA_PSM2
#define MPIDI_OFI_ENABLE_AV_TABLE           MPIDI_OFI_ENABLE_AV_TABLE_PSM2
#define MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS_PSM2
#define MPIDI_OFI_MAX_ENDPOINTS             MPIDI_OFI_MAX_ENDPOINTS_PSM2
#define MPIDI_OFI_MAX_ENDPOINTS_BITS        MPIDI_OFI_MAX_ENDPOINTS_BITS_PSM2
#define MPIDI_OFI_ENABLE_STX_RMA            MPIDI_OFI_ENABLE_STX_RMA_PSM2
#define MPIDI_OFI_ENABLE_MR_SCALABLE        MPIDI_OFI_ENABLE_MR_SCALABLE_PSM2
#define MPIDI_OFI_ENABLE_TAGGED             MPIDI_OFI_ENABLE_TAGGED_PSM2
#define MPIDI_OFI_ENABLE_AM                 MPIDI_OFI_ENABLE_AM_PSM2
#define MPIDI_OFI_ENABLE_RMA                MPIDI_OFI_ENABLE_RMA_PSM2
#define MPIDI_OFI_ENABLE_ATOMICS            MPIDI_OFI_ENABLE_ATOMICS_PSM2
#define MPIDI_OFI_FETCH_ATOMIC_IOVECS       MPIDI_OFI_FETCH_ATOMIC_IOVECS_PSM2
#define MPIDI_OFI_CONTEXT_MASK_CAPSET       MPIDI_OFI_CONTEXT_MASK_PSM2
#define MPIDI_OFI_SOURCE_MASK_CAPSET        MPIDI_OFI_SOURCE_MASK_PSM2
#define MPIDI_OFI_TAG_MASK_CAPSET           MPIDI_OFI_TAG_MASK_PSM2
#define MPIDI_OFI_CONTEXT_BITS              MPIDI_OFI_CONTEXT_BITS_PSM2
#define MPIDI_OFI_SOURCE_BITS               MPIDI_OFI_SOURCE_BITS_PSM2
#define MPIDI_OFI_TAG_BITS                  MPIDI_OFI_TAG_BITS_PSM2
#endif

#define MPIDI_OFI_ENABLE_DATA_GNI               MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_AV_TABLE_GNI           MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS_GNI MPIDI_OFI_OFF
#define MPIDI_OFI_MAX_ENDPOINTS_GNI             MPIDI_OFI_MAX_ENDPOINTS_REGULAR
#define MPIDI_OFI_MAX_ENDPOINTS_BITS_GNI        MPIDI_OFI_MAX_ENDPOINTS_BITS_REGULAR
#define MPIDI_OFI_ENABLE_STX_RMA_GNI            MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_MR_SCALABLE_GNI        MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_TAGGED_GNI             MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_AM_GNI                 MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_RMA_GNI                MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_ATOMICS_GNI            MPIDI_OFI_ENABLE_RMA_GNI
#define MPIDI_OFI_FETCH_ATOMIC_IOVECS_GNI       1
#define MPIDI_OFI_CONTEXT_MASK_GNI              (0x0FFFF00000000000ULL)
#define MPIDI_OFI_SOURCE_MASK_GNI               (0x00000FFFFFF00000ULL) /* GNI does not support immediate data
                                                                         * so this field needs to be available */
#define MPIDI_OFI_TAG_MASK_GNI                  (0x00000000000FFFFFULL)
#define MPIDI_OFI_CONTEXT_BITS_GNI              (16)
#define MPIDI_OFI_SOURCE_BITS_GNI               (24)
#define MPIDI_OFI_TAG_BITS_GNI                  (20)

#ifdef MPIDI_CH4_OFI_USE_SET_GNI
#define MPIDI_OFI_ENABLE_RUNTIME_CHECKS     MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_DATA               MPIDI_OFI_ENABLE_DATA_GNI
#define MPIDI_OFI_ENABLE_AV_TABLE           MPIDI_OFI_ENABLE_AV_TABLE_GNI
#define MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS_GNI
#define MPIDI_OFI_MAX_ENDPOINTS             MPIDI_OFI_MAX_ENDPOINTS_GNI
#define MPIDI_OFI_MAX_ENDPOINTS_BITS        MPIDI_OFI_MAX_ENDPOINTS_BITS_GNI
#define MPIDI_OFI_ENABLE_STX_RMA            MPIDI_OFI_ENABLE_STX_RMA_GNI
#define MPIDI_OFI_ENABLE_MR_SCALABLE        MPIDI_OFI_ENABLE_MR_SCALABLE_GNI
#define MPIDI_OFI_ENABLE_TAGGED             MPIDI_OFI_ENABLE_TAGGED_GNI
#define MPIDI_OFI_ENABLE_AM                 MPIDI_OFI_ENABLE_AM_GNI
#define MPIDI_OFI_ENABLE_RMA                MPIDI_OFI_ENABLE_RMA_GNI
#define MPIDI_OFI_ENABLE_ATOMICS            MPIDI_OFI_ENABLE_ATOMICS_GNI
#define MPIDI_OFI_FETCH_ATOMIC_IOVECS       MPIDI_OFI_FETCH_ATOMIC_IOVECS_GNI
#define MPIDI_OFI_CONTEXT_MASK_CAPSET       MPIDI_OFI_CONTEXT_MASK_GNI
#define MPIDI_OFI_SOURCE_MASK_CAPSET        MPIDI_OFI_SOURCE_MASK_GNI
#define MPIDI_OFI_TAG_MASK_CAPSET           MPIDI_OFI_TAG_MASK_GNI
#define MPIDI_OFI_CONTEXT_BITS              MPIDI_OFI_CONTEXT_BITS_GNI
#define MPIDI_OFI_SOURCE_BITS               MPIDI_OFI_SOURCE_BITS_GNI
#define MPIDI_OFI_TAG_BITS                  MPIDI_OFI_TAG_BITS_GNI
#endif

#define MPIDI_OFI_ENABLE_DATA_SOCKETS               MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_AV_TABLE_SOCKETS           MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS_SOCKETS MPIDI_OFI_ON
#define MPIDI_OFI_MAX_ENDPOINTS_SOCKETS             MPIDI_OFI_MAX_ENDPOINTS_SCALABLE
#define MPIDI_OFI_MAX_ENDPOINTS_BITS_SOCKETS        MPIDI_OFI_MAX_ENDPOINTS_BITS_SCALABLE
#define MPIDI_OFI_ENABLE_STX_RMA_SOCKETS            MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_MR_SCALABLE_SOCKETS        MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_TAGGED_SOCKETS             MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_AM_SOCKETS                 MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_RMA_SOCKETS                MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_ATOMICS_SOCKETS            MPIDI_OFI_ENABLE_RMA_SOCKETS
#define MPIDI_OFI_FETCH_ATOMIC_IOVECS_SOCKETS       1
#define MPIDI_OFI_CONTEXT_MASK_SOCKETS              (0x0000FFFF00000000ULL)
#define MPIDI_OFI_SOURCE_MASK_SOCKETS               (0x0000000000000000ULL) /* Sockets does support immediate data
                                                                             * so this field is zeroed */
#define MPIDI_OFI_TAG_MASK_SOCKETS                  (0x000000007FFFFFFFULL)
#define MPIDI_OFI_CONTEXT_BITS_SOCKETS              (16)
#define MPIDI_OFI_SOURCE_BITS_SOCKETS               (0)
#define MPIDI_OFI_TAG_BITS_SOCKETS                  (31)

#ifdef MPIDI_CH4_OFI_USE_SET_SOCKETS
#define MPIDI_OFI_ENABLE_RUNTIME_CHECKS     MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_DATA               MPIDI_OFI_ENABLE_DATA_SOCKETS
#define MPIDI_OFI_ENABLE_AV_TABLE           MPIDI_OFI_ENABLE_AV_TABLE_SOCKETS
#define MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS_SOCKETS
#define MPIDI_OFI_MAX_ENDPOINTS             MPIDI_OFI_MAX_ENDPOINTS_SOCKETS
#define MPIDI_OFI_MAX_ENDPOINTS_BITS        MPIDI_OFI_MAX_ENDPOINTS_BITS_SOCKETS
#define MPIDI_OFI_ENABLE_STX_RMA            MPIDI_OFI_ENABLE_STX_RMA_SOCKETS
#define MPIDI_OFI_ENABLE_MR_SCALABLE        MPIDI_OFI_ENABLE_MR_SCALABLE_SOCKETS
#define MPIDI_OFI_ENABLE_TAGGED             MPIDI_OFI_ENABLE_TAGGED_SOCKETS
#define MPIDI_OFI_ENABLE_AM                 MPIDI_OFI_ENABLE_AM_SOCKETS
#define MPIDI_OFI_ENABLE_RMA                MPIDI_OFI_ENABLE_RMA_SOCKETS
#define MPIDI_OFI_ENABLE_ATOMICS            MPIDI_OFI_ENABLE_ATOMICS_SOCKETS
#define MPIDI_OFI_FETCH_ATOMIC_IOVECS       MPIDI_OFI_FETCH_ATOMIC_IOVECS_SOCKETS
#define MPIDI_OFI_CONTEXT_MASK_CAPSET       MPIDI_OFI_CONTEXT_MASK_SOCKETS
#define MPIDI_OFI_SOURCE_MASK_CAPSET        MPIDI_OFI_SOURCE_MASK_SOCKETS
#define MPIDI_OFI_TAG_MASK_CAPSET           MPIDI_OFI_TAG_MASK_SOCKETS
#define MPIDI_OFI_CONTEXT_BITS              MPIDI_OFI_CONTEXT_BITS_SOCKETS
#define MPIDI_OFI_SOURCE_BITS               MPIDI_OFI_SOURCE_BITS_SOCKETS
#define MPIDI_OFI_TAG_BITS                  MPIDI_OFI_TAG_BITS_SOCKETS
#endif

#define MPIDI_OFI_ENABLE_DATA_BGQ               MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_AV_TABLE_BGQ           MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS_BGQ MPIDI_OFI_OFF
#define MPIDI_OFI_MAX_ENDPOINTS_BGQ             MPIDI_OFI_MAX_ENDPOINTS_REGULAR
#define MPIDI_OFI_MAX_ENDPOINTS_BITS_BGQ        MPIDI_OFI_MAX_ENDPOINTS_BITS_REGULAR
#define MPIDI_OFI_ENABLE_STX_RMA_BGQ            MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_MR_SCALABLE_BGQ        MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_TAGGED_BGQ             MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_AM_BGQ                 MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_RMA_BGQ                MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_ATOMICS_BGQ            MPIDI_OFI_ENABLE_RMA_BGQ
#define MPIDI_OFI_FETCH_ATOMIC_IOVECS_BGQ       1
#define MPIDI_OFI_CONTEXT_MASK_BGQ              (0x0000FFFF00000000ULL)
#define MPIDI_OFI_SOURCE_MASK_BGQ               (0x0000000000000000ULL) /* BGQ does support immediate data
                                                                         * so this field is zeroed */
#define MPIDI_OFI_TAG_MASK_BGQ                  (0x000000007FFFFFFFULL)
#define MPIDI_OFI_CONTEXT_BITS_BGQ              (16)
#define MPIDI_OFI_SOURCE_BITS_BGQ               (0)
#define MPIDI_OFI_TAG_BITS_BGQ                  (31)

#ifdef MPIDI_CH4_OFI_USE_SET_BGQ
#define MPIDI_OFI_ENABLE_RUNTIME_CHECKS     MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_DATA               MPIDI_OFI_ENABLE_DATA_BGQ
#define MPIDI_OFI_ENABLE_AV_TABLE           MPIDI_OFI_ENABLE_AV_TABLE_BGQ
#define MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS_BGQ
#define MPIDI_OFI_MAX_ENDPOINTS             MPIDI_OFI_MAX_ENDPOINTS_BGQ
#define MPIDI_OFI_MAX_ENDPOINTS_BITS        MPIDI_OFI_MAX_ENDPOINTS_BITS_BGQ
#define MPIDI_OFI_ENABLE_STX_RMA            MPIDI_OFI_ENABLE_STX_RMA_BGQ
#define MPIDI_OFI_ENABLE_MR_SCALABLE        MPIDI_OFI_ENABLE_MR_SCALABLE_BGQ
#define MPIDI_OFI_ENABLE_TAGGED             MPIDI_OFI_ENABLE_TAGGED_BGQ
#define MPIDI_OFI_ENABLE_AM                 MPIDI_OFI_ENABLE_AM_BGQ
#define MPIDI_OFI_ENABLE_RMA                MPIDI_OFI_ENABLE_RMA_BGQ
#define MPIDI_OFI_ENABLE_ATOMICS            MPIDI_OFI_ENABLE_ATOMICS_BGQ
#define MPIDI_OFI_FETCH_ATOMIC_IOVECS       MPIDI_OFI_FETCH_ATOMIC_IOVECS_BGQ
#define MPIDI_OFI_CONTEXT_MASK_CAPSET       MPIDI_OFI_CONTEXT_MASK_BGQ
#define MPIDI_OFI_SOURCE_MASK_CAPSET        MPIDI_OFI_SOURCE_MASK_BGQ
#define MPIDI_OFI_TAG_MASK_CAPSET           MPIDI_OFI_TAG_MASK_BGQ
#define MPIDI_OFI_CONTEXT_BITS              MPIDI_OFI_CONTEXT_BITS_BGQ
#define MPIDI_OFI_SOURCE_BITS               MPIDI_OFI_SOURCE_BITS_BGQ
#define MPIDI_OFI_TAG_BITS                  MPIDI_OFI_TAG_BITS_BGQ
#endif

#define MPIDI_OFI_ENABLE_DATA_VERBS               MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_AV_TABLE_VERBS           MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS_VERBS MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_STX_RMA_VERBS            MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_MR_SCALABLE_VERBS        MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_TAGGED_VERBS             MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_AM_VERBS                 MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_RMA_VERBS                MPIDI_OFI_ON
#define MPIDI_OFI_ENABLE_ATOMICS_VERBS            MPIDI_OFI_OFF
#define MPIDI_OFI_MAX_ENDPOINTS_VERBS             MPIDI_OFI_MAX_ENDPOINTS_REGULAR
#define MPIDI_OFI_MAX_ENDPOINTS_BITS_VERBS        MPIDI_OFI_MAX_ENDPOINTS_BITS_REGULAR
#define MPIDI_OFI_CONTEXT_MASK_VERBS              (0x0FFFF00000000000ULL)
#define MPIDI_OFI_SOURCE_MASK_VERBS               (0x00000FFFFFF00000ULL) /* Verbs does not support immediate data
                                                                           * so this field needs to be available */
#define MPIDI_OFI_TAG_MASK_VERBS                  (0x00000000000FFFFFULL)
#define MPIDI_OFI_CONTEXT_BITS_VERBS              (16)
#define MPIDI_OFI_SOURCE_BITS_VERBS               (24)
#define MPIDI_OFI_TAG_BITS_VERBS                  (20)

#ifdef MPIDI_CH4_OFI_USE_SET_VERBS
#define MPIDI_OFI_ENABLE_RUNTIME_CHECKS     MPIDI_OFI_OFF
#define MPIDI_OFI_ENABLE_DATA               MPIDI_OFI_ENABLE_DATA_VERBS
#define MPIDI_OFI_ENABLE_AV_TABLE           MPIDI_OFI_ENABLE_AV_TABLE_VERBS
#define MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS_VERBS
#define MPIDI_OFI_MAX_ENDPOINTS             MPIDI_OFI_MAX_ENDPOINTS_VERBS
#define MPIDI_OFI_MAX_ENDPOINTS_BITS        MPIDI_OFI_MAX_ENDPOINTS_BITS_VERBS
#define MPIDI_OFI_ENABLE_STX_RMA            MPIDI_OFI_ENABLE_STX_RMA_VERBS
#define MPIDI_OFI_ENABLE_MR_SCALABLE        MPIDI_OFI_ENABLE_MR_SCALABLE_VERBS
#define MPIDI_OFI_ENABLE_TAGGED             MPIDI_OFI_ENABLE_TAGGED_VERBS
#define MPIDI_OFI_ENABLE_AM                 MPIDI_OFI_ENABLE_AM_VERBS
#define MPIDI_OFI_ENABLE_RMA                MPIDI_OFI_ENABLE_RMA_VERBS
#define MPIDI_OFI_ENABLE_ATOMICS            MPIDI_OFI_ENABLE_ATOMICS_VERBS
#define MPIDI_OFI_FETCH_ATOMIC_IOVECS       MPIDI_OFI_FETCH_ATOMIC_IOVECS_VERBS
#define MPIDI_OFI_CONTEXT_MASK_CAPSET       MPIDI_OFI_CONTEXT_MASK_VERBS
#define MPIDI_OFI_SOURCE_MASK_CAPSET        MPIDI_OFI_SOURCE_MASK_VERBS
#define MPIDI_OFI_TAG_MASK_CAPSET           MPIDI_OFI_TAG_MASK_VERBS
#define MPIDI_OFI_CONTEXT_BITS              MPIDI_OFI_CONTEXT_BITS_VERBS
#define MPIDI_OFI_SOURCE_BITS               MPIDI_OFI_SOURCE_BITS_VERBS
#define MPIDI_OFI_TAG_BITS                  MPIDI_OFI_TAG_BITS_VERBS
#endif

#ifdef MPIDI_CH4_OFI_USE_SET_RUNTIME
#define MPIDI_OFI_ENABLE_RUNTIME_CHECKS     1
#define MPIDI_OFI_ENABLE_DATA               MPIDI_Global.settings.enable_data
#define MPIDI_OFI_ENABLE_AV_TABLE           MPIDI_Global.settings.enable_av_table
#define MPIDI_OFI_ENABLE_SCALABLE_ENDPOINTS MPIDI_Global.settings.enable_scalable_endpoints
#define MPIDI_OFI_MAX_ENDPOINTS             MPIDI_Global.settings.max_endpoints
#define MPIDI_OFI_MAX_ENDPOINTS_BITS        MPIDI_Global.settings.max_endpoints_bits
#define MPIDI_OFI_ENABLE_STX_RMA            MPIDI_Global.settings.enable_stx_rma
#define MPIDI_OFI_ENABLE_MR_SCALABLE        MPIDI_Global.settings.enable_mr_scalable
#define MPIDI_OFI_ENABLE_TAGGED             MPIDI_Global.settings.enable_tagged
#define MPIDI_OFI_ENABLE_AM                 MPIDI_Global.settings.enable_am
#define MPIDI_OFI_ENABLE_RMA                MPIDI_Global.settings.enable_rma
#define MPIDI_OFI_ENABLE_ATOMICS            MPIDI_Global.settings.enable_atomics
#define MPIDI_OFI_FETCH_ATOMIC_IOVECS       MPIDI_Global.settings.fetch_atomic_iovecs
#define MPIDI_OFI_CONTEXT_BITS              MPIDI_Global.settings.context_bits
#define MPIDI_OFI_SOURCE_BITS               MPIDI_Global.settings.source_bits
#define MPIDI_OFI_TAG_BITS                  MPIDI_Global.settings.tag_bits
#endif

#endif
