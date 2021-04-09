#
_XDCBUILDCOUNT = 0
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/CCStudio_v8/bios_6_70_01_03/packages;C:/CCStudio_v8/ccsv8/ccs_base;C:/dan/omapl138/SE423_Sp20/LabRepo/labfiles/f28335McBSPasSPI/f28335McBSPasSPIProject/.config
override XDCROOT = C:/CCStudio_v8/xdctools_3_50_05_12_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/CCStudio_v8/bios_6_70_01_03/packages;C:/CCStudio_v8/ccsv8/ccs_base;C:/dan/omapl138/SE423_Sp20/LabRepo/labfiles/f28335McBSPasSPI/f28335McBSPasSPIProject/.config;C:/CCStudio_v8/xdctools_3_50_05_12_core/packages;..
HOSTOS = Windows
endif
