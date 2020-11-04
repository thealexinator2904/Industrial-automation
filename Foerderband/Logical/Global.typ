
TYPE
	error_codes : 
		(
		KEIN_ERROR,
		MOTOR_LAEUFT_ZU_LANGE,
		KEINE_DRUCKLUFT,
		ERROR_ANTRIEB
		);
	programm_states : 
		(
		EMER_HALT,
		INIT,
		STOP,
		GO_PRE_WORK,
		DETECT,
		WORK,
		GO_AFT_WORK,
		WAIT_TO_LET_GO,
		LET_GO,
		MANUAL,
		ERROR
		);
	koppel_state : 
		(
		RTR,
		RTT,
		BUSY
		);
END_TYPE
