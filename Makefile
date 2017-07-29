CC=gcc

default: rpibrightness

rpibrightness: rpi-brightness-ctrl.c config.h
	${CC} -Wall -o rpi-brightness-ctrl rpi-brightness-ctrl.c

config.h:
	cp config.def.h $@

clean:
	rm rpi-brightness-ctrl
