/// See Encoder.h for source info.
///
///
#include <Arduino.h>
#include "Encoder.h"
#include "../util.h"
#include "../Devices/PulseOutputTask.h"


EncoderInterruptClass EncoderInterrupt;

void computeEncoder()
{
	EncoderInterrupt.computeAll();
}
#ifndef ARDUINO_SIM

#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
void setupTimerInterrupt()
{
	TCCR3A = 0; // set entire TCCR3A register to 0
	TCCR3B = 0; // same for TCCR3B
	TCNT3 = 0; // initialize counter value to 0

	// set compare match register (write to the high bit first) 
	OCR3AH = 0;

	// set compare match register for particular frequency increments
	//  OCR3AL = 133; // = (16000000) / 64 / 2000  -> 133   This is  clock_frequency / prescaler / desired_frequency  ( 2 KHz, 0.5ms)
	//  OCR3AL = 50;  // = (16000000) / 64 / 5000  ->  50   This is  clock_frequency / prescaler / desired_frequency  ( 5 KHz, 0.2ms)
	//  OCR3AL = 25;  // = (16000000) / 64 / 10000 ->  25   This is  clock_frequency / prescaler / desired_frequency  (10 kHz, 0.1ms)
	OCR3AL = INTERRUPT_PERIOD;

	// enable timer compare interrupt
	TIMSK3 = (1 << OCIE3A);

	// turn on mode 4 (CTC mode) (up to OCR3A)
	TCCR3B |= (1 << WGM32);

	// Set CS10 and CS12 bits for 64 prescaler
	TCCR3B |= (1 << CS30) | (1 << CS31);

	// More information at
	// http://medesign.seas.upenn.edu/index.php/Guides/MaEvArM-timers 
	//
}

SIGNAL(TIMER3_COMPA_vect)
{
	computeEncoder();
}

#elif  defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
void setupTimerInterrupt()
{
  TCCR2A = 0; // set entire TCCR2A register to 0
  TCCR2B = 0; // same for TCCR2B
  TCNT2  = 0; // initialize counter value to 0

  // set compare match register for particular frequency increments
//  OCR2A = 133; // = (16000000) / 64 / 2000  -> 133   This is  clock_frequency / prescaler / desired_frequency  ( 2 KHz, 0.5ms)
//  OCR2A = 50;  // = (16000000) / 64 / 5000  ->  50   This is  clock_frequency / prescaler / desired_frequency  ( 5 KHz, 0.2ms)
//  OCR2A = 25;  // = (16000000) / 64 / 10000 ->  25   This is  clock_frequency / prescaler / desired_frequency  (10 kHz, 0.1ms)
  OCR2A = INTERRUPT_PERIOD;
  
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);
  
  // turn on mode 2 (CTC mode) (up to OCR2A)
  TCCR2A |= (1 << WGM21);
  
  // Set CS22 bit for 64 prescaler
  TCCR2B |= (1 << CS22);
}

SIGNAL(TIMER2_COMPA_vect)
{
  computeEncoder();
}

#else
#error "Unsupported or unknown board"
#endif
#endif

void Encoder::compute()
{
	byte eA = !input_device_->read(_pinA);
	byte eB = !input_device_->read(_pinB);


	byte st = ((byte)eB << 1) | (byte)eA;

	if (stDebouncer.isDebounced(st, DEBOUNCE_COUNT))
	{
		byte encoderSt = _encoderStVL;
		if (encoderSt != st)
		{
			bool wentDown = ((encoderSt == 0 && st == 2) || (encoderSt == 2 && st == 3) || (encoderSt == 3 && st == 1)
				|| (encoderSt == 1 && st == 0));

			if (wentDown) _encoderValueVL--;
			else _encoderValueVL++;

			/* if ( st == 0 || st == 3 )
			{
			  if ( wentDown ) _encoderTickVL--;
			  else _encoderTickVL++;
			}*/
			_encoderTickVL = _encoderValueVL / 2;

			/*if ( st == 0 )
			{
			  if ( wentDown ) _encoderTick2VL--;
			  else _encoderTick2VL++;
			}*/
			_encoderTick2VL = _encoderTickVL / 2;

			_encoderStVL = st;
		}
	}
}

void Encoder::setup_impl()
{
	byte eA = !input_device_->read(_pinA);
	byte eB = !input_device_->read(_pinB);
	_encoderStVL = eB << 1 | eA;
}

void Encoder::process()
{
	compute(); //WILL LIKELY NOT BE ENOUGH!
	//DBG_PRINTLN("ENC  process()");

	//this also debounces, at least for my encoders, which give 4 signal increments per 1 physical tick of the knob
	working_delta += delta();
	if (abs(working_delta) >= trigger_delta)
	{
		if (working_delta != 0)
		{
			if (working_delta > 0)
			{
				// Turned clockwise
				output_device_->pulse(incr_out_id_, 33);
				//last_execution_status.new_task = new PulseOutputTask(output_device_, incr_out_id_, 50);
				//last_execution_status.new_task_immediate = true;
			}
			else
			{
				// Turned counter-clockwise
				output_device_->pulse(decr_out_id_, 33);
				//last_execution_status.new_task = new PulseOutputTask(output_device_, decr_out_id_, 50);
				//last_execution_status.new_task_immediate = true;
			}
		}
		last_encoder_value += working_delta;
		working_delta = 0;
	}
}



Encoder::Encoder(InputDevice* channel, int pin_a, int pin_b, OutputDevice* output_channel,
                 int decr_out_id, int incr_out_id, int sampling_interval):
	Control(channel, output_channel, sampling_interval), _pinA(pin_a), _pinB(pin_b),
	decr_out_id_(decr_out_id),
	incr_out_id_(incr_out_id)
{
}

int Encoder::delta()
{
	unsigned int v = _encoderValueVL; // put in a local var to avoid multiple reads of a volatile var
	int d = v - _encoderValue;
	_encoderValue = v;
	return d;
}

int Encoder::deltaTick()
{
	unsigned int v = _encoderTickVL; // put in a local var to avoid multiple reads of a volatile var
	int d = v - _encoderTick;
	_encoderTick = v;
	return d;
}

int Encoder::deltaTick2()
{
	unsigned int v = _encoderTick2VL; // put in a local var to avoid multiple reads of a volatile var
	int d = v - _encoderTick2;
	_encoderTick2 = v;
	return d;
}


void EncoderInterruptClass::begin(Encoder** encoderRefs, int numEncoders)
{
	_encoderArray = encoderRefs;
	_numEncoders = numEncoders;

	//setupTimerInterrupt();
}

void EncoderInterruptClass::computeAll()
{
	for (int i = 0; i < _numEncoders; i++)
	{
		_encoderArray[i]->compute();
	}
}
