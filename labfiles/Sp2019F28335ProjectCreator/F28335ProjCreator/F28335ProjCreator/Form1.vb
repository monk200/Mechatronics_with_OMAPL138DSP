Public Class Form1
    Dim DirSelected As Integer

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        FolderBrowserDialog1.ShowDialog()
        Label3.Text = FolderBrowserDialog1.SelectedPath & "\" & TextBox2.Text
        Button2.Enabled = True
        DirSelected = 1
    End Sub

    Private Sub TextBox2_TextChanged(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TextBox2.TextChanged
        If DirSelected = 1 Then
            Label3.Text = FolderBrowserDialog1.SelectedPath & "\" & TextBox2.Text
        End If
    End Sub


    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Dim retvalue As Object

        Dim ProjectDirectory As String
        Dim ProjectName As String
        Dim Project_project_fileFullPath As Object
        Dim Project_cproject_fileFullPath As Object
        Dim Project_ccsproject_fileFullPath As Object
        'Dim Project_postbat_fileFullPath As Object
        Dim Project_projectinclude_fileFullPath As Object
        Dim Project_copybat_fileFullPath As Object

        Dim ProjectSubDirectory As String
        Dim ProjectSub_settings_Dir As String
        Dim ProjectSub_Debug_Dir As String
        Dim ProjectSub_targetConfigs_Dir As String
        Dim Project_SYSBIOS_Dir As String
        Dim Project_include_Dir As String
        Dim Project_source_Dir As String
        Dim Project_v110_Dir As String
        Dim Project_cmd_Dir As String
        Dim Project_DSP2833x_common_Dir As String
        Dim Project_DSP2833x_common_cmd_Dir As String
        Dim Project_DSP2833x_common_include_Dir As String
        Dim Project_DSP2833x_common_source_Dir As String
        Dim Project_DSP2833x_headers_Dir As String
        Dim Project_DSP2833x_headers_cmd_Dir As String
        Dim Project_DSP2833x_headers_include_Dir As String
        Dim Project_DSP2833x_headers_source_Dir As String


        Dim i As Integer
        Dim Drive As String
        Dim PathStr As String, NameStr As String

        On Error GoTo SaveError

        ProjectName = TextBox2.Text
        Drive = Mid(FolderBrowserDialog1.SelectedPath, 1, 2)
        PathStr = Mid(FolderBrowserDialog1.SelectedPath, 4)
        NameStr = ProjectName

        ' Check for bad characters in path
        For i = 0 To PathStr.Length - 1
            If Not ((Asc(PathStr(i)) > 47 And Asc(PathStr(i)) < 58) _
                    Or (Asc(PathStr(i)) > 64 And Asc(PathStr(i)) < 91) _
                    Or (Asc(PathStr(i)) > 96 And Asc(PathStr(i)) < 123) _
                    Or Asc(PathStr(i)) = 92 Or Asc(PathStr(i)) = 95) Then
                MsgBox("Path contains a non-alphanumeric character or a space." & _
                    Chr(13) & Chr(10) & "Please choose a different path.")

                Exit Sub
            End If
        Next i

        ' Check for bad characters in project name
        For i = 0 To NameStr.Length - 1
            If Not ((Asc(NameStr(i)) > 47 And Asc(NameStr(i)) < 58) _
                    Or (Asc(NameStr(i)) > 64 And Asc(NameStr(i)) < 91) _
                    Or (Asc(NameStr(i)) > 96 And Asc(NameStr(i)) < 123) _
                    Or Asc(NameStr(i)) = 92 Or Asc(NameStr(i)) = 95) Then
                MsgBox("Project name contains a non-alphanumeric character or a space." & _
                    Chr(13) & Chr(10) & "Please choose a different name.")

                Exit Sub
            End If
        Next i


        ProjectDirectory = FolderBrowserDialog1.SelectedPath & "\" & ProjectName & "\"
        ProjectSubDirectory = ProjectDirectory & ProjectName & "Project\"
        ProjectSub_settings_Dir = ProjectSubDirectory & ".settings\"
        ProjectSub_Debug_Dir = ProjectSubDirectory & "Debug\"
        ProjectSub_targetConfigs_Dir = ProjectSubDirectory & "targetConfigs\"


        Project_SYSBIOS_Dir = ProjectDirectory & "SYSBIOS\"
        Project_include_Dir = ProjectDirectory & "include\"
        Project_source_Dir = ProjectDirectory & "source\"
        Project_v110_Dir = ProjectDirectory & "v110\"
        Project_cmd_Dir = ProjectDirectory & "cmd\"
        Project_DSP2833x_common_Dir = Project_v110_Dir & "DSP2833x_common\"
        Project_DSP2833x_common_cmd_Dir = Project_DSP2833x_common_Dir & "cmd\"
        Project_DSP2833x_common_include_Dir = Project_DSP2833x_common_Dir & "include\"
        Project_DSP2833x_common_source_Dir = Project_DSP2833x_common_Dir & "source\"
        Project_DSP2833x_headers_Dir = Project_v110_Dir & "DSP2833x_headers\"
        Project_DSP2833x_headers_cmd_Dir = Project_DSP2833x_headers_Dir & "cmd\"
        Project_DSP2833x_headers_include_Dir = Project_DSP2833x_headers_Dir & "include\"
        Project_DSP2833x_headers_source_Dir = Project_DSP2833x_headers_Dir & "source\"





        Project_project_fileFullPath = ProjectSubDirectory & ".project"
        Project_cproject_fileFullPath = ProjectSubDirectory & ".cproject"
        Project_ccsproject_fileFullPath = ProjectSubDirectory & ".ccsproject"
        'Project_postbat_fileFullPath = ProjectDirectory & "postBuildStep_Debug.bat"
        Project_copybat_fileFullPath = ProjectDirectory & "tmpcopy.bat"
        Project_projectinclude_fileFullPath = Project_include_Dir & "user_include.h"

        MkDir(ProjectDirectory)
        MkDir(ProjectSubDirectory)
        MkDir(ProjectSub_settings_Dir)
        MkDir(ProjectSub_Debug_Dir)
        MkDir(ProjectSub_targetConfigs_Dir)
        MkDir(Project_SYSBIOS_Dir)
        MkDir(Project_include_Dir)
        MkDir(Project_source_Dir)
        MkDir(Project_cmd_Dir)
        MkDir(Project_v110_Dir)
        MkDir(Project_DSP2833x_common_Dir)
        MkDir(Project_DSP2833x_common_cmd_Dir)
        MkDir(Project_DSP2833x_common_include_Dir)
        MkDir(Project_DSP2833x_common_source_Dir)
        MkDir(Project_DSP2833x_headers_Dir)
        MkDir(Project_DSP2833x_headers_cmd_Dir)
        MkDir(Project_DSP2833x_headers_include_Dir)
        MkDir(Project_DSP2833x_headers_source_Dir)


        GoTo NoError
SaveError:
        'MsgBox "Error" & CStr(Err.Number)
        If Err.Number = 75 Then
            MsgBox("Directory already Exists!")
            GoTo NoWrite
        End If
NoError:


        FileOpen(1, Project_project_fileFullPath, OpenMode.Output)

        PrintLine(1, "<?xml version=""1.0"" encoding=""UTF-8""?>")
        PrintLine(1, "<projectDescription>")
        PrintLine(1, "	<name>" & ProjectName & "</name>")
        PrintLine(1, "	<comment></comment>")
        PrintLine(1, "	<projects>")
        PrintLine(1, "	</projects>")
        PrintLine(1, "	<buildSpec>")
        PrintLine(1, "		<buildCommand>")
        PrintLine(1, "			<name>org.eclipse.cdt.managedbuilder.core.genmakebuilder</name>")
        PrintLine(1, "			<arguments>")
        PrintLine(1, "			</arguments>")
        PrintLine(1, "		</buildCommand>")
        PrintLine(1, "		<buildCommand>")
        PrintLine(1, "			<name>org.eclipse.cdt.managedbuilder.core.ScannerConfigBuilder</name>")
        PrintLine(1, "			<triggers>full,incremental,</triggers>")
        PrintLine(1, "			<arguments>")
        PrintLine(1, "			</arguments>")
        PrintLine(1, "		</buildCommand>")
        PrintLine(1, "	</buildSpec>")
        PrintLine(1, "	<natures>")
        PrintLine(1, "		<nature>org.eclipse.rtsc.xdctools.buildDefinitions.XDC.xdcNature</nature>")
        PrintLine(1, "		<nature>com.ti.ccstudio.core.ccsNature</nature>")
        PrintLine(1, "		<nature>org.eclipse.cdt.core.cnature</nature>")
        PrintLine(1, "		<nature>org.eclipse.cdt.managedbuilder.core.managedBuildNature</nature>")
        PrintLine(1, "		<nature>org.eclipse.cdt.core.ccnature</nature>")
        PrintLine(1, "		<nature>org.eclipse.cdt.managedbuilder.core.ScannerConfigNature</nature>")
        PrintLine(1, "	</natures>")
        PrintLine(1, "	<linkedResources>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>28335_dma.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/28335_dma.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>28335_eqep.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/28335_eqep.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>28335_inits.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/28335_inits.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>28335_mcbsp.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/28335_mcbsp.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>28335_pwm.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/28335_pwm.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>28335_serial.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/28335_serial.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>28335_spi.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/28335_spi.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>DSP2833x_ADC_cal.asm</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/v110/DSP2833x_common/source/DSP2833x_ADC_cal.asm</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>DSP2833x_Adc.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/v110/DSP2833x_common/source/DSP2833x_Adc.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>DSP2833x_CSMPasswords.asm</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/v110/DSP2833x_common/source/DSP2833x_CSMPasswords.asm</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>DSP2833x_CodeStartBranch.asm</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/v110/DSP2833x_common/source/DSP2833x_CodeStartBranch.asm</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>DSP2833x_CpuTimers.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/v110/DSP2833x_common/source/DSP2833x_CpuTimers.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>DSP2833x_GlobalVariableDefs.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/v110/DSP2833x_headers/source/DSP2833x_GlobalVariableDefs.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>DSP2833x_Headers_BIOS.cmd</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/v110/DSP2833x_headers/cmd/DSP2833x_Headers_BIOS.cmd</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>DSP2833x_Mcbsp.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/v110/DSP2833x_common/source/DSP2833x_Mcbsp.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>DSP2833x_PieCtrl.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/v110/DSP2833x_common/source/DSP2833x_PieCtrl.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>DSP2833x_Spi.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/v110/DSP2833x_common/source/DSP2833x_Spi.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>DSP2833x_SysCtrl.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/v110/DSP2833x_common/source/DSP2833x_SysCtrl.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>DSP2833x_usDelay.asm</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/v110/DSP2833x_common/source/DSP2833x_usDelay.asm</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>i2c.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/i2c.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>lcd.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/lcd.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>" & ProjectName & ".cfg</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/sysbios/" & ProjectName & ".cfg</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>user_" & ProjectName & ".c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/user_" & ProjectName & ".c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>user_lnk.cmd</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/cmd/user_lnk.cmd</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "	</linkedResources>")
        PrintLine(1, "</projectDescription>")
        PrintLine(1, "")

        FileClose(1)


        FileOpen(1, Project_cproject_fileFullPath, OpenMode.Output)

        PrintLine(1, "<?xml version=""1.0"" encoding=""UTF-8"" standalone=""no""?>")
        PrintLine(1, "<?fileVersion 4.0.0?><cproject storage_type_id=""org.eclipse.cdt.core.XmlProjectDescriptionStorage"">")
        PrintLine(1, "	<storageModule configRelations=""2"" moduleId=""org.eclipse.cdt.core.settings"">")
        PrintLine(1, "		<cconfiguration id=""com.ti.ccstudio.buildDefinitions.C2000.Debug.1665383588"">")
        PrintLine(1, "			<storageModule buildSystemId=""org.eclipse.cdt.managedbuilder.core.configurationDataProvider"" id=""com.ti.ccstudio.buildDefinitions.C2000.Debug.1665383588"" moduleId=""org.eclipse.cdt.core.settings"" name=""Debug"">")
        PrintLine(1, "				<externalSettings/>")
        PrintLine(1, "				<extensions>")
        PrintLine(1, "					<extension id=""com.ti.ccstudio.binaryparser.CoffParser"" point=""org.eclipse.cdt.core.BinaryParser""/>")
        PrintLine(1, "					<extension id=""org.eclipse.cdt.core.GmakeErrorParser"" point=""org.eclipse.cdt.core.ErrorParser""/>")
        PrintLine(1, "					<extension id=""com.ti.ccstudio.errorparser.CoffErrorParser"" point=""org.eclipse.cdt.core.ErrorParser""/>")
        PrintLine(1, "					<extension id=""org.eclipse.rtsc.xdctools.parsers.ErrorParser"" point=""org.eclipse.cdt.core.ErrorParser""/>")
        PrintLine(1, "					<extension id=""com.ti.ccstudio.errorparser.AsmErrorParser"" point=""org.eclipse.cdt.core.ErrorParser""/>")
        PrintLine(1, "					<extension id=""com.ti.ccstudio.errorparser.LinkErrorParser"" point=""org.eclipse.cdt.core.ErrorParser""/>")
        PrintLine(1, "				</extensions>")
        PrintLine(1, "			</storageModule>")
        PrintLine(1, "			<storageModule moduleId=""cdtBuildSystem"" version=""4.0.0"">")
        PrintLine(1, "				<configuration artifactExtension=""out"" artifactName=""${ProjName}"" buildProperties="""" cleanCommand=""${CG_CLEAN_CMD}"" description="""" errorParsers=""org.eclipse.rtsc.xdctools.parsers.ErrorParser;org.eclipse.cdt.core.GmakeErrorParser;com.ti.ccstudio.errorparser.CoffErrorParser;com.ti.ccstudio.errorparser.AsmErrorParser;com.ti.ccstudio.errorparser.LinkErrorParser"" id=""com.ti.ccstudio.buildDefinitions.C2000.Debug.1665383588"" name=""Debug"" parent=""com.ti.ccstudio.buildDefinitions.C2000.Debug"">")
        PrintLine(1, "					<folderInfo id=""com.ti.ccstudio.buildDefinitions.C2000.Debug.1665383588."" name=""/"" resourcePath="""">")
        PrintLine(1, "						<toolChain id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.DebugToolchain.695002928"" name=""TI Build Tools"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.DebugToolchain"" targetTool=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.linkerDebug.678085839"">")
        PrintLine(1, "							<option id=""com.ti.ccstudio.buildDefinitions.core.OPT_TAGS.1783368195"" superClass=""com.ti.ccstudio.buildDefinitions.core.OPT_TAGS"" valueType=""stringList"">")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""DEVICE_CONFIGURATION_ID=TMS320C28XX.TMS320F28335""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""DEVICE_ENDIANNESS=little""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""OUTPUT_FORMAT=COFF""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""CCS_MBS_VERSION=6.1.3""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""LINKER_COMMAND_FILE=TMS320F28335.cmd""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""RUNTIME_SUPPORT_LIBRARY=libc.a""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""RTSC_MBS_VERSION=7.0.0""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""XDC_VERSION=3.50.2.20_core""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""EXPANDED_REPOS=""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""OUTPUT_TYPE=rtscApplication:executable""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""PRODUCTS=com.ti.rtsc.SYSBIOS:6.51.0.15;""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""PRODUCT_MACRO_IMPORTS={&quot;com.ti.rtsc.SYSBIOS&quot;:[&quot;${BIOS_INCLUDE_PATH}&quot;,&quot;${BIOS_LIBRARY_PATH}&quot;,&quot;${BIOS_LIBRARIES}&quot;,&quot;${BIOS_SYMBOLS}&quot;]}""/>")
        PrintLine(1, "							</option>")
        PrintLine(1, "							<option id=""com.ti.ccstudio.buildDefinitions.core.OPT_CODEGEN_VERSION.767181934"" name=""Compiler version"" superClass=""com.ti.ccstudio.buildDefinitions.core.OPT_CODEGEN_VERSION"" value=""17.6.0.STS"" valueType=""string""/>")
        PrintLine(1, "							<targetPlatform id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.targetPlatformDebug.550449163"" name=""Platform"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.targetPlatformDebug""/>")
        PrintLine(1, "							<builder buildPath=""${BuildDirectory}"" id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.builderDebug.1007255424"" keepEnvironmentInBuildfile=""false"" name=""GNU Make"" parallelBuildOn=""true"" parallelizationNumber=""optimal"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.builderDebug""/>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.compilerDebug.127634024"" name=""C2000 Compiler"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.compilerDebug"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.LARGE_MEMORY_MODEL.555042877"" name=""Option deprecated, set by default (--large_memory_model, -ml)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.LARGE_MEMORY_MODEL"" useByScannerDiscovery=""false"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.UNIFIED_MEMORY.1012327745"" name=""Unified memory (--unified_memory, -mt)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.UNIFIED_MEMORY"" useByScannerDiscovery=""false"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.SILICON_VERSION.1690075827"" name=""Processor version (--silicon_version, -v)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.SILICON_VERSION"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.SILICON_VERSION.28"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.FLOAT_SUPPORT.520570912"" name=""Specify floating point support (--float_support)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.FLOAT_SUPPORT"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.FLOAT_SUPPORT.fpu32"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DEBUGGING_MODEL.1425490909"" name=""Debugging model"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DEBUGGING_MODEL"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DEBUGGING_MODEL.SYMDEBUG__DWARF"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DIAG_WARNING.1573303871"" name=""Treat diagnostic &lt;id&gt; as warning (--diag_warning, -pdsw)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DIAG_WARNING"" useByScannerDiscovery=""false"" valueType=""stringList"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""225""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""255""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DISPLAY_ERROR_NUMBER.316913835"" name=""Emit diagnostic identifier numbers (--display_error_number, -pden)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DISPLAY_ERROR_NUMBER"" useByScannerDiscovery=""false"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DIAG_WRAP.675924748"" name=""Wrap diagnostic messages (--diag_wrap)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DIAG_WRAP"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DIAG_WRAP.off"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.INCLUDE_PATH.957906834"" name=""Add dir to #include search path (--include_path, -I)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.INCLUDE_PATH"" valueType=""includePath"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${BIOS_INCLUDE_PATH}&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;..\..\include&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;..\..\v110\DSP2833x_common\include&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;..\..\v110\DSP2833x_headers\include&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;..\..\..\..\LabFiles\mcbsp_com&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;configPkg\package\cfg&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${PROJECT_ROOT}&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${CG_TOOL_ROOT}/include&quot;""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DEFINE.1122673803"" name=""Pre-define NAME (--define, -D)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DEFINE"" valueType=""definedSymbols"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_SYMBOLS}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""LARGE_MODEL""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""_DEBUG""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""DSP28_BIOS""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""F28335_CONTROL_CARD""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""F28335_CONTROL_CARD30""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.GEN_FUNC_SUBSECTIONS.89883060"" name=""Place each function in a separate subsection (--gen_func_subsections, -mo)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.GEN_FUNC_SUBSECTIONS"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.GEN_FUNC_SUBSECTIONS.on"" valueType=""enumerated""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__C_SRCS.164431757"" name=""C Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__C_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__CPP_SRCS.1360841307"" name=""C++ Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__CPP_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__ASM_SRCS.1795525003"" name=""Assembly Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__ASM_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__ASM2_SRCS.1685843556"" name=""Assembly Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__ASM2_SRCS""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.linkerDebug.678085839"" name=""C2000 Linker"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.linkerDebug"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.STACK_SIZE.1636213648"" name=""Set C system stack size (--stack_size, -stack)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.STACK_SIZE"" useByScannerDiscovery=""false"" value=""0x300"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.OUTPUT_FILE.1853192315"" name=""Specify output file name (--output_file, -o)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.OUTPUT_FILE"" useByScannerDiscovery=""false"" value=""&quot;${ProjName}.out&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.MAP_FILE.2070274873"" name=""Link information (map) listed into &lt;file&gt; (--map_file, -m)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.MAP_FILE"" useByScannerDiscovery=""false"" value=""&quot;${ProjName}.map&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.XML_LINK_INFO.828363633"" name=""Detailed link information data-base into &lt;file&gt; (--xml_link_info, -xml_link_info)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.XML_LINK_INFO"" useByScannerDiscovery=""false"" value=""&quot;${ProjName}_linkInfo.xml&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.DISPLAY_ERROR_NUMBER.993278205"" name=""Emit diagnostic identifier numbers (--display_error_number)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.DISPLAY_ERROR_NUMBER"" useByScannerDiscovery=""false"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.DIAG_WRAP.1245390109"" name=""Wrap diagnostic messages (--diag_wrap)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.DIAG_WRAP"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.DIAG_WRAP.off"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.SEARCH_PATH.679120593"" name=""Add &lt;dir&gt; to library search path (--search_path, -i)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.SEARCH_PATH"" valueType=""libPaths"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${BIOS_LIBRARY_PATH}&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${CG_TOOL_ROOT}/lib&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${CG_TOOL_ROOT}/include&quot;""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.LIBRARY.1668412696"" name=""Include library file or command file as input (--library, -l)"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.LIBRARY"" useByScannerDiscovery=""false"" valueType=""libs"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_LIBRARIES}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""libc.a""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exeLinker.inputType__CMD_SRCS.832945723"" name=""Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exeLinker.inputType__CMD_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exeLinker.inputType__CMD2_SRCS.1947037808"" name=""Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exeLinker.inputType__CMD2_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exeLinker.inputType__GEN_CMDS.1318856158"" name=""Generated Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exeLinker.inputType__GEN_CMDS""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.hex.1693127147"" name=""C2000 Hex Utility"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.hex""/>")
        PrintLine(1, "							<tool id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.476417110"" name=""XDCtools"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool"">")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.CODEGEN_TOOL_DIR.363680589"" name=""Compiler tools directory (-c)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.CODEGEN_TOOL_DIR"" value=""&quot;${CG_TOOL_ROOT}&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.TARGET.2014523602"" name=""Target (-t)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.TARGET"" value=""ti.targets.C28_float"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM.402099886"" name=""Platform (-p)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM"" value=""ti.platforms.tms320x28:TMS320F28335"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM_RAW.572704861"" name=""Platform (-p)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM_RAW"" value=""ti.platforms.tms320x28:$DeviceId$"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.BUILD_PROFILE.300495788"" name=""Build-profile (-r)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.BUILD_PROFILE"" value=""release"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.XDC_PATH.39348477"" name=""Package repositories (--xdcpath)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.XDC_PATH"" valueType=""stringList"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_CG_ROOT}/packages""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TARGET_CONTENT_BASE}""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.COMPILE_OPTIONS.704208231"" name=""Additional compiler options (--compileOptions)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.COMPILE_OPTIONS"" useByScannerDiscovery=""false"" value=""&quot;-g --optimize_with_debug&quot;"" valueType=""string""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "						</toolChain>")
        PrintLine(1, "					</folderInfo>")
        PrintLine(1, "					<sourceEntries>")
        PrintLine(1, "						<entry flags=""VALUE_WORKSPACE_PATH|RESOLVED"" kind=""sourcePath"" name=""""/>")
        PrintLine(1, "					</sourceEntries>")
        PrintLine(1, "				</configuration>")
        PrintLine(1, "			</storageModule>")
        PrintLine(1, "			<storageModule moduleId=""org.eclipse.cdt.core.externalSettings""/>")
        PrintLine(1, "		</cconfiguration>")
        PrintLine(1, "		<cconfiguration id=""com.ti.ccstudio.buildDefinitions.C2000.Release.1150448699"">")
        PrintLine(1, "			<storageModule buildSystemId=""org.eclipse.cdt.managedbuilder.core.configurationDataProvider"" id=""com.ti.ccstudio.buildDefinitions.C2000.Release.1150448699"" moduleId=""org.eclipse.cdt.core.settings"" name=""Release"">")
        PrintLine(1, "				<externalSettings/>")
        PrintLine(1, "				<extensions>")
        PrintLine(1, "					<extension id=""com.ti.ccstudio.binaryparser.CoffParser"" point=""org.eclipse.cdt.core.BinaryParser""/>")
        PrintLine(1, "					<extension id=""org.eclipse.cdt.core.GmakeErrorParser"" point=""org.eclipse.cdt.core.ErrorParser""/>")
        PrintLine(1, "					<extension id=""com.ti.ccstudio.errorparser.CoffErrorParser"" point=""org.eclipse.cdt.core.ErrorParser""/>")
        PrintLine(1, "					<extension id=""org.eclipse.rtsc.xdctools.parsers.ErrorParser"" point=""org.eclipse.cdt.core.ErrorParser""/>")
        PrintLine(1, "					<extension id=""com.ti.ccstudio.errorparser.AsmErrorParser"" point=""org.eclipse.cdt.core.ErrorParser""/>")
        PrintLine(1, "					<extension id=""com.ti.ccstudio.errorparser.LinkErrorParser"" point=""org.eclipse.cdt.core.ErrorParser""/>")
        PrintLine(1, "				</extensions>")
        PrintLine(1, "			</storageModule>")
        PrintLine(1, "			<storageModule moduleId=""cdtBuildSystem"" version=""4.0.0"">")
        PrintLine(1, "				<configuration artifactExtension=""out"" artifactName=""${ProjName}"" buildProperties="""" cleanCommand=""${CG_CLEAN_CMD}"" description="""" errorParsers=""org.eclipse.rtsc.xdctools.parsers.ErrorParser;org.eclipse.cdt.core.GmakeErrorParser;com.ti.ccstudio.errorparser.CoffErrorParser;com.ti.ccstudio.errorparser.AsmErrorParser;com.ti.ccstudio.errorparser.LinkErrorParser"" id=""com.ti.ccstudio.buildDefinitions.C2000.Release.1150448699"" name=""Release"" parent=""com.ti.ccstudio.buildDefinitions.C2000.Release"">")
        PrintLine(1, "					<folderInfo id=""com.ti.ccstudio.buildDefinitions.C2000.Release.1150448699."" name=""/"" resourcePath="""">")
        PrintLine(1, "						<toolChain id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.ReleaseToolchain.1943380104"" name=""TI Build Tools"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.ReleaseToolchain"" targetTool=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.linkerRelease.107626739"">")
        PrintLine(1, "							<option id=""com.ti.ccstudio.buildDefinitions.core.OPT_TAGS.1682115487"" superClass=""com.ti.ccstudio.buildDefinitions.core.OPT_TAGS"" valueType=""stringList"">")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""DEVICE_CONFIGURATION_ID=TMS320C28XX.TMS320F28335""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""DEVICE_ENDIANNESS=little""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""OUTPUT_FORMAT=COFF""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""CCS_MBS_VERSION=6.1.3""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""LINKER_COMMAND_FILE=TMS320F28335.cmd""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""RUNTIME_SUPPORT_LIBRARY=libc.a""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""RTSC_MBS_VERSION=7.0.0""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""XDC_VERSION=3.50.2.20_core""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""EXPANDED_REPOS=""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""OUTPUT_TYPE=rtscApplication:executable""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""PRODUCTS=com.ti.rtsc.SYSBIOS:6.51.0.15;""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""PRODUCT_MACRO_IMPORTS={&quot;com.ti.rtsc.SYSBIOS&quot;:[&quot;${BIOS_INCLUDE_PATH}&quot;,&quot;${BIOS_LIBRARY_PATH}&quot;,&quot;${BIOS_LIBRARIES}&quot;,&quot;${BIOS_SYMBOLS}&quot;]}""/>")
        PrintLine(1, "							</option>")
        PrintLine(1, "							<option id=""com.ti.ccstudio.buildDefinitions.core.OPT_CODEGEN_VERSION.544322648"" superClass=""com.ti.ccstudio.buildDefinitions.core.OPT_CODEGEN_VERSION"" value=""17.6.0.STS"" valueType=""string""/>")
        PrintLine(1, "							<targetPlatform id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.targetPlatformRelease.577703670"" name=""Platform"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.targetPlatformRelease""/>")
        PrintLine(1, "							<builder buildPath=""${BuildDirectory}"" id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.builderRelease.92469453"" name=""GNU Make.Release"" parallelBuildOn=""true"" parallelizationNumber=""optimal"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.builderRelease""/>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.compilerRelease.1603434915"" name=""C2000 Compiler"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.compilerRelease"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.LARGE_MEMORY_MODEL.266156582"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.LARGE_MEMORY_MODEL"" useByScannerDiscovery=""false"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.UNIFIED_MEMORY.672724471"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.UNIFIED_MEMORY"" useByScannerDiscovery=""false"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.SILICON_VERSION.801406013"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.SILICON_VERSION"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.SILICON_VERSION.28"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.FLOAT_SUPPORT.63736916"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.FLOAT_SUPPORT"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.FLOAT_SUPPORT.fpu32"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DIAG_WARNING.39625678"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DIAG_WARNING"" useByScannerDiscovery=""false"" valueType=""stringList"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""225""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""255""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DISPLAY_ERROR_NUMBER.1937512107"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DISPLAY_ERROR_NUMBER"" useByScannerDiscovery=""false"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DIAG_WRAP.2104207415"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DIAG_WRAP"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DIAG_WRAP.off"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.INCLUDE_PATH.731925651"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.INCLUDE_PATH"" valueType=""includePath"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${BIOS_INCLUDE_PATH}&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${PROJECT_ROOT}&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${CG_TOOL_ROOT}/include&quot;""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DEFINE.1031227575"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.DEFINE"" valueType=""definedSymbols"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_SYMBOLS}""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.GEN_FUNC_SUBSECTIONS.17732161"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.GEN_FUNC_SUBSECTIONS"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compilerID.GEN_FUNC_SUBSECTIONS.on"" valueType=""enumerated""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__C_SRCS.1039718762"" name=""C Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__C_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__CPP_SRCS.1265391779"" name=""C++ Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__CPP_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__ASM_SRCS.1607087725"" name=""Assembly Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__ASM_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__ASM2_SRCS.723710580"" name=""Assembly Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.compiler.inputType__ASM2_SRCS""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.linkerRelease.107626739"" name=""C2000 Linker"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exe.linkerRelease"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.STACK_SIZE.1199208726"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.STACK_SIZE"" useByScannerDiscovery=""false"" value=""0x300"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.OUTPUT_FILE.64928122"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.OUTPUT_FILE"" useByScannerDiscovery=""false"" value=""&quot;${ProjName}.out&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.MAP_FILE.1078780074"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.MAP_FILE"" useByScannerDiscovery=""false"" value=""&quot;${ProjName}.map&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.XML_LINK_INFO.1494309552"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.XML_LINK_INFO"" useByScannerDiscovery=""false"" value=""&quot;${ProjName}_linkInfo.xml&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.DISPLAY_ERROR_NUMBER.1066883649"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.DISPLAY_ERROR_NUMBER"" useByScannerDiscovery=""false"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.DIAG_WRAP.798565403"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.DIAG_WRAP"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.DIAG_WRAP.off"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.SEARCH_PATH.163743866"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.SEARCH_PATH"" valueType=""libPaths"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${BIOS_LIBRARY_PATH}&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${CG_TOOL_ROOT}/lib&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${CG_TOOL_ROOT}/include&quot;""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.LIBRARY.2042334563"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.linkerID.LIBRARY"" useByScannerDiscovery=""false"" valueType=""libs"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_LIBRARIES}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""libc.a""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exeLinker.inputType__CMD_SRCS.8283163"" name=""Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exeLinker.inputType__CMD_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exeLinker.inputType__CMD2_SRCS.1709982477"" name=""Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exeLinker.inputType__CMD2_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exeLinker.inputType__GEN_CMDS.1808625849"" name=""Generated Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.exeLinker.inputType__GEN_CMDS""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C2000_17.6.hex.49467201"" name=""C2000 Hex Utility"" superClass=""com.ti.ccstudio.buildDefinitions.C2000_17.6.hex""/>")
        PrintLine(1, "							<tool id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.951942055"" name=""XDCtools"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool"">")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.CODEGEN_TOOL_DIR.1037366481"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.CODEGEN_TOOL_DIR"" value=""&quot;${CG_TOOL_ROOT}&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.TARGET.964676532"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.TARGET"" value=""ti.targets.C28_float"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM.1171551134"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM"" value=""ti.platforms.tms320x28:TMS320F28335"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM_RAW.1456542962"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM_RAW"" value=""ti.platforms.tms320x28:$DeviceId$"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.BUILD_PROFILE.85747407"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.BUILD_PROFILE"" value=""release"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.XDC_PATH.1389432405"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.XDC_PATH"" valueType=""stringList"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_CG_ROOT}/packages""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TARGET_CONTENT_BASE}""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.COMPILE_OPTIONS.1521262716"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.COMPILE_OPTIONS"" useByScannerDiscovery=""false"" value=""&quot;-g --optimize_with_debug&quot;"" valueType=""string""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "						</toolChain>")
        PrintLine(1, "					</folderInfo>")
        PrintLine(1, "					<sourceEntries>")
        PrintLine(1, "						<entry flags=""VALUE_WORKSPACE_PATH|RESOLVED"" kind=""sourcePath"" name=""""/>")
        PrintLine(1, "					</sourceEntries>")
        PrintLine(1, "				</configuration>")
        PrintLine(1, "			</storageModule>")
        PrintLine(1, "			<storageModule moduleId=""org.eclipse.cdt.core.externalSettings""/>")
        PrintLine(1, "		</cconfiguration>")
        PrintLine(1, "	</storageModule>")
        PrintLine(1, "	<storageModule moduleId=""org.eclipse.cdt.core.LanguageSettingsProviders""/>")
        PrintLine(1, "	<storageModule moduleId=""cdtBuildSystem"" version=""4.0.0"">")
        PrintLine(1, "		<project id=""sysbiosLab6F28335.com.ti.ccstudio.buildDefinitions.C2000.ProjectType.1956388702"" name=""C2000"" projectType=""com.ti.ccstudio.buildDefinitions.C2000.ProjectType""/>")
        PrintLine(1, "	</storageModule>")
        PrintLine(1, "	<storageModule moduleId=""scannerConfiguration""/>")
        PrintLine(1, "	<storageModule moduleId=""org.eclipse.cdt.core.language.mapping"">")
        PrintLine(1, "		<project-mappings>")
        PrintLine(1, "			<content-type-mapping configuration="""" content-type=""org.eclipse.cdt.core.asmSource"" language=""com.ti.ccstudio.core.TIASMLanguage""/>")
        PrintLine(1, "			<content-type-mapping configuration="""" content-type=""org.eclipse.cdt.core.cHeader"" language=""com.ti.ccstudio.core.TIGCCLanguage""/>")
        PrintLine(1, "			<content-type-mapping configuration="""" content-type=""org.eclipse.cdt.core.cSource"" language=""com.ti.ccstudio.core.TIGCCLanguage""/>")
        PrintLine(1, "			<content-type-mapping configuration="""" content-type=""org.eclipse.cdt.core.cxxHeader"" language=""com.ti.ccstudio.core.TIGPPLanguage""/>")
        PrintLine(1, "			<content-type-mapping configuration="""" content-type=""org.eclipse.cdt.core.cxxSource"" language=""com.ti.ccstudio.core.TIGPPLanguage""/>")
        PrintLine(1, "		</project-mappings>")
        PrintLine(1, "	</storageModule>")
        PrintLine(1, "</cproject>")
        PrintLine(1, "")

        FileClose(1)


        FileOpen(1, Project_ccsproject_fileFullPath, OpenMode.Output)

        PrintLine(1, "<?xml version=""1.0"" encoding=""UTF-8"" ?>")
        PrintLine(1, "<?ccsproject version=""1.0""?>")
        PrintLine(1, "<projectOptions>")
        PrintLine(1, "	<ccsVersion value=""7.2.0""/>")
        PrintLine(1, "	<deviceVariant value=""TMS320C28XX.TMS320F28335""/>")
        PrintLine(1, "	<deviceFamily value=""C2000""/>")
        PrintLine(1, "	<deviceEndianness value=""little""/>")
        PrintLine(1, "	<codegenToolVersion value=""17.6.0.STS""/>")
        PrintLine(1, "	<isElfFormat value=""false""/>")
        PrintLine(1, "	<connection value=""common/targetdb/connections/TIXDS2XXUSB_Connection.xml""/>")
        PrintLine(1, "	<linkerCommandFile value=""TMS320F28335.cmd""/>")
        PrintLine(1, "	<rts value=""libc.a""/>")
        PrintLine(1, "	<createSlaveProjects value=""""/>")
        PrintLine(1, "	<templateProperties value=""id=com.ti.rtsc.SYSBIOS.example_40,type=rtsc,products=com.ti.rtsc.SYSBIOS,target=ti.targets.C28_float,platform=ti.platforms.tms320x28:$DeviceId$,buildProfile=release,isHybrid=true,configuroOptions=--compileOptions &quot;-g --optimize_with_debug&quot;,""/>")
        PrintLine(1, "	<filesToOpen value=""""/>")
        PrintLine(1, "	<isTargetManual value=""false""/>")
        PrintLine(1, "</projectOptions>")
        PrintLine(1, "")

        FileClose(1)


        '        FileOpen(1, Project_postbat_fileFullPath, OpenMode.Output)
        '
        '        PrintLine(1, "@echo off")
        '        PrintLine(1, "pushd ..\..\")
        '        PrintLine(1, "setlocal")
        '        PrintLine(1, "")
        '        PrintLine(1, ":process_arg")
        '        PrintLine(1, "if ""%1""=="""" goto end_process_arg")
        '        PrintLine(1, "set name=%1")
        '        PrintLine(1, "set value=")
        '        PrintLine(1, "")
        '        PrintLine(1, ":process_arg_value")
        '        PrintLine(1, "if NOT ""%value%""=="""" set value=%value% %2")
        '        PrintLine(1, "if ""%value%""=="""" set value=%2")
        '        PrintLine(1, "shift")
        '        PrintLine(1, "if ""%2""==""!"" goto set_arg")
        '        PrintLine(1, "if ""%2""=="""" goto set_arg")
        '        PrintLine(1, "goto process_arg_value")
        '        PrintLine(1, "")
        '        PrintLine(1, ":set_arg")
        '        PrintLine(1, "set %name%=%value%")
        '        PrintLine(1, "shift")
        '        PrintLine(1, "shift")
        '        PrintLine(1, "goto process_arg")
        '        PrintLine(1, ":end_process_arg")
        '        PrintLine(1, "")
        '        PrintLine(1, "echo. > temp_postBuildStep_Debug.bat")
        '        PrintLine(1, "")
        '        PrintLine(1, "echo hex6x.exe %PROJECT_ROOT%\..\out2bootbin.cmd -o %PROJECT_ROOT%\..\" & ProjectName & ".bin %PROJECT_ROOT%\debug\" & ProjectName & ".out >> temp_postBuildStep_Debug.bat")
        '        PrintLine(1, "")
        '        PrintLine(1, "call temp_postBuildStep_Debug.bat")
        '        PrintLine(1, "del temp_postBuildStep_Debug.bat")
        '        PrintLine(1, "")
        '        PrintLine(1, "endlocal")
        '        PrintLine(1, "popd")
        '        PrintLine(1, " ")

        '        FileClose(1)


        FileOpen(1, Project_projectinclude_fileFullPath, OpenMode.Output)

        PrintLine(1, "#include """ & ProjectName & "_p28FP.h""")
        PrintLine(1, "")
        PrintLine(1, " ")

        FileClose(1)


        FileOpen(1, Project_copybat_fileFullPath, OpenMode.Output)


        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019F28335ProjectCreator\cmd\*.cmd " & Project_cmd_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019F28335ProjectCreator\SYSBIOS\PROJECTNAME.cfg " & Project_SYSBIOS_Dir & ProjectName & ".cfg")
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019F28335ProjectCreator\include\*.* " & Project_include_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019F28335ProjectCreator\source\*.* " & Project_source_Dir)
        PrintLine(1, "move " & Project_source_Dir & "user_PROJECTNAME.c " & Project_source_Dir & "user_" & ProjectName & ".c")
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019F28335ProjectCreator\project\*.* " & ProjectSubDirectory)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019F28335ProjectCreator\project\targetConfigs\*.* " & ProjectSub_targetConfigs_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019F28335ProjectCreator\project\.settings\*.* " & ProjectSub_settings_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019F28335ProjectCreator\v110\DSP2833x_common\cmd\*.* " & Project_DSP2833x_common_cmd_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019F28335ProjectCreator\v110\DSP2833x_common\include\*.* " & Project_DSP2833x_common_include_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019F28335ProjectCreator\v110\DSP2833x_common\source\*.* " & Project_DSP2833x_common_source_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019F28335ProjectCreator\v110\DSP2833x_headers\cmd\*.* " & Project_DSP2833x_headers_cmd_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019F28335ProjectCreator\v110\DSP2833x_headers\include\*.* " & Project_DSP2833x_headers_include_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019F28335ProjectCreator\v110\DSP2833x_headers\source\*.* " & Project_DSP2833x_headers_source_Dir)
        PrintLine(1, Drive)
        PrintLine(1, "cd """ & ProjectDirectory & """")
        PrintLine(1, "pause")
        PrintLine(1, "del """ & Project_copybat_fileFullPath & """")

        FileClose(1)


        Shell(Project_copybat_fileFullPath, 1)


        Me.Close()

NoWrite:

    End Sub

    Private Sub Form1_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load

    End Sub
End Class
