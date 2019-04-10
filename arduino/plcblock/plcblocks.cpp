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
    RS     : RS Biestable
    SR     : SR Biestable
		BLINK  : Digital Square wave generator
		
	Version control
	---------------
	* v1.0 AAL, Abril 2019
	
*/

#include "plcblocks.h"


/* 	Private. */
void TON::Init( unsigned long PT)
{
	m_ET= 0;
	m_PT= PT;
	m_IN= LOW;
	m_Q= LOW;
	m_LastTick= millis();  
}

/**
*/
TON::TON( unsigned long PT) 
{
  Init( PT);
}

/**
*/
TON::TON( BOOL IN, unsigned long PT)
{
  Init( PT);
  m_Q= Run( IN);
}  
  
/**
*/  
BOOL TON::Run( BOOL IN)
{
  unsigned long _ulTickCount;
  
  if( m_IN != IN) {   
    m_IN= IN;
    if( m_IN) {
      m_LastTick= millis();         
    }
    else {
      m_Q= LOW;      
    }
  }
  if( m_IN && m_Q == LOW) {
    _ulTickCount= millis();
    if( _ulTickCount >= m_LastTick) {
      m_ET= _ulTickCount - m_LastTick;
    }
    else {
      m_ET= (0xFFFFFFFF - m_LastTick) + _ulTickCount;
    }        
    if( (m_ET >= m_PT) && (m_PT > 0)) {	
      m_Q= HIGH;        
    }
  }
  return m_Q; 
}  

BOOL TON::Run( BOOL IN, unsigned long PT)
{
  m_PT= PT;
  return Run( IN);
}

unsigned long TON::ET(void)
{
	return m_ET;
}


/*
*   TOFF
*  ========
*/
/**
*    Private. 
*/
void TOF::Init( unsigned long PT)
{
  m_ET= 0;
  m_PT= PT;
  m_IN= LOW;
  m_Q= LOW;
  m_LastTick= millis();  
}

/**
 * Constructor
*/
TOF::TOF( unsigned long PT) 
{
  Init( PT);
}

/**
 * Constructor
*/
TOF::TOF( BOOL IN, unsigned long PT)
{
  Init( PT);
  m_Q= Run( IN);
}  
  
/**
 * 
*/  
BOOL TOF::Run( BOOL IN)
{
  unsigned long _ulTickCount;
  
  if( m_IN != IN) {   
    m_IN= IN;
    if( m_IN == LOW) {
      m_LastTick= millis();         
    }
    else {
      m_Q= HIGH;      
    }
  }
  if( m_IN == LOW && m_Q == HIGH) {
    _ulTickCount= millis();
    if( _ulTickCount >= m_LastTick) {
      m_ET= _ulTickCount - m_LastTick;
    }
    else {
      m_ET= (0xFFFFFFFF - m_LastTick) + _ulTickCount;
    }        
    if( (m_ET >= m_PT) && (m_PT > 0)) { 
      m_Q= LOW;        
    }
  }
  return m_Q; 
}  

/**
 * 
*/  
BOOL TOF::Run( BOOL IN, unsigned long PT)
{
  m_PT= PT;
  return Run( IN);
}

/**
 * 
*/  
unsigned long TOF::ET(void)
{
  return m_ET;
}


/*
*   TP
*  ========
*/
/**
*    Private. 
*/
void TP::Init( unsigned long PT)
{
  m_ET= 0;
  m_PT= PT;
  m_IN= LOW;
  m_Q= LOW;
  m_LastTick= millis();  
}

/**
 * Constructor
*/
TP::TP( unsigned long PT) 
{
  Init( PT);
}

/**
 * Constructor
*/
TP::TP( BOOL IN, unsigned long PT)
{
  Init( PT);
  m_Q= Run( IN);
}  
  
/**
 * 
*/  
BOOL TP::Run( BOOL IN)
{
  unsigned long _ulTickCount;
  
  if( m_IN != IN) {   
    m_IN= IN;
    if( m_IN == HIGH) {
      m_LastTick= millis();         
    }
    else {
      m_Q= LOW;      
    }
  }
  if( m_IN == HIGH && m_Q == HIGH) {
    _ulTickCount= millis();
    if( _ulTickCount >= m_LastTick) {
      m_ET= _ulTickCount - m_LastTick;
    }
    else {
      m_ET= (0xFFFFFFFF - m_LastTick) + _ulTickCount;
    }        
    if( (m_ET >= m_PT) && (m_PT > 0)) { 
      m_Q= LOW;        
    }
  }
  return m_Q; 
}  

/**
 * 
*/  
BOOL TP::Run( BOOL IN, unsigned long PT)
{
  m_PT= PT;
  return Run( IN);
}

/**
 * 
*/  
unsigned long TP::ET(void)
{
  return m_ET;
}


/*
*   R_TRIG
*
*/
R_TRIG::R_TRIG( BOOL IN)
{
    m_blMem= IN;
}

BOOL R_TRIG::Run( BOOL IN)
{
   if( m_blMem != IN){
        m_blMem= IN;
        if( IN ) {
          return HIGH;
        }
    }
    return LOW;
}


/*
*   F_TRIG
*  ========
*/
F_TRIG::F_TRIG( BOOL IN)
{
    m_blMem= IN;
}

/**
*/
BOOL F_TRIG::Run( BOOL IN)
{
   if( m_blMem != IN){
        m_blMem= IN;
        if( !IN ) {
          return HIGH;
        }
    }
    return LOW;
}


/*
*   TRIG
*  ========
*/
TRIG::TRIG( BOOL IN)
{
  m_blMem= IN;
}

/**
*/
BOOL TRIG::Run( BOOL IN)
{
   if( m_blMem != IN){
      m_blMem= IN;
      return HIGH;
    }
    return LOW;
}

/**
  RS 
  =====

*/
RS::RS( void)
{
  m_blQ= LOW;
}

/**
 * 
 */
BOOL RS::Run( BOOL SET, BOOL RESET)
{
  if( SET == RESET) {
    if( SET && RESET) {
      m_blQ= LOW;   
    } 
  } 
  else {
    m_blQ= LOW;   
    if( SET) {
      m_blQ= HIGH;   
    }
  }
  return m_blQ;
}


/**
  RS 
  =====

*/
SR::SR( void)
{
  m_blQ= LOW;
}

/**
 * 
 */
BOOL SR::Run( BOOL SET, BOOL RESET)
{
  if( SET == RESET) {
    if( SET && RESET) {
      m_blQ= HIGH;   
    } 
  } 
  else {
    m_blQ= LOW;   
    if( SET) {
      m_blQ= HIGH;   
    }
  }
  return m_blQ;
}


/**
  CTU: Upwards Counter 
  =====

*/
/* 	Private. */
void CTU::Init( WORD PV)
{
	m_CV= 0;
	m_PV= PV;
	m_Clock= LOW;
	m_Q= LOW;
}

/**
*/
CTU::CTU( WORD PV) 
{
  Init( PV);
}
  
/**
*/  
BOOL CTU::Run( BOOL CU, BOOL RESET)
{
  if( RESET == HIGH) {
    m_CV= 0;
  } 
  if( m_Clock != CU) {   
    m_Clock= CU;
    if( m_Clock) {
      if( m_CV < 65535) {
        m_CV++;         
      } 
      m_Q= LOW;
      if( m_CV >= m_PV) {
        m_Q= HIGH;    
      } 
    }
  }
  return m_Q;
}  

/**
*/
BOOL CTU::Run( BOOL CU, BOOL RESET, WORD PV)
{
  m_PV= PV;
  return Run( CU, RESET);
}

/**
*/
void CTU::PV( WORD value)
{
  m_PV= value;
}    
 
/**
*/
WORD CTU::CV(void)
{
	return m_CV;
}

/**
*/
BOOL CTU::Q(void)
{
  return m_Q;
}


/**
  CTD: Downwards Counter 
  =====

*/
/* 	Private. */
void CTD::Init( WORD PV)
{
	m_CV= 0;
	m_PV= PV;
	m_Clock= LOW;
	m_Q= LOW;
}

/**
*/
CTD::CTD( WORD PV) 
{
  Init( PV);
}
  
/**
*/  
BOOL CTD::Run( BOOL CD, BOOL LOAD)
{  
  if( LOAD == HIGH) {
    m_CV= m_PV;
  } 
  if( m_Clock != CD) {   
    m_Clock= CD;
    if( m_Clock) {
      if( m_CV > 0) {
        m_CV--;         
      } 
      m_Q= LOW;
      if( m_CV == 0) {
        m_Q= HIGH;    
      } 
    }
  }
  return m_Q;
}  

/**
*/ 
BOOL CTD::Run( BOOL CD, BOOL LOAD, WORD PV)
{
  m_PV= PV;
  return Run( CD, LOAD);
}

/**
*/ 
void CTD::PV( WORD value)
{
  m_PV= value;
}    
 
/**
*/ 
WORD CTD::CV(void)
{
	return m_CV;
}

/**
*/ 
BOOL CTD::Q(void)
{
  return m_Q;
}
