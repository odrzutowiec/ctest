build_test:
	cc -Wall main.c engine/*.c -o bin/test
	@echo "-- RUNNING --"
