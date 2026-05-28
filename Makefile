debug:
	cmake --build --preset Debug

flash:
	STM32_Programmer_CLI -c port=SWD -w build/Debug/flight_controller.elf -rst


clean:
	rm -rf build
