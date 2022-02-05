import serial
import time

ser = serial.Serial('/dev/ttyS0',9600,timeout=1)

# command to set module to flight/nav mode
# header = xB5 x62
# class = x06
# id = x24
# then x24 x00 # what is this? I took it out
# bitmask = x00 x01 #this means only touch nav mode
# or should the bitmask be x80 x00?
# x06 for airborne with < 1g
# x00 for the rest because they are masked
# last two bytes (added in later) are the CRC checksums
cmd_navmode = b'\xB5\x62\x06\x24\x00\x01\x06\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'

# receive message to confirm navmode
cmd_poll_config = b'\xB5\x62\x06\x01\x06\x24'

# calculate the cyclic redundancy check
def calc_crc(cmd):
    ck_a = 0
    ck_b = 0
    for i in cmd:
        #print(i,' ',end='')
        ck_a = ck_a + i
        ck_b = ck_b + ck_a
    return (ck_a & 0xff, ck_b & 0xff)


# add checksums to navmode command
ck_a, ck_b = calc_crc(cmd_navmode)
cmd_navmode = cmd_navmode + bytes([ck_a,ck_b])

# add checksums to poll command
ck_a, ck_b = calc_crc(cmd_poll_config)
cmd_poll_config = cmd_navmode + bytes([ck_a,ck_b])

print(cmd_navmode.hex() + '\n\n')

if True == ser.is_open:
    ser.write(cmd_navmode)
    ser.write(cmd_poll_config)
    
    times_to_poll = 5
    for _ in range(times_to_poll):
        nmea = ser.read_until()
        print("decoded NMEA:")
        try:
            print(nmea.decode())
        except Exception as e:
            print(e)
        print('\n')
        
    time.sleep(1)
    ser.close()
    
    print("done")