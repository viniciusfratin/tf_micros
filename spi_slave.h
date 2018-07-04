#ifndef _SPISLAVE_H_
#define _SPISLAVE_H_

// Use IO13 as SCLK
class SclkSlave
{
	int fd;

	public:

	SclkSlave(void);
	~SclkSlave(void);
	void waitRise(void);
};

// Use IO11 as MOSI
class MosiSlave
{
	int fd;

	public:

	MosiSlave(void);
	~MosiSlave(void);
	int sample(void);

};

// Use IO12 as MISO
class MisoSlave
{
	int fd;

	public:

	MisoSlave(void);
	~MisoSlave(void);
	int sample(void);

};

// Use IO10 as #SS
class SsSlave
{
	int fd;

	public:

	SsSlave(void);
	~SsSlave(void);
	int selected(void);
};

#endif
