/*
 *    Copyright (c) 2018, The OpenThread Authors.
 *    All rights reserved.
 *
 *    Redistribution and use in source and binary forms, with or without
 *    modification, are permitted provided that the following conditions are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *    3. Neither the name of the copyright holder nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 *    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file implements general thread device required Spinel interface to the OpenThread stack.
 */

#include "ncp_base.hpp"

namespace ot {
namespace Ncp {

constexpr bool NcpBase::AreHandlerEntriesSorted(const HandlerEntry *aHandlerEntries, size_t aSize)
{
    return aSize < 2 ? true
                     : ((aHandlerEntries[aSize - 1].mKey > aHandlerEntries[aSize - 2].mKey) &&
                        AreHandlerEntriesSorted(aHandlerEntries, aSize - 1));
}

NcpBase::PropertyHandler NcpBase::FindGetPropertyHandler(spinel_prop_key_t aKey)
{
#define OT_NCP_GET_HANDLER_ENTRY(aPropertyName)                   \
    {                                                             \
        aPropertyName, &NcpBase::HandlePropertyGet<aPropertyName> \
    }

    constexpr static HandlerEntry sHandlerEntries[] = {
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_LAST_STATUS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_PROTOCOL_VERSION),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NCP_VERSION),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_INTERFACE_TYPE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_VENDOR_ID),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CAPS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_INTERFACE_COUNT),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_POWER_STATE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_HWADDR),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_LOCK),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_HOST_POWER_STATE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MCU_POWER_STATE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_PHY_ENABLED),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_PHY_CHAN),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_PHY_CHAN_SUPPORTED),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_PHY_FREQ),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_PHY_CCA_THRESHOLD),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_PHY_TX_POWER),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_PHY_RSSI),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_PHY_RX_SENSITIVITY),
#if OPENTHREAD_MTD || OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_PHY_PCAP_ENABLED),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_PHY_CHAN_PREFERRED),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_PHY_FEM_LNA_GAIN),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_PHY_REGION_CODE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_SCAN_STATE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_SCAN_MASK),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_SCAN_PERIOD),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_15_4_LADDR),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_15_4_SADDR),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_15_4_PANID),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_RAW_STREAM_ENABLED),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_PROMISCUOUS_MODE),
#if OPENTHREAD_MTD || OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_DATA_POLL_PERIOD),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NET_SAVED),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NET_IF_UP),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NET_STACK_UP),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NET_ROLE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NET_NETWORK_NAME),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NET_XPANID),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NET_MASTER_KEY),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NET_KEY_SEQUENCE_COUNTER),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NET_PARTITION_ID),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NET_REQUIRE_JOIN_EXISTING),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NET_KEY_SWITCH_GUARDTIME),
#if OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NET_PSKC),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_LEADER_ADDR),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_PARENT),
#if OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CHILD_TABLE),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_LEADER_RID),
#if OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_LEADER_WEIGHT),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_LOCAL_LEADER_WEIGHT),
#endif
#if OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_NETWORK_DATA),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_NETWORK_DATA_VERSION),
#if OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_STABLE_NETWORK_DATA),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_STABLE_NETWORK_DATA_VERSION),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ON_MESH_NETS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_OFF_MESH_ROUTES),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ASSISTING_PORTS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ALLOW_LOCAL_NET_DATA_CHANGE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_MODE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_IPV6_LL_ADDR),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_IPV6_ML_ADDR),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_IPV6_ML_PREFIX),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_IPV6_ADDRESS_TABLE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_IPV6_ROUTE_TABLE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_IPV6_ICMP_PING_OFFLOAD),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_IPV6_MULTICAST_ADDRESS_TABLE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_IPV6_ICMP_PING_OFFLOAD_MODE),
#if OPENTHREAD_CONFIG_JOINER_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_JOINER_STATE),
#endif
#if OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_COMMISSIONER_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_COMMISSIONER_STATE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_COMMISSIONER_JOINERS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_COMMISSIONER_PROVISIONING_URL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_COMMISSIONER_SESSION_ID),
#endif
#endif // OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_JOINER_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_JOINER_DISCERNER),
#endif
#if OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_SERVER_ALLOW_LOCAL_DATA_CHANGE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_SERVER_SERVICES),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_SERVER_LEADER_SERVICES),
#endif // OPENTHREAD_MTD || OPENTHREAD_FTD
#if OPENTHREAD_RADIO
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_RCP_API_VERSION),
#endif
#if OPENTHREAD_MTD || OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_PKT_TOTAL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_PKT_ACK_REQ),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_PKT_ACKED),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_PKT_NO_ACK_REQ),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_PKT_DATA),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_PKT_DATA_POLL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_PKT_BEACON),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_PKT_BEACON_REQ),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_PKT_OTHER),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_PKT_RETRY),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_ERR_CCA),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_PKT_UNICAST),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_PKT_BROADCAST),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_ERR_ABORT),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_PKT_TOTAL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_PKT_DATA),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_PKT_DATA_POLL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_PKT_BEACON),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_PKT_BEACON_REQ),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_PKT_OTHER),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_PKT_FILT_WL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_PKT_FILT_DA),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_ERR_EMPTY),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_ERR_UKWN_NBR),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_ERR_NVLD_SADDR),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_ERR_SECURITY),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_ERR_BAD_FCS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_ERR_OTHER),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_PKT_DUP),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_PKT_UNICAST),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_PKT_BROADCAST),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_IP_SEC_TOTAL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_IP_INSEC_TOTAL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_IP_DROPPED),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_IP_SEC_TOTAL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_IP_INSEC_TOTAL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_IP_DROPPED),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_TX_SPINEL_TOTAL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_SPINEL_TOTAL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RX_SPINEL_ERR),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_IP_TX_SUCCESS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_IP_RX_SUCCESS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_IP_TX_FAILURE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_IP_RX_FAILURE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MSG_BUFFER_COUNTERS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_ALL_MAC_COUNTERS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_MLE_COUNTERS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_ALL_IP_COUNTERS),
#if OPENTHREAD_CONFIG_MAC_RETRY_SUCCESS_HISTOGRAM_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CNTR_MAC_RETRY_HISTOGRAM),
#endif
#endif // OPENTHREAD_MTD || OPENTHREAD_FTD
#if OPENTHREAD_RADIO || OPENTHREAD_CONFIG_LINK_RAW_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_RCP_TIMESTAMP),
#endif
#if OPENTHREAD_MTD || OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_UNSOL_UPDATE_FILTER),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_UNSOL_UPDATE_LIST),
#if OPENTHREAD_CONFIG_JAM_DETECTION_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_JAM_DETECT_ENABLE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_JAM_DETECTED),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_JAM_DETECT_RSSI_THRESHOLD),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_JAM_DETECT_WINDOW),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_JAM_DETECT_BUSY),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_JAM_DETECT_HISTORY_BITMAP),
#endif
#if OPENTHREAD_CONFIG_CHANNEL_MONITOR_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MONITOR_SAMPLE_INTERVAL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MONITOR_RSSI_THRESHOLD),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MONITOR_SAMPLE_WINDOW),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MONITOR_SAMPLE_COUNT),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MONITOR_CHANNEL_OCCUPANCY),
#endif
#endif // OPENTHREAD_MTD || OPENTHREAD_FTD
#if OPENTHREAD_RADIO || OPENTHREAD_CONFIG_LINK_RAW_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_RADIO_CAPS),
#endif
#if OPENTHREAD_CONFIG_PLATFORM_RADIO_COEX_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_RADIO_COEX_METRICS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_RADIO_COEX_ENABLE),
#endif
#if OPENTHREAD_MTD || OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_MAC_FILTER_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_ALLOWLIST),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_ALLOWLIST_ENABLED),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_EXTENDED_ADDR),
#endif
#endif // OPENTHREAD_MTD || OPENTHREAD_FTD
#if OPENTHREAD_RADIO || OPENTHREAD_CONFIG_LINK_RAW_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_SRC_MATCH_ENABLED),
#endif
#if OPENTHREAD_MTD || OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_MAC_FILTER_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_DENYLIST),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_DENYLIST_ENABLED),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_FIXED_RSS),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_CCA_FAILURE_RATE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_MAX_RETRY_NUMBER_DIRECT),
#if OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_MAC_MAX_RETRY_NUMBER_INDIRECT),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CHILD_TIMEOUT),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_RLOC16),
#if OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ROUTER_UPGRADE_THRESHOLD),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CONTEXT_REUSE_DELAY),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_NETWORK_ID_TIMEOUT),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_RLOC16_DEBUG_PASSTHRU),
#if OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ROUTER_ROLE_ENABLED),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ROUTER_DOWNGRADE_THRESHOLD),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ROUTER_SELECTION_JITTER),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_PREFERRED_ROUTER_ID),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_NEIGHBOR_TABLE),
#if OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CHILD_COUNT_MAX),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_LEADER_NETWORK_DATA),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_STABLE_LEADER_NETWORK_DATA),
#if OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_COMMISSIONER_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_COMMISSIONER_ENABLED),
#endif
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_DISCOVERY_SCAN_JOINER_FLAG),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_DISCOVERY_SCAN_ENABLE_FILTERING),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_DISCOVERY_SCAN_PANID),
#if OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_MLE_STEERING_DATA_SET_OOB_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_STEERING_DATA),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ROUTER_TABLE),
#endif // OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ACTIVE_DATASET),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_PENDING_DATASET),
#if OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CHILD_TABLE_ADDRESSES),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_NEIGHBOR_TABLE_ERROR_RATES),
#if OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ADDRESS_CACHE_TABLE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_NEW_DATASET),
#endif
#if OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CSL_PERIOD),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CSL_TIMEOUT),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CSL_CHANNEL),
#endif
#if OPENTHREAD_FTD
#if (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_DOMAIN_NAME),
#endif
#if OPENTHREAD_CONFIG_DUA_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_DUA_ID),
#endif
#endif // OPENTHREAD_FTD
#if (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_BACKBONE_ROUTER_PRIMARY),
#endif
#if OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_BACKBONE_ROUTER_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_BACKBONE_ROUTER_LOCAL_STATE),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_BACKBONE_ROUTER_LOCAL_CONFIG),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_BACKBONE_ROUTER_LOCAL_REGISTRATION_JITTER),
#endif
#if OPENTHREAD_CONFIG_CHANNEL_MANAGER_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_NEW_CHANNEL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_DELAY),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_SUPPORTED_CHANNELS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_FAVORED_CHANNELS),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_CHANNEL_SELECT),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_AUTO_SELECT_ENABLED),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_AUTO_SELECT_INTERVAL),
#endif
#if OPENTHREAD_CONFIG_TIME_SYNC_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_THREAD_NETWORK_TIME),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_TIME_SYNC_PERIOD),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_TIME_SYNC_XTAL_THRESHOLD),
#endif
#if OPENTHREAD_CONFIG_CHILD_SUPERVISION_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHILD_SUPERVISION_INTERVAL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_CHILD_SUPERVISION_CHECK_TIMEOUT),
#endif
#endif // OPENTHREAD_FTD
#if OPENTHREAD_PLATFORM_POSIX
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_RCP_VERSION),
#endif
#if OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_SLAAC_ENABLED),
#endif
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_SUPPORTED_RADIO_LINKS),
#if OPENTHREAD_CONFIG_MULTI_RADIO
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NEIGHBOR_TABLE_MULTI_RADIO_INFO),
#endif
#if OPENTHREAD_CONFIG_SRP_CLIENT_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_LEASE_INTERVAL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_KEY_LEASE_INTERVAL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_HOST_INFO),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_HOST_NAME),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_HOST_ADDRESSES),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_SERVICES),
#endif

#if OPENTHREAD_CONFIG_LEGACY_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NEST_LEGACY_ULA_PREFIX),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_NEST_LEGACY_LAST_NODE_JOINED),
#endif
#endif // OPENTHREAD_MTD || OPENTHREAD_FTD
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_DEBUG_TEST_ASSERT),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_DEBUG_NCP_LOG_LEVEL),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_DEBUG_TEST_WATCHDOG),
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_DEBUG_LOG_TIMESTAMP_BASE),
#if OPENTHREAD_CONFIG_RADIO_LINK_TREL_ENABLE
        OT_NCP_GET_HANDLER_ENTRY(SPINEL_PROP_DEBUG_TREL_TEST_MODE_ENABLE),
#endif
    };

#undef OT_NCP_GET_HANDLER_ENTRY

    static_assert(AreHandlerEntriesSorted(sHandlerEntries, OT_ARRAY_LENGTH(sHandlerEntries)),
                  "NCP property getter entries not sorted!");

    return FindPropertyHandler(sHandlerEntries, OT_ARRAY_LENGTH(sHandlerEntries), aKey);
}

NcpBase::PropertyHandler NcpBase::FindSetPropertyHandler(spinel_prop_key_t aKey)
{
#define OT_NCP_SET_HANDLER_ENTRY(aPropertyName)                   \
    {                                                             \
        aPropertyName, &NcpBase::HandlePropertySet<aPropertyName> \
    }

    constexpr static HandlerEntry sHandlerEntries[] = {
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_POWER_STATE),
#if OPENTHREAD_CONFIG_NCP_ENABLE_MCU_POWER_STATE_CONTROL
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MCU_POWER_STATE),
#endif
#if OPENTHREAD_RADIO || OPENTHREAD_CONFIG_LINK_RAW_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_PHY_ENABLED),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_PHY_CHAN),
#if OPENTHREAD_MTD || OPENTHREAD_FTD
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_PHY_CHAN_SUPPORTED),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_PHY_CCA_THRESHOLD),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_PHY_TX_POWER),
#if OPENTHREAD_MTD || OPENTHREAD_FTD
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_PHY_PCAP_ENABLED),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_PHY_FEM_LNA_GAIN),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_PHY_CHAN_MAX_POWER),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_PHY_REGION_CODE),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_SCAN_STATE),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_SCAN_MASK),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_SCAN_PERIOD),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_15_4_LADDR),
#if OPENTHREAD_RADIO || OPENTHREAD_CONFIG_LINK_RAW_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_15_4_SADDR),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_15_4_PANID),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_RAW_STREAM_ENABLED),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_PROMISCUOUS_MODE),
#if OPENTHREAD_MTD || OPENTHREAD_FTD
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_DATA_POLL_PERIOD),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_NET_IF_UP),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_NET_STACK_UP),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_NET_ROLE),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_NET_NETWORK_NAME),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_NET_XPANID),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_NET_MASTER_KEY),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_NET_KEY_SEQUENCE_COUNTER),
#if OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_REFERENCE_DEVICE_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_NET_PARTITION_ID),
#endif
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_NET_REQUIRE_JOIN_EXISTING),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_NET_KEY_SWITCH_GUARDTIME),
#if OPENTHREAD_FTD
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_NET_PSKC),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_LOCAL_LEADER_WEIGHT),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ASSISTING_PORTS),
#if OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ALLOW_LOCAL_NET_DATA_CHANGE),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_MODE),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_IPV6_ML_PREFIX),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_IPV6_ICMP_PING_OFFLOAD),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_IPV6_ICMP_PING_OFFLOAD_MODE),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_STREAM_NET),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_STREAM_NET_INSECURE),
#if OPENTHREAD_CONFIG_JOINER_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_JOINER_COMMISSIONING),
#endif
#if OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_COMMISSIONER_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_COMMISSIONER_STATE),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_COMMISSIONER_PROVISIONING_URL),
#endif
#endif // OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_JOINER_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_JOINER_DISCERNER),
#endif
#if OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_SERVER_ALLOW_LOCAL_DATA_CHANGE),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CNTR_RESET),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CNTR_ALL_MAC_COUNTERS),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CNTR_MLE_COUNTERS),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CNTR_ALL_IP_COUNTERS),
#if OPENTHREAD_CONFIG_MAC_RETRY_SUCCESS_HISTOGRAM_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CNTR_MAC_RETRY_HISTOGRAM),
#endif
#endif // OPENTHREAD_MTD || OPENTHREAD_FTD
#if OPENTHREAD_RADIO || OPENTHREAD_CONFIG_LINK_RAW_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_RCP_MAC_KEY),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_RCP_MAC_FRAME_COUNTER),
#endif
#if OPENTHREAD_MTD || OPENTHREAD_FTD
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_UNSOL_UPDATE_FILTER),
#if OPENTHREAD_CONFIG_JAM_DETECTION_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_JAM_DETECT_ENABLE),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_JAM_DETECT_RSSI_THRESHOLD),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_JAM_DETECT_WINDOW),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_JAM_DETECT_BUSY),
#endif
#endif // OPENTHREAD_MTD || OPENTHREAD_FTD

#if OPENTHREAD_CONFIG_PLATFORM_RADIO_COEX_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_RADIO_COEX_ENABLE),
#endif

#if OPENTHREAD_MTD || OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_MAC_FILTER_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_ALLOWLIST),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_ALLOWLIST_ENABLED),
#endif
#endif // OPENTHREAD_MTD || OPENTHREAD_FTD

#if OPENTHREAD_RADIO || OPENTHREAD_CONFIG_LINK_RAW_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_SRC_MATCH_ENABLED),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_SRC_MATCH_SHORT_ADDRESSES),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_SRC_MATCH_EXTENDED_ADDRESSES),
#endif

#if OPENTHREAD_MTD || OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_MAC_FILTER_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_DENYLIST),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_DENYLIST_ENABLED),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_FIXED_RSS),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_MAX_RETRY_NUMBER_DIRECT),
#if OPENTHREAD_FTD
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MAC_MAX_RETRY_NUMBER_INDIRECT),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CHILD_TIMEOUT),
#if OPENTHREAD_FTD
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ROUTER_UPGRADE_THRESHOLD),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CONTEXT_REUSE_DELAY),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_NETWORK_ID_TIMEOUT),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_RLOC16_DEBUG_PASSTHRU),
#if OPENTHREAD_FTD
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ROUTER_ROLE_ENABLED),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ROUTER_DOWNGRADE_THRESHOLD),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ROUTER_SELECTION_JITTER),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_PREFERRED_ROUTER_ID),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CHILD_COUNT_MAX),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_DISCOVERY_SCAN_JOINER_FLAG),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_DISCOVERY_SCAN_ENABLE_FILTERING),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_DISCOVERY_SCAN_PANID),
#if OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_MLE_STEERING_DATA_SET_OOB_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_STEERING_DATA),
#endif
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_ACTIVE_DATASET),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_PENDING_DATASET),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_MGMT_SET_ACTIVE_DATASET),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_MGMT_SET_PENDING_DATASET),
#if OPENTHREAD_CONFIG_UDP_FORWARD_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_UDP_FORWARD_STREAM),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_MGMT_GET_ACTIVE_DATASET),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_MGMT_GET_PENDING_DATASET),
#if OPENTHREAD_CONFIG_MAC_CSL_RECEIVER_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CSL_PERIOD),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CSL_TIMEOUT),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_CSL_CHANNEL),
#endif
#if OPENTHREAD_FTD
#if (OPENTHREAD_CONFIG_THREAD_VERSION >= OT_THREAD_VERSION_1_2)
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_DOMAIN_NAME),
#endif
#if OPENTHREAD_CONFIG_TMF_PROXY_MLR_ENABLE && OPENTHREAD_CONFIG_COMMISSIONER_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_MLR_REQUEST),
#endif
#if OPENTHREAD_CONFIG_DUA_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_DUA_ID),
#endif
#if OPENTHREAD_CONFIG_BACKBONE_ROUTER_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_BACKBONE_ROUTER_LOCAL_STATE),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_BACKBONE_ROUTER_LOCAL_CONFIG),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_BACKBONE_ROUTER_LOCAL_REGISTER),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_THREAD_BACKBONE_ROUTER_LOCAL_REGISTRATION_JITTER),
#endif
#if OPENTHREAD_CONFIG_COMMISSIONER_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_COMMISSIONER_ANNOUNCE_BEGIN),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_COMMISSIONER_ENERGY_SCAN),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_COMMISSIONER_PAN_ID_QUERY),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_COMMISSIONER_MGMT_GET),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_COMMISSIONER_MGMT_SET),
#endif
#if OPENTHREAD_CONFIG_CHANNEL_MANAGER_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_NEW_CHANNEL),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_DELAY),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_SUPPORTED_CHANNELS),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_FAVORED_CHANNELS),
#if OPENTHREAD_CONFIG_CHANNEL_MONITOR_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_CHANNEL_SELECT),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_AUTO_SELECT_ENABLED),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CHANNEL_MANAGER_AUTO_SELECT_INTERVAL),
#endif // OPENTHREAD_CONFIG_CHANNEL_MANAGER_ENABLE
#if OPENTHREAD_CONFIG_TIME_SYNC_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_TIME_SYNC_PERIOD),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_TIME_SYNC_XTAL_THRESHOLD),
#endif
#if OPENTHREAD_CONFIG_CHILD_SUPERVISION_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CHILD_SUPERVISION_INTERVAL),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_CHILD_SUPERVISION_CHECK_TIMEOUT),
#endif
#endif // OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_IP6_SLAAC_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_SLAAC_ENABLED),
#endif
#if OPENTHREAD_CONFIG_SRP_CLIENT_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_START),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_LEASE_INTERVAL),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_KEY_LEASE_INTERVAL),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_HOST_NAME),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_HOST_ADDRESSES),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_HOST_SERVICES_REMOVE),
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_HOST_SERVICES_CLEAR),
#endif
#if OPENTHREAD_CONFIG_LEGACY_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_NEST_LEGACY_ULA_PREFIX),
#endif
#endif // OPENTHREAD_MTD || OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_LOG_LEVEL_DYNAMIC_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_DEBUG_NCP_LOG_LEVEL),
#endif
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_DEBUG_LOG_TIMESTAMP_BASE),
#if OPENTHREAD_CONFIG_RADIO_LINK_TREL_ENABLE
        OT_NCP_SET_HANDLER_ENTRY(SPINEL_PROP_DEBUG_TREL_TEST_MODE_ENABLE),
#endif
    };

#undef OT_NCP_SET_HANDLER_ENTRY

    static_assert(AreHandlerEntriesSorted(sHandlerEntries, OT_ARRAY_LENGTH(sHandlerEntries)),
                  "NCP property setter entries not sorted!");

    return FindPropertyHandler(sHandlerEntries, OT_ARRAY_LENGTH(sHandlerEntries), aKey);
}

NcpBase::PropertyHandler NcpBase::FindInsertPropertyHandler(spinel_prop_key_t aKey)
{
#define OT_NCP_INSERT_HANDLER_ENTRY(aPropertyName)                   \
    {                                                                \
        aPropertyName, &NcpBase::HandlePropertyInsert<aPropertyName> \
    }

    constexpr static HandlerEntry sHandlerEntries[] = {
#if OPENTHREAD_MTD || OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_THREAD_ON_MESH_NETS),
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_THREAD_OFF_MESH_ROUTES),
#endif
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_THREAD_ASSISTING_PORTS),
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_IPV6_ADDRESS_TABLE),
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_IPV6_MULTICAST_ADDRESS_TABLE),
#if OPENTHREAD_FTD && OPENTHREAD_CONFIG_COMMISSIONER_ENABLE
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_COMMISSIONER_JOINERS),
#endif
#if OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_SERVER_SERVICES),
#endif
#endif // #if OPENTHREAD_MTD || OPENTHREAD_FTD
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_UNSOL_UPDATE_FILTER),
#if (OPENTHREAD_MTD || OPENTHREAD_FTD) && OPENTHREAD_CONFIG_MAC_FILTER_ENABLE
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_MAC_ALLOWLIST),
#endif
#if OPENTHREAD_RADIO || OPENTHREAD_CONFIG_LINK_RAW_ENABLE
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_MAC_SRC_MATCH_SHORT_ADDRESSES),
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_MAC_SRC_MATCH_EXTENDED_ADDRESSES),
#endif
#if (OPENTHREAD_MTD || OPENTHREAD_FTD) && OPENTHREAD_CONFIG_MAC_FILTER_ENABLE
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_MAC_DENYLIST),
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_MAC_FIXED_RSS),
#endif
#if OPENTHREAD_FTD && OPENTHREAD_CONFIG_COMMISSIONER_ENABLE
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_THREAD_JOINERS),
#endif
#if OPENTHREAD_FTD || OPENTHREAD_MTD
#if OPENTHREAD_CONFIG_SRP_CLIENT_ENABLE
        OT_NCP_INSERT_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_SERVICES),
#endif
#endif
    };

#undef OT_NCP_INSERT_HANDLER_ENTRY

    static_assert(AreHandlerEntriesSorted(sHandlerEntries, OT_ARRAY_LENGTH(sHandlerEntries)),
                  "NCP property setter entries not sorted!");

    return FindPropertyHandler(sHandlerEntries, OT_ARRAY_LENGTH(sHandlerEntries), aKey);
}

NcpBase::PropertyHandler NcpBase::FindRemovePropertyHandler(spinel_prop_key_t aKey)
{
#define OT_NCP_REMOVE_HANDLER_ENTRY(aPropertyName)                   \
    {                                                                \
        aPropertyName, &NcpBase::HandlePropertyRemove<aPropertyName> \
    }

    constexpr static HandlerEntry sHandlerEntries[] = {
#if OPENTHREAD_MTD || OPENTHREAD_FTD
#if OPENTHREAD_CONFIG_BORDER_ROUTER_ENABLE
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_THREAD_ON_MESH_NETS),
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_THREAD_OFF_MESH_ROUTES),
#endif
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_THREAD_ASSISTING_PORTS),
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_IPV6_ADDRESS_TABLE),
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_IPV6_MULTICAST_ADDRESS_TABLE),
#if OPENTHREAD_FTD && OPENTHREAD_CONFIG_COMMISSIONER_ENABLE
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_MESHCOP_COMMISSIONER_JOINERS),
#endif
#if OPENTHREAD_CONFIG_TMF_NETDATA_SERVICE_ENABLE
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_SERVER_SERVICES),
#endif
#endif // #if OPENTHREAD_MTD || OPENTHREAD_FTD
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_UNSOL_UPDATE_FILTER),
#if (OPENTHREAD_MTD || OPENTHREAD_FTD) && OPENTHREAD_CONFIG_MAC_FILTER_ENABLE
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_MAC_ALLOWLIST),
#endif
#if OPENTHREAD_RADIO || OPENTHREAD_CONFIG_LINK_RAW_ENABLE
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_MAC_SRC_MATCH_SHORT_ADDRESSES),
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_MAC_SRC_MATCH_EXTENDED_ADDRESSES),
#endif
#if (OPENTHREAD_MTD || OPENTHREAD_FTD) && OPENTHREAD_CONFIG_MAC_FILTER_ENABLE
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_MAC_DENYLIST),
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_MAC_FIXED_RSS),
#endif
#if OPENTHREAD_FTD
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_THREAD_ACTIVE_ROUTER_IDS),
#endif
#if OPENTHREAD_FTD || OPENTHREAD_MTD
#if OPENTHREAD_CONFIG_SRP_CLIENT_ENABLE
        OT_NCP_REMOVE_HANDLER_ENTRY(SPINEL_PROP_SRP_CLIENT_SERVICES),
#endif
#endif
    };

#undef OT_NCP_REMOVE_HANDLER_ENTRY

    static_assert(AreHandlerEntriesSorted(sHandlerEntries, OT_ARRAY_LENGTH(sHandlerEntries)),
                  "NCP property setter entries not sorted!");

    return FindPropertyHandler(sHandlerEntries, OT_ARRAY_LENGTH(sHandlerEntries), aKey);
}

NcpBase::PropertyHandler NcpBase::FindPropertyHandler(const HandlerEntry *aHandlerEntries,
                                                      size_t              aSize,
                                                      spinel_prop_key_t   aKey)
{
    size_t l = 0;

    OT_ASSERT(aSize > 0);

    for (size_t r = aSize - 1; l < r;)
    {
        size_t m = (l + r) / 2;

        if (aHandlerEntries[m].mKey < aKey)
        {
            l = m + 1;
        }
        else
        {
            r = m;
        }
    }

    return aHandlerEntries[l].mKey == aKey ? aHandlerEntries[l].mHandler : nullptr;
}

} // namespace Ncp
} // namespace ot
