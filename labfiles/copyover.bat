:: start cmd /k "cd \dgnava2_maneyko2\SE423Repo\Labs\lab8_dgnava2_maneyko2\lab8_dgnava2_maneyko2Project\Debug"
@ECHO OFF

SET fname="\kt2_smm2_dg2_ma2\SE423Repo\Labs\productive_walruses\productive_walrusesProject\Debug\productive_walruses.hex"

pscp -pw '' %fname% root@192.168.1.76:
PAUSE