build_test:
	cc -Wall -g -std=c99 main.c engine/*.c -o bin/test
	@echo "-- COMPILED --"
