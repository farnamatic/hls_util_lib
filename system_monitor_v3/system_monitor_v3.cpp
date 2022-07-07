/* COMPANY: 
 * AUTHOR: FARNAM KHALILI MAYBODI
 * DATE: 2020-10-17
 * DESCRIPTION: This module is connected to the PS through an AXI-Lite Slave port. The features of this module are
 * 1) 20 Free-running Counter, controlled from the PL (FRC-PL).
 * 2) 10 Free-running Counter, controlled from the PS (FRC-PS).
 * 3) 10 event capture for generating the interrupt and controlled from the PL. In SYSMON_CTLREG which is the control
 *  register of this IP, There are bits (B3 ... B0 ), which if are enabled, will assign each of event capture to
 *  its corresponding free-running counter  (FRC-PS), and will stop the counter. Note: that when these bits (B3 .. B0)
 *  are disable, the (FRC-PS) counters are only stopped from the PS.

 Please note that the counters will be invoked when the interval cycles are passed. So, after synthizing the use MUST check and control
 if the interval delay is equal to 1, then calcuate the time from the counting intervals. for example if the interval cycles is 1, the value 
 of each counter is equivalent to each clock cycle. Or, if the interval cycles is 2, the value of each counter represents for two clock periods on each counts. 

 */
#include "hls_lib.h"



void system_monitor_v3 (
		// ------------------------------------------------------------
		uint32 &reg_pl_max_value_1_o,
		uint32 &reg_pl_max_value_2_o,
		// ------------------------------------------------------------
		uint1 reg_ps_cnt_0_en_i,
		uint1 reg_ps_cnt_1_en_i,
		uint1 reg_ps_cnt_2_en_i,
		uint1 reg_ps_cnt_3_en_i,
		uint1 reg_ps_cnt_4_en_i,
		uint1 reg_ps_cnt_5_en_i,
		uint1 reg_ps_cnt_6_en_i,
		uint1 reg_ps_cnt_7_en_i,
		uint1 reg_ps_cnt_8_en_i,
		uint1 reg_ps_cnt_9_en_i,
		// ------------------------------------------------------------
		uint32 reg_ps_ctlr_i,
		// ------------------------------------------------------------
		uint32 &reg_pl_cnt_0_value_o,
		uint32 &reg_pl_cnt_1_value_o,
		uint32 &reg_pl_cnt_2_value_o,
		uint32 &reg_pl_cnt_3_value_o,
		uint32 &reg_pl_cnt_4_value_o,
		uint32 &reg_pl_cnt_5_value_o,
		uint32 &reg_pl_cnt_6_value_o,
		uint32 &reg_pl_cnt_7_value_o,
		uint32 &reg_pl_cnt_8_value_o,
		uint32 &reg_pl_cnt_9_value_o,
		uint32 &reg_pl_cnt_10_value_o,
		uint32 &reg_pl_cnt_11_value_o,
		uint32 &reg_pl_cnt_12_value_o,
		uint32 &reg_pl_cnt_13_value_o,
		uint32 &reg_pl_cnt_14_value_o,
		uint32 &reg_pl_cnt_15_value_o,
		uint32 &reg_pl_cnt_16_value_o,
		uint32 &reg_pl_cnt_17_value_o,
		uint32 &reg_pl_cnt_18_value_o,
		uint32 &reg_pl_cnt_19_value_o,
		// ------------------------------------------------------------
		uint32 &reg_ps_cnt_0_value_o,
		uint32 &reg_ps_cnt_1_value_o,
		uint32 &reg_ps_cnt_2_value_o,
		uint32 &reg_ps_cnt_3_value_o,
		uint32 &reg_ps_cnt_4_value_o,
		uint32 &reg_ps_cnt_5_value_o,
		uint32 &reg_ps_cnt_6_value_o,
		uint32 &reg_ps_cnt_7_value_o,
		uint32 &reg_ps_cnt_8_value_o,
		uint32 &reg_ps_cnt_9_value_o,
		// ------------------------------------------------------------
		uint32 &reg_ps_start_cnt_0_value_o,
		uint32 &reg_ps_start_cnt_1_value_o,
		uint32 &reg_ps_start_cnt_2_value_o,
		uint32 &reg_ps_start_cnt_3_value_o,
		uint32 &reg_ps_start_cnt_4_value_o,
		uint32 &reg_ps_start_cnt_5_value_o,
		uint32 &reg_ps_start_cnt_6_value_o,
		uint32 &reg_ps_start_cnt_7_value_o,
		uint32 &reg_ps_start_cnt_8_value_o,
		uint32 &reg_ps_start_cnt_9_value_o,
		// ------------------------------------------------------------
		uint32 &reg_ps_stop_cnt_0_value_o,
		uint32 &reg_ps_stop_cnt_1_value_o,
		uint32 &reg_ps_stop_cnt_2_value_o,
		uint32 &reg_ps_stop_cnt_3_value_o,
		uint32 &reg_ps_stop_cnt_4_value_o,
		uint32 &reg_ps_stop_cnt_5_value_o,
		uint32 &reg_ps_stop_cnt_6_value_o,
		uint32 &reg_ps_stop_cnt_7_value_o,
		uint32 &reg_ps_stop_cnt_8_value_o,
		uint32 &reg_ps_stop_cnt_9_value_o,
		// ------------------------------------------------------------
		uint32 &reg_pl_start_cnt_0_value_o,
		uint32 &reg_pl_start_cnt_1_value_o,
		uint32 &reg_pl_start_cnt_2_value_o,
		uint32 &reg_pl_start_cnt_3_value_o,
		uint32 &reg_pl_start_cnt_4_value_o,
		uint32 &reg_pl_start_cnt_5_value_o,
		uint32 &reg_pl_start_cnt_6_value_o,
		uint32 &reg_pl_start_cnt_7_value_o,
		uint32 &reg_pl_start_cnt_8_value_o,
		uint32 &reg_pl_start_cnt_9_value_o,
		uint32 &reg_pl_start_cnt_10_value_o,
		uint32 &reg_pl_start_cnt_11_value_o,
		uint32 &reg_pl_start_cnt_12_value_o,
		uint32 &reg_pl_start_cnt_13_value_o,
		uint32 &reg_pl_start_cnt_14_value_o,
		uint32 &reg_pl_start_cnt_15_value_o,
		uint32 &reg_pl_start_cnt_16_value_o,
		uint32 &reg_pl_start_cnt_17_value_o,
		uint32 &reg_pl_start_cnt_18_value_o,
		uint32 &reg_pl_start_cnt_19_value_o,
		// ------------------------------------------------------------
		uint32 &reg_pl_stop_cnt_0_value_o,
		uint32 &reg_pl_stop_cnt_1_value_o,
		uint32 &reg_pl_stop_cnt_2_value_o,
		uint32 &reg_pl_stop_cnt_3_value_o,
		uint32 &reg_pl_stop_cnt_4_value_o,
		uint32 &reg_pl_stop_cnt_5_value_o,
		uint32 &reg_pl_stop_cnt_6_value_o,
		uint32 &reg_pl_stop_cnt_7_value_o,
		uint32 &reg_pl_stop_cnt_8_value_o,
		uint32 &reg_pl_stop_cnt_9_value_o,
		uint32 &reg_pl_stop_cnt_10_value_o,
		uint32 &reg_pl_stop_cnt_11_value_o,
		uint32 &reg_pl_stop_cnt_12_value_o,
		uint32 &reg_pl_stop_cnt_13_value_o,
		uint32 &reg_pl_stop_cnt_14_value_o,
		uint32 &reg_pl_stop_cnt_15_value_o,
		uint32 &reg_pl_stop_cnt_16_value_o,
		uint32 &reg_pl_stop_cnt_17_value_o,
		uint32 &reg_pl_stop_cnt_18_value_o,
		uint32 &reg_pl_stop_cnt_19_value_o,

		//
		uint2 frcpl_0_start_i,
		uint2 frcpl_1_start_i,
		uint2 frcpl_2_start_i,
		uint2 frcpl_3_start_i,
		uint2 frcpl_4_start_i,
		uint2 frcpl_5_start_i,
		uint2 frcpl_6_start_i,
		uint2 frcpl_7_start_i,
		uint2 frcpl_8_start_i,
		uint2 frcpl_9_start_i,
		uint2 frcpl_10_start_i,
		uint2 frcpl_11_start_i,
		uint2 frcpl_12_start_i,
		uint2 frcpl_13_start_i,
		uint2 frcpl_14_start_i,
		uint2 frcpl_15_start_i,
		uint2 frcpl_16_start_i,
		uint2 frcpl_17_start_i,
		uint2 frcpl_18_start_i,
		uint2 frcpl_19_start_i,

		uint2 frcpl_0_stop_i,
		uint2 frcpl_1_stop_i,
		uint2 frcpl_2_stop_i,
		uint2 frcpl_3_stop_i,
		uint2 frcpl_4_stop_i,
		uint2 frcpl_5_stop_i,
		uint2 frcpl_6_stop_i,
		uint2 frcpl_7_stop_i,
		uint2 frcpl_8_stop_i,
		uint2 frcpl_9_stop_i,
		uint2 frcpl_10_stop_i,
		uint2 frcpl_11_stop_i,
		uint2 frcpl_12_stop_i,
		uint2 frcpl_13_stop_i,
		uint2 frcpl_14_stop_i,
		uint2 frcpl_15_stop_i,
		uint2 frcpl_16_stop_i,
		uint2 frcpl_17_stop_i,
		uint2 frcpl_18_stop_i,
		uint2 frcpl_19_stop_i,
		// ------------------------------------------------------------
		uint2 pl_event_cmd_0_i,
		uint2 pl_event_cmd_1_i,
		uint2 pl_event_cmd_2_i,
		uint2 pl_event_cmd_3_i,
		uint2 pl_event_cmd_4_i,
		uint2 pl_event_cmd_5_i,
		uint2 pl_event_cmd_6_i,
		uint2 pl_event_cmd_7_i,
		uint2 pl_event_cmd_8_i,
		uint2 pl_event_cmd_9_i,
		// ------------------------------------------------------------
		uint32 xmax_1_i,
		uint32 xmax_2_i,
		//-------------------------------------------------------------
		uint1 sw_rst_i


		)
{

#pragma HLS PIPELINE

#pragma HLS INTERFACE ap_ctrl_none port=return

#pragma HLS INTERFACE ap_none port=reg_ps_cnt_0_en_i
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_1_en_i
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_2_en_i
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_3_en_i
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_4_en_i
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_5_en_i
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_6_en_i
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_7_en_i
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_8_en_i
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_9_en_i

#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_0_en_i bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_1_en_i bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_2_en_i bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_3_en_i bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_4_en_i bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_5_en_i bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_6_en_i bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_7_en_i bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_8_en_i bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_9_en_i bundle=registers

#pragma HLS INTERFACE ap_none port=reg_pl_max_value_1_o
#pragma HLS INTERFACE ap_none port=reg_pl_max_value_2_o

#pragma HLS INTERFACE s_axilite port=reg_pl_max_value_1_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_max_value_2_o bundle=registers

#pragma HLS INTERFACE ap_none port=reg_ps_ctlr_i
#pragma HLS INTERFACE s_axilite port=reg_ps_ctlr_i bundle=registers

#pragma HLS INTERFACE ap_none port=reg_pl_cnt_0_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_1_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_2_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_3_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_4_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_5_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_6_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_7_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_8_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_9_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_10_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_11_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_12_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_13_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_14_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_15_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_16_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_17_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_18_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_cnt_19_value_o

#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_0_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_1_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_2_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_3_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_4_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_5_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_6_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_7_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_8_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_9_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_10_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_11_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_12_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_13_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_14_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_15_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_16_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_17_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_18_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_cnt_19_value_o bundle=registers
 
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_0_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_1_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_2_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_3_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_4_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_5_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_6_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_7_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_8_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_cnt_9_value_o

#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_0_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_1_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_2_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_3_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_4_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_5_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_6_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_7_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_8_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_cnt_9_value_o bundle=registers

#pragma HLS INTERFACE ap_none port=reg_ps_start_cnt_0_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_start_cnt_1_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_start_cnt_2_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_start_cnt_3_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_start_cnt_4_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_start_cnt_5_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_start_cnt_6_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_start_cnt_7_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_start_cnt_8_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_start_cnt_9_value_o

#pragma HLS INTERFACE s_axilite port=reg_ps_start_cnt_0_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_start_cnt_1_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_start_cnt_2_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_start_cnt_3_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_start_cnt_4_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_start_cnt_5_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_start_cnt_6_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_start_cnt_7_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_start_cnt_8_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_start_cnt_9_value_o bundle=registers

#pragma HLS INTERFACE ap_none port=reg_ps_stop_cnt_0_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_stop_cnt_1_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_stop_cnt_2_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_stop_cnt_3_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_stop_cnt_4_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_stop_cnt_5_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_stop_cnt_6_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_stop_cnt_7_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_stop_cnt_8_value_o
#pragma HLS INTERFACE ap_none port=reg_ps_stop_cnt_9_value_o

#pragma HLS INTERFACE s_axilite port=reg_ps_stop_cnt_0_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_stop_cnt_1_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_stop_cnt_2_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_stop_cnt_3_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_stop_cnt_4_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_stop_cnt_5_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_stop_cnt_6_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_stop_cnt_7_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_stop_cnt_8_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_ps_stop_cnt_9_value_o bundle=registers

#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_0_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_1_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_2_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_3_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_4_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_5_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_6_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_7_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_8_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_9_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_10_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_11_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_12_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_13_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_14_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_15_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_16_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_17_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_18_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_start_cnt_19_value_o

#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_0_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_1_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_2_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_3_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_4_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_5_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_6_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_7_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_8_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_9_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_10_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_11_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_12_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_13_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_14_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_15_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_16_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_17_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_18_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_start_cnt_19_value_o bundle=registers

#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_0_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_1_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_2_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_3_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_4_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_5_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_6_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_7_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_8_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_9_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_10_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_11_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_12_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_13_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_14_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_15_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_16_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_17_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_18_value_o
#pragma HLS INTERFACE ap_none port=reg_pl_stop_cnt_19_value_o

#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_0_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_1_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_2_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_3_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_4_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_5_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_6_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_7_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_8_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_9_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_10_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_11_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_12_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_13_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_14_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_15_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_16_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_17_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_18_value_o bundle=registers
#pragma HLS INTERFACE s_axilite port=reg_pl_stop_cnt_19_value_o bundle=registers
 

	static uint1 frcpl_0_enable;
	static uint1 frcpl_1_enable;
	static uint1 frcpl_2_enable;
	static uint1 frcpl_3_enable;
	static uint1 frcpl_4_enable;
	static uint1 frcpl_5_enable;
	static uint1 frcpl_6_enable;
	static uint1 frcpl_7_enable;
	static uint1 frcpl_8_enable;
	static uint1 frcpl_9_enable;
	static uint1 frcpl_10_enable;
	static uint1 frcpl_11_enable;
	static uint1 frcpl_12_enable;
	static uint1 frcpl_13_enable;
	static uint1 frcpl_14_enable;
	static uint1 frcpl_15_enable;
	static uint1 frcpl_16_enable;
	static uint1 frcpl_17_enable;
	static uint1 frcpl_18_enable;
	static uint1 frcpl_19_enable;

	static uint1 frcps_0_enable;
	static uint1 frcps_1_enable;
	static uint1 frcps_2_enable;
	static uint1 frcps_3_enable;
	static uint1 frcps_4_enable;
	static uint1 frcps_5_enable;
	static uint1 frcps_6_enable;
	static uint1 frcps_7_enable;
	static uint1 frcps_8_enable;
	static uint1 frcps_9_enable;

	static uint32 frcpl_0_value_Img = 0;
	static uint32 frcpl_1_value_Img = 0;
	static uint32 frcpl_2_value_Img = 0;
	static uint32 frcpl_3_value_Img = 0;
	static uint32 frcpl_4_value_Img = 0;
	static uint32 frcpl_5_value_Img = 0;
	static uint32 frcpl_6_value_Img = 0;
	static uint32 frcpl_7_value_Img = 0;
	static uint32 frcpl_8_value_Img = 0;
	static uint32 frcpl_9_value_Img = 0;
	static uint32 frcpl_10_value_Img = 0;
	static uint32 frcpl_11_value_Img = 0;
	static uint32 frcpl_12_value_Img = 0;
	static uint32 frcpl_13_value_Img = 0;
	static uint32 frcpl_14_value_Img = 0;
	static uint32 frcpl_15_value_Img = 0;
	static uint32 frcpl_16_value_Img = 0;
	static uint32 frcpl_17_value_Img = 0;
	static uint32 frcpl_18_value_Img = 0;
	static uint32 frcpl_19_value_Img = 0;

	static uint32 frcps_0_value_Img = 0;
	static uint32 frcps_1_value_Img = 0;
	static uint32 frcps_2_value_Img = 0;
	static uint32 frcps_3_value_Img = 0;
	static uint32 frcps_4_value_Img = 0;
	static uint32 frcps_5_value_Img = 0;
	static uint32 frcps_6_value_Img = 0;
	static uint32 frcps_7_value_Img = 0;
	static uint32 frcps_8_value_Img = 0;
	static uint32 frcps_9_value_Img = 0;

	static uint32 frcps_ps_start_counter_0_Img = 0;
	static uint32 frcps_ps_start_counter_1_Img = 0;
	static uint32 frcps_ps_start_counter_2_Img = 0;
	static uint32 frcps_ps_start_counter_3_Img = 0;
	static uint32 frcps_ps_start_counter_4_Img = 0;
	static uint32 frcps_ps_start_counter_5_Img = 0;
	static uint32 frcps_ps_start_counter_6_Img = 0;
	static uint32 frcps_ps_start_counter_7_Img = 0;
	static uint32 frcps_ps_start_counter_8_Img = 0;
	static uint32 frcps_ps_start_counter_9_Img = 0;

	static uint32 frcps_ps_stop_counter_0_Img = 0;
	static uint32 frcps_ps_stop_counter_1_Img = 0;
	static uint32 frcps_ps_stop_counter_2_Img = 0;
	static uint32 frcps_ps_stop_counter_3_Img = 0;
	static uint32 frcps_ps_stop_counter_4_Img = 0;
	static uint32 frcps_ps_stop_counter_5_Img = 0;
	static uint32 frcps_ps_stop_counter_6_Img = 0;
	static uint32 frcps_ps_stop_counter_7_Img = 0;
	static uint32 frcps_ps_stop_counter_8_Img = 0;
	static uint32 frcps_ps_stop_counter_9_Img = 0;

	static uint32 frcps_pl_start_counter_0_Img = 0;
	static uint32 frcps_pl_start_counter_1_Img = 0;
	static uint32 frcps_pl_start_counter_2_Img = 0;
	static uint32 frcps_pl_start_counter_3_Img = 0;
	static uint32 frcps_pl_start_counter_4_Img = 0;
	static uint32 frcps_pl_start_counter_5_Img = 0;
	static uint32 frcps_pl_start_counter_6_Img = 0;
	static uint32 frcps_pl_start_counter_7_Img = 0;
	static uint32 frcps_pl_start_counter_8_Img = 0;
	static uint32 frcps_pl_start_counter_9_Img = 0;
	static uint32 frcps_pl_start_counter_10_Img = 0;
	static uint32 frcps_pl_start_counter_11_Img = 0;
	static uint32 frcps_pl_start_counter_12_Img = 0;
	static uint32 frcps_pl_start_counter_13_Img = 0;
	static uint32 frcps_pl_start_counter_14_Img = 0;
	static uint32 frcps_pl_start_counter_15_Img = 0;
	static uint32 frcps_pl_start_counter_16_Img = 0;
	static uint32 frcps_pl_start_counter_17_Img = 0;
	static uint32 frcps_pl_start_counter_18_Img = 0;
	static uint32 frcps_pl_start_counter_19_Img = 0;

	static uint32 frcps_pl_stop_counter_0_Img = 0;
	static uint32 frcps_pl_stop_counter_1_Img = 0;
	static uint32 frcps_pl_stop_counter_2_Img = 0;
	static uint32 frcps_pl_stop_counter_3_Img = 0;
	static uint32 frcps_pl_stop_counter_4_Img = 0;
	static uint32 frcps_pl_stop_counter_5_Img = 0;
	static uint32 frcps_pl_stop_counter_6_Img = 0;
	static uint32 frcps_pl_stop_counter_7_Img = 0;
	static uint32 frcps_pl_stop_counter_8_Img = 0;
	static uint32 frcps_pl_stop_counter_9_Img = 0;
	static uint32 frcps_pl_stop_counter_10_Img = 0;
	static uint32 frcps_pl_stop_counter_11_Img = 0;
	static uint32 frcps_pl_stop_counter_12_Img = 0;
	static uint32 frcps_pl_stop_counter_13_Img = 0;
	static uint32 frcps_pl_stop_counter_14_Img = 0;
	static uint32 frcps_pl_stop_counter_15_Img = 0;
	static uint32 frcps_pl_stop_counter_16_Img = 0;
	static uint32 frcps_pl_stop_counter_17_Img = 0;
	static uint32 frcps_pl_stop_counter_18_Img = 0;
	static uint32 frcps_pl_stop_counter_19_Img = 0;

	static uint2 pl_event_cmd_0_prev = 0;
	static uint2 pl_event_cmd_1_prev = 0;
	static uint2 pl_event_cmd_2_prev = 0;
	static uint2 pl_event_cmd_3_prev = 0;
	static uint2 pl_event_cmd_4_prev = 0;
	static uint2 pl_event_cmd_5_prev = 0;
	static uint2 pl_event_cmd_6_prev = 0;
	static uint2 pl_event_cmd_7_prev = 0;
	static uint2 pl_event_cmd_8_prev = 0;
	static uint2 pl_event_cmd_9_prev = 0;

	static uint2 frcpl_0_start_i_pre =0;
	static uint2 frcpl_1_start_i_pre =0;
	static uint2 frcpl_2_start_i_pre =0;
	static uint2 frcpl_3_start_i_pre =0;
	static uint2 frcpl_4_start_i_pre =0;
	static uint2 frcpl_5_start_i_pre =0;
	static uint2 frcpl_6_start_i_pre =0;
	static uint2 frcpl_7_start_i_pre =0;
	static uint2 frcpl_8_start_i_pre =0;
	static uint2 frcpl_9_start_i_pre =0;
	static uint2 frcpl_10_start_i_pre =0;
	static uint2 frcpl_11_start_i_pre =0;
	static uint2 frcpl_12_start_i_pre =0;
	static uint2 frcpl_13_start_i_pre =0;
	static uint2 frcpl_14_start_i_pre =0;
	static uint2 frcpl_15_start_i_pre =0;
	static uint2 frcpl_16_start_i_pre =0;
	static uint2 frcpl_17_start_i_pre =0;
	static uint2 frcpl_18_start_i_pre =0;
	static uint2 frcpl_19_start_i_pre =0;

	static uint2 frcpl_0_stop_i_pre =0;
	static uint2 frcpl_1_stop_i_pre =0;
	static uint2 frcpl_2_stop_i_pre =0;
	static uint2 frcpl_3_stop_i_pre =0;
	static uint2 frcpl_4_stop_i_pre =0;
	static uint2 frcpl_5_stop_i_pre =0;
	static uint2 frcpl_6_stop_i_pre =0;
	static uint2 frcpl_7_stop_i_pre =0;
	static uint2 frcpl_8_stop_i_pre =0;
	static uint2 frcpl_9_stop_i_pre =0;
	static uint2 frcpl_10_stop_i_pre =0;
	static uint2 frcpl_11_stop_i_pre =0;
	static uint2 frcpl_12_stop_i_pre =0;
	static uint2 frcpl_13_stop_i_pre =0;
	static uint2 frcpl_14_stop_i_pre =0;
	static uint2 frcpl_15_stop_i_pre =0;
	static uint2 frcpl_16_stop_i_pre =0;
	static uint2 frcpl_17_stop_i_pre =0;
	static uint2 frcpl_18_stop_i_pre =0;
	static uint2 frcpl_19_stop_i_pre =0;

	static uint32 max_value_buffer_1;
	static uint32 max_value_buffer_2;

    if (sw_rst_i == 1 || reg_ps_ctlr_i.range(16,16) == 1) {


    	frcps_0_value_Img = 0;
    	frcps_1_value_Img = 0;
    	frcps_2_value_Img = 0;
    	frcps_3_value_Img = 0;
    	frcps_4_value_Img = 0;
		frcps_5_value_Img = 0;
		frcps_6_value_Img = 0;
		frcps_7_value_Img = 0;
		frcps_8_value_Img = 0;
		frcps_9_value_Img = 0;

		frcps_ps_start_counter_0_Img = 0;
		frcps_ps_start_counter_1_Img = 0;
		frcps_ps_start_counter_2_Img = 0;
		frcps_ps_start_counter_3_Img = 0;
		frcps_ps_start_counter_4_Img = 0;
		frcps_ps_start_counter_5_Img = 0;
		frcps_ps_start_counter_6_Img = 0;
		frcps_ps_start_counter_7_Img = 0;
		frcps_ps_start_counter_8_Img = 0;
		frcps_ps_start_counter_9_Img = 0;

		frcps_ps_stop_counter_0_Img = 0;
		frcps_ps_stop_counter_1_Img = 0;
		frcps_ps_stop_counter_2_Img = 0;
		frcps_ps_stop_counter_3_Img = 0;
		frcps_ps_stop_counter_4_Img = 0;
		frcps_ps_stop_counter_5_Img = 0;
		frcps_ps_stop_counter_6_Img = 0;
		frcps_ps_stop_counter_7_Img = 0;
		frcps_ps_stop_counter_8_Img = 0;
		frcps_ps_stop_counter_9_Img = 0;

		frcpl_0_value_Img = 0;
		frcpl_1_value_Img = 0;
		frcpl_2_value_Img = 0;
		frcpl_3_value_Img = 0;
		frcpl_4_value_Img = 0;
		frcpl_5_value_Img = 0;
		frcpl_6_value_Img = 0;
		frcpl_7_value_Img = 0;
		frcpl_8_value_Img = 0;
		frcpl_9_value_Img = 0;
		frcpl_10_value_Img = 0;
		frcpl_11_value_Img = 0;
		frcpl_12_value_Img = 0;
		frcpl_13_value_Img = 0;
		frcpl_14_value_Img = 0;
		frcpl_15_value_Img = 0;
		frcpl_16_value_Img = 0;
		frcpl_17_value_Img = 0;
		frcpl_18_value_Img = 0;
		frcpl_19_value_Img = 0;

		frcps_pl_start_counter_0_Img = 0;
		frcps_pl_start_counter_1_Img = 0;
		frcps_pl_start_counter_2_Img = 0;
		frcps_pl_start_counter_3_Img = 0;
		frcps_pl_start_counter_4_Img = 0;
		frcps_pl_start_counter_5_Img = 0;
		frcps_pl_start_counter_6_Img = 0;
		frcps_pl_start_counter_7_Img = 0;
		frcps_pl_start_counter_8_Img = 0;
		frcps_pl_start_counter_9_Img = 0;
		frcps_pl_start_counter_10_Img = 0;
		frcps_pl_start_counter_11_Img = 0;
		frcps_pl_start_counter_12_Img = 0;
		frcps_pl_start_counter_13_Img = 0;
		frcps_pl_start_counter_14_Img = 0;
		frcps_pl_start_counter_15_Img = 0;
		frcps_pl_start_counter_16_Img = 0;
		frcps_pl_start_counter_17_Img = 0;
		frcps_pl_start_counter_18_Img = 0;
		frcps_pl_start_counter_19_Img = 0;

		frcps_pl_stop_counter_0_Img = 0;
		frcps_pl_stop_counter_1_Img = 0;
		frcps_pl_stop_counter_2_Img = 0;
		frcps_pl_stop_counter_3_Img = 0;
		frcps_pl_stop_counter_4_Img = 0;
		frcps_pl_stop_counter_5_Img = 0;
		frcps_pl_stop_counter_6_Img = 0;
		frcps_pl_stop_counter_7_Img = 0;
		frcps_pl_stop_counter_8_Img = 0;
		frcps_pl_stop_counter_9_Img = 0;
		frcps_pl_stop_counter_10_Img = 0;
		frcps_pl_stop_counter_11_Img = 0;
		frcps_pl_stop_counter_12_Img = 0;
		frcps_pl_stop_counter_13_Img = 0;
		frcps_pl_stop_counter_14_Img = 0;
		frcps_pl_stop_counter_15_Img = 0;
		frcps_pl_stop_counter_16_Img = 0;
		frcps_pl_stop_counter_17_Img = 0;
		frcps_pl_stop_counter_18_Img = 0;
		frcps_pl_stop_counter_19_Img = 0;

		frcpl_1_enable = 0;
		frcpl_2_enable = 0;
		frcpl_3_enable = 0;
		frcpl_0_enable = 0;
		frcpl_4_enable = 0;
		frcpl_5_enable = 0;
		frcpl_6_enable = 0;
		frcpl_7_enable = 0;
		frcpl_8_enable = 0;
		frcpl_9_enable = 0;
		frcpl_10_enable = 0;
		frcpl_11_enable = 0;
		frcpl_12_enable = 0;
		frcpl_13_enable = 0;
		frcpl_14_enable = 0;
		frcpl_15_enable = 0;
		frcpl_16_enable = 0;
		frcpl_17_enable = 0;
		frcpl_18_enable = 0;
		frcpl_19_enable = 0;

    	pl_event_cmd_0_prev = 0;
    	pl_event_cmd_1_prev = 0;
    	pl_event_cmd_2_prev = 0;
    	pl_event_cmd_3_prev = 0;
    	pl_event_cmd_4_prev = 0;
    	pl_event_cmd_5_prev = 0;
    	pl_event_cmd_6_prev = 0;
    	pl_event_cmd_7_prev = 0;
    	pl_event_cmd_7_prev = 0;
    	pl_event_cmd_8_prev = 0;


		frcpl_0_start_i_pre =0;
		frcpl_1_start_i_pre =0;
		frcpl_2_start_i_pre =0;
		frcpl_3_start_i_pre =0;
		frcpl_4_start_i_pre =0;
		frcpl_5_start_i_pre =0;
		frcpl_6_start_i_pre =0;
		frcpl_7_start_i_pre =0;
		frcpl_8_start_i_pre =0;
		frcpl_9_start_i_pre =0;
		frcpl_10_start_i_pre =0;
		frcpl_11_start_i_pre =0;
		frcpl_12_start_i_pre =0;
		frcpl_13_start_i_pre =0;
		frcpl_14_start_i_pre =0;
		frcpl_15_start_i_pre =0;
		frcpl_16_start_i_pre =0;
		frcpl_17_start_i_pre =0;
		frcpl_18_start_i_pre =0;
		frcpl_19_start_i_pre =0;

		frcpl_0_stop_i_pre =0;
		frcpl_1_stop_i_pre =0;
		frcpl_2_stop_i_pre =0;
		frcpl_3_stop_i_pre =0;
		frcpl_4_stop_i_pre =0;
		frcpl_5_stop_i_pre =0;
		frcpl_6_stop_i_pre =0;
		frcpl_7_stop_i_pre =0;
		frcpl_8_stop_i_pre =0;
		frcpl_9_stop_i_pre =0;
		frcpl_10_stop_i_pre =0;
		frcpl_11_stop_i_pre =0;
		frcpl_12_stop_i_pre =0;
		frcpl_13_stop_i_pre =0;
		frcpl_14_stop_i_pre =0;
		frcpl_15_stop_i_pre =0;
		frcpl_16_stop_i_pre =0;
		frcpl_17_stop_i_pre =0;
		frcpl_18_stop_i_pre =0;
		frcpl_19_stop_i_pre =0;

		frcps_0_enable = 0;
		frcps_1_enable = 0;
		frcps_2_enable = 0;
		frcps_3_enable = 0;
		frcps_4_enable = 0;
		frcps_5_enable = 0;
		frcps_6_enable = 0;
		frcps_7_enable = 0;
		frcps_8_enable = 0;
		frcps_9_enable = 0;

		max_value_buffer_1 = 0;
		max_value_buffer_2 = 0;

    } else {

			if (xmax_1_i > max_value_buffer_1) {
				max_value_buffer_1 = xmax_1_i;
			}
    	//--------------------------------------------------------------
			if (xmax_2_i > max_value_buffer_2) {
				max_value_buffer_2 = xmax_2_i;
			}
        //---------------------------------------
    	//This timer counter are dedicated as accumulative time counter to count PL Clocks (execution time)
    	// for any operation. This timer will be activated from PL, also will be disabled from the PL
		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_0) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 0 (FRCPL_0) ------------------------------------------------------------
		if ( frcpl_0_start_i != frcpl_0_start_i_pre  ) {
           	frcpl_0_enable = 1;
           	frcps_pl_start_counter_0_Img++;
           	frcpl_0_start_i_pre = frcpl_0_start_i;

		} else if ( frcpl_0_stop_i != frcpl_0_stop_i_pre ) {

			frcpl_0_enable = 0;
			frcps_pl_stop_counter_0_Img++;
			frcpl_0_stop_i_pre = frcpl_0_stop_i;

		} else {

			frcpl_0_start_i_pre = frcpl_0_start_i;
			frcpl_0_stop_i_pre = frcpl_0_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
        if (frcpl_0_enable == 0) {

        	reg_pl_cnt_0_value_o = frcpl_0_value_Img;

        } else if (frcpl_0_enable == 1) {

        	reg_pl_cnt_0_value_o =  frcpl_0_value_Img++;
    	}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_0) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------



        //  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_1) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 1 (FRCPL_1) ------------------------------------------------------------
        if (frcpl_1_start_i != frcpl_1_start_i_pre  ) {
			frcpl_1_enable = 1;
			frcps_pl_start_counter_1_Img++;
			frcpl_1_start_i_pre = frcpl_1_start_i;

        } else if (frcpl_1_stop_i !=  frcpl_1_stop_i_pre ) {

			frcpl_1_enable = 0;
			frcps_pl_stop_counter_1_Img++;
			frcpl_1_stop_i_pre = frcpl_1_stop_i;
        } else {

			frcpl_1_start_i_pre = frcpl_1_start_i;
			frcpl_1_stop_i_pre = frcpl_1_stop_i;
		}
        // ------------------------------- COUNTER Main Function -----------------------------
        if (frcpl_1_enable == 0) {

			reg_pl_cnt_1_value_o = frcpl_1_value_Img;

		} else if (frcpl_1_enable == 1) {

			reg_pl_cnt_1_value_o =  frcpl_1_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_1) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------

		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_2) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 2 (FRCPL_2) ------------------------------------------------------------
		if (frcpl_2_start_i != frcpl_2_start_i_pre ) {
			frcpl_2_enable = 1;
			frcps_pl_start_counter_2_Img++;
			frcpl_2_start_i_pre = frcpl_2_start_i;

		} else if (frcpl_2_stop_i != frcpl_2_stop_i_pre ) {

			frcpl_2_enable = 0;
			frcps_pl_stop_counter_2_Img++;
			frcpl_2_stop_i_pre = frcpl_2_stop_i;
		} else {

			frcpl_2_start_i_pre = frcpl_2_start_i;
			frcpl_2_stop_i_pre = frcpl_2_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_2_enable == 0) {

			reg_pl_cnt_2_value_o = frcpl_2_value_Img;

		} else if (frcpl_2_enable == 1) {

			reg_pl_cnt_2_value_o = frcpl_2_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_2) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------



		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_3) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 3 (FRCPL_3) -----------------------------------------------------------
		if (frcpl_3_start_i != frcpl_3_start_i_pre ) {
			frcpl_3_enable = 1;
			frcps_pl_start_counter_3_Img++;
			frcpl_3_start_i_pre = frcpl_3_start_i;

		} else if (frcpl_3_stop_i != frcpl_3_stop_i_pre ) {

			frcpl_3_enable = 0;
			frcps_pl_stop_counter_3_Img++;
			frcpl_3_stop_i_pre = frcpl_3_stop_i;
		} else {

			frcpl_3_start_i_pre = frcpl_3_start_i;
			frcpl_3_stop_i_pre = frcpl_3_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_3_enable == 0) {

			reg_pl_cnt_3_value_o = frcpl_3_value_Img;

		} else if (frcpl_3_enable == 1) {

			reg_pl_cnt_3_value_o = frcpl_3_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_3) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------



		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_4) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 4 (FRCPL_4) -----------------------------------------------------------
		if (frcpl_4_start_i != frcpl_4_start_i_pre ) {
			frcpl_4_enable = 1;
			frcps_pl_start_counter_4_Img++;
			frcpl_4_start_i_pre = frcpl_4_start_i;

		} else if (frcpl_4_stop_i != frcpl_4_stop_i_pre ) {

			frcpl_4_enable = 0;
			frcps_pl_stop_counter_4_Img++;
			frcpl_4_stop_i_pre = frcpl_4_stop_i;
		} else {

			frcpl_4_start_i_pre = frcpl_4_start_i;
			frcpl_4_stop_i_pre = frcpl_4_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_4_enable == 0) {

			reg_pl_cnt_4_value_o = frcpl_4_value_Img;

		} else if (frcpl_4_enable == 1) {

			reg_pl_cnt_4_value_o = frcpl_4_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_4) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------




		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_5) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 5 (FRCPL_5) -----------------------------------------------------------
		if (frcpl_5_start_i != frcpl_5_start_i_pre ) {
			frcpl_5_enable = 1;
			frcps_pl_start_counter_5_Img++;
			frcpl_5_start_i_pre = frcpl_5_start_i;

		} else if (frcpl_5_stop_i != frcpl_5_stop_i_pre  ) {

			frcpl_5_enable = 0;
			frcps_pl_stop_counter_5_Img++;
			frcpl_5_stop_i_pre = frcpl_5_stop_i;
		} else {

			frcpl_5_start_i_pre = frcpl_5_start_i;
			frcpl_5_stop_i_pre = frcpl_5_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_5_enable == 0) {

			reg_pl_cnt_5_value_o = frcpl_5_value_Img;

		} else if (frcpl_5_enable == 1) {

			reg_pl_cnt_5_value_o = frcpl_5_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_5) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------



		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_6) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 6 (FRCPL_6) -----------------------------------------------------------
		if (frcpl_6_start_i != frcpl_6_start_i_pre ) {
			frcpl_6_enable = 1;
			frcps_pl_start_counter_6_Img++;
			frcpl_6_start_i_pre = frcpl_6_start_i;

		} else if (frcpl_6_stop_i != frcpl_6_stop_i_pre ) {

			frcpl_6_enable = 0;
			frcps_pl_stop_counter_6_Img++;
			frcpl_6_stop_i_pre = frcpl_6_stop_i;
		} else {

			frcpl_6_start_i_pre = frcpl_6_start_i;
			frcpl_6_stop_i_pre = frcpl_6_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_6_enable == 0) {

			reg_pl_cnt_6_value_o = frcpl_6_value_Img;

		} else if (frcpl_6_enable == 1) {

			reg_pl_cnt_6_value_o = frcpl_6_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_6) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------



		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_7) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 7 (FRCPL_7) -----------------------------------------------------------
		if (frcpl_7_start_i != frcpl_7_start_i_pre  ) {
			frcpl_7_enable = 1;
			frcps_pl_start_counter_7_Img++;
			frcpl_7_start_i_pre = frcpl_7_start_i;

		} else if (frcpl_7_stop_i != frcpl_7_stop_i_pre  ) {

			frcpl_7_enable = 0;
			frcps_pl_stop_counter_7_Img++;
			frcpl_7_stop_i_pre = frcpl_7_stop_i;
		} else {

			frcpl_7_start_i_pre = frcpl_7_start_i;
			frcpl_7_stop_i_pre = frcpl_7_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_7_enable == 0) {

			reg_pl_cnt_7_value_o = frcpl_7_value_Img;

		} else if (frcpl_7_enable == 1) {

			reg_pl_cnt_7_value_o = frcpl_7_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_7) ---------------------------------------------------------------------------------------------------
		//------------------------------------------------frcps_counter_0_Img---------------------------------------------------------------------------------------


		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_8) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 8 (FRCPL_8) -----------------------------------------------------------
		if (frcpl_8_start_i != frcpl_8_start_i_pre ) {
			frcpl_8_enable = 1;
			frcps_pl_start_counter_8_Img++;
			frcpl_8_start_i_pre = frcpl_8_start_i;

		} else if (frcpl_8_stop_i != frcpl_8_stop_i_pre ) {

			frcpl_8_enable = 0;
			frcps_pl_stop_counter_8_Img++;
			frcpl_8_stop_i_pre = frcpl_8_stop_i;
		} else {

			frcpl_8_start_i_pre = frcpl_8_start_i;
			frcpl_8_stop_i_pre = frcpl_8_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_8_enable == 0) {

			reg_pl_cnt_8_value_o = frcpl_8_value_Img;

		} else if (frcpl_8_enable == 1) {

			reg_pl_cnt_8_value_o = frcpl_8_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_8) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------


		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_9) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 9 (FRCPL_9) -----------------------------------------------------------
		if (frcpl_9_start_i !=  frcpl_9_start_i_pre ) {
			frcpl_9_enable = 1;
			frcps_pl_start_counter_9_Img++;
			frcpl_9_start_i_pre = frcpl_9_start_i;

		} else if (frcpl_9_stop_i != frcpl_9_stop_i_pre  ) {

			frcpl_9_enable = 0;
			frcps_pl_stop_counter_9_Img++;
			frcpl_9_stop_i_pre = frcpl_9_stop_i;
		} else {

			frcpl_9_start_i_pre = frcpl_9_start_i;
			frcpl_9_stop_i_pre = frcpl_9_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_9_enable == 0) {

			reg_pl_cnt_9_value_o = frcpl_9_value_Img;

		} else if (frcpl_9_enable == 1) {

			reg_pl_cnt_9_value_o = frcpl_9_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_9) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------


		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_10) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 10 (FRCPL_10) -----------------------------------------------------------
		if (frcpl_10_start_i != frcpl_10_start_i_pre ) {
			frcpl_10_enable = 1;
			frcps_pl_start_counter_10_Img++;
			frcpl_10_start_i_pre = frcpl_10_start_i;

		} else if (frcpl_10_stop_i != frcpl_10_stop_i_pre  ) {

			frcpl_10_enable = 0;
			frcps_pl_stop_counter_10_Img++;
			frcpl_10_stop_i_pre = frcpl_10_stop_i;
		} else {

			frcpl_10_start_i_pre = frcpl_10_start_i;
			frcpl_10_stop_i_pre = frcpl_10_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_10_enable == 0) {

			reg_pl_cnt_10_value_o = frcpl_10_value_Img;

		} else if (frcpl_10_enable == 1) {

			reg_pl_cnt_10_value_o = frcpl_10_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_10) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------



		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_11) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 11 (FRCPL_11) -----------------------------------------------------------
		if (frcpl_11_start_i != frcpl_11_start_i_pre ) {
			frcpl_11_enable = 1;
			frcps_pl_start_counter_11_Img++;
			frcpl_11_start_i_pre = frcpl_11_start_i;

		} else if (frcpl_11_stop_i != frcpl_11_stop_i_pre ) {

			frcpl_11_enable = 0;
			frcps_pl_stop_counter_11_Img++;
			frcpl_11_stop_i_pre = frcpl_11_stop_i;
		} else {

			frcpl_11_start_i_pre = frcpl_11_start_i;
			frcpl_11_stop_i_pre = frcpl_11_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_11_enable == 0) {

			reg_pl_cnt_11_value_o = frcpl_11_value_Img;

		} else if (frcpl_11_enable == 1) {

			reg_pl_cnt_11_value_o = frcpl_11_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_11) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------


		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_12) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 12 (FRCPL_12) -----------------------------------------------------------
		if (frcpl_12_start_i != frcpl_12_start_i_pre  ) {
			frcpl_12_enable = 1;
			frcps_pl_start_counter_12_Img++;
			frcpl_12_start_i_pre = frcpl_12_start_i;

		} else if (frcpl_12_stop_i != frcpl_12_stop_i_pre ) {

			frcpl_12_enable = 0;
			frcps_pl_stop_counter_12_Img++;
			frcpl_12_stop_i_pre = frcpl_12_stop_i;
		} else {

			frcpl_12_start_i_pre = frcpl_12_start_i;
			frcpl_12_stop_i_pre = frcpl_12_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_12_enable == 0) {

			reg_pl_cnt_12_value_o = frcpl_12_value_Img;

		} else if (frcpl_12_enable == 1) {

			reg_pl_cnt_12_value_o = frcpl_12_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_12) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------



		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_13) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 13 (FRCPL_13) -----------------------------------------------------------
		if (frcpl_13_start_i != frcpl_13_start_i_pre  ) {
			frcpl_13_enable = 1;
			frcps_pl_start_counter_13_Img++;
			frcpl_13_start_i_pre = frcpl_13_start_i;

		} else if (frcpl_13_stop_i != frcpl_13_stop_i_pre  ) {

			frcpl_13_enable = 0;
			frcps_pl_stop_counter_13_Img++;
			frcpl_13_stop_i_pre = frcpl_13_stop_i;
		} else {

			frcpl_13_start_i_pre = frcpl_13_start_i;
			frcpl_13_stop_i_pre = frcpl_13_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_13_enable == 0) {

			reg_pl_cnt_13_value_o = frcpl_13_value_Img;

		} else if (frcpl_13_enable == 1) {

			reg_pl_cnt_13_value_o = frcpl_13_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_13) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------


		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_14) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 14 (FRCPL_14) -----------------------------------------------------------
		if (frcpl_14_start_i !=  frcpl_14_start_i_pre  ) {
			frcpl_14_enable = 1;
			frcps_pl_start_counter_14_Img++;
			frcpl_14_start_i_pre = frcpl_14_start_i;

		} else if (frcpl_14_stop_i != frcpl_14_stop_i_pre  ) {

			frcpl_14_enable = 0;
			frcps_pl_stop_counter_14_Img++;
			frcpl_14_stop_i_pre = frcpl_14_stop_i;
		} else {

			frcpl_14_start_i_pre = frcpl_14_start_i;
			frcpl_14_stop_i_pre = frcpl_14_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_14_enable == 0) {

			reg_pl_cnt_14_value_o = frcpl_14_value_Img;

		} else if (frcpl_14_enable == 1) {

			reg_pl_cnt_14_value_o = frcpl_14_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_14) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------



		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_15) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 15 (FRCPL_15) -----------------------------------------------------------
		if (frcpl_15_start_i != frcpl_15_start_i_pre  ) {
			frcpl_15_enable = 1;
			frcps_pl_start_counter_15_Img++;
			frcpl_15_start_i_pre = frcpl_15_start_i;

		} else if (frcpl_15_stop_i != frcpl_15_stop_i_pre ) {

			frcpl_15_enable = 0;
			frcps_pl_stop_counter_15_Img++;
			frcpl_15_stop_i_pre = frcpl_15_stop_i;
		} else {

			frcpl_15_start_i_pre = frcpl_15_start_i;
			frcpl_15_stop_i_pre = frcpl_15_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_15_enable == 0) {

			reg_pl_cnt_15_value_o = frcpl_15_value_Img;

		} else if (frcpl_15_enable == 1) {

			reg_pl_cnt_15_value_o = frcpl_15_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_15) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------

		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_16) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 16 (FRCPL_16) -----------------------------------------------------------
		if (frcpl_16_start_i != frcpl_16_start_i_pre  ) {
			frcpl_16_enable = 1;
			frcps_pl_start_counter_16_Img++;
			frcpl_16_start_i_pre = frcpl_16_start_i;

		} else if (frcpl_16_stop_i != frcpl_16_stop_i_pre ) {

			frcpl_16_enable = 0;
			frcps_pl_stop_counter_16_Img++;
			frcpl_16_stop_i_pre = frcpl_16_stop_i;
		} else {

			frcpl_16_start_i_pre = frcpl_16_start_i;
			frcpl_16_stop_i_pre = frcpl_16_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_16_enable == 0) {

			reg_pl_cnt_16_value_o = frcpl_16_value_Img;

		} else if (frcpl_16_enable == 1) {

			reg_pl_cnt_16_value_o = frcpl_16_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_16) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------

		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_17) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 17 (FRCPL_17) -----------------------------------------------------------
		if (frcpl_17_start_i != frcpl_17_start_i_pre  ) {
			frcpl_17_enable = 1;
			frcps_pl_start_counter_17_Img++;
			frcpl_17_start_i_pre = frcpl_17_start_i;

		} else if (frcpl_17_stop_i != frcpl_17_stop_i_pre ) {

			frcpl_17_enable = 0;
			frcps_pl_stop_counter_17_Img++;
			frcpl_17_stop_i_pre = frcpl_17_stop_i;
		} else {

			frcpl_17_start_i_pre = frcpl_17_start_i;
			frcpl_17_stop_i_pre = frcpl_17_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_17_enable == 0) {

			reg_pl_cnt_17_value_o = frcpl_17_value_Img;

		} else if (frcpl_17_enable == 1) {

			reg_pl_cnt_17_value_o = frcpl_17_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_17) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------

		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_18) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 18 (FRCPL_18) -----------------------------------------------------------
		if (frcpl_18_start_i != frcpl_18_start_i_pre  ) {
			frcpl_18_enable = 1;
			frcps_pl_start_counter_18_Img++;
			frcpl_18_start_i_pre = frcpl_18_start_i;

		} else if (frcpl_18_stop_i != frcpl_18_stop_i_pre ) {

			frcpl_18_enable = 0;
			frcps_pl_stop_counter_18_Img++;
			frcpl_18_stop_i_pre = frcpl_18_stop_i;
		} else {

			frcpl_18_start_i_pre = frcpl_18_start_i;
			frcpl_18_stop_i_pre = frcpl_18_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_18_enable == 0) {

			reg_pl_cnt_18_value_o = frcpl_18_value_Img;

		} else if (frcpl_18_enable == 1) {

			reg_pl_cnt_18_value_o = frcpl_18_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_18) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------


		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PL.
		// ---------- START PF (FRCPL_19) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PL FREE RUNNING COUNTER NUMBER 19 (FRCPL_19) -----------------------------------------------------------
		if (frcpl_19_start_i != frcpl_19_start_i_pre  ) {
			frcpl_19_enable = 1;
			frcps_pl_start_counter_19_Img++;
			frcpl_19_start_i_pre = frcpl_19_start_i;

		} else if (frcpl_19_stop_i != frcpl_19_stop_i_pre ) {

			frcpl_19_enable = 0;
			frcps_pl_stop_counter_19_Img++;
			frcpl_19_stop_i_pre = frcpl_19_stop_i;
		} else {

			frcpl_19_start_i_pre = frcpl_19_start_i;
			frcpl_19_stop_i_pre = frcpl_19_stop_i;
		}
		// ------------------------------- COUNTER Main Function -----------------------------
		if (frcpl_19_enable == 0) {

			reg_pl_cnt_19_value_o = frcpl_19_value_Img;

		} else if (frcpl_19_enable == 1) {

			reg_pl_cnt_19_value_o = frcpl_19_value_Img++;
		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPL_19) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------

    //  ------------------------------------------------------------------------------------------------------------------------------------------------------
    // following free-running counters are controlled from the PS.
		// ---------- START PF (FRCPS_0) -------------------------------------------------------------------------------------------------------------------------
        // ----------------------------------------------- PS FREE RUNNING COUNTER NUMBER 0 (FRCPS_0) ------------------------------------------------------------

        // ------------------------------------------------------------------------
		if (reg_ps_ctlr_i.range(0,0) == 1 && (pl_event_cmd_0_i != pl_event_cmd_0_prev )) {
			frcps_0_enable = 0;
			pl_event_cmd_0_prev = pl_event_cmd_0_i;

    	} else if (reg_ps_cnt_0_en_i == 0 ) {

			frcps_0_enable = 0;
			frcps_ps_stop_counter_0_Img++;

		} else if (reg_ps_cnt_0_en_i == 1 ) {

			frcps_0_enable = 1;
			frcps_ps_start_counter_0_Img++;
		} else {
			pl_event_cmd_0_prev = pl_event_cmd_0_i;
		}

		// ------------------------------- Main Counter function --------------------------------------------------------------------------------
		if (frcps_0_enable == 0) {

			reg_ps_cnt_0_value_o = frcps_0_value_Img;

		} else {

			reg_ps_cnt_0_value_o = frcps_0_value_Img++;

		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPS_0) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------


		 //  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PS.
		// ---------- START PF (FRCPS_1) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PS FREE RUNNING COUNTER NUMBER 1 (FRCPS_1) ------------------------------------------------------------

		// ------------------------------------------------------------------------
		if (reg_ps_ctlr_i.range(1,1) == 1 && (pl_event_cmd_1_i != pl_event_cmd_1_prev )) {
			frcps_1_enable = 0;
			pl_event_cmd_1_prev = pl_event_cmd_1_i;

		} else if (reg_ps_cnt_1_en_i==0 ) {

			frcps_1_enable = 0;
			frcps_ps_stop_counter_1_Img++;

		} else if (reg_ps_cnt_1_en_i==1  ) {

			frcps_1_enable = 1;
			frcps_ps_start_counter_1_Img++;

		} else {
			pl_event_cmd_1_prev = pl_event_cmd_1_i;
		}

		// ------------------------------- Main Counter function --------------------------------------------------------------------------------
		if (frcps_1_enable == 0) {

			reg_ps_cnt_1_value_o = frcps_1_value_Img;

		} else {

			reg_ps_cnt_1_value_o = frcps_1_value_Img++;

		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPS_1) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------

		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PS.
		// ---------- START PF (FRCPS_2) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PS FREE RUNNING COUNTER NUMBER 2 (FRCPS_2) ------------------------------------------------------------

		// ------------------------------------------------------------------------
		if (reg_ps_ctlr_i.range(2,2) == 1 && (pl_event_cmd_2_i != pl_event_cmd_2_prev )) {
			frcps_2_enable = 0;
			pl_event_cmd_2_prev = pl_event_cmd_2_i;

		} else if (reg_ps_cnt_2_en_i==0  ) {

			frcps_2_enable = 0;
			frcps_ps_stop_counter_2_Img++;

		} else if (reg_ps_cnt_2_en_i==1 ) {

			frcps_2_enable = 1;
			frcps_ps_start_counter_2_Img++;

		} else {

			pl_event_cmd_2_prev = pl_event_cmd_2_i;
		}

		// ------------------------------- Main Counter function --------------------------------------------------------------------------------
		if (frcps_2_enable == 0) {

			reg_ps_cnt_2_value_o = frcps_2_value_Img;

		} else {

			reg_ps_cnt_2_value_o = frcps_2_value_Img++;

		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPS_2) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------


		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PS.
		// ---------- START PF (FRCPS_3) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PS FREE RUNNING COUNTER NUMBER 3 (FRCPS_3) ------------------------------------------------------------

		// ------------------------------------------------------------------------
		if (reg_ps_ctlr_i.range(3,3) == 1 && (pl_event_cmd_3_i != pl_event_cmd_3_prev )) {
			frcps_3_enable = 0;
			pl_event_cmd_3_prev = pl_event_cmd_3_i;

		} else if (reg_ps_cnt_3_en_i==0  ) {

			frcps_3_enable = 0;
			frcps_ps_stop_counter_3_Img++;

		} else if (reg_ps_cnt_3_en_i==1   ) {

			frcps_3_enable = 1;
			frcps_ps_start_counter_3_Img++;

		} else {

			pl_event_cmd_3_prev = pl_event_cmd_3_i;
		}

		// ------------------------------- Main Counter function --------------------------------------------------------------------------------
		if (frcps_3_enable == 0) {

			reg_ps_cnt_3_value_o = frcps_3_value_Img;

		} else {

			reg_ps_cnt_3_value_o = frcps_3_value_Img++;

		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPS_3) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------



		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PS.
		// ---------- START PF (FRCPS_4) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PS FREE RUNNING COUNTER NUMBER 4 (FRCPS_4) ------------------------------------------------------------
		// --------------------- checks the interrupt signals ----------------------------------------------------------------------------------------------------

		// ------------------------------------------------------------------------
		if (reg_ps_ctlr_i.range(4,4) == 1 && (pl_event_cmd_4_i != pl_event_cmd_4_prev )) {
			frcps_4_enable = 0;
			pl_event_cmd_4_prev = pl_event_cmd_4_i;


		} else if (reg_ps_cnt_4_en_i==0  ) {

			frcps_4_enable = 0;
			frcps_ps_stop_counter_4_Img++;


		} else if (reg_ps_cnt_4_en_i==1  ) {

			frcps_4_enable = 1;
			frcps_ps_start_counter_4_Img++;

		} else {

			pl_event_cmd_4_prev = pl_event_cmd_4_i;
		}

		// ------------------------------- Main Counter function --------------------------------------------------------------------------------
		if (frcps_4_enable == 0) {

			reg_ps_cnt_4_value_o = frcps_4_value_Img;

		} else {

			reg_ps_cnt_4_value_o = frcps_4_value_Img++;

		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPS_4) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------



		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PS.
		// ---------- START PF (FRCPS_5) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PS FREE RUNNING COUNTER NUMBER 5 (FRCPS_5) ------------------------------------------------------------

		// ------------------------------------------------------------------------
		if (reg_ps_ctlr_i.range(5,5) == 1 && (pl_event_cmd_5_i != pl_event_cmd_5_prev  )) {
//		if (reg_ps_ctlr_i.range(0,0) == 1 && frcps_0_pndirq == 1) {
			frcps_5_enable = 0;
			pl_event_cmd_5_prev = pl_event_cmd_5_i;


		} else if (reg_ps_cnt_5_en_i==0  ) {

			frcps_5_enable = 0;
			frcps_ps_stop_counter_5_Img++;

		} else if (reg_ps_cnt_5_en_i==1  ) {

			frcps_5_enable = 1;
			frcps_ps_start_counter_5_Img++;

		} else {
			pl_event_cmd_5_prev = pl_event_cmd_5_i;
		}

		// ------------------------------- Main Counter function --------------------------------------------------------------------------------
		if (frcps_5_enable == 0) {

			reg_ps_cnt_5_value_o = frcps_5_value_Img;

		} else {

			reg_ps_cnt_5_value_o = frcps_5_value_Img++;

		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPS_5) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------


		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PS.
		// ---------- START PF (FRCPS_6) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PS FREE RUNNING COUNTER NUMBER 6 (FRCPS_6) ------------------------------------------------------------

		// ------------------------------------------------------------------------
		if (reg_ps_ctlr_i.range(6,6) == 1 && (pl_event_cmd_6_i != pl_event_cmd_6_prev )) {
//		if (reg_ps_ctlr_i.range(0,0) == 1 && frcps_0_pndirq == 1) {
			frcps_6_enable = 0;
			pl_event_cmd_6_prev = pl_event_cmd_6_i;

		} else if (reg_ps_cnt_6_en_i==0  ) {

			frcps_6_enable = 0;
			frcps_ps_stop_counter_6_Img++;

		} else if (reg_ps_cnt_6_en_i==1  ) {

			frcps_6_enable = 1;
			frcps_ps_start_counter_6_Img++;

		} else {

			pl_event_cmd_6_prev = pl_event_cmd_6_i;
		}
		// ------------------------------- Main Counter function --------------------------------------------------------------------------------
		if (frcps_6_enable == 0) {

			reg_ps_cnt_6_value_o = frcps_6_value_Img;

		} else {

			reg_ps_cnt_6_value_o = frcps_6_value_Img++;

		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPS_6) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------



		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PS.
		// ---------- START PF (FRCPS_7) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PS FREE RUNNING COUNTER NUMBER 7 (FRCPS_7) ------------------------------------------------------------

		// ------------------------------------------------------------------------
		if (reg_ps_ctlr_i.range(7,7) == 1 && (pl_event_cmd_7_i != pl_event_cmd_7_prev  )) {
//		if (reg_ps_ctlr_i.range(0,0) == 1 && frcps_0_pndirq == 1) {
			frcps_7_enable = 0;
			pl_event_cmd_7_prev = pl_event_cmd_7_i;

		} else if (reg_ps_cnt_7_en_i==0  ) {

			frcps_7_enable = 0;
			frcps_ps_stop_counter_7_Img++;

		} else if (reg_ps_cnt_7_en_i==1  ) {

			frcps_7_enable = 1;
			frcps_ps_start_counter_7_Img++;
		} else {
			pl_event_cmd_7_prev = pl_event_cmd_7_i;

		}
		// ------------------------------- Main Counter function --------------------------------------------------------------------------------
		if (frcps_7_enable == 0) {

			reg_ps_cnt_7_value_o = frcps_7_value_Img;

		} else {

			reg_ps_cnt_7_value_o = frcps_7_value_Img++;

		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPS_7) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------



		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PS.
		// ---------- START PF (FRCPS_8) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PS FREE RUNNING COUNTER NUMBER 8 (FRCPS_8) ------------------------------------------------------------

		// ------------------------------------------------------------------------
		if (reg_ps_ctlr_i.range(8,8) == 1 && (pl_event_cmd_8_i != pl_event_cmd_8_prev  )) {
//		if (reg_ps_ctlr_i.range(0,0) == 1 && frcps_0_pndirq == 1) {
			frcps_8_enable = 0;
			pl_event_cmd_8_prev = pl_event_cmd_8_i;

		} else if (reg_ps_cnt_8_en_i==0  ) {

			frcps_8_enable = 0;
			frcps_ps_stop_counter_8_Img++;

		} else if (reg_ps_cnt_8_en_i==1  ) {

			frcps_8_enable = 1;
			frcps_ps_start_counter_8_Img++;

		} else {
			pl_event_cmd_8_prev = pl_event_cmd_8_i;
		}
		// ------------------------------- Main Counter function --------------------------------------------------------------------------------
		if (frcps_8_enable == 0) {

			reg_ps_cnt_8_value_o = frcps_8_value_Img;

		} else {

			reg_ps_cnt_8_value_o = frcps_8_value_Img++;

		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPS_8) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------



		//  ------------------------------------------------------------------------------------------------------------------------------------------------------
		// following free-running counters are controlled from the PS.
		// ---------- START PF (FRCPS_9) -------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------- PS FREE RUNNING COUNTER NUMBER 9 (FRCPS_9) ------------------------------------------------------------

		// ------------------------------------------------------------------------
		if (reg_ps_ctlr_i.range(9,9) == 1 && (pl_event_cmd_9_i != pl_event_cmd_9_prev )) {

			frcps_9_enable = 0;
			pl_event_cmd_9_prev = pl_event_cmd_9_i;

		} else if (reg_ps_cnt_9_en_i==0  ) {

			frcps_9_enable = 0;
			frcps_ps_stop_counter_9_Img++;

		} else if (reg_ps_cnt_9_en_i==1  ) {

			frcps_9_enable = 1;
			frcps_ps_start_counter_9_Img++;

		} else {
			pl_event_cmd_9_prev = pl_event_cmd_9_i;

		}
		// ------------------------------- Main Counter function --------------------------------------------------------------------------------
		if (frcps_9_enable == 0) {

			reg_ps_cnt_9_value_o = frcps_9_value_Img;

		} else {

			reg_ps_cnt_9_value_o = frcps_9_value_Img++;

		}
		//---------------------------------------------------------------------------------------------------------------------------------------
		// ----------------- END OF (FRCPS_9) ---------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------------------------------------




    }


    reg_ps_start_cnt_0_value_o = frcps_ps_start_counter_0_Img;
    reg_ps_start_cnt_1_value_o = frcps_ps_start_counter_1_Img;
    reg_ps_start_cnt_2_value_o = frcps_ps_start_counter_2_Img;
    reg_ps_start_cnt_3_value_o = frcps_ps_start_counter_3_Img;
    reg_ps_start_cnt_4_value_o = frcps_ps_start_counter_4_Img;
    reg_ps_start_cnt_5_value_o = frcps_ps_start_counter_5_Img;
    reg_ps_start_cnt_6_value_o = frcps_ps_start_counter_6_Img;
    reg_ps_start_cnt_7_value_o = frcps_ps_start_counter_7_Img;
    reg_ps_start_cnt_8_value_o = frcps_ps_start_counter_8_Img;
    reg_ps_start_cnt_9_value_o = frcps_ps_start_counter_9_Img;

    reg_ps_stop_cnt_0_value_o = frcps_ps_stop_counter_0_Img;
    reg_ps_stop_cnt_1_value_o = frcps_ps_stop_counter_1_Img;
	reg_ps_stop_cnt_2_value_o = frcps_ps_stop_counter_2_Img;
	reg_ps_stop_cnt_3_value_o = frcps_ps_stop_counter_3_Img;
	reg_ps_stop_cnt_4_value_o = frcps_ps_stop_counter_4_Img;
	reg_ps_stop_cnt_5_value_o = frcps_ps_stop_counter_5_Img;
	reg_ps_stop_cnt_6_value_o = frcps_ps_stop_counter_6_Img;
	reg_ps_stop_cnt_7_value_o = frcps_ps_stop_counter_7_Img;
	reg_ps_stop_cnt_8_value_o = frcps_ps_stop_counter_8_Img;
	reg_ps_stop_cnt_9_value_o = frcps_ps_stop_counter_9_Img;

    reg_pl_start_cnt_0_value_o = frcps_pl_start_counter_0_Img;
    reg_pl_start_cnt_1_value_o = frcps_pl_start_counter_1_Img;
    reg_pl_start_cnt_2_value_o = frcps_pl_start_counter_2_Img;
    reg_pl_start_cnt_3_value_o = frcps_pl_start_counter_3_Img;
    reg_pl_start_cnt_4_value_o = frcps_pl_start_counter_4_Img;
    reg_pl_start_cnt_5_value_o = frcps_pl_start_counter_5_Img;
    reg_pl_start_cnt_6_value_o = frcps_pl_start_counter_6_Img;
    reg_pl_start_cnt_7_value_o = frcps_pl_start_counter_7_Img;
    reg_pl_start_cnt_8_value_o = frcps_pl_start_counter_8_Img;
    reg_pl_start_cnt_9_value_o = frcps_pl_start_counter_9_Img;
    reg_pl_start_cnt_10_value_o = frcps_pl_start_counter_10_Img;
    reg_pl_start_cnt_11_value_o = frcps_pl_start_counter_11_Img;
    reg_pl_start_cnt_12_value_o = frcps_pl_start_counter_12_Img;
    reg_pl_start_cnt_13_value_o = frcps_pl_start_counter_13_Img;
    reg_pl_start_cnt_14_value_o = frcps_pl_start_counter_14_Img;
    reg_pl_start_cnt_15_value_o = frcps_pl_start_counter_15_Img;
    reg_pl_start_cnt_16_value_o = frcps_pl_start_counter_16_Img;
    reg_pl_start_cnt_17_value_o = frcps_pl_start_counter_17_Img;
    reg_pl_start_cnt_18_value_o = frcps_pl_start_counter_18_Img;
    reg_pl_start_cnt_19_value_o = frcps_pl_start_counter_19_Img;

    reg_pl_stop_cnt_0_value_o = frcps_pl_stop_counter_0_Img;
    reg_pl_stop_cnt_1_value_o = frcps_pl_stop_counter_1_Img;
	reg_pl_stop_cnt_2_value_o = frcps_pl_stop_counter_2_Img;
	reg_pl_stop_cnt_3_value_o = frcps_pl_stop_counter_3_Img;
	reg_pl_stop_cnt_4_value_o = frcps_pl_stop_counter_4_Img;
	reg_pl_stop_cnt_5_value_o = frcps_pl_stop_counter_5_Img;
	reg_pl_stop_cnt_6_value_o = frcps_pl_stop_counter_6_Img;
	reg_pl_stop_cnt_7_value_o = frcps_pl_stop_counter_7_Img;
	reg_pl_stop_cnt_8_value_o = frcps_pl_stop_counter_8_Img;
	reg_pl_stop_cnt_9_value_o = frcps_pl_stop_counter_9_Img;
	reg_pl_stop_cnt_10_value_o = frcps_pl_stop_counter_10_Img;
	reg_pl_stop_cnt_11_value_o = frcps_pl_stop_counter_11_Img;
	reg_pl_stop_cnt_12_value_o = frcps_pl_stop_counter_12_Img;
	reg_pl_stop_cnt_13_value_o = frcps_pl_stop_counter_13_Img;
	reg_pl_stop_cnt_14_value_o = frcps_pl_stop_counter_14_Img;
	reg_pl_stop_cnt_15_value_o = frcps_pl_stop_counter_15_Img;
	reg_pl_stop_cnt_16_value_o = frcps_pl_stop_counter_16_Img;
	reg_pl_stop_cnt_17_value_o = frcps_pl_stop_counter_17_Img;
	reg_pl_stop_cnt_18_value_o = frcps_pl_stop_counter_18_Img;
	reg_pl_stop_cnt_19_value_o = frcps_pl_stop_counter_19_Img;

	reg_pl_max_value_1_o = max_value_buffer_1;
	reg_pl_max_value_2_o = max_value_buffer_2;


}

