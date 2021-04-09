#!/usr/bin/env bash





# Some information about the shell:

# > $SHELL

# /bin/sh

# > $SHELL --version

# bash 4.2.10





(  # Run in subshell



set -x



/home/root/DSP_Reset



# Dan said you need to wait a couple seconds

sleep 2s



/home/root/DSP_Load productive_walruses.hex



)



test $? -eq 0 && echo 'All good!'