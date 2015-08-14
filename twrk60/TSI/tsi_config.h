/*
 * tsi_config.h
 *
 *  Created on: Jul 28, 2015
 *      Author: lincoln
 */

#ifndef TSI_CONFIG_H_
#define TSI_CONFIG_H_

#include "MK60DZ10.h"
#include "Mk60.h"
void tsi_init(void){
	//Enable clock gates
	SIM_SCGC5 |= (SIM_SCGC5_TSI_MASK);
	SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK);
	PORTA_PCR4 = PORT_PCR_MUX(0);
	//Enable ALT0 for portA4
	//Configure the number of scans and enable the interrupt
	TSI0_GENCS |= ((TSI_GENCS_NSCN(10))|(TSI_GENCS_TSIIE_MASK)|(TSI_GENCS_PS(3)));
	TSI0_SCANC |= ((TSI_SCANC_EXTCHRG(3))|(TSI_SCANC_REFCHRG(31))|
	(TSI_SCANC_DELVOL(7))|(TSI_SCANC_SMOD(0))|(TSI_SCANC_AMPSC(0)));
	//Enable the channels desired
	TSI0_PEN |= (TSI_PEN_PEN5_MASK|TSI_PEN_PEN7_MASK|
	TSI_PEN_PEN8_MASK|TSI_PEN_PEN9_MASK);
	TSI0_THRESHLD5 = (uint32_t)((TSI0_CHAN5_OFFSET));
	TSI0_THRESHLD7 = (uint32_t)((TSI_CHAN7_OFFSET));
	TSI0_THRESHLD8 = (uint32_t)((TSI_CHAN8_OFFSET));
	TSI0_THRESHLD9 = (uint32_t)((TSI_CHAN9_OFFSET));
	//Enable TSI module
	TSI0_GENCS |= (TSI_GENCS_TSIEN_MASK);
	//Enables TSI
}



#endif /* TSI_CONFIG_H_ */

