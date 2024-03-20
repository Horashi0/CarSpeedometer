upload:
	#sudo usermod -a -G tty horashio
	sudo pio run --target clean 
	sudo pio run --target upload --verbose --upload-port /dev/ttyUSB0
	sudo pio device monitor -p /dev/ttyUSB0

monitor:
	sudo pio device monitor -p /dev/ttyUSB0

debug:
	sudo pio device monitor -p /dev/ttyUSB0
