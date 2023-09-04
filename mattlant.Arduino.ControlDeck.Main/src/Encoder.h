/// A modified version of https://github.com/John-Lluch/Encoder
///	Thank you! I dont know what license this is under, so I will keep this for now until I find out.


#ifndef Encoder_H
#define Encoder_H


// This is the number of consecutive reads that must be the same before accepting a pin change
#define DEBOUNCE_COUNT 3

// This is   cpu_clock_frequency / prescaler / desired_interrupt_frequency
// for example, set to 133 for 0.5ms (2kHz)  on a 16MHz processor: (16000000L / 64 / 2000  -> 133
// for example, set to 50  for 0.2ms (5kHz)  on a 16MHz processor: (16000000L / 64 / 5000  -> 50
// for example, set to 25  for 0.1ms (10kHz) on a 16MHz processor: (16000000L / 64 / 10000 -> 25
#define INTERRUPT_PERIOD 133

#include "InputDebouncer.h"
#include "ButtonBase.h"

class Encoder : public ButtonBase
{
public:
	Encoder(InputChannel* channel, int pin_a, int pin_b, int pin_pb, OutputChannel* output_channel, int decr_out_id,
	        int incr_out_id, int btn_out_id);

	int delta();
	int deltaTick();
	int deltaTick2();
	bool button() const;

private:
	void compute();

public:
	void setup() override;
	void process() override;

protected:
	void state_changed(uint8_t current_state) override;

public:
	~Encoder() override = default;

private:
	volatile unsigned int _encoderValueVL = 0;
	volatile unsigned int _encoderTickVL = 0;
	volatile unsigned int _encoderTick2VL = 0;
	volatile bool _encoderButtonVL = false;
	volatile byte _encoderStVL;
	unsigned int _encoderValue = 0;
	unsigned int _encoderTick = 0;
	unsigned int _encoderTick2 = 0;
	byte _pinA, _pinB, _pinP;
	InputDebouncer stDebouncer, pDebouncer;
	int decr_out_id_;
	int incr_out_id_;
	int last_encoder_value = 0;
	int8_t working_delta = 0;
	byte trigger_delta = 4;

public:
	friend class EncoderInterruptClass;
};

class EncoderInterruptClass
{
public:
	EncoderInterruptClass() : _numEncoders(0)
	{
	}

public:
	void begin(Encoder** encoderRefs, int numEncoders);
	void begin(Encoder* encoder) { begin(&encoder, 1); }

private:
	int _numEncoders;
	Encoder** _encoderArray;
	void computeAll();

public:
	friend void computeEncoder();
};

extern EncoderInterruptClass EncoderInterrupt;

#endif
