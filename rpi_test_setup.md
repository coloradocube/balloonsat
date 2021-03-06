### Setup for testing UPS power and Qwiic sensors

1. Update RPi OS to latest.  
2. Install [Adafruit Blinka](https://github.com/adafruit/Adafruit_Blinka) ([API reference](https://circuitpython.readthedocs.io/projects/blinka/en/latest/index.html)):
   ```
   cd ~
   sudo pip3 install --upgrade adafruit-python-shell
   wget https://raw.githubusercontent.com/adafruit/Raspberry-Pi-Installer-Scripts/master/raspi-blinka.py
   sudo python3 raspi-blinka.py
   ```
3. Update libraries with:  
   ```
   pip3 install adafruit-circuitpython-lis3dh
   ```
4. Install X728 battery board (https://wiki.geekworm.com/X728):   
   ```
   cd ~
   git clone https://github.com/geekworm-com/x728
   cd x728
   chmod +x *.sh	
   sudo bash x728-v2.1.sh
   ```  
5. **Reboot** the RPi.  
6. Instal individual sensors and RockBLOCK:
   ```
   sudo pip3 install adafruit-circuitpython-ina219
   sudo pip3 install adafruit-circuitpython-tmp117
   sudo pip3 install adafruit-circuitpython-bme680
   sudo pip3 install adafruit-circuitpython-icm20x
   sudo pip3 install adafruit-circuitpython-rockblock
   ```
7. Clone repos to get prebuilt test scripts for sensors:
   ```
   cd ~
   git clone https://github.com/adafruit/Adafruit_CircuitPython_TMP117.git
   cd ~  
   git clone https://github.com/adafruit/Adafruit_CircuitPython_BME680.git
   cd ~
   git clone https://github.com/adafruit/Adafruit_CircuitPython_ICM20X.git
   cd ~
   git clone https://github.com/adafruit/Adafruit_CircuitPython_INA219.git
   cd ~
   git clone https://github.com/adafruit/Adafruit_CircuitPython_RockBlock.git
   ```
   
### Run test Scripts 

Path depends on where repos were cloned to.  
1. In `/home/pi/` directory: 
   1. Read battery voltage: `python x728bat.py`  
   2. Test AC power off/loss or power adapter failure: `python detectionx728pld.py`  
2. In `/Adafruit_CircuitPython_INA219/examples/` directory:
   1. Read current and voltage through ina219 sensor: `python ina219_simpletest.py`  
3. In `/Adafruit_CircuitPython_TMP117/examples/` directory:
   1. Read tmp117 sensor: `python tmp117_simpletest.py`  
4. In `/Adafruit_CircuitPython_BME680/examples/` directory:  
   1. Read bme680 sensor: `python bme680_simpletest.py`  
5. In `/Adafruit_CircuitPython_ICM20X/examples/` directory:
   1. `python icm20x_icm20948_simpletest.py`
6. In `/Adafruit_CircuitPython_RockBlock/examples/` directory:
   1. `python rockblock_simpletest.py`
