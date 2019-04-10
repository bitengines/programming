/**
	PlcBlocks
	==========

	Collection of classes that resembles common components found in IEC 61131 
	PLC programming languajes. 
		TON    : Turn-on Delay Timer
		TOFF   : Turn-off Delay Timer
    TP     : Pulse Timer
		R_TRIG : Rising Edge Detection
		F_TRIG : Falling Edge Detection
		TRIG   : Both Rising and Falling Edge Detection
    RS     : RS Biestable
    SR     : SR Biestable
		CTU    : Upwards Counter 
    DTU    : Downwards Counter 
		
	Version control
	---------------
	* v1.0 AAL, Abril 2019
	
*/

#ifndef __PlcBlocks_HPP
#define __PlcBlocks_HPP


#include "Arduino.h"


#define BOOL uint8_t
#define WORD uint16_t


/**
	TON	
	
	  Turn-on Delay Timer
	
	Usage: 
	
	Version control
	---------------
	* v1.0 AAL, March 2019	
*/
class TON {
private:
  unsigned long m_LastTick;  
  BOOL m_IN;  
  unsigned long m_PT;  
  unsigned long m_ET;  
  BOOL m_Q;    
  
  void Init(unsigned long PT);

public:
  TON( unsigned long PT= 0);
  TON( BOOL IN, unsigned long PT);
  BOOL Run( BOOL IN);
  BOOL Run( BOOL IN, unsigned long PT);
  void PT( unsigned long millisecs);    
  unsigned long ET(void);
};

/**
  TOF 
  
    Turn-off Delay Timer
  
  Usage: 
  
  Version control
  ---------------
  * v1.0 AAL, March 2019
*/
class TOF {
private:
  unsigned long m_LastTick;  
  BOOL m_IN;  
  unsigned long m_PT;  
  unsigned long m_ET;  
  BOOL m_Q;    
  
  void Init(unsigned long PT);
public:
  TOF( unsigned long PT= 0);
  TOF( BOOL IN, unsigned long PT);
  BOOL Run( BOOL IN);
  BOOL Run( BOOL IN, unsigned long PT);
  void PT( unsigned long millisecs);    
  unsigned long ET(void);
};

/**
	TP	
	
	  Turn-on Delay Timer
	
	Usage: 
	
	Version control
	---------------
	* v1.0 AAL, March 2019	
*/
class TP {
private:
  unsigned long m_LastTick;  
  BOOL m_IN;  
  unsigned long m_PT;  
  unsigned long m_ET;  
  BOOL m_Q;    
  
  void Init(unsigned long PT);
public:
  TP( unsigned long PT= 0);
  TP( BOOL IN, unsigned long PT);
  BOOL Run( BOOL IN);
  BOOL Run( BOOL IN, unsigned long PT);
  void PT( unsigned long millisecs);    
  unsigned long ET(void);
};

/**
  R_TRIG 
  
    Risig Edge Detector
  
  Usage: 
  
  Version control
  ---------------
  - v1.0 AAL, April 2019
*/
class R_TRIG {
private:   
  BOOL m_blMem;    
public:
  R_TRIG( BOOL IN= LOW);
  BOOL Run( BOOL IN);
};


/**
  F_TRIG 
  
    Falling Edge Detector
  
  Usage: 
  
  Version control
  ---------------
  - v1.0 AAL, April 2019
*/
class F_TRIG {
private:   
  BOOL m_blMem;    
public:
  F_TRIG( BOOL IN= LOW);
  BOOL Run( BOOL IN);
};

/**
  TRIG 
  
    Both, Falling and Rising Edge Detector
  
  Usage: 
  
  Version control
  ---------------
  - v1.0 AAL, April 2019
*/
class TRIG {
private:   
  BOOL m_blMem;    
public:
  TRIG( BOOL IN= false);
  BOOL Run( BOOL IN);
};


/**
  RS 
  
    Reseting Biestable 
  
  Usage: 
  
  Version control
  ---------------
  - v1.0 AAL, April 2019
*/
class RS {
private:   
  BOOL m_blQ;    
public:
  RS(void);
  BOOL Run( BOOL SET, BOOL RESET);
};

/**
  SR 
  
    Making Biestable 
  
  Usage: 
  
  Version control
  ---------------
  - v1.0 AAL, April 2019
*/
class SR {
private:   
  BOOL m_blQ;    
public:
  SR(void);
  BOOL Run( BOOL SET, BOOL RESET);
};


/**
  CTU 
  
    Upwards Counter
  
  Usage: 
  
  Version control
  ---------------
  - v1.0 AAL, April 2019
*/
class CTU {
private:
  BOOL m_Clock;  
  WORD m_PV;  
  WORD m_CV;  
  BOOL m_Q;    
  
  void Init( WORD PV);
public:
  CTU( WORD PV= 0);
  BOOL Run( BOOL CU, BOOL RESET= LOW);
  BOOL Run( BOOL CU, BOOL RESET, WORD PV);
  void PV( WORD value);    
  WORD CV(void);
  BOOL Q(void);
};


/**
  CTD 
  
    Downwards Counter
  
  Usage: 
  
  Version control
  ---------------
  - v1.0 AAL, April 2019
*/
class CTD {
private:
  BOOL m_Clock;  
  WORD m_PV;  
  WORD m_CV;  
  BOOL m_Q;    
  
  void Init( WORD PV);
public:
  CTD( WORD PV= 0);
  BOOL Run( BOOL CD, BOOL LOAD= LOW);
  BOOL Run( BOOL CD, BOOL LOAD, WORD PV);
  void PV( WORD value);    
  WORD CV(void);
  BOOL Q(void);
};


#endif