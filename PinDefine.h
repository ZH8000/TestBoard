#ifndef __PIN_DEFINE_H__
#define __PIN_DEFINE_H__

	#define STARTER_KIT_EMU
	
	#ifdef STARTER_KIT_EMU
		#define LCR_CHANNEL_1							P3_0
		#define LCR_CHANNEL_2							P3_2
		#define LCR_CHANNEL_3							P3_4

		#define LC_CHANNEL_1							P3_1
		#define LC_CHANNEL_2							P3_3
		#define LC_CHANNEL_3							P3_5

		#define HV_READY_1								P4_0
		#define HV_READY_2								P4_2
		#define HV_READY_3								P4_4

		#define HV_FAULT_1								P4_1
		#define HV_FAULT_2								P4_3
		#define HV_FAULT_3								P4_5

		#define	HV_CHANNEL								P3_6
		#define CHARGE_CHANNEL						P3_7
		#define DISCHARGE_CHANNEL					P1_2
	#else
		#define LCR_CHANNEL_1							P1_0
		#define LCR_CHANNEL_2							P1_2
		#define LCR_CHANNEL_3							P1_4

		#define LC_CHANNEL_1							P1_1
		#define LC_CHANNEL_2							P1_3
		#define LC_CHANNEL_3							P1_5

		#define HV_READY_1								P4_0
		#define HV_READY_2								P4_2
		#define HV_READY_3								P4_4

		#define HV_FAULT_1								P4_1
		#define HV_FAULT_2								P4_3
		#define HV_FAULT_3								P4_5

		#define	HV_CHANNEL								P3_7
		#define CHARGE_CHANNEL						P3_4
		#define DISCHARGE_CHANNEL					P4_6
	#endif

#define SET_LCR_CHANNEL_1  				LCR_CHANNEL_1 = 1
#define SET_LCR_CHANNEL_2 				LCR_CHANNEL_2 = 1
#define SET_LCR_CHANNEL_3 				LCR_CHANNEL_3 = 1
#define SET_LC_CHANNEL_1  				LC_CHANNEL_1 = 1
#define SET_LC_CHANNEL_2  				LC_CHANNEL_2 = 1
#define SET_LC_CHANNEL_3  				LC_CHANNEL_3 = 1
#define SET_HV_CHANNEL						HV_CHANNEL = 1
#define SET_CHARGE_CHANNEL				CHARGE_CHANNEL = 1
#define SET_DISCHARGE_CHANNEL			DISCHARGE_CHANNEL = 1

#define RESET_LCR_CHANNEL_1  			LCR_CHANNEL_1 = 0
#define RESET_LCR_CHANNEL_2  			LCR_CHANNEL_2 = 0
#define RESET_LCR_CHANNEL_3  			LCR_CHANNEL_3 = 0
#define RESET_LC_CHANNEL_1  			LC_CHANNEL_1 = 0
#define RESET_LC_CHANNEL_2  			LC_CHANNEL_2 = 0
#define RESET_LC_CHANNEL_3  			LC_CHANNEL_3 = 0
#define RESET_HV_CHANNEL					HV_CHANNEL = 0
#define RESET_CHARGE_CHANNEL			CHARGE_CHANNEL = 0
#define RESET_DISCHARGE_CHANNEL		DISCHARGE_CHANNEL = 0

#define READ_HV_READY_1						HV_READY_1
#define READ_HV_READY_2						HV_READY_2
#define READ_HV_READY_3						HV_READY_3

#define READ_HV_FAULT_1						HV_FAULT_1
#define READ_HV_FAULT_2						HV_FAULT_2
#define READ_HV_FAULT_3						HV_FAULT_3

#endif