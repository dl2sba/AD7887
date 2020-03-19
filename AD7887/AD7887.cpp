//=================================================================
//
//  Simple library to access the AD7887 ADC with an Arduino. The work is based on Makis's work (https://www.sv1afn.com/ad8318.html).
//
//	Version 1.1.0
//
//  (c) Dietmar Krause, DL2SBA 2017
//
//  License see https://creativecommons.org/licenses/by/4.0/

#include <arduino.h>
#include "AD7887.h"

#define AD7887_DELAY_T1 // delayMicroseconds(10)
#define AD7887_DELAY_T2 // delayMicroseconds(1)
#define AD7887_DELAY_T3 // delayMicroseconds(1)
#define AD7887_DELAY_T4 // delayMicroseconds(1)

AD7887::AD7887 ( uint8_t pPinSelect, uint8_t pPinDataOut, uint8_t pPinDataIn, uint8_t pPinSPIClock ) {

  this->mPinSelect   = pPinSelect;
  this->mPinDataOut  = pPinDataOut;
  this->mPinDataIn   = pPinDataIn;
  this->mPinSPIClock = pPinSPIClock;

  pinMode(this->mPinSelect,   OUTPUT);
  pinMode(this->mPinDataOut,  OUTPUT);
  pinMode(this->mPinDataIn,   INPUT);
  pinMode(this->mPinSPIClock, OUTPUT);

  digitalWrite(this->mPinSelect, HIGH);
  digitalWrite(this->mPinDataOut, LOW);
  digitalWrite(this->mPinSPIClock, HIGH);
  mControlByte = AD7887_CONTROL_BYTE;
}

void AD7887::setControlByte(uint8_t pByte) {
	mControlByte = pByte;
}


uint8_t AD7887::readWriteByte(uint8_t in) {
  uint8_t rc = 0;

  for ( uint8_t i = 0; i < 8; ++i ) {
    rc <<= 1;

    // write data out
    // high bit set?
    if ( in & 0x80 ) {
      //  send high bit
      digitalWrite(this->mPinDataOut, 1);
    } else {
      // send low bit
      digitalWrite(this->mPinDataOut, 0);
    }
    AD7887_DELAY_T3;

	//	 toggle clock
    digitalWrite(this->mPinSPIClock, LOW);
    AD7887_DELAY_T2;

    //  rising edge copies data to adc
    digitalWrite(this->mPinSPIClock, HIGH);
    AD7887_DELAY_T4;

    //  read dataline
    rc += digitalRead(this->mPinDataIn);

    //  shift input one left
    in <<= 1;
  }
  return rc;
}

/**
 *  Read a 12bit value from the ADC
 *  Return 0xffff in case of an read error
 */
uint16_t AD7887::readADC( void ) {
  digitalWrite(this->mPinSelect, LOW);    //  Select adc

  AD7887_DELAY_T1;

  uint16_t highByte = readWriteByte(mControlByte);
  uint16_t lowByte =  readWriteByte(0x00);

  digitalWrite(this->mPinSelect, HIGH); //  deselect adc

  if ( highByte & 0xf0 ) {
    //  return error
    return 0xffff;
  } else {
    return ( highByte << 8 ) + lowByte;
  }
}


