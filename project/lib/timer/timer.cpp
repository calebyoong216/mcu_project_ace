#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

CTimer *selfPtr;

void handleInterrupt() {
  CTimer *p = selfPtr;

  // Decrement counter, if it hits zero
  // call the callback and reset the counter

  for(int i = 0; i<p->_callbackCount; i++) {
    p->_callbacks[i].count--;

    if(p->_callbacks[i].count == 0) {
      p->_callbacks[i].callbackPtr();
      p->_callbacks[i].count = p->_callbacks[i].period;
    }
  }
}
ISR(TIMER0_COMPA_vect) {
  handleInterrupt();
}
// Note: When using this class you will not be able to use delay anymore.
CTimer::CTimer() {
  // Set up timer 0
  selfPtr = this;
  _callbackCount = 0;

  cli();
  TCCR0A = 0b10;
  TIMSK0 |= 0b10;
  TCNT0 = 0;
  OCR0A = 250;
  sei();
}

void CTimer::startTimer(){
  TCCR0B=0b11;
}

void CTimer::stopTimer() {
  TCCR0B=0;
}

int CTimer::attachCallback(void (*callback)(), unsigned int period) {
  
  // Return error if too many callbacks
  if(_callbackCount >= MAX_CALLBACKS)
    return -1;
  
  int n = _callbackCount;
  _callbackCount++;

  _callbacks[n].callbackPtr = callback;
  _callbacks[n].period = period;
  _callbacks[n].count = period;

  return n;
}

int CTimer::changePeriod(int callbackNumber, unsigned int newPeriod) {
    if(callbackNumber < 0 || callbackNumber >= _callbackCount)
        return -1;

    _callbacks[callbackNumber].period = newPeriod;
    _callbacks[callbackNumber].count = newPeriod;
}

CTimer::~CTimer() {
  // Do nothing.
}
