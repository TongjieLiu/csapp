# A modified Makefile for data lab in CS:APP3e
#
# Copyright (C) 2022 Tongjie Liu <tongjieandliu@gmail.com>.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

#	In this file, the author of the solution modified the optimization
# level given by the author of CS:APP to "no optimization".
# 	The reason behind this choice is very simple, the optimization will
# modify behavior of the solution for function logicalNeg.
# 	More specifically, it will optimize the expression:
# 	Tmin_plus_x_sign = (Tmin_plus_x >> 31) & 1;
# After this optimization, Tmin_plus_x_sign = 1 even when Tmin_plus_x >> 31
# = 0.
 
CC = gcc
CFLAGS = -Wall -m32 # ***Modified***: deleted -O option
LIBS = -lm

all: btest fshow ishow

btest: btest.c bits.c decl.c tests.c btest.h bits.h
	$(CC) $(CFLAGS) $(LIBS) -o btest bits.c btest.c decl.c tests.c

fshow: fshow.c
	$(CC) $(CFLAGS) -o fshow fshow.c

ishow: ishow.c
	$(CC) $(CFLAGS) -o ishow ishow.c

# Forces a recompile. Used by the driver program. 
btestexplicit:
	$(CC) $(CFLAGS) $(LIBS) -o btest bits.c btest.c decl.c tests.c 

clean:
	rm -f *.o btest fshow ishow *~


