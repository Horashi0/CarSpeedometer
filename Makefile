upload0:
	sudo pio run --target clean 
	sudo pio run --target upload --verbose --upload-port /dev/ttyUSB0
	sudo pio device monitor -p /dev/ttyUSB0

upload1:
	sudo pio run --target clean
	sudo pio run --target upload --verbose --upload-port /dev/ttyUSB1
	sudo pio device monitor -p /dev/ttyUSB1

monitor0:
	sudo pio device monitor -p /dev/ttyUSB0

monitor1:
	sudo pio device monitor -p /dev/ttyUSB1

debug:
	sudo pio device monitor -p /dev/ttyUSB0
