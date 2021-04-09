## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,28FP linker.cmd package/cfg/f28335McBSPasSPI_p28FP.o28FP

# To simplify configuro usage in makefiles:
#     o create a generic linker command file name 
#     o set modification times of compiler.opt* files to be greater than
#       or equal to the generated config header
#
linker.cmd: package/cfg/f28335McBSPasSPI_p28FP.xdl
	$(SED) 's"^\"\(package/cfg/f28335McBSPasSPI_p28FPcfg.cmd\)\"$""\"C:/dan/omapl138/SE423_Sp20/LabRepo/labfiles/f28335McBSPasSPI/f28335McBSPasSPIProject/.config/xconfig_f28335McBSPasSPI/\1\""' package/cfg/f28335McBSPasSPI_p28FP.xdl > $@
	-$(SETDATE) -r:max package/cfg/f28335McBSPasSPI_p28FP.h compiler.opt compiler.opt.defs
