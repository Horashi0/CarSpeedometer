DEV = ttyUSB0

ifeq (yes,$(VERBOSE))
	ARGS += --verbose
endif

.PHONY: help

help:
	@echo "Usage: make [target] [VERBOSE=yes] [command]"
	@echo ""
	@echo "Targets:"
	@echo "  DEV=target  "
	@echo ""
	@echo "Commands:"
	@echo "  monitor  : View output of target"
	@echo "  upload   : Upload to target"


monitor:
	pio device monitor -p /dev/$(DEV)

upload-commands:
	pio run --target clean
	pio run --target upload --upload-port /dev/$(DEV) $(ARGS)

upload: upload-commands monitor .NOTPARALLEL
