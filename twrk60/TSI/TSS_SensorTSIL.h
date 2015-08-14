/***********************************************************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
*********************************************************************************************************************//*!
*
* @file   TSS_SensorTSIL.h
*
* @brief  Functions Prototypes, constants, variables and macros for the sensing of electrodes
*
* @version 1.0.17.0
*
* @date Sep-12-2012
*
*
***********************************************************************************************************************/

#ifndef TSS_SENSORTSIL_H
  #define TSS_SENSORTSIL_H

  #include "TSS_Sensor.h"

  /***************************** Types ***************************/

  #if TSS_HCS08_MCU || TSS_CFV1_MCU

    #if TSS_USE_SIMPLE_LOW_LEVEL
  
      /* Electrode Data */
      typedef struct {
        const UINT8 tsil_cu8ModuleID;
      } TSS_TSIL_ELECTRODE_ROMDATA;
      
      typedef struct {
        UINT8 u8Dummy;
      } TSS_TSIL_ELECTRODE_RAMDATA;

    #else /* TSS_USE_SIMPLE_LOW_LEVEL == 0 */
    
      typedef enum
      {
        TSIL_EOSF_STATE_NONE    = 0,
        TSIL_EOSF_STATE_REGULAR = 1,
        TSIL_EOSF_STATE_ERROR   = 2,
        TSIL_EOSF_STATE_PROCESS = 3
      } TSS_TSIL_EOSF_STATES;

      typedef enum
      {
        TSIL_SCNIP_STATE_NONE    = 0,
        TSIL_SCNIP_STATE_WAIT    = 1,
        TSIL_SCNIP_STATE_PROCESS = 2
      } TSS_TSIL_SCNIP_STATES;

      /*! TSIL - Peripheral register structure */
      typedef struct TSIL_MemMap {
        UINT8 CS0;
        UINT8 CS1;
        UINT8 CS2;
        UINT8 CS3;
        union {
            UINT16 Word;
            UINT8 Byte[2];
        } PEN; 
        union {
            UINT16 Word;
            UINT8 Byte[2];
        } CNT;
      } volatile *TSS_TSIL_MemMapPtr;
      
      /* Method Data */
      typedef struct {
        const TSS_METHOD_CONTROL tsil_cpfMethodControl;
        const UINT8 * const tsil_cpsModule;
        const UINT16 *tsil_cpu16ChannelCounterBuffer;
      } TSS_TSIL_METHOD_ROMDATA;
      
      typedef struct {
        volatile TSS_TSIL_EOSF_STATES tsil_eEndOfScanState;
        volatile UINT8 tsil_u8StartElectrode;
        volatile TSS_TSIL_SCNIP_STATES tsil_eScanInProgressState;
      } TSS_TSIL_METHOD_RAMDATA;
  
      /* Electrode Data */
      typedef struct {
        const TSS_TSIL_METHOD_ROMDATA * const tsil_cpsMethodROMData; 
        const TSS_TSIL_METHOD_RAMDATA volatile * tsil_cpsMethodRAMData;
        const UINT8 tsil_cu8ChannelNum;
      } TSS_TSIL_ELECTRODE_ROMDATA;    
      
      typedef struct {
        UINT8 u8Dummy;
      } TSS_TSIL_ELECTRODE_RAMDATA;
   
    #endif /* TSS_USE_SIMPLE_LOW_LEVEL == 0 */

  #elif TSS_KINETIS_MCU || TSS_CFM_MCU

      typedef enum
      {
        TSIL_EOSF_STATE_NONE    = 0,
        TSIL_EOSF_STATE_REGULAR = 1,
        TSIL_EOSF_STATE_ERROR   = 2,
        TSIL_EOSF_STATE_PROCESS = 3
      } TSS_TSIL_EOSF_STATES;

      typedef enum
      {
        TSIL_SCNIP_STATE_NONE    = 0,
        TSIL_SCNIP_STATE_WAIT    = 1,
        TSIL_SCNIP_STATE_PROCESS = 2
      } TSS_TSIL_SCNIP_STATES;

      /*! TSIL - Peripheral register structure */
      typedef struct TSIL_MemMap {
        UINT32 GENCS;
        UINT32 DATA;
        UINT32 TSHD;
      } volatile *TSS_TSIL_MemMapPtr;
      
      /* Method Data */
      typedef struct {
        const TSS_METHOD_CONTROL tsil_cpfMethodControl;
        const UINT32 * const tsil_cpsModule;
        const UINT16 *tsil_cpu16ChannelCounterBuffer;
        const UINT8 tsil_u8ModuleIRQNum;
        const UINT8 tsil_u8LowPowerControlSource;
      } TSS_TSIL_METHOD_ROMDATA;
      
      typedef struct {
        volatile TSS_TSIL_EOSF_STATES tsil_eEndOfScanState;
        volatile UINT8 tsil_u8StartElectrode;
        volatile TSS_TSIL_SCNIP_STATES tsil_eScanInProgressState;
        volatile UINT16 tsil_u16PEN;
        UINT16 tsi_au16Resolution;
      } TSS_TSIL_METHOD_RAMDATA;
  
      /* Electrode Data */
      typedef struct {
        const TSS_TSIL_METHOD_ROMDATA * const tsil_cpsMethodROMData; 
        const TSS_TSIL_METHOD_RAMDATA volatile * tsil_cpsMethodRAMData;
        const UINT8 tsil_cu8ChannelNum;
      } TSS_TSIL_ELECTRODE_ROMDATA;    
      
      typedef struct {
        UINT8 u8Dummy;
      } TSS_TSIL_ELECTRODE_RAMDATA;

  #else /* End of TSS_KINETIS_MCU || TSS_CFM_MCU */
    #error "TSS - Not supported MCU used"
  #endif

  /************************ Function prototypes *********************/

  extern UINT8 TSIL_SensorInit(UINT8 u8Command);
  /*
  function:   TSIL_SensorInit
  brief:      Initializes modules for the sensing of the electrodes.
  param:      Command to be performed                           
  return:     Status code                              
  */
    
  extern UINT8 TSIL_SampleElectrode(UINT8 u8ElecNum, UINT8 u8Command);
  /*
  function:   TSIL_SampleElectrode
  brief:      Performs a valid reading of one electrode, and returns a status code
  param:      u8ElecNum - Number of electrode to be scanned
              u8Command - Measurement command
  return:     Status code
  */

  /*********************************************************************************
  *    Determination if TSIL method is used for later conditional TSIL module 
  *    initialization
  *********************************************************************************/

  #define TSS_TSIL_USED           (TSS_DETECT_EL_MODULE(0,TSIL) || TSS_DETECT_EL_MODULE(1,TSIL) || TSS_DETECT_EL_MODULE(2,TSIL) || TSS_DETECT_EL_MODULE(3,TSIL) || TSS_DETECT_EL_MODULE(4,TSIL) || TSS_DETECT_EL_MODULE(5,TSIL) || TSS_DETECT_EL_MODULE(6,TSIL) || TSS_DETECT_EL_MODULE(7,TSIL) || TSS_DETECT_EL_MODULE(8,TSIL) || TSS_DETECT_EL_MODULE(9,TSIL) || TSS_DETECT_EL_MODULE(10,TSIL) || TSS_DETECT_EL_MODULE(11,TSIL) || TSS_DETECT_EL_MODULE(12,TSIL) || TSS_DETECT_EL_MODULE(13,TSIL) || TSS_DETECT_EL_MODULE(14,TSIL) || TSS_DETECT_EL_MODULE(15,TSIL) || TSS_DETECT_EL_MODULE(16,TSIL) || TSS_DETECT_EL_MODULE(17,TSIL) || TSS_DETECT_EL_MODULE(18,TSIL) || TSS_DETECT_EL_MODULE(19,TSIL) || TSS_DETECT_EL_MODULE(20,TSIL) || TSS_DETECT_EL_MODULE(21,TSIL) || TSS_DETECT_EL_MODULE(22,TSIL) || TSS_DETECT_EL_MODULE(23,TSIL) || TSS_DETECT_EL_MODULE(24,TSIL) || TSS_DETECT_EL_MODULE(25,TSIL) || TSS_DETECT_EL_MODULE(26,TSIL) || TSS_DETECT_EL_MODULE(27,TSIL) || TSS_DETECT_EL_MODULE(28,TSIL) || TSS_DETECT_EL_MODULE(29,TSIL) || TSS_DETECT_EL_MODULE(30,TSIL) || TSS_DETECT_EL_MODULE(31,TSIL) || TSS_DETECT_EL_MODULE(32,TSIL) || TSS_DETECT_EL_MODULE(33,TSIL) || TSS_DETECT_EL_MODULE(34,TSIL) || TSS_DETECT_EL_MODULE(35,TSIL) || TSS_DETECT_EL_MODULE(36,TSIL) || TSS_DETECT_EL_MODULE(37,TSIL) || TSS_DETECT_EL_MODULE(38,TSIL) || TSS_DETECT_EL_MODULE(39,TSIL) || TSS_DETECT_EL_MODULE(40,TSIL) || TSS_DETECT_EL_MODULE(41,TSIL) || TSS_DETECT_EL_MODULE(42,TSIL) || TSS_DETECT_EL_MODULE(43,TSIL) || TSS_DETECT_EL_MODULE(44,TSIL) || TSS_DETECT_EL_MODULE(45,TSIL) || TSS_DETECT_EL_MODULE(46,TSIL) || TSS_DETECT_EL_MODULE(47,TSIL) || TSS_DETECT_EL_MODULE(48,TSIL) || TSS_DETECT_EL_MODULE(49,TSIL) || TSS_DETECT_EL_MODULE(50,TSIL) || TSS_DETECT_EL_MODULE(51,TSIL) || TSS_DETECT_EL_MODULE(52,TSIL) || TSS_DETECT_EL_MODULE(53,TSIL) || TSS_DETECT_EL_MODULE(54,TSIL) || TSS_DETECT_EL_MODULE(55,TSIL) || TSS_DETECT_EL_MODULE(56,TSIL) || TSS_DETECT_EL_MODULE(57,TSIL) || TSS_DETECT_EL_MODULE(58,TSIL) || TSS_DETECT_EL_MODULE(59,TSIL) || TSS_DETECT_EL_MODULE(60,TSIL) || TSS_DETECT_EL_MODULE(61,TSIL) || TSS_DETECT_EL_MODULE(62,TSIL) || TSS_DETECT_EL_MODULE(63,TSIL))
  #define TSS_TSIL0_USED          (TSS_DETECT_EL_MODULE(0,TSIL0) || TSS_DETECT_EL_MODULE(1,TSIL0) || TSS_DETECT_EL_MODULE(2,TSIL0) || TSS_DETECT_EL_MODULE(3,TSIL0) || TSS_DETECT_EL_MODULE(4,TSIL0) || TSS_DETECT_EL_MODULE(5,TSIL0) || TSS_DETECT_EL_MODULE(6,TSIL0) || TSS_DETECT_EL_MODULE(7,TSIL0) || TSS_DETECT_EL_MODULE(8,TSIL0) || TSS_DETECT_EL_MODULE(9,TSIL0) || TSS_DETECT_EL_MODULE(10,TSIL0) || TSS_DETECT_EL_MODULE(11,TSIL0) || TSS_DETECT_EL_MODULE(12,TSIL0) || TSS_DETECT_EL_MODULE(13,TSIL0) || TSS_DETECT_EL_MODULE(14,TSIL0) || TSS_DETECT_EL_MODULE(15,TSIL0) || TSS_DETECT_EL_MODULE(16,TSIL0) || TSS_DETECT_EL_MODULE(17,TSIL0) || TSS_DETECT_EL_MODULE(18,TSIL0) || TSS_DETECT_EL_MODULE(19,TSIL0) || TSS_DETECT_EL_MODULE(20,TSIL0) || TSS_DETECT_EL_MODULE(21,TSIL0) || TSS_DETECT_EL_MODULE(22,TSIL0) || TSS_DETECT_EL_MODULE(23,TSIL0) || TSS_DETECT_EL_MODULE(24,TSIL0) || TSS_DETECT_EL_MODULE(25,TSIL0) || TSS_DETECT_EL_MODULE(26,TSIL0) || TSS_DETECT_EL_MODULE(27,TSIL0) || TSS_DETECT_EL_MODULE(28,TSIL0) || TSS_DETECT_EL_MODULE(29,TSIL0) || TSS_DETECT_EL_MODULE(30,TSIL0) || TSS_DETECT_EL_MODULE(31,TSIL0) || TSS_DETECT_EL_MODULE(32,TSIL0) || TSS_DETECT_EL_MODULE(33,TSIL0) || TSS_DETECT_EL_MODULE(34,TSIL0) || TSS_DETECT_EL_MODULE(35,TSIL0) || TSS_DETECT_EL_MODULE(36,TSIL0) || TSS_DETECT_EL_MODULE(37,TSIL0) || TSS_DETECT_EL_MODULE(38,TSIL0) || TSS_DETECT_EL_MODULE(39,TSIL0) || TSS_DETECT_EL_MODULE(40,TSIL0) || TSS_DETECT_EL_MODULE(41,TSIL0) || TSS_DETECT_EL_MODULE(42,TSIL0) || TSS_DETECT_EL_MODULE(43,TSIL0) || TSS_DETECT_EL_MODULE(44,TSIL0) || TSS_DETECT_EL_MODULE(45,TSIL0) || TSS_DETECT_EL_MODULE(46,TSIL0) || TSS_DETECT_EL_MODULE(47,TSIL0) || TSS_DETECT_EL_MODULE(48,TSIL0) || TSS_DETECT_EL_MODULE(49,TSIL0) || TSS_DETECT_EL_MODULE(50,TSIL0) || TSS_DETECT_EL_MODULE(51,TSIL0) || TSS_DETECT_EL_MODULE(52,TSIL0) || TSS_DETECT_EL_MODULE(53,TSIL0) || TSS_DETECT_EL_MODULE(54,TSIL0) || TSS_DETECT_EL_MODULE(55,TSIL0) || TSS_DETECT_EL_MODULE(56,TSIL0) || TSS_DETECT_EL_MODULE(57,TSIL0) || TSS_DETECT_EL_MODULE(58,TSIL0) || TSS_DETECT_EL_MODULE(59,TSIL0) || TSS_DETECT_EL_MODULE(60,TSIL0) || TSS_DETECT_EL_MODULE(61,TSIL0) || TSS_DETECT_EL_MODULE(62,TSIL0) || TSS_DETECT_EL_MODULE(63,TSIL0))
  #define TSS_TSIL1_USED          (TSS_DETECT_EL_MODULE(0,TSIL1) || TSS_DETECT_EL_MODULE(1,TSIL1) || TSS_DETECT_EL_MODULE(2,TSIL1) || TSS_DETECT_EL_MODULE(3,TSIL1) || TSS_DETECT_EL_MODULE(4,TSIL1) || TSS_DETECT_EL_MODULE(5,TSIL1) || TSS_DETECT_EL_MODULE(6,TSIL1) || TSS_DETECT_EL_MODULE(7,TSIL1) || TSS_DETECT_EL_MODULE(8,TSIL1) || TSS_DETECT_EL_MODULE(9,TSIL1) || TSS_DETECT_EL_MODULE(10,TSIL1) || TSS_DETECT_EL_MODULE(11,TSIL1) || TSS_DETECT_EL_MODULE(12,TSIL1) || TSS_DETECT_EL_MODULE(13,TSIL1) || TSS_DETECT_EL_MODULE(14,TSIL1) || TSS_DETECT_EL_MODULE(15,TSIL1) || TSS_DETECT_EL_MODULE(16,TSIL1) || TSS_DETECT_EL_MODULE(17,TSIL1) || TSS_DETECT_EL_MODULE(18,TSIL1) || TSS_DETECT_EL_MODULE(19,TSIL1) || TSS_DETECT_EL_MODULE(20,TSIL1) || TSS_DETECT_EL_MODULE(21,TSIL1) || TSS_DETECT_EL_MODULE(22,TSIL1) || TSS_DETECT_EL_MODULE(23,TSIL1) || TSS_DETECT_EL_MODULE(24,TSIL1) || TSS_DETECT_EL_MODULE(25,TSIL1) || TSS_DETECT_EL_MODULE(26,TSIL1) || TSS_DETECT_EL_MODULE(27,TSIL1) || TSS_DETECT_EL_MODULE(28,TSIL1) || TSS_DETECT_EL_MODULE(29,TSIL1) || TSS_DETECT_EL_MODULE(30,TSIL1) || TSS_DETECT_EL_MODULE(31,TSIL1) || TSS_DETECT_EL_MODULE(32,TSIL1) || TSS_DETECT_EL_MODULE(33,TSIL1) || TSS_DETECT_EL_MODULE(34,TSIL1) || TSS_DETECT_EL_MODULE(35,TSIL1) || TSS_DETECT_EL_MODULE(36,TSIL1) || TSS_DETECT_EL_MODULE(37,TSIL1) || TSS_DETECT_EL_MODULE(38,TSIL1) || TSS_DETECT_EL_MODULE(39,TSIL1) || TSS_DETECT_EL_MODULE(40,TSIL1) || TSS_DETECT_EL_MODULE(41,TSIL1) || TSS_DETECT_EL_MODULE(42,TSIL1) || TSS_DETECT_EL_MODULE(43,TSIL1) || TSS_DETECT_EL_MODULE(44,TSIL1) || TSS_DETECT_EL_MODULE(45,TSIL1) || TSS_DETECT_EL_MODULE(46,TSIL1) || TSS_DETECT_EL_MODULE(47,TSIL1) || TSS_DETECT_EL_MODULE(48,TSIL1) || TSS_DETECT_EL_MODULE(49,TSIL1) || TSS_DETECT_EL_MODULE(50,TSIL1) || TSS_DETECT_EL_MODULE(51,TSIL1) || TSS_DETECT_EL_MODULE(52,TSIL1) || TSS_DETECT_EL_MODULE(53,TSIL1) || TSS_DETECT_EL_MODULE(54,TSIL1) || TSS_DETECT_EL_MODULE(55,TSIL1) || TSS_DETECT_EL_MODULE(56,TSIL1) || TSS_DETECT_EL_MODULE(57,TSIL1) || TSS_DETECT_EL_MODULE(58,TSIL1) || TSS_DETECT_EL_MODULE(59,TSIL1) || TSS_DETECT_EL_MODULE(60,TSIL1) || TSS_DETECT_EL_MODULE(61,TSIL1) || TSS_DETECT_EL_MODULE(62,TSIL1) || TSS_DETECT_EL_MODULE(63,TSIL1))

  #define TSS_TSIL_METHOD_USED    (TSS_DETECT_EL_METHOD(0,TSIL) || TSS_DETECT_EL_METHOD(1,TSIL) || TSS_DETECT_EL_METHOD(2,TSIL) || TSS_DETECT_EL_METHOD(3,TSIL) || TSS_DETECT_EL_METHOD(4,TSIL) || TSS_DETECT_EL_METHOD(5,TSIL) || TSS_DETECT_EL_METHOD(6,TSIL) || TSS_DETECT_EL_METHOD(7,TSIL) || TSS_DETECT_EL_METHOD(8,TSIL) || TSS_DETECT_EL_METHOD(9,TSIL) || TSS_DETECT_EL_METHOD(10,TSIL) || TSS_DETECT_EL_METHOD(11,TSIL) || TSS_DETECT_EL_METHOD(12,TSIL) || TSS_DETECT_EL_METHOD(13,TSIL) || TSS_DETECT_EL_METHOD(14,TSIL) || TSS_DETECT_EL_METHOD(15,TSIL) || TSS_DETECT_EL_METHOD(16,TSIL) || TSS_DETECT_EL_METHOD(17,TSIL) || TSS_DETECT_EL_METHOD(18,TSIL) || TSS_DETECT_EL_METHOD(19,TSIL) || TSS_DETECT_EL_METHOD(20,TSIL) || TSS_DETECT_EL_METHOD(21,TSIL) || TSS_DETECT_EL_METHOD(22,TSIL) || TSS_DETECT_EL_METHOD(23,TSIL) || TSS_DETECT_EL_METHOD(24,TSIL) || TSS_DETECT_EL_METHOD(25,TSIL) || TSS_DETECT_EL_METHOD(26,TSIL) || TSS_DETECT_EL_METHOD(27,TSIL) || TSS_DETECT_EL_METHOD(28,TSIL) || TSS_DETECT_EL_METHOD(29,TSIL) || TSS_DETECT_EL_METHOD(30,TSIL) || TSS_DETECT_EL_METHOD(31,TSIL) || TSS_DETECT_EL_METHOD(32,TSIL) || TSS_DETECT_EL_METHOD(33,TSIL) || TSS_DETECT_EL_METHOD(34,TSIL) || TSS_DETECT_EL_METHOD(35,TSIL) || TSS_DETECT_EL_METHOD(36,TSIL) || TSS_DETECT_EL_METHOD(37,TSIL) || TSS_DETECT_EL_METHOD(38,TSIL) || TSS_DETECT_EL_METHOD(39,TSIL) || TSS_DETECT_EL_METHOD(40,TSIL) || TSS_DETECT_EL_METHOD(41,TSIL) || TSS_DETECT_EL_METHOD(42,TSIL) || TSS_DETECT_EL_METHOD(43,TSIL) || TSS_DETECT_EL_METHOD(44,TSIL) || TSS_DETECT_EL_METHOD(45,TSIL) || TSS_DETECT_EL_METHOD(46,TSIL) || TSS_DETECT_EL_METHOD(47,TSIL) || TSS_DETECT_EL_METHOD(48,TSIL) || TSS_DETECT_EL_METHOD(49,TSIL) || TSS_DETECT_EL_METHOD(50,TSIL) || TSS_DETECT_EL_METHOD(51,TSIL) || TSS_DETECT_EL_METHOD(52,TSIL) || TSS_DETECT_EL_METHOD(53,TSIL) || TSS_DETECT_EL_METHOD(54,TSIL) || TSS_DETECT_EL_METHOD(55,TSIL) || TSS_DETECT_EL_METHOD(56,TSIL) || TSS_DETECT_EL_METHOD(57,TSIL) || TSS_DETECT_EL_METHOD(58,TSIL) || TSS_DETECT_EL_METHOD(59,TSIL) || TSS_DETECT_EL_METHOD(60,TSIL) || TSS_DETECT_EL_METHOD(61,TSIL) || TSS_DETECT_EL_METHOD(62,TSIL) || TSS_DETECT_EL_METHOD(63,TSIL))

  /****************** ROM & RAM Data prototypes ******************/

  #if TSS_N_ELECTRODES > 0
    #if (TSS_DETECT_EL_METHOD(0,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E0_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E0_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 1
    #if (TSS_DETECT_EL_METHOD(1,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E1_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E1_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 2
    #if (TSS_DETECT_EL_METHOD(2,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E2_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E2_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 3
    #if (TSS_DETECT_EL_METHOD(3,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E3_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E3_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 4
    #if (TSS_DETECT_EL_METHOD(4,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E4_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E4_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 5
    #if (TSS_DETECT_EL_METHOD(5,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E5_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E5_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 6
    #if (TSS_DETECT_EL_METHOD(6,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E6_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E6_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 7
    #if (TSS_DETECT_EL_METHOD(7,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E7_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E7_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 8
    #if (TSS_DETECT_EL_METHOD(8,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E8_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E8_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 9
    #if (TSS_DETECT_EL_METHOD(9,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E9_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E9_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 10
    #if (TSS_DETECT_EL_METHOD(10,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E10_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E10_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 11
    #if (TSS_DETECT_EL_METHOD(11,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E11_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E11_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 12
    #if (TSS_DETECT_EL_METHOD(12,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E12_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E12_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 13
    #if (TSS_DETECT_EL_METHOD(13,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E13_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E13_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 14
    #if (TSS_DETECT_EL_METHOD(14,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E14_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E14_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 15
    #if (TSS_DETECT_EL_METHOD(15,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E15_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E15_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 16
    #if (TSS_DETECT_EL_METHOD(16,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E16_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E16_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 17
    #if (TSS_DETECT_EL_METHOD(17,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E17_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E17_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 18
    #if (TSS_DETECT_EL_METHOD(18,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E18_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E18_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 19
    #if (TSS_DETECT_EL_METHOD(19,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E19_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E19_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 20
    #if (TSS_DETECT_EL_METHOD(20,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E20_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E20_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 21
    #if (TSS_DETECT_EL_METHOD(21,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E21_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E21_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 22
    #if (TSS_DETECT_EL_METHOD(22,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E22_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E22_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 23
    #if (TSS_DETECT_EL_METHOD(23,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E23_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E23_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 24
    #if (TSS_DETECT_EL_METHOD(24,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E24_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E24_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 25
    #if (TSS_DETECT_EL_METHOD(25,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E25_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E25_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 26
    #if (TSS_DETECT_EL_METHOD(26,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E26_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E26_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 27
    #if (TSS_DETECT_EL_METHOD(27,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E27_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E27_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 28
    #if (TSS_DETECT_EL_METHOD(28,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E28_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E28_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 29
    #if (TSS_DETECT_EL_METHOD(29,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E29_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E29_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 30
    #if (TSS_DETECT_EL_METHOD(30,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E30_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E30_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 31
    #if (TSS_DETECT_EL_METHOD(31,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E31_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E31_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 32
    #if (TSS_DETECT_EL_METHOD(32,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E32_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E32_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 33
    #if (TSS_DETECT_EL_METHOD(33,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E33_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E33_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 34
    #if (TSS_DETECT_EL_METHOD(34,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E34_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E34_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 35
    #if (TSS_DETECT_EL_METHOD(35,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E35_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E35_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 36
    #if (TSS_DETECT_EL_METHOD(36,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E36_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E36_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 37
    #if (TSS_DETECT_EL_METHOD(37,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E37_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E37_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 38
    #if (TSS_DETECT_EL_METHOD(38,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E38_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E38_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 39
    #if (TSS_DETECT_EL_METHOD(39,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E39_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E39_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 40
    #if (TSS_DETECT_EL_METHOD(40,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E40_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E40_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 41
    #if (TSS_DETECT_EL_METHOD(41,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E41_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E41_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 42
    #if (TSS_DETECT_EL_METHOD(42,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E42_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E42_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 43
    #if (TSS_DETECT_EL_METHOD(43,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E43_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E43_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 44
    #if (TSS_DETECT_EL_METHOD(44,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E44_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E44_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 45
    #if (TSS_DETECT_EL_METHOD(45,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E45_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E45_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 46
    #if (TSS_DETECT_EL_METHOD(46,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E46_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E46_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 47
    #if (TSS_DETECT_EL_METHOD(47,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E47_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E47_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 48
    #if (TSS_DETECT_EL_METHOD(48,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E48_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E48_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 49
    #if (TSS_DETECT_EL_METHOD(49,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E49_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E49_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 50
    #if (TSS_DETECT_EL_METHOD(50,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E50_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E50_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 51
    #if (TSS_DETECT_EL_METHOD(51,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E51_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E51_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 52
    #if (TSS_DETECT_EL_METHOD(52,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E52_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E52_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 53
    #if (TSS_DETECT_EL_METHOD(53,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E53_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E53_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 54
    #if (TSS_DETECT_EL_METHOD(54,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E54_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E54_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 55
    #if (TSS_DETECT_EL_METHOD(55,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E55_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E55_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 56
    #if (TSS_DETECT_EL_METHOD(56,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E56_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E56_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 57
    #if (TSS_DETECT_EL_METHOD(57,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E57_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E57_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 58
    #if (TSS_DETECT_EL_METHOD(58,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E58_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E58_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 59
    #if (TSS_DETECT_EL_METHOD(59,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E59_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E59_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 60
    #if (TSS_DETECT_EL_METHOD(60,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E60_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E60_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 61
    #if (TSS_DETECT_EL_METHOD(61,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E61_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E61_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 62
    #if (TSS_DETECT_EL_METHOD(62,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E62_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E62_RAMDATA_CONTEXT;
    #endif
  #endif

  #if TSS_N_ELECTRODES > 63
    #if (TSS_DETECT_EL_METHOD(63,TSIL))
      extern const TSS_TSIL_ELECTRODE_ROMDATA TSS_E63_ROMDATA_CONTEXT;
      extern       TSS_TSIL_ELECTRODE_RAMDATA TSS_E63_RAMDATA_CONTEXT;
    #endif
  #endif

  /*******************************************************
  ******        Determine what is needed             *****
  *******************************************************/

  #if TSS_DETECT_METHOD(TSIL)
    /* HW Timer */
    #ifndef TSS_HW_TIMER_USED
      #define TSS_HW_TIMER_USED      0
    #endif
    /* GPIO */
    #ifndef TSS_HW_GPIO_USED
      #define TSS_HW_GPIO_USED       0
    #endif
  #endif

  /*
  * Main TSI module determination for TSS_USE_SIMPLE_LOW_LEVEL = 1
  */

  #if TSS_USE_SIMPLE_LOW_LEVEL
    #if TSS_DETECT_MODULE(TSIL)
      #define TSS_TSIL_MAIN_MODULE_NAME   TSI 
    #elif TSS_DETECT_MODULE(TSIL0)
      #define TSS_TSIL_MAIN_MODULE_NAME   TSI0
    #elif TSS_DETECT_MODULE(TSIL1)
      #define TSS_TSIL_MAIN_MODULE_NAME   TSI1
    #else
      #define TSS_TSIL_MAIN_MODULE_NAME   UNUSED
    #endif
  #else
    #define TSS_TSIL_MAIN_MODULE_NAME   UNUSED
  #endif
        
  /*
  * Handler Body of the measurement method
  */
      
  /* Macros for TSIL register decoding */
  #define TSS_GET_TSIL_REGISTER_RESULT(res, suffix)       res##_##suffix
  #define TSS_GET_TSIL_REGISTER_CONV(text, suffix)        TSS_GET_TSIL_REGISTER_RESULT(text, suffix)
  #define TSS_GET_TSIL_REGISTER_TYPE(module,suffix)       TSS_GET_TSIL_REGISTER_CONV(module, suffix)
  
  #define TSS_GET_TSIL_EL_REGISTER(el, suffix)            TSS_GET_TSIL_REGISTER_TYPE(TSS_TSIL_EL_MODULE_NAME(el), suffix)
  #define TSS_GET_TSIL_REGISTER(suffix)                   TSS_GET_TSIL_REGISTER_TYPE(TSS_TSIL_MAIN_MODULE_NAME, suffix)
  
  #define TSIL_CHANNEL0_PEN_NUM                           PEN0
  #define TSIL_CHANNEL1_PEN_NUM                           PEN0
  #define TSIL_CHANNEL2_PEN_NUM                           PEN0
  #define TSIL_CHANNEL3_PEN_NUM                           PEN0
  #define TSIL_CHANNEL4_PEN_NUM                           PEN0
  #define TSIL_CHANNEL5_PEN_NUM                           PEN0
  #define TSIL_CHANNEL6_PEN_NUM                           PEN0
  #define TSIL_CHANNEL7_PEN_NUM                           PEN0
  #define TSIL_CHANNEL8_PEN_NUM                           PEN1
  #define TSIL_CHANNEL9_PEN_NUM                           PEN1
  #define TSIL_CHANNEL10_PEN_NUM                          PEN1
  #define TSIL_CHANNEL11_PEN_NUM                          PEN1
  #define TSIL_CHANNEL12_PEN_NUM                          PEN1
  #define TSIL_CHANNEL13_PEN_NUM                          PEN1
  #define TSIL_CHANNEL14_PEN_NUM                          PEN1
  #define TSIL_CHANNEL15_PEN_NUM                          PEN1

  #define TSS_GET_TSIL_CHANNEL_PEN_RESULT(res)            TSIL_CHANNEL##res##_PEN_NUM
  #define TSS_GET_TSIL_CHANNEL_PEN_CONV(text)             TSS_GET_TSIL_CHANNEL_PEN_RESULT(text)
  #define TSS_GET_TSIL_CHANNEL_PEN_TYPE(channel)          TSS_GET_TSIL_CHANNEL_PEN_CONV(channel)
 
  #define TSS_GET_TSIL_CHANNEL_PEN(el)                    TSS_GET_TSIL_CHANNEL_PEN_TYPE(TSS_TSIL_EL_CHANNEL_NUM(el))

  #define TSS_TSIL_ENABLE_PEN(el)                         TSS_GET_TSIL_EL_REGISTER(el, TSS_GET_TSIL_CHANNEL_PEN(el)) |= (UINT8) (1u << (TSS_TSIL_EL_CHANNEL_NUM(el) & 0x07))      
  #define TSS_TSIL_DISABLE_PEN(el)                        TSS_GET_TSIL_EL_REGISTER(el, TSS_GET_TSIL_CHANNEL_PEN(el)) &= ~((UINT8) (1u << (TSS_TSIL_EL_CHANNEL_NUM(el) & 0x07)))
      
  /* Low Routine body */
      
  #if TSS_HCS08_MCU || TSS_CFV1_MCU
    #if TSS_USE_SIMPLE_LOW_LEVEL
      #define TSS_TSIL_SAMPLE_ELECTRODE_LOW(el)    TSS_GET_TSIL_EL_REGISTER(el, CS0) |= TSI_CS0_TSIEN_MASK; /* Enable TSIL*/\
                                                   TSS_TSIL_ENABLE_PEN(el); /* Enable PEN */\
                                                   TSS_GET_TSIL_EL_REGISTER(el, CS3) = TSIL_CS3_TSICH_FIT(TSS_TSIL_EL_CHANNEL_NUM(el)); /* Set Channel */\
                                                   TSS_GET_TSIL_EL_REGISTER(el, CS0) |= TSI_CS0_SWTS_MASK; /* Toggle SW trigger */\
                                                   while((TSS_GET_TSIL_EL_REGISTER(el, CS0) & TSI_CS0_EOSF_MASK) == 0u)   /* Waits until the electrode has been charged */\
                                                   {\
                                                     /* MISRA Rule 14.8 */\
                                                   }\
                                                   TSS_GET_TSIL_EL_REGISTER(el, CS0) |= TSI_CS0_EOSF_MASK; /* Toggle EOSF flag */\
                                                   TSS_TSIL_DISABLE_PEN(el); /* Disable PEN */\
                                                   u16Result = TSS_GET_TSIL_EL_REGISTER(el, CNT);
    #else /* TSS_USE_SIMPLE_LOW_LEVEL == 0 */
      #define  TSS_TSIL_SAMPLE_ELECTRODE_LOW(el)   ;     /* Nothing */
    #endif /* TSS_USE_SIMPLE_LOW_LEVEL == 0 */
  #elif TSS_KINETIS_MCU || TSS_CFM_MCU
    #define  TSS_TSIL_SAMPLE_ELECTRODE_LOW(el)     ;     /* Nothing */
  #else /* End of TSS_KINETIS_MCU || TSS_CFM_MCU */
    #error "TSS - Not supported MCU used"
  #endif

  /*********** Sample Electrode Low Level Routine assignment *******/

  #if TSS_N_ELECTRODES > 0
    #if (TSS_DETECT_EL_METHOD(0,TSIL))
      #define TSS_E0_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(0)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 1
    #if (TSS_DETECT_EL_METHOD(1,TSIL))
      #define TSS_E1_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(1)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 2
    #if (TSS_DETECT_EL_METHOD(2,TSIL))
      #define TSS_E2_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(2)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 3
    #if (TSS_DETECT_EL_METHOD(3,TSIL))
      #define TSS_E3_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(3)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 4
    #if (TSS_DETECT_EL_METHOD(4,TSIL))
      #define TSS_E4_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(4)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 5
    #if (TSS_DETECT_EL_METHOD(5,TSIL))
      #define TSS_E5_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(5)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 6
    #if (TSS_DETECT_EL_METHOD(6,TSIL))
      #define TSS_E6_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(6)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 7
    #if (TSS_DETECT_EL_METHOD(7,TSIL))
      #define TSS_E7_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(7)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 8
    #if (TSS_DETECT_EL_METHOD(8,TSIL))
      #define TSS_E8_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(8)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 9
    #if (TSS_DETECT_EL_METHOD(9,TSIL))
      #define TSS_E9_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(9)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 10
    #if (TSS_DETECT_EL_METHOD(10,TSIL))
      #define TSS_E10_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(10)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 11
    #if (TSS_DETECT_EL_METHOD(11,TSIL))
      #define TSS_E11_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(11)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 12
    #if (TSS_DETECT_EL_METHOD(12,TSIL))
      #define TSS_E12_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(12)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 13
    #if (TSS_DETECT_EL_METHOD(13,TSIL))
      #define TSS_E13_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(13)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 14
    #if (TSS_DETECT_EL_METHOD(14,TSIL))
      #define TSS_E14_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(14)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 15
    #if (TSS_DETECT_EL_METHOD(15,TSIL))
      #define TSS_E15_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(15)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 16
    #if (TSS_DETECT_EL_METHOD(16,TSIL))
      #define TSS_E16_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(16)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 17
    #if (TSS_DETECT_EL_METHOD(17,TSIL))
      #define TSS_E17_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(17)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 18
    #if (TSS_DETECT_EL_METHOD(18,TSIL))
      #define TSS_E18_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(18)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 19
    #if (TSS_DETECT_EL_METHOD(19,TSIL))
      #define TSS_E19_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(19)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 20
    #if (TSS_DETECT_EL_METHOD(20,TSIL))
      #define TSS_E20_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(20)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 21
    #if (TSS_DETECT_EL_METHOD(21,TSIL))
      #define TSS_E21_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(21)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 22
    #if (TSS_DETECT_EL_METHOD(22,TSIL))
      #define TSS_E22_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(22)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 23
    #if (TSS_DETECT_EL_METHOD(23,TSIL))
      #define TSS_E23_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(23)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 24
    #if (TSS_DETECT_EL_METHOD(24,TSIL))
      #define TSS_E24_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(24)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 25
    #if (TSS_DETECT_EL_METHOD(25,TSIL))
      #define TSS_E25_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(25)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 26
    #if (TSS_DETECT_EL_METHOD(26,TSIL))
      #define TSS_E26_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(26)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 27
    #if (TSS_DETECT_EL_METHOD(27,TSIL))
      #define TSS_E27_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(27)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 28
    #if (TSS_DETECT_EL_METHOD(28,TSIL))
      #define TSS_E28_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(28)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 29
    #if (TSS_DETECT_EL_METHOD(29,TSIL))
      #define TSS_E29_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(29)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 30
    #if (TSS_DETECT_EL_METHOD(30,TSIL))
      #define TSS_E30_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(30)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 31
    #if (TSS_DETECT_EL_METHOD(31,TSIL))
      #define TSS_E31_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(31)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 32
    #if (TSS_DETECT_EL_METHOD(32,TSIL))
      #define TSS_E32_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(32)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 33
    #if (TSS_DETECT_EL_METHOD(33,TSIL))
      #define TSS_E33_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(33)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 34
    #if (TSS_DETECT_EL_METHOD(34,TSIL))
      #define TSS_E34_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(34)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 35
    #if (TSS_DETECT_EL_METHOD(35,TSIL))
      #define TSS_E35_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(35)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 36
    #if (TSS_DETECT_EL_METHOD(36,TSIL))
      #define TSS_E36_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(36)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 37
    #if (TSS_DETECT_EL_METHOD(37,TSIL))
      #define TSS_E37_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(37)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 38
    #if (TSS_DETECT_EL_METHOD(38,TSIL))
      #define TSS_E38_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(38)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 39
    #if (TSS_DETECT_EL_METHOD(39,TSIL))
      #define TSS_E39_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(39)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 40
    #if (TSS_DETECT_EL_METHOD(40,TSIL))
      #define TSS_E40_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(40)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 41
    #if (TSS_DETECT_EL_METHOD(41,TSIL))
      #define TSS_E41_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(41)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 42
    #if (TSS_DETECT_EL_METHOD(42,TSIL))
      #define TSS_E42_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(42)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 43
    #if (TSS_DETECT_EL_METHOD(43,TSIL))
      #define TSS_E43_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(43)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 44
    #if (TSS_DETECT_EL_METHOD(44,TSIL))
      #define TSS_E44_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(44)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 45
    #if (TSS_DETECT_EL_METHOD(45,TSIL))
      #define TSS_E45_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(45)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 46
    #if (TSS_DETECT_EL_METHOD(46,TSIL))
      #define TSS_E46_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(46)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 47
    #if (TSS_DETECT_EL_METHOD(47,TSIL))
      #define TSS_E47_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(47)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 48
    #if (TSS_DETECT_EL_METHOD(48,TSIL))
      #define TSS_E48_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(48)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 49
    #if (TSS_DETECT_EL_METHOD(49,TSIL))
      #define TSS_E49_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(49)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 50
    #if (TSS_DETECT_EL_METHOD(50,TSIL))
      #define TSS_E50_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(50)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 51
    #if (TSS_DETECT_EL_METHOD(51,TSIL))
      #define TSS_E51_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(51)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 52
    #if (TSS_DETECT_EL_METHOD(52,TSIL))
      #define TSS_E52_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(52)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 53
    #if (TSS_DETECT_EL_METHOD(53,TSIL))
      #define TSS_E53_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(53)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 54
    #if (TSS_DETECT_EL_METHOD(54,TSIL))
      #define TSS_E54_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(54)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 55
    #if (TSS_DETECT_EL_METHOD(55,TSIL))
      #define TSS_E55_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(55)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 56
    #if (TSS_DETECT_EL_METHOD(56,TSIL))
      #define TSS_E56_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(56)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 57
    #if (TSS_DETECT_EL_METHOD(57,TSIL))
      #define TSS_E57_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(57)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 58
    #if (TSS_DETECT_EL_METHOD(58,TSIL))
      #define TSS_E58_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(58)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 59
    #if (TSS_DETECT_EL_METHOD(59,TSIL))
      #define TSS_E59_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(59)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 60
    #if (TSS_DETECT_EL_METHOD(60,TSIL))
      #define TSS_E60_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(60)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 61
    #if (TSS_DETECT_EL_METHOD(61,TSIL))
      #define TSS_E61_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(61)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 62
    #if (TSS_DETECT_EL_METHOD(62,TSIL))
      #define TSS_E62_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(62)
    #endif
  #endif
  #if TSS_N_ELECTRODES > 63
    #if (TSS_DETECT_EL_METHOD(63,TSIL))
      #define TSS_E63_SAMPLE_ELECTRODE_LOW()   TSS_TSIL_SAMPLE_ELECTRODE_LOW(63)
    #endif
  #endif

  /*************** Sample Electrode Routine assignment *************/

  #if TSS_N_ELECTRODES > 0
    #if (TSS_DETECT_EL_METHOD(0,TSIL))
      #define TSS_E0_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 1
    #if (TSS_DETECT_EL_METHOD(1,TSIL))
      #define TSS_E1_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 2
    #if (TSS_DETECT_EL_METHOD(2,TSIL))
      #define TSS_E2_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 3
    #if (TSS_DETECT_EL_METHOD(3,TSIL))
      #define TSS_E3_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 4
    #if (TSS_DETECT_EL_METHOD(4,TSIL))
      #define TSS_E4_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 5
    #if (TSS_DETECT_EL_METHOD(5,TSIL))
      #define TSS_E5_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 6
    #if (TSS_DETECT_EL_METHOD(6,TSIL))
      #define TSS_E6_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 7
    #if (TSS_DETECT_EL_METHOD(7,TSIL))
      #define TSS_E7_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 8
    #if (TSS_DETECT_EL_METHOD(8,TSIL))
      #define TSS_E8_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 9
    #if (TSS_DETECT_EL_METHOD(9,TSIL))
      #define TSS_E9_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 10
    #if (TSS_DETECT_EL_METHOD(10,TSIL))
      #define TSS_E10_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 11
    #if (TSS_DETECT_EL_METHOD(11,TSIL))
      #define TSS_E11_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 12
    #if (TSS_DETECT_EL_METHOD(12,TSIL))
      #define TSS_E12_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 13
    #if (TSS_DETECT_EL_METHOD(13,TSIL))
      #define TSS_E13_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 14
    #if (TSS_DETECT_EL_METHOD(14,TSIL))
      #define TSS_E14_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 15
    #if (TSS_DETECT_EL_METHOD(15,TSIL))
      #define TSS_E15_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 16
    #if (TSS_DETECT_EL_METHOD(16,TSIL))
      #define TSS_E16_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 17
    #if (TSS_DETECT_EL_METHOD(17,TSIL))
      #define TSS_E17_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 18
    #if (TSS_DETECT_EL_METHOD(18,TSIL))
      #define TSS_E18_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 19
    #if (TSS_DETECT_EL_METHOD(19,TSIL))
      #define TSS_E19_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 20
    #if (TSS_DETECT_EL_METHOD(20,TSIL))
      #define TSS_E20_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 21
    #if (TSS_DETECT_EL_METHOD(21,TSIL))
      #define TSS_E21_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 22
    #if (TSS_DETECT_EL_METHOD(22,TSIL))
      #define TSS_E22_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 23
    #if (TSS_DETECT_EL_METHOD(23,TSIL))
      #define TSS_E23_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 24
    #if (TSS_DETECT_EL_METHOD(24,TSIL))
      #define TSS_E24_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 25
    #if (TSS_DETECT_EL_METHOD(25,TSIL))
      #define TSS_E25_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 26
    #if (TSS_DETECT_EL_METHOD(26,TSIL))
      #define TSS_E26_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 27
    #if (TSS_DETECT_EL_METHOD(27,TSIL))
      #define TSS_E27_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 28
    #if (TSS_DETECT_EL_METHOD(28,TSIL))
      #define TSS_E28_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 29
    #if (TSS_DETECT_EL_METHOD(29,TSIL))
      #define TSS_E29_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 30
    #if (TSS_DETECT_EL_METHOD(30,TSIL))
      #define TSS_E30_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 31
    #if (TSS_DETECT_EL_METHOD(31,TSIL))
      #define TSS_E31_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 32
    #if (TSS_DETECT_EL_METHOD(32,TSIL))
      #define TSS_E32_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 33
    #if (TSS_DETECT_EL_METHOD(33,TSIL))
      #define TSS_E33_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 34
    #if (TSS_DETECT_EL_METHOD(34,TSIL))
      #define TSS_E34_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 35
    #if (TSS_DETECT_EL_METHOD(35,TSIL))
      #define TSS_E35_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 36
    #if (TSS_DETECT_EL_METHOD(36,TSIL))
      #define TSS_E36_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 37
    #if (TSS_DETECT_EL_METHOD(37,TSIL))
      #define TSS_E37_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 38
    #if (TSS_DETECT_EL_METHOD(38,TSIL))
      #define TSS_E38_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 39
    #if (TSS_DETECT_EL_METHOD(39,TSIL))
      #define TSS_E39_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 40
    #if (TSS_DETECT_EL_METHOD(40,TSIL))
      #define TSS_E40_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 41
    #if (TSS_DETECT_EL_METHOD(41,TSIL))
      #define TSS_E41_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 42
    #if (TSS_DETECT_EL_METHOD(42,TSIL))
      #define TSS_E42_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 43
    #if (TSS_DETECT_EL_METHOD(43,TSIL))
      #define TSS_E43_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 44
    #if (TSS_DETECT_EL_METHOD(44,TSIL))
      #define TSS_E44_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 45
    #if (TSS_DETECT_EL_METHOD(45,TSIL))
      #define TSS_E45_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 46
    #if (TSS_DETECT_EL_METHOD(46,TSIL))
      #define TSS_E46_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 47
    #if (TSS_DETECT_EL_METHOD(47,TSIL))
      #define TSS_E47_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 48
    #if (TSS_DETECT_EL_METHOD(48,TSIL))
      #define TSS_E48_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 49
    #if (TSS_DETECT_EL_METHOD(49,TSIL))
      #define TSS_E49_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 50
    #if (TSS_DETECT_EL_METHOD(50,TSIL))
      #define TSS_E50_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 51
    #if (TSS_DETECT_EL_METHOD(51,TSIL))
      #define TSS_E51_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 52
    #if (TSS_DETECT_EL_METHOD(52,TSIL))
      #define TSS_E52_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 53
    #if (TSS_DETECT_EL_METHOD(53,TSIL))
      #define TSS_E53_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 54
    #if (TSS_DETECT_EL_METHOD(54,TSIL))
      #define TSS_E54_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 55
    #if (TSS_DETECT_EL_METHOD(55,TSIL))
      #define TSS_E55_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 56
    #if (TSS_DETECT_EL_METHOD(56,TSIL))
      #define TSS_E56_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 57
    #if (TSS_DETECT_EL_METHOD(57,TSIL))
      #define TSS_E57_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 58
    #if (TSS_DETECT_EL_METHOD(58,TSIL))
      #define TSS_E58_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 59
    #if (TSS_DETECT_EL_METHOD(59,TSIL))
      #define TSS_E59_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 60
    #if (TSS_DETECT_EL_METHOD(60,TSIL))
      #define TSS_E60_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 61
    #if (TSS_DETECT_EL_METHOD(61,TSIL))
      #define TSS_E61_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 62
    #if (TSS_DETECT_EL_METHOD(62,TSIL))
      #define TSS_E62_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif
  #if TSS_N_ELECTRODES > 63
    #if (TSS_DETECT_EL_METHOD(63,TSIL))
      #define TSS_E63_SAMPLE_ELECTRODE()    TSIL_SampleElectrode
    #endif
  #endif

  #if TSS_DETECT_METHOD(TSIL)      
      
    /*********************************************************************************
    *                    TSS_SystemSetup.h Back compatibility
    *********************************************************************************/
    
    #ifdef TSS_TSI_SCANC_EXTCHRG_LOW_LIMIT
      #ifndef TSS_TSI_EXTCHRG_LOW_LIMIT
        #define TSS_TSI_EXTCHRG_LOW_LIMIT      TSS_TSI_SCANC_EXTCHRG_LOW_LIMIT /* Low Limit of External OSC Charge Current value for TSI autocalibration */
      #endif  
    #endif
    #ifdef TSS_TSI_SCANC_EXTCHRG_HIGH_LIMIT
      #ifndef TSS_TSI_EXTCHRG_HIGH_LIMIT
        #define TSS_TSI_EXTCHRG_HIGH_LIMIT     TSS_TSI_SCANC_EXTCHRG_HIGH_LIMIT /* High Limit of External OSC Charge Current value for TSI autocalibration */
      #endif
    #endif
    #ifdef TSS_TSI_GENCS_PS_LOW_LIMIT
      #ifndef TSS_TSI_PS_LOW_LIMIT 
        #define TSS_TSI_PS_LOW_LIMIT           TSS_TSI_GENCS_PS_LOW_LIMIT /* Low Limit of External OSC Prescaler register value for TSI autocalibration */
      #endif
    #endif
    #ifdef TSS_TSI_GENCS_PS_HIGH_LIMIT
      #ifndef TSS_TSI_PS_HIGH_LIMIT
        #define TSS_TSI_PS_HIGH_LIMIT          TSS_TSI_GENCS_PS_HIGH_LIMIT /* High Limit of External OSC Prescaler register value for TSI autocalibration */
      #endif
    #endif
        
    /*********************************************************************************
    *                              TSIL Specfic Settings
    *********************************************************************************/
        
    /* TSIL RefOSC definitions */
    #define TSS_TSIL_REFCHRG                6   /* Reference Oscillator Charge Current 0 = 500 nA, 7 = 64uA */     

    /* Electrode Default Threshold definition */
    #define TSS_TSIL_DEFAULT_LOW_THRESHOLD  0      /* Low Threshold for the electrode */
    #define TSS_TSIL_DEFAULT_HIGH_THRESHOLD 0xFFFF /* High Threshold for the electrode */
    
    /* TSIL final calibration finding fault limit */
    #define TSIL_FINAL_CALIB_FAULT_LIMIT    1
      
    /* Masks */
    #define TSIL_CS2_REFCHRG_FIT(x)         (((UINT8)(((UINT8)(x))<<TSI_CS2_REFCHRG_BITNUM))&TSI_CS2_REFCHRG_MASK)
    #define TSIL_CS2_DVOLT_FIT(x)           (((UINT8)(((UINT8)(x))<<TSI_CS2_DVOLT_BITNUM))&TSI_CS2_DVOLT_MASK)
    #define TSIL_CS1_NSCN_FIT(x)            (((UINT8)(((UINT8)(x))<<TSI_CS1_NSCN_BITNUM))&TSI_CS1_NSCN_MASK)
    #define TSIL_CS1_PS_FIT(x)              (((UINT8)(((UINT8)(x))<<TSI_CS1_PS_BITNUM))&TSI_CS1_PS_MASK)
    #define TSIL_CS2_EXTCHRG_FIT(x)         (((UINT8)(((UINT8)(x))<<TSI_CS2_EXTCHRG_BITNUM))&TSI_CS2_EXTCHRG_MASK)  
    #define TSIL_CS3_TSICH_FIT(x)           (((UINT8)(((UINT8)(x))<<TSI_CS3_TSICH_BITNUM))&TSI_CS3_TSICH_MASK)
  
    /*** If not defined in TSS_SysteSetup.h then set default values ****/
    
    /* TSIL Autocalibration Settings */
    #ifndef TSS_TSI_RESOLUTION
      #define TSS_TSIL_RESOLUTION           11 /* Required Bit resolution of the TSIL */
    #else
      #define TSS_TSIL_RESOLUTION           TSS_TSI_RESOLUTION /* Required Bit resolution of the TSIL */
    #endif
    #ifndef TSS_TSI_EXTCHRG_LOW_LIMIT
      #define TSS_TSIL_EXTCHRG_LOW_LIMIT    0 /* Low Limit of External OSC Charge Current value for TSIL autocalibration */
    #else
      #define TSS_TSIL_EXTCHRG_LOW_LIMIT    TSS_TSI_EXTCHRG_LOW_LIMIT /* Low Limit of External OSC Charge Current value for TSIL autocalibration */  
    #endif
    #ifndef TSS_TSI_EXTCHRG_HIGH_LIMIT
      #define TSS_TSIL_EXTCHRG_HIGH_LIMIT   7 /* High Limit of External OSC Charge Current value for TSIL autocalibration */
    #else
      #define TSS_TSIL_EXTCHRG_HIGH_LIMIT   TSS_TSI_EXTCHRG_HIGH_LIMIT /* Low Limit of External OSC Charge Current value for TSIL autocalibration */
    #endif
    #ifndef TSS_TSI_PS_LOW_LIMIT
      #define TSS_TSIL_PS_LOW_LIMIT         0 /* Low Limit of External OSC Prescaler register value for TSIL autocalibration */
    #else
      #define TSS_TSIL_PS_LOW_LIMIT         TSS_TSI_PS_LOW_LIMIT /* Low Limit of External OSC Prescaler register value for TSIL autocalibration */
    #endif
    #ifndef TSS_TSI_PS_HIGH_LIMIT
      #define TSS_TSIL_PS_HIGH_LIMIT        7 /* High Limit of External OSC Prescaler register value for TSIL autocalibration */
    #else
      #define TSS_TSIL_PS_HIGH_LIMIT        TSS_TSI_PS_HIGH_LIMIT /* High Limit of External OSC Prescaler register value for TSIL autocalibration */    
    #endif
    #ifndef TSS_TSI_PROX_RESOLUTION
      #define TSS_TSIL_PROX_RESOLUTION      11 /* Required Bit resolution of the TSI */
    #else  
      #define TSS_TSIL_PROX_RESOLUTION      TSS_TSI_PROX_RESOLUTION /* Required Bit resolution of the TSI */
    #endif
    #ifndef TSS_TSI_PROX_EXTCHRG_LOW_LIMIT
      #define TSS_TSIL_PROX_EXTCHRG_LOW_LIMIT    0 /* Low Limit of External OSC Charge Current value for TSI autocalibration */
    #else        
      #define TSS_TSIL_PROX_EXTCHRG_LOW_LIMIT    TSS_TSI_PROX_EXTCHRG_LOW_LIMIT /* Low Limit of External OSC Charge Current value for TSI autocalibration */
    #endif
    #ifndef TSS_TSI_PROX_EXTCHRG_HIGH_LIMIT
      #define TSS_TSIL_PROX_EXTCHRG_HIGH_LIMIT   7 /* High Limit of External OSC Charge Current value for TSI autocalibration */
    #else      
      #define TSS_TSIL_PROX_EXTCHRG_HIGH_LIMIT   TSS_TSI_PROX_EXTCHRG_HIGH_LIMIT /* High Limit of External OSC Charge Current value for TSI autocalibration */      
    #endif
    #ifndef TSS_TSI_PROX_PS_LOW_LIMIT
      #define TSS_TSIL_PROX_PS_LOW_LIMIT    0 /* Low Limit of External OSC Prescaler register value for TSI autocalibration */
    #else      
      #define TSS_TSIL_PROX_PS_LOW_LIMIT    TSS_TSI_PROX_PS_LOW_LIMIT /* Low Limit of External OSC Prescaler register value for TSI autocalibration */      
    #endif
    #ifndef TSS_TSI_PROX_PS_HIGH_LIMIT
      #define TSS_TSIL_PROX_PS_HIGH_LIMIT   7 /* High Limit of External OSC Prescaler register value for TSI autocalibration */
    #else      
      #define TSS_TSIL_PROX_PS_HIGH_LIMIT   TSS_TSI_PROX_PS_HIGH_LIMIT /* High Limit of External OSC Prescaler register value for TSI autocalibration */      
    #endif
    #ifndef TSS_TSIL_DVOLT
      #ifdef TSS_TSI_DVOLT
        #define TSS_TSIL_DVOLT              TSS_TSI_DVOLT   /* Delta Voltage settings for ElOSC and RefOSC 0 = 1.03 V, 3 = 0.29 V */
      #else         
        #define TSS_TSIL_DVOLT              0   /* Delta Voltage settings for ElOSC and RefOSC 0 = 1.03 V, 3 = 0.29 V */
      #endif
    #endif
  
    /********************** Auto Calculated Settings *******************/
  
    /* Usable ranges for Recalibration */ 
    #define TSS_TSIL_EXTCHRG_RANGE                  ((TSS_TSIL_EXTCHRG_HIGH_LIMIT + 1u) - TSS_TSIL_EXTCHRG_LOW_LIMIT) 
    #define TSS_TSIL_PS_RANGE                       ((TSS_TSIL_PS_HIGH_LIMIT + 1u) - TSS_TSIL_PS_LOW_LIMIT)
    #define TSS_TSIL_PROX_EXTCHRG_RANGE             ((TSS_TSIL_PROX_EXTCHRG_HIGH_LIMIT + 1u) - TSS_TSIL_PROX_EXTCHRG_LOW_LIMIT) 
    #define TSS_TSIL_PROX_PS_RANGE                  ((TSS_TSIL_PROX_PS_HIGH_LIMIT + 1u) - TSS_TSIL_PROX_PS_LOW_LIMIT)       
    /* TSI Resolution Value Determination */
    #define TSS_TSIL_RESOLUTION_VALUE               (1 << (TSS_TSIL_RESOLUTION - 1))
    #define TSS_TSIL_PROX_RESOLUTION_VALUE          (1 << (TSS_TSIL_PROX_RESOLUTION - 1))            
    /* Recalibration Thresholds */
    #define TSS_TSIL_RECALIBRATION_LOW_THRESHOLD(resolution)           (UINT16)(((UINT32)(resolution)*13107) >> 16u) 
    #define TSS_TSIL_RECALIBRATION_HIGH_THRESHOLD(resolution)          (0xFFFF-TSS_TSIL_RECALIBRATION_HIGH_THRESHOLD_RANGE(resolution))    
    #define TSS_TSIL_RECALIBRATION_HIGH_THRESHOLD_RANGE(resolution)    (UINT16)(((UINT32)(0xFFFF-resolution)*13107) >> 16u)   
    /* Fault Thresholds */
    #define TSS_TSIL_CAP_LOW_LIMIT(resolution)                   (UINT16)(((UINT32)(resolution)*13107) >> 17u)                  
    #define TSS_TSIL_CAP_HIGH_LIMIT(resolution)                  (0xFFFF-TSS_TSIL_CAP_HIGH_LIMIT_RANGE(resolution)) 
    #define TSS_TSIL_CAP_HIGH_LIMIT_RANGE(resolution)            (UINT16)(((UINT32)(0xFFFF-resolution)*13107) >> 17u)
        
    /*********************************************************************************
    *                          Validation of the Settings
    *********************************************************************************/
    
    #if (TSS_TSIL_RESOLUTION < 1) || (TSS_TSIL_RESOLUTION > 16) 
        #error "TSS - TSS_TSI_RESOLUTION is out of range"
    #endif
    
    #if (TSS_TSIL_EXTCHRG_LOW_LIMIT  > 7)
        #error "TSS - TSS_TSI_EXTCHRG_LOW_LIMIT is out of range"
    #endif
    
    #if (TSS_TSIL_EXTCHRG_HIGH_LIMIT > 7)
        #error "TSS - TSS_TSI_EXTCHRG_HIGH_LIMIT is out of range"
    #endif
  
    #if (TSS_TSIL_EXTCHRG_LOW_LIMIT > TSS_TSIL_EXTCHRG_HIGH_LIMIT)
        #error "TSS - TSS_TSI_EXTCHRG_LOW_LIMIT may not be higher than TSS_TSI_EXTCHRG_HIGH_LIMIT"
    #endif
  
    #if (TSS_TSIL_PS_LOW_LIMIT  > 7)
        #error "TSS - TSS_TSI_PS_LOW_LIMIT is out of range"
    #endif
    
    #if (TSS_TSIL_PS_HIGH_LIMIT > 7)
        #error "TSS - TSS_TSI_PS_HIGH_LIMIT is out of range"
    #endif
    
    #if (TSS_TSIL_PS_LOW_LIMIT > TSS_TSIL_PS_HIGH_LIMIT)
        #error "TSS - TSS_TSI_PS_LOW_LIMIT may not be higher than TSS_TSI_PS_HIGH_LIMIT"
    #endif

    #if (TSS_AUTOTRIGGER_SOURCE_USED && TSS_USE_TRIGGER_FUNCTION)
      #if (TSS_DETECT_AUTOTRIGGER_SOURCE_USAGE(TSI) || TSS_DETECT_AUTOTRIGGER_SOURCE_USAGE(TSI0) || TSS_DETECT_AUTOTRIGGER_SOURCE_USAGE(TSI1))
        #error "TSS - TSS_USE_AUTOTRIGGER_SOURCE is set to invalid value. TSI auto-triggering is not possible on the MCU"
      #elif TSS_DETECT_AUTOTRIGGER_SOURCE_USAGE(RTC)
        #if (TSS_TSIL_VERSION != 1)
          #error "TSS - TSS_USE_AUTOTRIGGER_SOURCE is set to invalid value. RTC auto-triggering is not possible on the MCU"
        #endif
      #elif TSS_DETECT_AUTOTRIGGER_SOURCE_USAGE(LPTMR)
        #if (TSS_TSIL_VERSION != 2)
          #error "TSS - TSS_USE_AUTOTRIGGER_SOURCE is set to invalid value. LPTMR auto-triggering is not possible on the MCU"
        #endif
      #else      
        #error "TSS - TSS_USE_AUTOTRIGGER_SOURCE is set to invalid value."     
      #endif
    #endif   
      
    #if (TSS_LOWPOWER_USED)
      #if (TSS_DETECT_LOWPOWER_USAGE(TSI) || TSS_DETECT_LOWPOWER_USAGE(TSI0) || TSS_DETECT_LOWPOWER_USAGE(TSI1))
        #if (TSS_TSIL_VERSION > 1)
          #if TSS_DETECT_LOWPOWER_USAGE(TSI)
            #if !TSS_DETECT_MODULE(TSIL)
              #error "TSS - TSS_USE_LOWPOWER_CONTROL_SOURCE is set to invalid value. TSI module is not used in the TSS."
            #endif
          #endif
          #if TSS_DETECT_LOWPOWER_USAGE(TSI0)
            #if !TSS_DETECT_MODULE(TSIL0)
              #error "TSS - TSS_USE_LOWPOWER_CONTROL_SOURCE is set to invalid value. TSI0 module is not used in the TSS."
            #endif
          #endif
          #if TSS_DETECT_LOWPOWER_USAGE(TSI1)
            #if !TSS_DETECT_MODULE(TSIL1)
              #error "TSS - TSS_USE_LOWPOWER_CONTROL_SOURCE is set to invalid value. TSI1 module is not used in the TSS."
            #endif
          #endif
        #else      
          #error "TSS - TSS_USE_LOWPOWER_CONTROL_SOURCE is set to invalid value. Wake up by TSI module is not possible on the MCU"
        #endif 
      #else      
        #error "TSS - TSS_USE_LOWPOWER_CONTROL_SOURCE is set to invalid value."
      #endif
    #endif      
      
    #if TSS_USE_SIMPLE_LOW_LEVEL
      #if (TSS_TSIL_VERSION == 2)
        #error "TSS - Option TSS_USE_SIMPLE_LOW_LEVEL is not available for the TSI"
      #else
        #if ((TSS_DETECT_MODULE(TSIL) && TSS_DETECT_MODULE(TSIL0)) || (TSS_DETECT_MODULE(TSIL0) && TSS_DETECT_MODULE(TSIL1)) || (TSS_DETECT_MODULE(TSIL) && TSS_DETECT_MODULE(TSIL1))) 
          #error "TSS - More than one TSI module is selected in TSS_SystemSetup.h and TSS_USE_SIMPLE_LOW_LEVEL is enabled"
        #endif
      #endif
    #endif
      
    /*********************************************************************************
    *                      TSI Module Name Recognition Macros
    *********************************************************************************/
  
    #define TSS_TSICH0_TSIL_MODULE_NAME            TSI
    #define TSS_TSICH1_TSIL_MODULE_NAME            TSI
    #define TSS_TSICH2_TSIL_MODULE_NAME            TSI
    #define TSS_TSICH3_TSIL_MODULE_NAME            TSI
    #define TSS_TSICH4_TSIL_MODULE_NAME            TSI
    #define TSS_TSICH5_TSIL_MODULE_NAME            TSI
    #define TSS_TSICH6_TSIL_MODULE_NAME            TSI
    #define TSS_TSICH7_TSIL_MODULE_NAME            TSI
    #define TSS_TSICH8_TSIL_MODULE_NAME            TSI
    #define TSS_TSICH9_TSIL_MODULE_NAME            TSI
    #define TSS_TSICH10_TSIL_MODULE_NAME           TSI
    #define TSS_TSICH11_TSIL_MODULE_NAME           TSI
    #define TSS_TSICH12_TSIL_MODULE_NAME           TSI
    #define TSS_TSICH13_TSIL_MODULE_NAME           TSI
    #define TSS_TSICH14_TSIL_MODULE_NAME           TSI
    #define TSS_TSICH15_TSIL_MODULE_NAME           TSI
  
    #define TSS_TSI0CH0_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0CH1_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0CH2_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0CH3_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0CH4_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0CH5_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0CH6_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0CH7_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0CH8_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0CH9_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0CH10_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0CH11_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0CH12_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0CH13_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0CH14_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0CH15_TSIL_MODULE_NAME          TSI0
  
    #define TSS_TSI1CH0_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1CH1_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1CH2_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1CH3_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1CH4_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1CH5_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1CH6_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1CH7_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1CH8_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1CH9_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1CH10_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1CH11_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1CH12_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1CH13_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1CH14_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1CH15_TSIL_MODULE_NAME          TSI1
  
  
    #define TSS_TSI_CH0_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_CH1_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_CH2_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_CH3_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_CH4_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_CH5_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_CH6_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_CH7_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_CH8_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_CH9_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_CH10_TSIL_MODULE_NAME          TSI
    #define TSS_TSI_CH11_TSIL_MODULE_NAME          TSI
    #define TSS_TSI_CH12_TSIL_MODULE_NAME          TSI
    #define TSS_TSI_CH13_TSIL_MODULE_NAME          TSI
    #define TSS_TSI_CH14_TSIL_MODULE_NAME          TSI
    #define TSS_TSI_CH15_TSIL_MODULE_NAME          TSI
  
    #define TSS_TSI0_CH0_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_CH1_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_CH2_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_CH3_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_CH4_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_CH5_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_CH6_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_CH7_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_CH8_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_CH9_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_CH10_TSIL_MODULE_NAME         TSI0
    #define TSS_TSI0_CH11_TSIL_MODULE_NAME         TSI0
    #define TSS_TSI0_CH12_TSIL_MODULE_NAME         TSI0
    #define TSS_TSI0_CH13_TSIL_MODULE_NAME         TSI0
    #define TSS_TSI0_CH14_TSIL_MODULE_NAME         TSI0
    #define TSS_TSI0_CH15_TSIL_MODULE_NAME         TSI0
  
    #define TSS_TSI1_CH0_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_CH1_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_CH2_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_CH3_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_CH4_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_CH5_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_CH6_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_CH7_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_CH8_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_CH9_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_CH10_TSIL_MODULE_NAME         TSI1
    #define TSS_TSI1_CH11_TSIL_MODULE_NAME         TSI1
    #define TSS_TSI1_CH12_TSIL_MODULE_NAME         TSI1
    #define TSS_TSI1_CH13_TSIL_MODULE_NAME         TSI1
    #define TSS_TSI1_CH14_TSIL_MODULE_NAME         TSI1
    #define TSS_TSI1_CH15_TSIL_MODULE_NAME         TSI1
    
    
    #define TSS_TSIIN0_TSIL_MODULE_NAME            TSI
    #define TSS_TSIIN1_TSIL_MODULE_NAME            TSI
    #define TSS_TSIIN2_TSIL_MODULE_NAME            TSI
    #define TSS_TSIIN3_TSIL_MODULE_NAME            TSI
    #define TSS_TSIIN4_TSIL_MODULE_NAME            TSI
    #define TSS_TSIIN5_TSIL_MODULE_NAME            TSI
    #define TSS_TSIIN6_TSIL_MODULE_NAME            TSI
    #define TSS_TSIIN7_TSIL_MODULE_NAME            TSI
    #define TSS_TSIIN8_TSIL_MODULE_NAME            TSI
    #define TSS_TSIIN9_TSIL_MODULE_NAME            TSI
    #define TSS_TSIIN10_TSIL_MODULE_NAME           TSI
    #define TSS_TSIIN11_TSIL_MODULE_NAME           TSI
    #define TSS_TSIIN12_TSIL_MODULE_NAME           TSI
    #define TSS_TSIIN13_TSIL_MODULE_NAME           TSI
    #define TSS_TSIIN14_TSIL_MODULE_NAME           TSI
    #define TSS_TSIIN15_TSIL_MODULE_NAME           TSI
  
    #define TSS_TSI0IN0_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0IN1_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0IN2_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0IN3_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0IN4_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0IN5_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0IN6_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0IN7_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0IN8_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0IN9_TSIL_MODULE_NAME           TSI0
    #define TSS_TSI0IN10_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0IN11_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0IN12_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0IN13_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0IN14_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0IN15_TSIL_MODULE_NAME          TSI0
  
    #define TSS_TSI1IN0_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1IN1_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1IN2_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1IN3_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1IN4_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1IN5_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1IN6_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1IN7_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1IN8_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1IN9_TSIL_MODULE_NAME           TSI1
    #define TSS_TSI1IN10_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1IN11_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1IN12_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1IN13_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1IN14_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1IN15_TSIL_MODULE_NAME          TSI1
  
  
    #define TSS_TSI_IN0_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_IN1_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_IN2_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_IN3_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_IN4_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_IN5_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_IN6_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_IN7_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_IN8_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_IN9_TSIL_MODULE_NAME           TSI
    #define TSS_TSI_IN10_TSIL_MODULE_NAME          TSI
    #define TSS_TSI_IN11_TSIL_MODULE_NAME          TSI
    #define TSS_TSI_IN12_TSIL_MODULE_NAME          TSI
    #define TSS_TSI_IN13_TSIL_MODULE_NAME          TSI
    #define TSS_TSI_IN14_TSIL_MODULE_NAME          TSI
    #define TSS_TSI_IN15_TSIL_MODULE_NAME          TSI
  
    #define TSS_TSI0_IN0_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_IN1_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_IN2_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_IN3_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_IN4_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_IN5_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_IN6_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_IN7_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_IN8_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_IN9_TSIL_MODULE_NAME          TSI0
    #define TSS_TSI0_IN10_TSIL_MODULE_NAME         TSI0
    #define TSS_TSI0_IN11_TSIL_MODULE_NAME         TSI0
    #define TSS_TSI0_IN12_TSIL_MODULE_NAME         TSI0
    #define TSS_TSI0_IN13_TSIL_MODULE_NAME         TSI0
    #define TSS_TSI0_IN14_TSIL_MODULE_NAME         TSI0
    #define TSS_TSI0_IN15_TSIL_MODULE_NAME         TSI0
  
    #define TSS_TSI1_IN0_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_IN1_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_IN2_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_IN3_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_IN4_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_IN5_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_IN6_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_IN7_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_IN8_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_IN9_TSIL_MODULE_NAME          TSI1
    #define TSS_TSI1_IN10_TSIL_MODULE_NAME         TSI1
    #define TSS_TSI1_IN11_TSIL_MODULE_NAME         TSI1
    #define TSS_TSI1_IN12_TSIL_MODULE_NAME         TSI1
    #define TSS_TSI1_IN13_TSIL_MODULE_NAME         TSI1
    #define TSS_TSI1_IN14_TSIL_MODULE_NAME         TSI1
    #define TSS_TSI1_IN15_TSIL_MODULE_NAME         TSI1

  
    #define TSS_TSIL_MODULE_NAME_RESULT(res)       TSS_##res##_TSIL_MODULE_NAME
    #define TSS_TSIL_MODULE_NAME_CONV(text)        TSS_TSIL_MODULE_NAME_RESULT(text)
    #define TSS_GET_TSIL_EL_MODULE_NAME(elec)      TSS_TSIL_MODULE_NAME_CONV(elec)
  
    #define TSS_TSIL_EL_MODULE_NAME(el)            TSS_GET_TSIL_EL_MODULE_NAME(TSS_E##el##_TYPE)
  
    /*********************************************************************************
    *                      TSIL Method Module Name Recognition Macros
    *********************************************************************************/
  
    #define TSS_TSICH0_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSICH1_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSICH2_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSICH3_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSICH4_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSICH5_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSICH6_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSICH7_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSICH8_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSICH9_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSICH10_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSICH11_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSICH12_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSICH13_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSICH14_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSICH15_TSIL_METHOD_MODULE_NAME           TSIL
  
    #define TSS_TSI0CH0_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0CH1_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0CH2_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0CH3_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0CH4_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0CH5_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0CH6_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0CH7_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0CH8_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0CH9_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0CH10_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0CH11_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0CH12_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0CH13_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0CH14_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0CH15_TSIL_METHOD_MODULE_NAME          TSIL0
  
    #define TSS_TSI1CH0_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1CH1_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1CH2_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1CH3_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1CH4_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1CH5_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1CH6_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1CH7_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1CH8_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1CH9_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1CH10_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1CH11_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1CH12_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1CH13_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1CH14_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1CH15_TSIL_METHOD_MODULE_NAME          TSIL1
  
  
    #define TSS_TSI_CH0_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_CH1_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_CH2_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_CH3_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_CH4_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_CH5_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_CH6_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_CH7_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_CH8_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_CH9_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_CH10_TSIL_METHOD_MODULE_NAME          TSIL
    #define TSS_TSI_CH11_TSIL_METHOD_MODULE_NAME          TSIL
    #define TSS_TSI_CH12_TSIL_METHOD_MODULE_NAME          TSIL
    #define TSS_TSI_CH13_TSIL_METHOD_MODULE_NAME          TSIL
    #define TSS_TSI_CH14_TSIL_METHOD_MODULE_NAME          TSIL
    #define TSS_TSI_CH15_TSIL_METHOD_MODULE_NAME          TSIL
  
    #define TSS_TSI0_CH0_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_CH1_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_CH2_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_CH3_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_CH4_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_CH5_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_CH6_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_CH7_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_CH8_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_CH9_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_CH10_TSIL_METHOD_MODULE_NAME         TSIL0
    #define TSS_TSI0_CH11_TSIL_METHOD_MODULE_NAME         TSIL0
    #define TSS_TSI0_CH12_TSIL_METHOD_MODULE_NAME         TSIL0
    #define TSS_TSI0_CH13_TSIL_METHOD_MODULE_NAME         TSIL0
    #define TSS_TSI0_CH14_TSIL_METHOD_MODULE_NAME         TSIL0
    #define TSS_TSI0_CH15_TSIL_METHOD_MODULE_NAME         TSIL0
  
    #define TSS_TSI1_CH0_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_CH1_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_CH2_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_CH3_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_CH4_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_CH5_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_CH6_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_CH7_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_CH8_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_CH9_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_CH10_TSIL_METHOD_MODULE_NAME         TSIL1
    #define TSS_TSI1_CH11_TSIL_METHOD_MODULE_NAME         TSIL1
    #define TSS_TSI1_CH12_TSIL_METHOD_MODULE_NAME         TSIL1
    #define TSS_TSI1_CH13_TSIL_METHOD_MODULE_NAME         TSIL1
    #define TSS_TSI1_CH14_TSIL_METHOD_MODULE_NAME         TSIL1
    #define TSS_TSI1_CH15_TSIL_METHOD_MODULE_NAME         TSIL1
    
    
    #define TSS_TSIIN0_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSIIN1_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSIIN2_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSIIN3_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSIIN4_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSIIN5_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSIIN6_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSIIN7_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSIIN8_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSIIN9_TSIL_METHOD_MODULE_NAME            TSIL
    #define TSS_TSIIN10_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSIIN11_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSIIN12_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSIIN13_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSIIN14_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSIIN15_TSIL_METHOD_MODULE_NAME           TSIL
  
    #define TSS_TSI0IN0_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0IN1_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0IN2_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0IN3_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0IN4_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0IN5_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0IN6_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0IN7_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0IN8_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0IN9_TSIL_METHOD_MODULE_NAME           TSIL0
    #define TSS_TSI0IN10_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0IN11_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0IN12_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0IN13_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0IN14_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0IN15_TSIL_METHOD_MODULE_NAME          TSIL0
  
    #define TSS_TSI1IN0_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1IN1_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1IN2_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1IN3_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1IN4_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1IN5_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1IN6_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1IN7_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1IN8_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1IN9_TSIL_METHOD_MODULE_NAME           TSIL1
    #define TSS_TSI1IN10_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1IN11_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1IN12_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1IN13_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1IN14_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1IN15_TSIL_METHOD_MODULE_NAME          TSIL1
  
  
    #define TSS_TSI_IN0_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_IN1_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_IN2_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_IN3_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_IN4_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_IN5_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_IN6_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_IN7_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_IN8_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_IN9_TSIL_METHOD_MODULE_NAME           TSIL
    #define TSS_TSI_IN10_TSIL_METHOD_MODULE_NAME          TSIL
    #define TSS_TSI_IN11_TSIL_METHOD_MODULE_NAME          TSIL
    #define TSS_TSI_IN12_TSIL_METHOD_MODULE_NAME          TSIL
    #define TSS_TSI_IN13_TSIL_METHOD_MODULE_NAME          TSIL
    #define TSS_TSI_IN14_TSIL_METHOD_MODULE_NAME          TSIL
    #define TSS_TSI_IN15_TSIL_METHOD_MODULE_NAME          TSIL
  
    #define TSS_TSI0_IN0_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_IN1_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_IN2_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_IN3_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_IN4_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_IN5_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_IN6_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_IN7_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_IN8_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_IN9_TSIL_METHOD_MODULE_NAME          TSIL0
    #define TSS_TSI0_IN10_TSIL_METHOD_MODULE_NAME         TSIL0
    #define TSS_TSI0_IN11_TSIL_METHOD_MODULE_NAME         TSIL0
    #define TSS_TSI0_IN12_TSIL_METHOD_MODULE_NAME         TSIL0
    #define TSS_TSI0_IN13_TSIL_METHOD_MODULE_NAME         TSIL0
    #define TSS_TSI0_IN14_TSIL_METHOD_MODULE_NAME         TSIL0
    #define TSS_TSI0_IN15_TSIL_METHOD_MODULE_NAME         TSIL0
  
    #define TSS_TSI1_IN0_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_IN1_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_IN2_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_IN3_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_IN4_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_IN5_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_IN6_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_IN7_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_IN8_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_IN9_TSIL_METHOD_MODULE_NAME          TSIL1
    #define TSS_TSI1_IN10_TSIL_METHOD_MODULE_NAME         TSIL1
    #define TSS_TSI1_IN11_TSIL_METHOD_MODULE_NAME         TSIL1
    #define TSS_TSI1_IN12_TSIL_METHOD_MODULE_NAME         TSIL1
    #define TSS_TSI1_IN13_TSIL_METHOD_MODULE_NAME         TSIL1
    #define TSS_TSI1_IN14_TSIL_METHOD_MODULE_NAME         TSIL1
    #define TSS_TSI1_IN15_TSIL_METHOD_MODULE_NAME         TSIL1

  
    #define TSS_TSIL_METHOD_MODULE_NAME_RESULT(res)       TSS_##res##_TSIL_METHOD_MODULE_NAME
    #define TSS_TSIL_METHOD_MODULE_NAME_CONV(text)        TSS_TSIL_METHOD_MODULE_NAME_RESULT(text)
    #define TSS_TSIL_METHOD_MODULE_NAME(elec)             TSS_TSIL_METHOD_MODULE_NAME_CONV(elec)
  
    #define TSS_TSIL_EL_METHOD_MODULE_NAME(el)            TSS_TSIL_METHOD_MODULE_NAME(TSS_E##el##_TYPE)
        
  #endif /* End of TSS_DETECT_METHOD(TSIL) */
        
  /*********************************************************************************
  *                               TSIL Channel Macros
  *********************************************************************************/

  #define TSS_TSIL_TSICH0_PEN_SHIFT              0
  #define TSS_TSIL_TSICH1_PEN_SHIFT              1
  #define TSS_TSIL_TSICH2_PEN_SHIFT              2
  #define TSS_TSIL_TSICH3_PEN_SHIFT              3
  #define TSS_TSIL_TSICH4_PEN_SHIFT              4
  #define TSS_TSIL_TSICH5_PEN_SHIFT              5
  #define TSS_TSIL_TSICH6_PEN_SHIFT              6
  #define TSS_TSIL_TSICH7_PEN_SHIFT              7
  #define TSS_TSIL_TSICH8_PEN_SHIFT              8
  #define TSS_TSIL_TSICH9_PEN_SHIFT              9
  #define TSS_TSIL_TSICH10_PEN_SHIFT             10
  #define TSS_TSIL_TSICH11_PEN_SHIFT             11
  #define TSS_TSIL_TSICH12_PEN_SHIFT             12
  #define TSS_TSIL_TSICH13_PEN_SHIFT             13
  #define TSS_TSIL_TSICH14_PEN_SHIFT             14
  #define TSS_TSIL_TSICH15_PEN_SHIFT             15
  
  #define TSS_TSIL_TSI0CH0_PEN_SHIFT             0
  #define TSS_TSIL_TSI0CH1_PEN_SHIFT             1
  #define TSS_TSIL_TSI0CH2_PEN_SHIFT             2
  #define TSS_TSIL_TSI0CH3_PEN_SHIFT             3
  #define TSS_TSIL_TSI0CH4_PEN_SHIFT             4
  #define TSS_TSIL_TSI0CH5_PEN_SHIFT             5
  #define TSS_TSIL_TSI0CH6_PEN_SHIFT             6
  #define TSS_TSIL_TSI0CH7_PEN_SHIFT             7
  #define TSS_TSIL_TSI0CH8_PEN_SHIFT             8
  #define TSS_TSIL_TSI0CH9_PEN_SHIFT             9
  #define TSS_TSIL_TSI0CH10_PEN_SHIFT            10
  #define TSS_TSIL_TSI0CH11_PEN_SHIFT            11
  #define TSS_TSIL_TSI0CH12_PEN_SHIFT            12
  #define TSS_TSIL_TSI0CH13_PEN_SHIFT            13
  #define TSS_TSIL_TSI0CH14_PEN_SHIFT            14
  #define TSS_TSIL_TSI0CH15_PEN_SHIFT            15
  
  #define TSS_TSIL_TSI1CH0_PEN_SHIFT             0
  #define TSS_TSIL_TSI1CH1_PEN_SHIFT             1
  #define TSS_TSIL_TSI1CH2_PEN_SHIFT             2
  #define TSS_TSIL_TSI1CH3_PEN_SHIFT             3
  #define TSS_TSIL_TSI1CH4_PEN_SHIFT             4
  #define TSS_TSIL_TSI1CH5_PEN_SHIFT             5
  #define TSS_TSIL_TSI1CH6_PEN_SHIFT             6
  #define TSS_TSIL_TSI1CH7_PEN_SHIFT             7
  #define TSS_TSIL_TSI1CH8_PEN_SHIFT             8
  #define TSS_TSIL_TSI1CH9_PEN_SHIFT             9
  #define TSS_TSIL_TSI1CH10_PEN_SHIFT            10
  #define TSS_TSIL_TSI1CH11_PEN_SHIFT            11
  #define TSS_TSIL_TSI1CH12_PEN_SHIFT            12
  #define TSS_TSIL_TSI1CH13_PEN_SHIFT            13
  #define TSS_TSIL_TSI1CH14_PEN_SHIFT            14
  #define TSS_TSIL_TSI1CH15_PEN_SHIFT            15
  
  
  #define TSS_TSIL_TSI_CH0_PEN_SHIFT             0
  #define TSS_TSIL_TSI_CH1_PEN_SHIFT             1
  #define TSS_TSIL_TSI_CH2_PEN_SHIFT             2
  #define TSS_TSIL_TSI_CH3_PEN_SHIFT             3 
  #define TSS_TSIL_TSI_CH4_PEN_SHIFT             4
  #define TSS_TSIL_TSI_CH5_PEN_SHIFT             5
  #define TSS_TSIL_TSI_CH6_PEN_SHIFT             6
  #define TSS_TSIL_TSI_CH7_PEN_SHIFT             7
  #define TSS_TSIL_TSI_CH8_PEN_SHIFT             8
  #define TSS_TSIL_TSI_CH9_PEN_SHIFT             9
  #define TSS_TSIL_TSI_CH10_PEN_SHIFT            10
  #define TSS_TSIL_TSI_CH11_PEN_SHIFT            11
  #define TSS_TSIL_TSI_CH12_PEN_SHIFT            12
  #define TSS_TSIL_TSI_CH13_PEN_SHIFT            13
  #define TSS_TSIL_TSI_CH14_PEN_SHIFT            14
  #define TSS_TSIL_TSI_CH15_PEN_SHIFT            15
  
  #define TSS_TSIL_TSI0_CH0_PEN_SHIFT            0
  #define TSS_TSIL_TSI0_CH1_PEN_SHIFT            1
  #define TSS_TSIL_TSI0_CH2_PEN_SHIFT            2
  #define TSS_TSIL_TSI0_CH3_PEN_SHIFT            3
  #define TSS_TSIL_TSI0_CH4_PEN_SHIFT            4
  #define TSS_TSIL_TSI0_CH5_PEN_SHIFT            5 
  #define TSS_TSIL_TSI0_CH6_PEN_SHIFT            6
  #define TSS_TSIL_TSI0_CH7_PEN_SHIFT            7
  #define TSS_TSIL_TSI0_CH8_PEN_SHIFT            8
  #define TSS_TSIL_TSI0_CH9_PEN_SHIFT            9
  #define TSS_TSIL_TSI0_CH10_PEN_SHIFT           10
  #define TSS_TSIL_TSI0_CH11_PEN_SHIFT           11
  #define TSS_TSIL_TSI0_CH12_PEN_SHIFT           12
  #define TSS_TSIL_TSI0_CH13_PEN_SHIFT           13
  #define TSS_TSIL_TSI0_CH14_PEN_SHIFT           14
  #define TSS_TSIL_TSI0_CH15_PEN_SHIFT           15
  
  #define TSS_TSIL_TSI1_CH0_PEN_SHIFT            0
  #define TSS_TSIL_TSI1_CH1_PEN_SHIFT            1
  #define TSS_TSIL_TSI1_CH2_PEN_SHIFT            2
  #define TSS_TSIL_TSI1_CH3_PEN_SHIFT            3
  #define TSS_TSIL_TSI1_CH4_PEN_SHIFT            4
  #define TSS_TSIL_TSI1_CH5_PEN_SHIFT            5
  #define TSS_TSIL_TSI1_CH6_PEN_SHIFT            6
  #define TSS_TSIL_TSI1_CH7_PEN_SHIFT            7
  #define TSS_TSIL_TSI1_CH8_PEN_SHIFT            8
  #define TSS_TSIL_TSI1_CH9_PEN_SHIFT            9
  #define TSS_TSIL_TSI1_CH10_PEN_SHIFT           10
  #define TSS_TSIL_TSI1_CH11_PEN_SHIFT           11
  #define TSS_TSIL_TSI1_CH12_PEN_SHIFT           12
  #define TSS_TSIL_TSI1_CH13_PEN_SHIFT           13
  #define TSS_TSIL_TSI1_CH14_PEN_SHIFT           14
  #define TSS_TSIL_TSI1_CH15_PEN_SHIFT           15
  
  
  #define TSS_TSIL_TSIIN0_PEN_SHIFT              0
  #define TSS_TSIL_TSIIN1_PEN_SHIFT              1
  #define TSS_TSIL_TSIIN2_PEN_SHIFT              2
  #define TSS_TSIL_TSIIN3_PEN_SHIFT              3
  #define TSS_TSIL_TSIIN4_PEN_SHIFT              4
  #define TSS_TSIL_TSIIN5_PEN_SHIFT              5
  #define TSS_TSIL_TSIIN6_PEN_SHIFT              6
  #define TSS_TSIL_TSIIN7_PEN_SHIFT              7
  #define TSS_TSIL_TSIIN8_PEN_SHIFT              8
  #define TSS_TSIL_TSIIN9_PEN_SHIFT              9
  #define TSS_TSIL_TSIIN10_PEN_SHIFT             10
  #define TSS_TSIL_TSIIN11_PEN_SHIFT             11
  #define TSS_TSIL_TSIIN12_PEN_SHIFT             12
  #define TSS_TSIL_TSIIN13_PEN_SHIFT             13
  #define TSS_TSIL_TSIIN14_PEN_SHIFT             14
  #define TSS_TSIL_TSIIN15_PEN_SHIFT             15
  
  #define TSS_TSIL_TSI0IN0_PEN_SHIFT             0
  #define TSS_TSIL_TSI0IN1_PEN_SHIFT             1
  #define TSS_TSIL_TSI0IN2_PEN_SHIFT             2
  #define TSS_TSIL_TSI0IN3_PEN_SHIFT             3
  #define TSS_TSIL_TSI0IN4_PEN_SHIFT             4
  #define TSS_TSIL_TSI0IN5_PEN_SHIFT             5
  #define TSS_TSIL_TSI0IN6_PEN_SHIFT             6
  #define TSS_TSIL_TSI0IN7_PEN_SHIFT             7
  #define TSS_TSIL_TSI0IN8_PEN_SHIFT             8
  #define TSS_TSIL_TSI0IN9_PEN_SHIFT             9
  #define TSS_TSIL_TSI0IN10_PEN_SHIFT            10
  #define TSS_TSIL_TSI0IN11_PEN_SHIFT            11
  #define TSS_TSIL_TSI0IN12_PEN_SHIFT            12
  #define TSS_TSIL_TSI0IN13_PEN_SHIFT            13
  #define TSS_TSIL_TSI0IN14_PEN_SHIFT            14
  #define TSS_TSIL_TSI0IN15_PEN_SHIFT            15
  
  #define TSS_TSIL_TSI1IN0_PEN_SHIFT             0
  #define TSS_TSIL_TSI1IN1_PEN_SHIFT             1
  #define TSS_TSIL_TSI1IN2_PEN_SHIFT             2
  #define TSS_TSIL_TSI1IN3_PEN_SHIFT             3
  #define TSS_TSIL_TSI1IN4_PEN_SHIFT             4
  #define TSS_TSIL_TSI1IN5_PEN_SHIFT             5
  #define TSS_TSIL_TSI1IN6_PEN_SHIFT             6
  #define TSS_TSIL_TSI1IN7_PEN_SHIFT             7
  #define TSS_TSIL_TSI1IN8_PEN_SHIFT             8
  #define TSS_TSIL_TSI1IN9_PEN_SHIFT             9
  #define TSS_TSIL_TSI1IN10_PEN_SHIFT            10
  #define TSS_TSIL_TSI1IN11_PEN_SHIFT            11
  #define TSS_TSIL_TSI1IN12_PEN_SHIFT            12
  #define TSS_TSIL_TSI1IN13_PEN_SHIFT            13
  #define TSS_TSIL_TSI1IN14_PEN_SHIFT            14
  #define TSS_TSIL_TSI1IN15_PEN_SHIFT            15
  
  
  #define TSS_TSIL_TSI_IN0_PEN_SHIFT             0
  #define TSS_TSIL_TSI_IN1_PEN_SHIFT             1
  #define TSS_TSIL_TSI_IN2_PEN_SHIFT             2
  #define TSS_TSIL_TSI_IN3_PEN_SHIFT             3 
  #define TSS_TSIL_TSI_IN4_PEN_SHIFT             4
  #define TSS_TSIL_TSI_IN5_PEN_SHIFT             5
  #define TSS_TSIL_TSI_IN6_PEN_SHIFT             6
  #define TSS_TSIL_TSI_IN7_PEN_SHIFT             7
  #define TSS_TSIL_TSI_IN8_PEN_SHIFT             8
  #define TSS_TSIL_TSI_IN9_PEN_SHIFT             9
  #define TSS_TSIL_TSI_IN10_PEN_SHIFT            10
  #define TSS_TSIL_TSI_IN11_PEN_SHIFT            11
  #define TSS_TSIL_TSI_IN12_PEN_SHIFT            12
  #define TSS_TSIL_TSI_IN13_PEN_SHIFT            13
  #define TSS_TSIL_TSI_IN14_PEN_SHIFT            14
  #define TSS_TSIL_TSI_IN15_PEN_SHIFT            15
  
  #define TSS_TSIL_TSI0_IN0_PEN_SHIFT            0
  #define TSS_TSIL_TSI0_IN1_PEN_SHIFT            1
  #define TSS_TSIL_TSI0_IN2_PEN_SHIFT            2
  #define TSS_TSIL_TSI0_IN3_PEN_SHIFT            3
  #define TSS_TSIL_TSI0_IN4_PEN_SHIFT            4
  #define TSS_TSIL_TSI0_IN5_PEN_SHIFT            5 
  #define TSS_TSIL_TSI0_IN6_PEN_SHIFT            6
  #define TSS_TSIL_TSI0_IN7_PEN_SHIFT            7
  #define TSS_TSIL_TSI0_IN8_PEN_SHIFT            8
  #define TSS_TSIL_TSI0_IN9_PEN_SHIFT            9
  #define TSS_TSIL_TSI0_IN10_PEN_SHIFT           10
  #define TSS_TSIL_TSI0_IN11_PEN_SHIFT           11
  #define TSS_TSIL_TSI0_IN12_PEN_SHIFT           12
  #define TSS_TSIL_TSI0_IN13_PEN_SHIFT           13
  #define TSS_TSIL_TSI0_IN14_PEN_SHIFT           14
  #define TSS_TSIL_TSI0_IN15_PEN_SHIFT           15
  
  #define TSS_TSIL_TSI1_IN0_PEN_SHIFT            0
  #define TSS_TSIL_TSI1_IN1_PEN_SHIFT            1
  #define TSS_TSIL_TSI1_IN2_PEN_SHIFT            2
  #define TSS_TSIL_TSI1_IN3_PEN_SHIFT            3
  #define TSS_TSIL_TSI1_IN4_PEN_SHIFT            4
  #define TSS_TSIL_TSI1_IN5_PEN_SHIFT            5
  #define TSS_TSIL_TSI1_IN6_PEN_SHIFT            6
  #define TSS_TSIL_TSI1_IN7_PEN_SHIFT            7
  #define TSS_TSIL_TSI1_IN8_PEN_SHIFT            8
  #define TSS_TSIL_TSI1_IN9_PEN_SHIFT            9
  #define TSS_TSIL_TSI1_IN10_PEN_SHIFT           10
  #define TSS_TSIL_TSI1_IN11_PEN_SHIFT           11
  #define TSS_TSIL_TSI1_IN12_PEN_SHIFT           12
  #define TSS_TSIL_TSI1_IN13_PEN_SHIFT           13
  #define TSS_TSIL_TSI1_IN14_PEN_SHIFT           14
  #define TSS_TSIL_TSI1_IN15_PEN_SHIFT           15

  
  #define TSS_TSIL_GET_EL_PEN_TO_REG(reg)        TSS_TSIL_##reg##_PEN_SHIFT
  #define TSS_TSIL_GET_EL_PEN(name)              TSS_TSIL_GET_EL_PEN_TO_REG(name)

  #define TSS_TSIL_EL_CHANNEL_MASK(el)           1 << TSS_TSIL_GET_EL_PEN(TSS_E##el##_TYPE)
  #define TSS_TSIL_EL_CHANNEL_NUM(el)            TSS_TSIL_GET_EL_PEN(TSS_E##el##_TYPE)
      
#endif /* TSS_SENSORTSIL_H */