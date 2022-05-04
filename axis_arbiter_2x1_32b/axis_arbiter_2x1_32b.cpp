#include "hls_lib.h"


enum states { start, Payload1, Payload2};

void axis_arbitrator_2x1_32 (
							  stream<uaxis32_t> *input1,
							  stream<uaxis32_t> *input2,
							  stream<uaxis32_t> &output
							  )
{
#pragma HLS PIPELINE II=1
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis off port=output
#pragma HLS INTERFACE axis register both port=input2
#pragma HLS INTERFACE axis register both port=input1

	static enum states state = start;
	static uaxis32_t Packet1, Packet2;
	static uint1 pro1_lock=0, pro2_lock=0;

	if (input1->read_nb(Packet1) && pro1_lock == 0) {

		output.write(Packet1);
		pro1_lock = 1;

	} else if ( input2->read_nb(Packet2) && pro2_lock == 0) {

		output.write(Packet2);
		pro2_lock = 1;

	} else {

		pro1_lock = 0;
		pro2_lock = 0;

	}

}
