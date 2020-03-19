//=================================================================
//
//  Simple library to access the AD7887 ADC with an Arduino. The work is based on Makis's work (https://www.sv1afn.com/ad8318.html).
//
//	Version 1.1.0
//
//  (c) Dietmar Krause, DL2SBA 2017
//
//  License see https://creativecommons.org/licenses/by/4.0/

#ifndef _AD7887_H
#define _AD7887_H

#define AD7887_CONTROL_BYTE 0xA1

class AD7887 {
  public:
	/**
	 *  Create a new instance for the ADC.
	 *  
	 *  pPinSelect Pin number of the CS pin of the ADC
	 *  pPinDataOut Pin number of the data pin TO the ADC
	 *  pPinDataIn Pin number of the data pin FROM the ADC
	 *  pPinSPIClock Pin number of the SPI clock outputr TO the ADC
	 *  
	 *  Default control byte is 0xA1 - means
	 *  	External ref
	 *  	Single channel
	 *  	Powermode 2
	 *  
	 */
    AD7887(uint8_t pPinSelect, uint8_t pPinDataOut, uint8_t pPinDataIn, uint8_t pPinSPIClock );

	/**
	 *  Set the control byte for the next conversion
	 */
	void setControlByte(uint8_t pByte);

	/**
	 *  Read a 12bit value from the ADC
	 *  Return 0xffff in case of an read error
	 */
    uint16_t readADC( void );

  protected:
    uint8_t  readWriteByte(uint8_t in);

  protected:
    uint8_t mPinSelect;
    uint8_t mPinDataOut;
    uint8_t mPinDataIn;
    uint8_t mPinSPIClock;
	uint8_t mControlByte;
};


#endif
