#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/CCStudio_v8/bios_6_76_01_12/packages;C:/CCStudio_v8/ccsv8/ccs_base;C:/mspyte3_tdl2/mspyte3_tdl2/labs/Lab1_part2/Lab1_part2Project/.config
override XDCROOT = C:/CCStudio_v8/xdctools_3_50_05_12_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/CCStudio_v8/bios_6_76_01_12/packages;C:/CCStudio_v8/ccsv8/ccs_base;C:/mspyte3_tdl2/mspyte3_tdl2/labs/Lab1_part2/Lab1_part2Project/.config;C:/CCStudio_v8/xdctools_3_50_05_12_core/packages;..
HOSTOS = Windows
endif
