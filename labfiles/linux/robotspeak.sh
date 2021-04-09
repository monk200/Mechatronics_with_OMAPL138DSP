#!/bin/sh

espeak -s 120 --stdout "$@" | aplay -D plughw:1,0

