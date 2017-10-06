/**********************************************************
 * I2C driver for Max520 ADC
 *********************************************************/

#define MAX520_SLAVE_MASK 0x50 // must be ORed with slave device number
#define NUM_520_OP 4     // the maximum outputs of a Max 520


#inline
short WriteAnalogueOutput (int port_num, byte outval)
{
	short ret;
	byte slave_num, op_num, device_address;

	i2c_start();

	slave_num = port_num / NUM_520_OP;
  slave_num <<= 1;
	device_address = MAX520_SLAVE_MASK | slave_num;
#ifndef _SIMULATE
	i2c_write (device_address);
#endif

	op_num = port_num % NUM_520_OP;

#ifndef _SIMULATE
	i2c_write (op_num);
	i2c_write (outval);
	i2c_stop();
#else
  op_num = port_num % NUM_520_OP;
#endif
}
