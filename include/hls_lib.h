#include <ap_int.h>
#include <hls_stream.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <ap_axi_sdata.h>

using namespace hls;

typedef ap_uint<1> uint1;
typedef ap_uint<2> uint2;
typedef ap_uint<4> uint4;
typedef ap_uint<3> uint3;
typedef ap_uint<8> uint8;
typedef ap_uint<9> uint9;
typedef ap_uint<11> uint11;
typedef ap_uint<12> uint12;
typedef ap_uint<13> uint13;
typedef ap_uint<16> uint16;
typedef ap_uint<18> uint18;
typedef ap_uint<22> uint22;
typedef ap_uint<23> uint23;
typedef ap_uint<24> uint24;
typedef ap_uint<32> uint32;
typedef ap_uint<64> uint64;
typedef ap_uint<104> uint104;
typedef ap_uint<112> uint112;
typedef ap_uint<128> uint128;

typedef ap_axis<128, 0, 0, 0> uaxis128_t;
typedef ap_axis<64, 0, 0, 0> uaxis64_t;
typedef ap_axis<32, 0, 0, 0> uaxis32_t;
typedef ap_axis<16, 0, 0, 0> uaxis16_t;
typedef ap_axis<8, 0, 0, 0> uaxis8_t;


struct uaxis8_v16_t {
	ap_uint<8> data;
	ap_uint<1> keep;
	ap_uint<1> strb;
	ap_uint<1> last;
};

struct uaxis16_v16_t {
	ap_uint<16> data;
	ap_uint<2> keep;
	ap_uint<2> strb;
	ap_uint<1> last;
};

struct uaxis32_v16_t {
	ap_uint<32> data;
	ap_uint<4> keep;
	ap_uint<4> strb;
	ap_uint<1> last;
};

struct uaxis64_v16_t {
	ap_uint<64> data;
	ap_uint<8> keep;
	ap_uint<8> strb;
	ap_uint<1> last;
};

struct uaxis128_v16_t {
	ap_uint<128> data;
	ap_uint<16> keep;
	ap_uint<16> strb;
	ap_uint<1> last;
};

#define PROCESS_1 1
#define PROCESS_2 2
#define PROCESS_3 3
#define PROCESS_4 4

#define FLUSH_PAYLOAD_SIZE_IN_WORD 8;
#define FLUSH_PAYLOAD_SIZE_IN_BYTE 8*FLUSH_PAYLOAD_SIZE_IN_WORD;

#define WR_MODE 2
#define RD_MODE 3

#define PSC_OP_INCR 2
#define PSC_OP_DECR 3

#define XID_DEPTH 512

#define PSCQ_FIFO_OCCUPANCY 4096

#define FLUSHQ_FIFO_OCCUPANCY 4096

//headers belong for the bram_arbiter_2x1_64 module to specify the depth of the BRAM used
#define BRAM_DEPTH 8192


#define X_FIFO_OCCUPANCY 4096
//headers belong to the   
#define XSCHEDULE_FIFO_OCCUPANCY 512
#define XDECREASE_FIFO_OCCUPANCY 512
#define XDESTROY_FIFO_OCCUPANCY 512
#define XPOSTORE_FIFO_OCCUPANCY 512
#define XSUBSCRIBE_FIFO_OCCUPANCY 512
#define XPUBLISH_FIFO_OCCUPANCY 512

#define XSCHEDULE_OP_CODE 5
#define XDECREASE_OP_CODE 15
#define XDESTROY_OP_CODE 6
#define XSUBSCRIBE_OP_CODE 16
#define XPOSTORE_OP_CODE 14
#define XPUBLISH_OP_CODE 17
#define XGUARD_OP_CODE 20

//headers belong to the xsmll_xdecrease_v5 module
#define SC_UPDATE_FIFO_OCCUPANCY 4090

//headers belong to xsmll_xffp_status_v1 module
#define XFFP_FIFO_DEPTH_SIZE  131072

// headers belong to xsmll_xffmu_v1 module
#define  GM_THRESHOLD_RES 16

// Definition of sub XSMLL message types-----------------------
#define XSMLL_RDMA_MERGE_MSG 0b0101

#define PSC_UPDATE_INCR 2
#define PSC_UPDATE_DECR 3

// Constants used in the Load Balancing Module ---------------------------------
// Definition of main XSMLL message types ---------------------
#define XSMLL_NIC_RAW_NEIGHBOR 0b10
#define XSMLL_NIC_RDMA 0b01
// Definition of sub XSMLL message types-----------------------
#define XSMLL_LB_JOB_MSG 0b1001
#define XSMLL_LB_RESPONSE_MSG 0b1010
#define XSMLL_RDMA_WRITE_MERGE_MSG 0b0101
#define XSMLL_RDMA_WRITE_MSG 0b0111
#define LB_JOB_REQ 0xAA
#define LB_JOB_ACC 0x55
#define LB_JOB_REJ 0xA5
#define LB_RES_ACK 0x77
#define LB_RES_NACK 0x99
#define LB_JOB_MIG_ALMOST_EMPTY_THRESHOLD 4
//------------------------------------------------------------------------------
#define NIC_TYPE_RAW_NEIGHBOUR          2
#define NIC_TYPE_RAW_DATA               3
#define NIC_TYPE_RDMA_DATA              5
#define NIC_TYPE_RDMA_WRITE_MERGE       5

#define RAW_MAX_OCCUPANCY 255
#define DMA_MAX_OCCUPANCY 255

// headers from the xsm.h
#define FP_OFF_SZ		          8
#define _X_OFF(_x)             ((uint64)(_x)&((1ULL<<0)))
#define _X_OFF_FP(_x)          ((uint64)(_x)<<FP_OFF_SZ | 0)
#define _X_GET_OFF_FIELD(_x)   ((uint64)(_x)&((1ULL<<FP_OFF_SZ)-1))
#define _X_GET_VFP(_x)	       ((uint64)(_x)>>FP_OFF_SZ)

