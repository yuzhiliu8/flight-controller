USB_PORT ?= USB1

.PHONY: debug flash flash-usb clean

debug:
	cmake --build --preset Debug

flash:
	STM32_Programmer_CLI -c port=SWD -w build/Debug/flight_controller.elf -rst

# Enter DFU with BOOT0 + RESET before running; reset with BOOT0 low afterward.
flash-usb: debug
	STM32_Programmer_CLI -c port=$(USB_PORT) -w build/Debug/flight_controller.elf -v

clean:
	rm -rf build
