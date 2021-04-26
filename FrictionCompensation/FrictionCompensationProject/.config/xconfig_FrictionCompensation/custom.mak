## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,28FP linker.cmd package/cfg/Lab3_Part1_p28FP.o28FP

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/Lab3_Part1_p28FP.xdl
	$(SED) 's"^\"\(package/cfg/Lab3_Part1_p28FPcfg.cmd\)\"$""\"C:/mspyte3_tdl2/mspyte3_tdl2/labs/Lab3_Part1/Lab3_Part1Project/.config/xconfig_Lab3_Part1/\1\""' package/cfg/Lab3_Part1_p28FP.xdl > $@
	-$(SETDATE) -r:max package/cfg/Lab3_Part1_p28FP.h compiler.opt compiler.opt.defs
