/**********************************************************
 * I2C driver for ds1803 digital pot
 *********************************************************/

#define DS1803_SLAVE_MASK 0x50 // must be ORed with slave device number
#define COMMAND_REGISTER_BASE 0xA9 // must be added to pot number
#define NUM_POTS 2     // the maximum outputs 

#define COMMAND_BYTE 0xAF // both pots

int val = 0;

#inline
short WriteAnalogueOutput (int port_num, byte outval)
{
	short ret;
	byte slave_num, op_num, device_address;

	i2c_start();

	slave_num = port_num / NUM_POTS;
	device_address = DS1803_SLAVE_MASK | (slave_num << 1);

#ifndef _SIMULATE
	i2c_write (device_address);
#endif

	op_num = (port_num % NUM_POTS) + COMMAND_REGISTER_BASE;

#ifndef _SIMULATE
	i2c_write (op_num);
	i2c_write (outval);

	i2c_stop();
#endif
}

