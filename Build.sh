#!/bin/bash

CC=g++
LDFLAGS=' -lGL -lGLU -lglut -lglfw -lGLEW'

rm Game
$CC Game.cpp $LDFLAGS -o Game -g
./Game