#
#  Do not edit this file.  This file is generated from 
#  package.bld.  Any modifications to this file will be 
#  overwritten whenever makefiles are re-generated.
#

unexport MAKEFILE_LIST
MK_NOGENDEPS := $(filter clean,$(MAKECMDGOALS))
override PKGDIR = xconfig_f28335McBSPasSPI
XDCINCS = -I. -I$(strip $(subst ;, -I,$(subst $(space),\$(space),$(XPKGPATH))))
XDCCFGDIR = package/cfg/

#
# The following dependencies ensure package.mak is rebuilt
# in the event that some included BOM script changes.
#
ifneq (clean,$(MAKECMDGOALS))
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/utils.js:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/utils.js
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/xdc.tci:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/xdc.tci
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/template.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/template.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/om2.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/om2.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/xmlgen.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/xmlgen.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/xmlgen2.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/xmlgen2.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/Warnings.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/Warnings.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/IPackage.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/IPackage.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/package.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/package.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/services/global/Clock.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/services/global/Clock.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/services/global/Trace.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/services/global/Trace.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/bld.js:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/bld.js
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/BuildEnvironment.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/BuildEnvironment.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/PackageContents.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/PackageContents.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/_gen.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/_gen.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Library.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Library.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Executable.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Executable.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Repository.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Repository.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Configuration.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Configuration.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Script.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Script.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Manifest.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Manifest.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Utils.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/Utils.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/ITarget.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/ITarget.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/ITarget2.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/ITarget2.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/ITarget3.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/ITarget3.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/ITargetFilter.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/ITargetFilter.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/package.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/bld/package.xs
package.mak: config.bld
C:/CCStudio_v8/bios_6_70_01_03/packages/ti/targets/ITarget.xs:
package.mak: C:/CCStudio_v8/bios_6_70_01_03/packages/ti/targets/ITarget.xs
C:/CCStudio_v8/bios_6_70_01_03/packages/ti/targets/C28_large.xs:
package.mak: C:/CCStudio_v8/bios_6_70_01_03/packages/ti/targets/C28_large.xs
C:/CCStudio_v8/bios_6_70_01_03/packages/ti/targets/C28_float.xs:
package.mak: C:/CCStudio_v8/bios_6_70_01_03/packages/ti/targets/C28_float.xs
C:/CCStudio_v8/bios_6_70_01_03/packages/ti/targets/package.xs:
package.mak: C:/CCStudio_v8/bios_6_70_01_03/packages/ti/targets/package.xs
package.mak: package.bld
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/tools/configuro/template/compiler.opt.xdt:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/tools/configuro/template/compiler.opt.xdt
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/services/io/File.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/services/io/File.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/services/io/package.xs:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/services/io/package.xs
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/tools/configuro/template/compiler.defs.xdt:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/tools/configuro/template/compiler.defs.xdt
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/tools/configuro/template/custom.mak.exe.xdt:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/tools/configuro/template/custom.mak.exe.xdt
C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/tools/configuro/template/package.xs.xdt:
package.mak: C:/CCStudio_v8/xdctools_3_50_05_12_core/packages/xdc/tools/configuro/template/package.xs.xdt
endif

ti.targets.C28_float.rootDir ?= C:/CCStudio_v8/ccsv8/tools/compiler/ti-cgt-c2000_17.6.0.STS
ti.targets.packageBase ?= C:/CCStudio_v8/bios_6_70_01_03/packages/ti/targets/
.PRECIOUS: $(XDCCFGDIR)/%.o28FP
.PHONY: all,28FP .dlls,28FP .executables,28FP test,28FP
all,28FP: .executables,28FP
.executables,28FP: .libraries,28FP
.executables,28FP: .dlls,28FP
.dlls,28FP: .libraries,28FP
.libraries,28FP: .interfaces
	@$(RM) $@
	@$(TOUCH) "$@"

.help::
	@$(ECHO) xdc test,28FP
	@$(ECHO) xdc .executables,28FP
	@$(ECHO) xdc .libraries,28FP
	@$(ECHO) xdc .dlls,28FP


all: .executables 
.executables: .libraries .dlls
.libraries: .interfaces

PKGCFGS := $(wildcard package.xs) package/build.cfg
.interfaces: package/package.xdc.inc package/package.defs.h package.xdc $(PKGCFGS)

-include package/package.xdc.dep
package/%.xdc.inc package/%_xconfig_f28335McBSPasSPI.c package/%.defs.h: %.xdc $(PKGCFGS)
	@$(MSG) generating interfaces for package xconfig_f28335McBSPasSPI" (because $@ is older than $(firstword $?))" ...
	$(XSRUN) -f xdc/services/intern/cmd/build.xs $(MK_IDLOPTS) -m package/package.xdc.dep -i package/package.xdc.inc package.xdc

.dlls,28FP .dlls: f28335McBSPasSPI.p28FP

-include package/cfg/f28335McBSPasSPI_p28FP.mak
-include package/cfg/f28335McBSPasSPI_p28FP.cfg.mak
ifeq (,$(MK_NOGENDEPS))
-include package/cfg/f28335McBSPasSPI_p28FP.dep
endif
f28335McBSPasSPI.p28FP: package/cfg/f28335McBSPasSPI_p28FP.xdl
	@


ifeq (,$(wildcard .libraries,28FP))
f28335McBSPasSPI.p28FP package/cfg/f28335McBSPasSPI_p28FP.c: .libraries,28FP
endif

package/cfg/f28335McBSPasSPI_p28FP.c package/cfg/f28335McBSPasSPI_p28FP.h package/cfg/f28335McBSPasSPI_p28FP.xdl: override _PROG_NAME := f28335McBSPasSPI.x28FP
package/cfg/f28335McBSPasSPI_p28FP.c: package/cfg/f28335McBSPasSPI_p28FP.cfg
package/cfg/f28335McBSPasSPI_p28FP.xdc.inc: package/cfg/f28335McBSPasSPI_p28FP.xdl
package/cfg/f28335McBSPasSPI_p28FP.xdl package/cfg/f28335McBSPasSPI_p28FP.c: .interfaces

clean:: clean,28FP
	-$(RM) package/cfg/f28335McBSPasSPI_p28FP.cfg
	-$(RM) package/cfg/f28335McBSPasSPI_p28FP.dep
	-$(RM) package/cfg/f28335McBSPasSPI_p28FP.c
	-$(RM) package/cfg/f28335McBSPasSPI_p28FP.xdc.inc

clean,28FP::
	-$(RM) f28335McBSPasSPI.p28FP
.executables,28FP .executables: f28335McBSPasSPI.x28FP

f28335McBSPasSPI.x28FP: |f28335McBSPasSPI.p28FP

-include package/cfg/f28335McBSPasSPI.x28FP.mak
f28335McBSPasSPI.x28FP: package/cfg/f28335McBSPasSPI_p28FP.o28FP 
	$(RM) $@
	@$(MSG) lnk28FP $@ ...
	$(RM) $(XDCCFGDIR)/$@.map
	$(ti.targets.C28_float.rootDir)/bin/cl2000 -q -u _c_int00 -z  -o $@ package/cfg/f28335McBSPasSPI_p28FP.o28FP   package/cfg/f28335McBSPasSPI_p28FP.xdl  -w -c -m $(XDCCFGDIR)/$@.map -l $(ti.targets.C28_float.rootDir)/lib/libc.a
	
f28335McBSPasSPI.x28FP: export C_DIR=
f28335McBSPasSPI.x28FP: PATH:=$(ti.targets.C28_float.rootDir)/bin/;$(PATH)
f28335McBSPasSPI.x28FP: Path:=$(ti.targets.C28_float.rootDir)/bin/;$(PATH)

f28335McBSPasSPI.test test,28FP test: f28335McBSPasSPI.x28FP.test

f28335McBSPasSPI.x28FP.test:: f28335McBSPasSPI.x28FP
ifeq (,$(_TESTLEVEL))
	@$(MAKE) -R -r --no-print-directory -f $(XDCROOT)/packages/xdc/bld/xdc.mak _TESTLEVEL=1 f28335McBSPasSPI.x28FP.test
else
	@$(MSG) running $<  ...
	$(call EXEC.f28335McBSPasSPI.x28FP, ) 
endif

clean,28FP::
	-$(RM) $(wildcard .tmp,f28335McBSPasSPI.x28FP,*)


clean:: clean,28FP

clean,28FP::
	-$(RM) f28335McBSPasSPI.x28FP
%,copy:
	@$(if $<,,$(MSG) don\'t know how to build $*; exit 1)
	@$(MSG) cp $< $@
	$(RM) $@
	$(CP) $< $@
f28335McBSPasSPI_p28FP.o28FP,copy : package/cfg/f28335McBSPasSPI_p28FP.o28FP
f28335McBSPasSPI_p28FP.s28FP,copy : package/cfg/f28335McBSPasSPI_p28FP.s28FP

$(XDCCFGDIR)%.c $(XDCCFGDIR)%.h $(XDCCFGDIR)%.xdl: $(XDCCFGDIR)%.cfg $(XDCROOT)/packages/xdc/cfg/Main.xs | .interfaces
	@$(MSG) "configuring $(_PROG_NAME) from $< ..."
	$(CONFIG) $(_PROG_XSOPTS) xdc.cfg $(_PROG_NAME) $(XDCCFGDIR)$*.cfg $(XDCCFGDIR)$*

.PHONY: release,xconfig_f28335McBSPasSPI
ifeq (,$(MK_NOGENDEPS))
-include package/rel/xconfig_f28335McBSPasSPI.tar.dep
endif
package/rel/xconfig_f28335McBSPasSPI/xconfig_f28335McBSPasSPI/package/package.rel.xml: package/package.bld.xml
package/rel/xconfig_f28335McBSPasSPI/xconfig_f28335McBSPasSPI/package/package.rel.xml: package/build.cfg
package/rel/xconfig_f28335McBSPasSPI/xconfig_f28335McBSPasSPI/package/package.rel.xml: package/package.xdc.inc
package/rel/xconfig_f28335McBSPasSPI/xconfig_f28335McBSPasSPI/package/package.rel.xml: .force
	@$(MSG) generating external release references $@ ...
	$(XS) $(JSENV) -f $(XDCROOT)/packages/xdc/bld/rel.js $(MK_RELOPTS) . $@

xconfig_f28335McBSPasSPI.tar: package/rel/xconfig_f28335McBSPasSPI.xdc.inc package/rel/xconfig_f28335McBSPasSPI/xconfig_f28335McBSPasSPI/package/package.rel.xml
	@$(MSG) making release file $@ "(because of $(firstword $?))" ...
	-$(RM) $@
	$(call MKRELTAR,package/rel/xconfig_f28335McBSPasSPI.xdc.inc,package/rel/xconfig_f28335McBSPasSPI.tar.dep)


release release,xconfig_f28335McBSPasSPI: all xconfig_f28335McBSPasSPI.tar
clean:: .clean
	-$(RM) xconfig_f28335McBSPasSPI.tar
	-$(RM) package/rel/xconfig_f28335McBSPasSPI.xdc.inc
	-$(RM) package/rel/xconfig_f28335McBSPasSPI.tar.dep

clean:: .clean
	-$(RM) .libraries $(wildcard .libraries,*)
clean:: 
	-$(RM) .dlls $(wildcard .dlls,*)
#
# The following clean rule removes user specified
# generated files or directories.
#

ifneq (clean,$(MAKECMDGOALS))
ifeq (,$(wildcard package))
    $(shell $(MKDIR) package)
endif
ifeq (,$(wildcard package/cfg))
    $(shell $(MKDIR) package/cfg)
endif
ifeq (,$(wildcard package/lib))
    $(shell $(MKDIR) package/lib)
endif
ifeq (,$(wildcard package/rel))
    $(shell $(MKDIR) package/rel)
endif
ifeq (,$(wildcard package/internal))
    $(shell $(MKDIR) package/internal)
endif
endif
clean::
	-$(RMDIR) package

include custom.mak
