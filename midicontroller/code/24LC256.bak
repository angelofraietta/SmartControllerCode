/**********************************************************
 * I2C driver for 24LC256 32k EEPROM
 *********************************************************/

#define LC256_SLAVE_MASK 0xA0 // must be ORed with slave device number
 
#define LC256_MEM_SIZE 0x00008000
#define LC256_PAGE_SIZE 64
#define LC256_NUM_REPOLLS 1
#define LC256_POLL_TIME 1

typedef struct
{
	int lower_address;
	int upper_address :7;
	int restart:1;
	int device;
} str_LC256;

str_LC256 LC_256_device_info; // this is current device info

void ExtEEpromIncAddress()
{
      LC_256_device_info.lower_address++;
      
      // check for cycle
      if (!LC_256_device_info.lower_address)
        {
          LC_256_device_info.upper_address++;
          
          if (!LC_256_device_info.upper_address)
            {
              LC_256_device_info.device++;
            }
        }
}

void ExtEEpromScheduleRestart()
{
	LC_256_device_info.restart = true;
}

void ResyncEEprom()
{
	LC_256_device_info.restart = true;
	
#ifndef _SIMULATE
	
	i2c_read (0); // clock anything out in case we stopped during a read without sending a stop
	i2c_stop();
#endif
	
}

void ResetEEPROM()
{
	LC_256_device_info.lower_address = 0;
	LC_256_device_info.upper_address = 0;
	LC_256_device_info.restart = 1;
	LC_256_device_info.device = 0;
	
	ResyncEEprom();
	
} // ResetEEPROM

#inline
int GenerateSlaveNum (int device_num)
{
	// packs the Control Byte
	device_num <<= 1;
	return LC256_SLAVE_MASK | device_num;
}

short PollSlave(int device_address, short stop)
{
	short ret = false;
	
	i2c_start();
	ret = !i2c_write(device_address); 
	restart_wdt();
	if (!ret)
		{
			i2c_stop();
			delay_ms (LC256_POLL_TIME);
		}
	
	
	if (ret && stop)
		{
			i2c_stop();
		}
	
	return ret;
} // end PollSlave(int device_address, short stop)


short WriteEEpromAddress ()
{
	short ret = false;
	
#ifndef _SIMULATE
	ret = ! i2c_write (LC_256_device_info.upper_address);
	
#else
	ret = true;
#endif
	
	if (ret)
		{
#ifndef _SIMULATE
			ret = !i2c_write (LC_256_device_info.lower_address);
#endif
		}
	
	return ret;
	
} //WriteEEpromAddress

short InitialiseReadExtEEProm (int port_num)
{
	// we will convert Port Num to the Slave Address
	short ret;
	int device_address;
	
	i2c_start();
	
	device_address = GenerateSlaveNum (port_num) | 0x01; // the lsb is the read control bit 
	
#ifndef _SIMULATE
	ret = !i2c_write (device_address);
#else
  ret = true;
#endif
	
	return ret;
} // InitialiseReadExtEEProm


short InitialiseWriteExtEEPROM (int port_num)
{
	// we will convert Port Num to the Slave Address
	short ret;
	int device_address;
	
	device_address = GenerateSlaveNum (port_num); 
	
#ifndef _SIMULATE
	ret = PollSlave (device_address, false);
#else
  ret = true;
#endif
	
	return ret;
} // InitialiseWriteExtEEPROM


short SetEEpromMemoryAddress ()
{
  short ret;
	
	ret = InitialiseWriteExtEEPROM (LC_256_device_info.device);
	
	ret |= WriteEEpromAddress ();
	
	return ret;
} // SetEEpromMemoryAddress

#inline 
void FinishEEpromWrite()
{
	i2c_stop();
	LC_256_device_info.restart = true;
}

#inline
short CheckCurrentEEpromDevice()
{
	return true; // for some reason this is not working
	//return PollSlave (LC_256_device_info.device, true);
}

// write a byte of data to eeprom
short WriteEEProm (int tx_byte)
{
	short ret = true;
		
	// we will restart if LC256_eeprom_address is zero or a multiple of LC256_PAGE_SIZE
	// this is becase of physical page boundaries
	LC_256_device_info.restart |= !(LC_256_device_info.lower_address % LC256_PAGE_SIZE);
	
	if (LC_256_device_info.restart)
		{
			ResyncEEprom();
			ret = SetEEpromMemoryAddress();
		}
		
	if (ret)
		{
#ifndef _SIMULATE
			ret = !i2c_write (tx_byte);
#endif
			if (ret)
				{
					ExtEEpromIncAddress();

					// test if we are going over boundary
					if (!(LC_256_device_info.lower_address % LC256_PAGE_SIZE))
						{
#ifndef _SIMULATE
							i2c_stop();
							LC_256_device_info.restart = true;
#else
							tx_byte++; // set a break point in debugger
#endif
						}
				}
		}
	
	LC_256_device_info.restart = !ret;
	
	return ret;
} // WriteEEProm 


short ReadEEprom (int *ret_byte)
{
	short ret;

	// we will restart if LC_256_device_info.upper_address is zero 
	// this is becase of physical size of memory, not boundary
	LC_256_device_info.restart |= (!LC_256_device_info.upper_address && !LC_256_device_info.lower_address);
	
	if (LC_256_device_info.restart)
		{
			ResyncEEprom();
			
      ret = SetEEpromMemoryAddress();
			
			ret &= InitialiseReadExtEEProm (LC_256_device_info.device);
		}
	else
		{
			ret = true;
		}
	
	if (ret)
		{
			ExtEEpromIncAddress();

#ifndef _SIMULATE
			// if we are going over a boundary, we will have to send a stop
			if (LC_256_device_info.upper_address || LC_256_device_info.lower_address)
				{
					*ret_byte = i2c_read (1); // send ack
				}
			else
				{
					*ret_byte = i2c_read (0); // do not send ack
					LC_256_device_info.restart = true;
					i2c_stop();
				}
#endif
			
		}

	LC_256_device_info.restart = !ret;

	return ret;
}







