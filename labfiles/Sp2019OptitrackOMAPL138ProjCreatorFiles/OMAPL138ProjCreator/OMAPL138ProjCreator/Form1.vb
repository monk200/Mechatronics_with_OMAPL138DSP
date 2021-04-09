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

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        DirSelected = 0

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
        Dim Project_SYSBIOS_Dir As String
        Dim Project_include_Dir As String
        Dim Project_PRUcode_Dir As String
        Dim Project_source_Dir As String
        Dim ProjectSub_launches_Dir As String
        Dim ProjectSub_targetConfigs_Dir As String

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
        ProjectSub_launches_Dir = ProjectSubDirectory & ".launches\"
        ProjectSub_targetConfigs_Dir = ProjectSubDirectory & "targetConfigs\"

        Project_SYSBIOS_Dir = ProjectDirectory & "SYSBIOS\"
        Project_include_Dir = ProjectDirectory & "include\"
        Project_PRUcode_Dir = ProjectDirectory & "PRUcode\"
        Project_source_Dir = ProjectDirectory & "source\"


        Project_project_fileFullPath = ProjectSubDirectory & ".project"
        Project_cproject_fileFullPath = ProjectSubDirectory & ".cproject"
        Project_ccsproject_fileFullPath = ProjectSubDirectory & ".ccsproject"
        'Project_postbat_fileFullPath = ProjectDirectory & "postBuildStep_Debug.bat"
        Project_copybat_fileFullPath = ProjectDirectory & "tmpcopy.bat"
        Project_projectinclude_fileFullPath = Project_include_Dir & "projectinclude.h"

        MkDir(ProjectDirectory)
        MkDir(ProjectSubDirectory)
        MkDir(ProjectSub_settings_Dir)
        MkDir(ProjectSub_Debug_Dir)
        MkDir(ProjectSub_launches_Dir)
        MkDir(ProjectSub_targetConfigs_Dir)

        MkDir(Project_SYSBIOS_Dir)
        MkDir(Project_include_Dir)
        MkDir(Project_PRUcode_Dir)
        MkDir(Project_source_Dir)


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
        PrintLine(1, "			<name>COECSL_edma3.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/COECSL_edma3.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>COECSL_mcbsp.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/COECSL_mcbsp.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>ColorLCD.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/ColorLCD.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>ColorVision.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/ColorVision.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>LCDprintf.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/LCDprintf.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>Ladar.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/Ladar.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>MatrixMath.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/MatrixMath.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>evmomapl138_bsl.lib</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-3-PROJECT_LOC/LabFiles/bsl_forSYSBIOS/lib/evmomapl138_bsl.lib</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>pru.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/pru.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>" & ProjectName & ".cfg</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/SYSBIOS/" & ProjectName & ".cfg</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>user_" & ProjectName & ".c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/user_" & ProjectName & ".c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>user_xy.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-1-PROJECT_LOC/source/user_xy.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "	</linkedResources>")
        PrintLine(1, "</projectDescription>")

        FileClose(1)


        FileOpen(1, Project_cproject_fileFullPath, OpenMode.Output)

        PrintLine(1, "<?xml version=""1.0"" encoding=""UTF-8"" standalone=""no""?>")
        PrintLine(1, "<?fileVersion 4.0.0?><cproject storage_type_id=""org.eclipse.cdt.core.XmlProjectDescriptionStorage"">")
        PrintLine(1, "	<storageModule configRelations=""2"" moduleId=""org.eclipse.cdt.core.settings"">")
        PrintLine(1, "		<cconfiguration id=""com.ti.ccstudio.buildDefinitions.C6000.Debug.1628145552"">")
        PrintLine(1, "			<storageModule buildSystemId=""org.eclipse.cdt.managedbuilder.core.configurationDataProvider"" id=""com.ti.ccstudio.buildDefinitions.C6000.Debug.1628145552"" moduleId=""org.eclipse.cdt.core.settings"" name=""Debug"">")
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
        PrintLine(1, "				<configuration artifactExtension=""out"" artifactName=""${ProjName}"" buildProperties="""" cleanCommand=""${CG_CLEAN_CMD}"" description="""" errorParsers=""org.eclipse.rtsc.xdctools.parsers.ErrorParser;org.eclipse.cdt.core.GmakeErrorParser;com.ti.ccstudio.errorparser.CoffErrorParser;com.ti.ccstudio.errorparser.AsmErrorParser;com.ti.ccstudio.errorparser.LinkErrorParser"" id=""com.ti.ccstudio.buildDefinitions.C6000.Debug.1628145552"" name=""Debug"" parent=""com.ti.ccstudio.buildDefinitions.C6000.Debug"">")
        PrintLine(1, "					<folderInfo id=""com.ti.ccstudio.buildDefinitions.C6000.Debug.1628145552."" name=""/"" resourcePath="""">")
        PrintLine(1, "						<toolChain id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.DebugToolchain.2112409722"" name=""TI Build Tools"" secondaryOutputs=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex.outputType__BIN"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.DebugToolchain"" targetTool=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.linkerDebug.59178368"">")
        PrintLine(1, "							<option id=""com.ti.ccstudio.buildDefinitions.core.OPT_TAGS.888941479"" superClass=""com.ti.ccstudio.buildDefinitions.core.OPT_TAGS"" valueType=""stringList"">")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""DEVICE_CONFIGURATION_ID=TMS320C67XX.OMAPL138.EXPKITOMAPL138""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""DEVICE_ENDIANNESS=little""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""OUTPUT_FORMAT=ELF""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""RUNTIME_SUPPORT_LIBRARY=libc.a""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""XDC_VERSION=3.50.2.20_core""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""INACTIVE_REPOS=""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""EXPANDED_REPOS=""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""CCS_MBS_VERSION=6.1.3""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""PRODUCTS=com.ti.rtsc.SYSBIOS:6.75.0.15;""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""PRODUCT_MACRO_IMPORTS={&quot;com.ti.rtsc.SYSBIOS&quot;:[&quot;${BIOS_INCLUDE_PATH}&quot;,&quot;${BIOS_LIBRARY_PATH}&quot;,&quot;${BIOS_LIBRARIES}&quot;,&quot;${BIOS_SYMBOLS}&quot;]}""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""RTSC_MBS_VERSION=7.0.0""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""OUTPUT_TYPE=rtscApplication:executable""/>")
        PrintLine(1, "							</option>")
        PrintLine(1, "							<option id=""com.ti.ccstudio.buildDefinitions.core.OPT_CODEGEN_VERSION.2037510099"" name=""Compiler version"" superClass=""com.ti.ccstudio.buildDefinitions.core.OPT_CODEGEN_VERSION"" value=""8.3.3"" valueType=""string""/>")
        PrintLine(1, "							<targetPlatform id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.targetPlatformDebug.299114680"" name=""Platform"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.targetPlatformDebug""/>")
        PrintLine(1, "							<builder buildPath=""${BuildDirectory}"" id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.builderDebug.351005530"" keepEnvironmentInBuildfile=""false"" name=""GNU Make"" parallelBuildOn=""true"" parallelizationNumber=""optimal"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.builderDebug""/>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.compilerDebug.899629370"" name=""C6000 Compiler"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.compilerDebug"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DEFINE.778676738"" name=""Pre-define NAME (--define, -D)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DEFINE"" valueType=""definedSymbols"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_SYMBOLS}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""RUNNING_ON_OMAPL138""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""PHILIPSCOLORLCD""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""omapl138""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.SILICON_VERSION.1050068491"" name=""Target processor version (--silicon_version, -mv)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.SILICON_VERSION"" value=""6740"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_LEVEL.1743377546"" name=""Optimization level (--opt_level, -O)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_LEVEL"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_LEVEL.3"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.INCLUDE_PATH.1603574751"" name=""Add dir to #include search path (--include_path, -I)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.INCLUDE_PATH"" valueType=""includePath"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${BIOS_INCLUDE_PATH}&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;..\..\&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;configPkg\package\cfg\&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;..\..\..\..\LabFiles\sharedmem_com&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;..\..\..\..\LabFiles\mcbsp_com&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;..\..\include&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;..\..\..\..\LabFiles\bsl_forSYSBIOS\inc&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${PROJECT_ROOT}&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${CG_TOOL_ROOT}/include&quot;""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DEBUGGING_MODEL.635254896"" name=""Debugging model"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DEBUGGING_MODEL"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DEBUGGING_MODEL.SYMDEBUG__DWARF"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WARNING.2120941328"" name=""Treat diagnostic &lt;id&gt; as warning (--diag_warning, -pdsw)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WARNING"" valueType=""stringList"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""225""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WRAP.988656899"" name=""Wrap diagnostic messages (--diag_wrap)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WRAP"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WRAP.off"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DISPLAY_ERROR_NUMBER.1735487731"" name=""Emit diagnostic identifier numbers (--display_error_number, -pden)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DISPLAY_ERROR_NUMBER"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_FOR_SPEED.1374247010"" name=""Speed vs. size trade-offs (--opt_for_speed, -mf)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_FOR_SPEED"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_FOR_SPEED.5"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_FOR_SPACE.2006049231"" name=""Optimize for code size (--opt_for_space, -ms)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_FOR_SPACE"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_FOR_SPACE._none"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.AUTO_INLINE.1914631176"" name=""Specify threshold for automatic inlining (--auto_inline, -oi)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.AUTO_INLINE"" value=""0"" valueType=""string""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__C_SRCS.736672630"" name=""C Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__C_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__CPP_SRCS.349882432"" name=""C++ Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__CPP_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__ASM_SRCS.262628177"" name=""Assembly Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__ASM_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__ASM2_SRCS.1359537539"" name=""Assembly Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__ASM2_SRCS""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.linkerDebug.59178368"" name=""C6000 Linker"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.linkerDebug"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DEFINE.1176803204"" name=""Pre-define preprocessor macro _name_ to _value_ (--define)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DEFINE"" valueType=""definedSymbols"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""DSP_CORE=1""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.STACK_SIZE.1540495256"" name=""Set C system stack size (--stack_size, -stack)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.STACK_SIZE"" value=""0x2000"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.HEAP_SIZE.1634236296"" name=""Heap size for C/C++ dynamic memory allocation (--heap_size, -heap)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.HEAP_SIZE"" value=""0x200"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.MAP_FILE.850117420"" name=""Link information (map) listed into &lt;file&gt; (--map_file, -m)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.MAP_FILE"" value=""&quot;${ProjName}.map&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.OUTPUT_FILE.1549144340"" name=""Specify output file name (--output_file, -o)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.OUTPUT_FILE"" value=""&quot;${ProjName}.out&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.LIBRARY.1686097868"" name=""Include library file or command file as input (--library, -l)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.LIBRARY"" valueType=""libs"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_LIBRARIES}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""libc.a""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.SEARCH_PATH.760507266"" name=""Add &lt;dir&gt; to library search path (--search_path, -i)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.SEARCH_PATH"" valueType=""libPaths"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${BIOS_LIBRARY_PATH}&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${CG_TOOL_ROOT}/lib&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${CG_TOOL_ROOT}/include&quot;""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DIAG_WRAP.436179226"" name=""Wrap diagnostic messages (--diag_wrap)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DIAG_WRAP"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DIAG_WRAP.off"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DISPLAY_ERROR_NUMBER.279483505"" name=""Emit diagnostic identifier numbers (--display_error_number)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DISPLAY_ERROR_NUMBER"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.XML_LINK_INFO.641104244"" name=""Detailed link information data-base into &lt;file&gt; (--xml_link_info, -xml_link_info)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.XML_LINK_INFO"" value=""&quot;${ProjName}_linkInfo.xml&quot;"" valueType=""string""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__CMD_SRCS.748258994"" name=""Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__CMD_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__CMD2_SRCS.1556724701"" name=""Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__CMD2_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__GEN_CMDS.574437557"" name=""Generated Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__GEN_CMDS""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool commandLinePattern=""${command} ${flags} &quot;..\..\..\..\LabFiles\SYSBIOShex\out2bootbin.cmd&quot; ${output_flag} ${output} ${inputs}"" id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex.222047851"" name=""C6000 Hex Utility"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex.TOOL_ENABLE.2041527628"" name=""Enable tool"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex.TOOL_ENABLE"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex.OTHER_FLAGS.336639400"" name=""Other flags"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex.OTHER_FLAGS"" valueType=""stringList"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.643473640"" name=""XDCtools"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool"">")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.XDC_PATH.913002923"" name=""Package repositories (--xdcpath)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.XDC_PATH"" valueType=""stringList"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_CG_ROOT}/packages""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TARGET_CONTENT_BASE}""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.TARGET.1316709298"" name=""Target (-t)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.TARGET"" value=""ti.targets.elf.C674"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM.1158912604"" name=""Platform (-p)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM"" value=""ti.platforms.evmOMAPL138"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM_RAW.1643413747"" name=""Platform (-p)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM_RAW"" value=""ti.platforms.evmOMAPL138"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.BUILD_PROFILE.840221485"" name=""Build-profile (-r)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.BUILD_PROFILE"" value=""debug"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.CODEGEN_TOOL_DIR.1974474586"" name=""Compiler tools directory (-c)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.CODEGEN_TOOL_DIR"" value=""&quot;${CG_TOOL_ROOT}&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.COMPILE_OPTIONS.2055862223"" name=""Additional compiler options (--compileOptions)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.COMPILE_OPTIONS"" value=""&quot;-g&quot;"" valueType=""string""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "						</toolChain>")
        PrintLine(1, "					</folderInfo>")
        PrintLine(1, "					<sourceEntries>")
        PrintLine(1, "						<entry excluding=""OMAPL138.cmd|src"" flags=""VALUE_WORKSPACE_PATH|RESOLVED"" kind=""sourcePath"" name=""""/>")
        PrintLine(1, "					</sourceEntries>")
        PrintLine(1, "				</configuration>")
        PrintLine(1, "			</storageModule>")
        PrintLine(1, "			<storageModule moduleId=""org.eclipse.cdt.core.externalSettings""/>")
        PrintLine(1, "		</cconfiguration>")
        PrintLine(1, "		<cconfiguration id=""com.ti.ccstudio.buildDefinitions.C6000.Release.771060527"">")
        PrintLine(1, "			<storageModule buildSystemId=""org.eclipse.cdt.managedbuilder.core.configurationDataProvider"" id=""com.ti.ccstudio.buildDefinitions.C6000.Release.771060527"" moduleId=""org.eclipse.cdt.core.settings"" name=""Release"">")
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
        PrintLine(1, "				<configuration artifactExtension=""out"" artifactName=""${ProjName}"" buildProperties="""" cleanCommand=""${CG_CLEAN_CMD}"" description="""" errorParsers=""org.eclipse.rtsc.xdctools.parsers.ErrorParser;org.eclipse.cdt.core.GmakeErrorParser;com.ti.ccstudio.errorparser.CoffErrorParser;com.ti.ccstudio.errorparser.AsmErrorParser;com.ti.ccstudio.errorparser.LinkErrorParser"" id=""com.ti.ccstudio.buildDefinitions.C6000.Release.771060527"" name=""Release"" parent=""com.ti.ccstudio.buildDefinitions.C6000.Release"">")
        PrintLine(1, "					<folderInfo id=""com.ti.ccstudio.buildDefinitions.C6000.Release.771060527."" name=""/"" resourcePath="""">")
        PrintLine(1, "						<toolChain id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.ReleaseToolchain.189744540"" name=""TI Build Tools"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.ReleaseToolchain"" targetTool=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.linkerRelease.2136070886"">")
        PrintLine(1, "							<option id=""com.ti.ccstudio.buildDefinitions.core.OPT_TAGS.1490324570"" superClass=""com.ti.ccstudio.buildDefinitions.core.OPT_TAGS"" valueType=""stringList"">")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""DEVICE_CONFIGURATION_ID=TMS320C67XX.OMAPL138.EXPKITOMAPL138""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""DEVICE_ENDIANNESS=little""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""OUTPUT_FORMAT=ELF""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""CCS_MBS_VERSION=6.1.3""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""RUNTIME_SUPPORT_LIBRARY=libc.a""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""RTSC_MBS_VERSION=7.0.0""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""XDC_VERSION=3.50.2.20_core""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""EXPANDED_REPOS=""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""OUTPUT_TYPE=rtscApplication:executable""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""PRODUCTS=com.ti.rtsc.SYSBIOS:6.75.0.15;""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""PRODUCT_MACRO_IMPORTS={&quot;com.ti.rtsc.SYSBIOS&quot;:[&quot;${BIOS_INCLUDE_PATH}&quot;,&quot;${BIOS_LIBRARY_PATH}&quot;,&quot;${BIOS_LIBRARIES}&quot;,&quot;${BIOS_SYMBOLS}&quot;]}""/>")
        PrintLine(1, "							</option>")
        PrintLine(1, "							<option id=""com.ti.ccstudio.buildDefinitions.core.OPT_CODEGEN_VERSION.1178402593"" name=""Compiler version"" superClass=""com.ti.ccstudio.buildDefinitions.core.OPT_CODEGEN_VERSION"" value=""8.3.3"" valueType=""string""/>")
        PrintLine(1, "							<targetPlatform id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.targetPlatformRelease.748692673"" name=""Platform"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.targetPlatformRelease""/>")
        PrintLine(1, "							<builder buildPath=""${BuildDirectory}"" id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.builderRelease.519067731"" keepEnvironmentInBuildfile=""false"" name=""GNU Make"" parallelBuildOn=""true"" parallelizationNumber=""optimal"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.builderRelease""/>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.compilerRelease.1529743159"" name=""C6000 Compiler"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.compilerRelease"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DEFINE.2104147973"" name=""Pre-define NAME (--define, -D)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DEFINE"" valueType=""definedSymbols"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_SYMBOLS}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""omapl138""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.SILICON_VERSION.1857045398"" name=""Target processor version (--silicon_version, -mv)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.SILICON_VERSION"" useByScannerDiscovery=""false"" value=""6740"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WARNING.116991667"" name=""Treat diagnostic &lt;id&gt; as warning (--diag_warning, -pdsw)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WARNING"" useByScannerDiscovery=""false"" valueType=""stringList"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""225""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DISPLAY_ERROR_NUMBER.1453925065"" name=""Emit diagnostic identifier numbers (--display_error_number, -pden)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DISPLAY_ERROR_NUMBER"" useByScannerDiscovery=""false"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WRAP.1820970868"" name=""Wrap diagnostic messages (--diag_wrap)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WRAP"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WRAP.off"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.INCLUDE_PATH.550795300"" name=""Add dir to #include search path (--include_path, -I)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.INCLUDE_PATH"" valueType=""includePath"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${BIOS_INCLUDE_PATH}&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${PROJECT_ROOT}&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${CG_TOOL_ROOT}/include&quot;""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__C_SRCS.597585542"" name=""C Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__C_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__CPP_SRCS.641710508"" name=""C++ Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__CPP_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__ASM_SRCS.921288630"" name=""Assembly Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__ASM_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__ASM2_SRCS.782947914"" name=""Assembly Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__ASM2_SRCS""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.linkerRelease.2136070886"" name=""C6000 Linker"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.linkerRelease"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DEFINE.918398097"" name=""Pre-define preprocessor macro _name_ to _value_ (--define)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DEFINE"" valueType=""definedSymbols"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""DSP_CORE=1""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.STACK_SIZE.1851544922"" name=""Set C system stack size (--stack_size, -stack)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.STACK_SIZE"" useByScannerDiscovery=""false"" value=""0x800"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.HEAP_SIZE.329050462"" name=""Heap size for C/C++ dynamic memory allocation (--heap_size, -heap)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.HEAP_SIZE"" useByScannerDiscovery=""false"" value=""0x800"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.OUTPUT_FILE.1987237831"" name=""Specify output file name (--output_file, -o)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.OUTPUT_FILE"" useByScannerDiscovery=""false"" value=""&quot;${ProjName}.out&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.MAP_FILE.1520934420"" name=""Link information (map) listed into &lt;file&gt; (--map_file, -m)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.MAP_FILE"" useByScannerDiscovery=""false"" value=""&quot;${ProjName}.map&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.XML_LINK_INFO.312164097"" name=""Detailed link information data-base into &lt;file&gt; (--xml_link_info, -xml_link_info)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.XML_LINK_INFO"" useByScannerDiscovery=""false"" value=""&quot;${ProjName}_linkInfo.xml&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DISPLAY_ERROR_NUMBER.1537193932"" name=""Emit diagnostic identifier numbers (--display_error_number)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DISPLAY_ERROR_NUMBER"" useByScannerDiscovery=""false"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DIAG_WRAP.750370311"" name=""Wrap diagnostic messages (--diag_wrap)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DIAG_WRAP"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DIAG_WRAP.off"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.SEARCH_PATH.202306944"" name=""Add &lt;dir&gt; to library search path (--search_path, -i)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.SEARCH_PATH"" valueType=""libPaths"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${BIOS_LIBRARY_PATH}&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${CG_TOOL_ROOT}/lib&quot;""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""&quot;${CG_TOOL_ROOT}/include&quot;""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.LIBRARY.485228916"" name=""Include library file or command file as input (--library, -l)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.LIBRARY"" useByScannerDiscovery=""false"" valueType=""libs"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_LIBRARIES}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""libc.a""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__CMD_SRCS.1102112542"" name=""Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__CMD_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__CMD2_SRCS.97832196"" name=""Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__CMD2_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__GEN_CMDS.1190556037"" name=""Generated Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__GEN_CMDS""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex.1142715902"" name=""C6000 Hex Utility"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex""/>")
        PrintLine(1, "							<tool id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.303928674"" name=""XDCtools"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool"">")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.CODEGEN_TOOL_DIR.1646267119"" name=""Compiler tools directory (-c)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.CODEGEN_TOOL_DIR"" value=""&quot;${CG_TOOL_ROOT}&quot;"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.TARGET.1030918454"" name=""Target (-t)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.TARGET"" value=""ti.targets.elf.C674"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM.1033919310"" name=""Platform (-p)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM"" value=""ti.platforms.evmOMAPL138"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM_RAW.1249254962"" name=""Platform (-p)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM_RAW"" value=""ti.platforms.evmOMAPL138"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.BUILD_PROFILE.843490870"" name=""Build-profile (-r)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.BUILD_PROFILE"" value=""debug"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.XDC_PATH.1469733225"" name=""Package repositories (--xdcpath)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.XDC_PATH"" valueType=""stringList"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_CG_ROOT}/packages""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TARGET_CONTENT_BASE}""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.COMPILE_OPTIONS.866018025"" name=""Additional compiler options (--compileOptions)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.COMPILE_OPTIONS"" useByScannerDiscovery=""false"" value=""&quot;-g &quot;"" valueType=""string""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "						</toolChain>")
        PrintLine(1, "					</folderInfo>")
        PrintLine(1, "					<sourceEntries>")
        PrintLine(1, "						<entry excluding=""src"" flags=""VALUE_WORKSPACE_PATH|RESOLVED"" kind=""sourcePath"" name=""""/>")
        PrintLine(1, "					</sourceEntries>")
        PrintLine(1, "				</configuration>")
        PrintLine(1, "			</storageModule>")
        PrintLine(1, "			<storageModule moduleId=""org.eclipse.cdt.core.externalSettings""/>")
        PrintLine(1, "		</cconfiguration>")
        PrintLine(1, "	</storageModule>")
        PrintLine(1, "	<storageModule moduleId=""org.eclipse.cdt.core.LanguageSettingsProviders""/>")
        PrintLine(1, "	<storageModule moduleId=""cdtBuildSystem"" version=""4.0.0"">")
        PrintLine(1, "		<project id=""omapSYSBIOS.com.ti.ccstudio.buildDefinitions.C6000.ProjectType.916633390"" name=""C6000"" projectType=""com.ti.ccstudio.buildDefinitions.C6000.ProjectType""/>")
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

        FileClose(1)

        FileOpen(1, Project_ccsproject_fileFullPath, OpenMode.Output)

        PrintLine(1, "<?xml version=""1.0"" encoding=""UTF-8"" ?>")
        PrintLine(1, "<?ccsproject version=""1.0""?>")
        PrintLine(1, "<projectOptions>")
        PrintLine(1, "	<ccsVersion value=""7.2.0""/>")
        PrintLine(1, "	<deviceVariant value=""TMS320C67XX.OMAPL138.EXPKITOMAPL138""/>")
        PrintLine(1, "	<deviceFamily value=""C6000""/>")
        PrintLine(1, "	<deviceEndianness value=""little""/>")
        PrintLine(1, "	<codegenToolVersion value=""8.3.3""/>")
        PrintLine(1, "	<isElfFormat value=""true""/>")
        PrintLine(1, "	<connection value=""common/targetdb/connections/TIXDS2XXUSB_Connection.xml""/>")
        PrintLine(1, "	<rts value=""libc.a""/>")
        PrintLine(1, "	<createSlaveProjects value=""""/>")
        PrintLine(1, "	<templateProperties value=""id=com.ti.rtsc.SYSBIOS.example_49,type=rtsc,products=com.ti.rtsc.SYSBIOS,buildProfile=release,isHybrid=true,configuroOptions=--compileOptions &quot;-g &quot;,""/>")
        PrintLine(1, "	<filesToOpen value=""""/>")
        PrintLine(1, "	<isTargetManual value=""false""/>")
        PrintLine(1, "</projectOptions>")

        FileClose(1)

        '        FileOpen(1, Project_postbat_fileFullPath, OpenMode.Output)

        'PrintLine(1, "@echo off")
        'PrintLine(1, "pushd ..\..\")
        'PrintLine(1, "setlocal")
        'PrintLine(1, "")
        'PrintLine(1, ":process_arg")
        'PrintLine(1, "if ""%1""=="""" goto end_process_arg")
        'PrintLine(1, "set name=%1")
        'PrintLine(1, "set value=")
        'PrintLine(1, "")
        'PrintLine(1, ":process_arg_value")
        'PrintLine(1, "if NOT ""%value%""=="""" set value=%value% %2")
        'PrintLine(1, "if ""%value%""=="""" set value=%2")
        'PrintLine(1, "shift")
        'PrintLine(1, "if ""%2""==""!"" goto set_arg")
        'PrintLine(1, "if ""%2""=="""" goto set_arg")
        'PrintLine(1, "goto process_arg_value")
        'PrintLine(1, "")
        'PrintLine(1, ":set_arg")
        'PrintLine(1, "set %name%=%value%")
        'PrintLine(1, "shift")
        'PrintLine(1, "shift")
        'PrintLine(1, "goto process_arg")
        'PrintLine(1, ":end_process_arg")
        'PrintLine(1, "")
        'PrintLine(1, "echo. > temp_postBuildStep_Debug.bat")
        'PrintLine(1, "")
        'PrintLine(1, "echo hex6x.exe %PROJECT_ROOT%\..\out2bootbin.cmd -o %PROJECT_ROOT%\..\" & ProjectName & ".bin %PROJECT_ROOT%\debug\" & ProjectName & ".out >> temp_postBuildStep_Debug.bat")
        'PrintLine(1, "")
        'PrintLine(1, "call temp_postBuildStep_Debug.bat")
        'PrintLine(1, "del temp_postBuildStep_Debug.bat")
        'PrintLine(1, "")
        'PrintLine(1, "endlocal")
        'PrintLine(1, "popd")
        'PrintLine(1, " ")

        'FileClose(1)

        FileOpen(1, Project_projectinclude_fileFullPath, OpenMode.Output)

        PrintLine(1, "#include """ & ProjectName & "_pe674.h""")
        PrintLine(1, "")
        PrintLine(1, " ")

        FileClose(1)

        FileOpen(1, Project_copybat_fileFullPath, OpenMode.Output)


        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019OptitrackOMAPL138ProjCreatorFiles\SYSBIOS\PROJECTNAME.cfg " & Project_SYSBIOS_Dir & ProjectName & ".cfg")
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019OptitrackOMAPL138ProjCreatorFiles\include\*.* " & Project_include_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019OptitrackOMAPL138ProjCreatorFiles\PRUcode\*.* " & Project_PRUcode_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019OptitrackOMAPL138ProjCreatorFiles\source\*.* " & Project_source_Dir)
        PrintLine(1, "move " & Project_source_Dir & "user_PROJECTNAME.c " & Project_source_Dir & "user_" & ProjectName & ".c")
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019OptitrackOMAPL138ProjCreatorFiles\project\*.ccxml " & ProjectSubDirectory)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019OptitrackOMAPL138ProjCreatorFiles\project\.settings\*.* " & ProjectSub_settings_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019OptitrackOMAPL138ProjCreatorFiles\project\.launches\*.* " & ProjectSub_launches_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2019OptitrackOMAPL138ProjCreatorFiles\project\targetConfigs\*.* " & ProjectSub_targetConfigs_Dir)
        PrintLine(1, Drive)
        PrintLine(1, "cd """ & ProjectDirectory & """")
        PrintLine(1, "pause")
        PrintLine(1, "del """ & Project_copybat_fileFullPath & """")

        FileClose(1)


        Shell(Project_copybat_fileFullPath, 1)


        Me.Close()

NoWrite:

    End Sub

    
End Class
