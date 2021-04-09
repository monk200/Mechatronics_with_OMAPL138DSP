#!/bin/sh

date "+%_H %M, %A %B %e, %Y" | espeak -s 120 --stdout | aplay -D plughw:1,0

