upload:
	#sudo usermod -a -G tty horashio
	sudo pio run --target clean 
	sudo pio run --target upload --verbose --upload-port /dev/ttyACM0
	sudo pio device -p /dev/ttyACM0

monitor:
	sudo pio device monitor -p /dev/ttyACM0

debug:
	sudo pio device monitor -p /dev/ttyACM1 
