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
        'ProjectSubDirectory = ProjectDirectory & ProjectName & "Project\"
        ProjectSub_settings_Dir = ProjectDirectory & ".settings\"
        ProjectSub_Debug_Dir = ProjectDirectory & "Debug\"
        ProjectSub_launches_Dir = ProjectDirectory & ".launches\"
        ProjectSub_targetConfigs_Dir = ProjectDirectory & "targetConfigs\"

        Project_SYSBIOS_Dir = ProjectDirectory
        'Project_include_Dir = ProjectDirectory & "include\"
        'Project_PRUcode_Dir = ProjectDirectory & "PRUcode\"
        'Project_source_Dir = ProjectDirectory & "source\"


        Project_project_fileFullPath = ProjectDirectory & ".project"
        Project_cproject_fileFullPath = ProjectDirectory & ".cproject"
        Project_ccsproject_fileFullPath = ProjectDirectory & ".ccsproject"
        'Project_postbat_fileFullPath = ProjectDirectory & "postBuildStep_Debug.bat"
        Project_copybat_fileFullPath = ProjectDirectory & "tmpcopy.bat"
        Project_projectinclude_fileFullPath = ProjectDirectory & "projectinclude.h"

        MkDir(ProjectDirectory)
        'MkDir(ProjectSubDirectory)
        MkDir(ProjectSub_settings_Dir)
        MkDir(ProjectSub_Debug_Dir)
        MkDir(ProjectSub_launches_Dir)
        MkDir(ProjectSub_targetConfigs_Dir)

        'MkDir(Project_SYSBIOS_Dir)
        'MkDir(Project_include_Dir)
        'MkDir(Project_PRUcode_Dir)
        'MkDir(Project_source_Dir)


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
        PrintLine(1, "			<name>GPIO_evmAM572x_board.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-2-PROJECT_LOC/labfiles/AM5729_DSPCores/source/GPIO_evmAM572x_board.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "		<link>")
        PrintLine(1, "			<name>app.c</name>")
        PrintLine(1, "			<type>1</type>")
        PrintLine(1, "			<locationURI>PARENT-2-PROJECT_LOC/labfiles/AM5729_DSPCores/source/app.c</locationURI>")
        PrintLine(1, "		</link>")
        PrintLine(1, "	</linkedResources>")
        PrintLine(1, "</projectDescription>")
        FileClose(1)


        FileOpen(1, Project_cproject_fileFullPath, OpenMode.Output)

        PrintLine(1, "<?xml version=""1.0"" encoding=""UTF-8"" standalone=""no""?>")
        PrintLine(1, "<?fileVersion 4.0.0?><cproject storage_type_id=""org.eclipse.cdt.core.XmlProjectDescriptionStorage"">")
        PrintLine(1, "	<storageModule configRelations=""2"" moduleId=""org.eclipse.cdt.core.settings"">")
        PrintLine(1, "		<cconfiguration id=""com.ti.ccstudio.buildDefinitions.C6000.Debug.78526890"">")
        PrintLine(1, "			<storageModule buildSystemId=""org.eclipse.cdt.managedbuilder.core.configurationDataProvider"" id=""com.ti.ccstudio.buildDefinitions.C6000.Debug.78526890"" moduleId=""org.eclipse.cdt.core.settings"" name=""Debug"">")
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
        PrintLine(1, "				<configuration artifactExtension=""out"" artifactName=""${ProjName}"" buildProperties="""" cleanCommand=""${CG_CLEAN_CMD}"" description="""" errorParsers=""org.eclipse.rtsc.xdctools.parsers.ErrorParser;org.eclipse.cdt.core.GmakeErrorParser;com.ti.ccstudio.errorparser.CoffErrorParser;com.ti.ccstudio.errorparser.AsmErrorParser;com.ti.ccstudio.errorparser.LinkErrorParser"" id=""com.ti.ccstudio.buildDefinitions.C6000.Debug.78526890"" name=""Debug"" parent=""com.ti.ccstudio.buildDefinitions.C6000.Debug"">")
        PrintLine(1, "					<folderInfo id=""com.ti.ccstudio.buildDefinitions.C6000.Debug.78526890."" name=""/"" resourcePath="""">")
        PrintLine(1, "						<toolChain id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.DebugToolchain.301392496"" name=""TI Build Tools"" secondaryOutputs=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex.outputType__BIN"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.DebugToolchain"" targetTool=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.linkerDebug.821132338"">")
        PrintLine(1, "							<option id=""com.ti.ccstudio.buildDefinitions.core.OPT_TAGS.2093024988"" superClass=""com.ti.ccstudio.buildDefinitions.core.OPT_TAGS"" valueType=""stringList"">")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""DEVICE_CONFIGURATION_ID=TMS320C66XX.TMS320C6672""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""DEVICE_ENDIANNESS=little""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""OUTPUT_FORMAT=ELF""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""RUNTIME_SUPPORT_LIBRARY=libc.a""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""XDC_VERSION=3.51.1.18_core""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""INACTIVE_REPOS=""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""EXPANDED_REPOS=""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""CCS_MBS_VERSION=6.1.3""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""PRODUCTS=com.ti.rtsc.SYSBIOS:6.75.2.00;com.ti.pdk.am57xx:1.0.14;""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""PRODUCT_MACRO_IMPORTS={&quot;com.ti.rtsc.SYSBIOS&quot;:[&quot;${BIOS_INCLUDE_PATH}&quot;,&quot;${BIOS_LIBRARY_PATH}&quot;,&quot;${BIOS_LIBRARIES}&quot;,&quot;${BIOS_SYMBOLS}&quot;,&quot;${BIOS_SYSCONFIG_MANIFEST}&quot;],&quot;com.ti.pdk.am57xx&quot;:[&quot;${TI_PDK_INCLUDE_PATH}&quot;,&quot;${TI_PDK_LIBRARY_PATH}&quot;,&quot;${TI_PDK_LIBRARIES}&quot;,&quot;${TI_PDK_SYMBOLS}&quot;,&quot;${TI_PDK_SYSCONFIG_MANIFEST}&quot;]}""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""RTSC_MBS_VERSION=7.0.0""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""OUTPUT_TYPE=rtscApplication:executable""/>")
        PrintLine(1, "							</option>")
        PrintLine(1, "							<option id=""com.ti.ccstudio.buildDefinitions.core.OPT_CODEGEN_VERSION.1077270113"" name=""Compiler version"" superClass=""com.ti.ccstudio.buildDefinitions.core.OPT_CODEGEN_VERSION"" value=""8.3.3"" valueType=""string""/>")
        PrintLine(1, "							<targetPlatform id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.targetPlatformDebug.2086069745"" name=""Platform"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.targetPlatformDebug""/>")
        PrintLine(1, "							<builder buildPath=""${BuildDirectory}"" id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.builderDebug.1779764620"" keepEnvironmentInBuildfile=""false"" name=""GNU Make"" parallelBuildOn=""true"" parallelizationNumber=""optimal"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.builderDebug""/>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.compilerDebug.704245566"" name=""C6000 Compiler"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.compilerDebug"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.SILICON_VERSION.256823142"" name=""Target processor version (--silicon_version, -mv)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.SILICON_VERSION"" value=""6600"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.INCLUDE_PATH.249492711"" name=""Add dir to #include search path (--include_path, -I)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.INCLUDE_PATH"" valueType=""includePath"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TI_PDK_INCLUDE_PATH}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""configPkg\package\cfg""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""..\..\..\labfiles\AM5729_DSPCores\include""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""..\..\..\labfiles\mcbspAsSpi_com""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""..\..\..\labfiles\sharedmem""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_INCLUDE_PATH}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${PROJECT_ROOT}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${CG_TOOL_ROOT}/include""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DEFINE.1518219677"" name=""Pre-define NAME (--define, -D)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DEFINE"" valueType=""definedSymbols"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TI_PDK_SYMBOLS}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_SYMBOLS}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""C66X""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""SOC_AM572x""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""evmAM572x""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""ti_targets_arm_elf_M4""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DEBUGGING_MODEL.1255341493"" name=""Debugging model"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DEBUGGING_MODEL"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DEBUGGING_MODEL.SYMDEBUG__DWARF"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WARNING.1663313432"" name=""Treat diagnostic &lt;id&gt; as warning (--diag_warning, -pdsw)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WARNING"" valueType=""stringList"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""225""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WRAP.1821391770"" name=""Wrap diagnostic messages (--diag_wrap)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WRAP"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DIAG_WRAP.off"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DISPLAY_ERROR_NUMBER.1406871790"" name=""Emit diagnostic identifier numbers (--display_error_number, -pden)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.DISPLAY_ERROR_NUMBER"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_LEVEL.1899953198"" name=""Optimization level (--opt_level, -O)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_LEVEL"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_LEVEL.3"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_FOR_SPEED.569730648"" name=""Speed vs. size trade-offs (--opt_for_speed, -mf)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_FOR_SPEED"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_FOR_SPEED.3"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_FOR_SPACE.505299329"" name=""Optimize for code size (--opt_for_space, -ms)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_FOR_SPACE"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compilerID.OPT_FOR_SPACE.3"" valueType=""enumerated""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__C_SRCS.363230096"" name=""C Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__C_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__CPP_SRCS.2083413384"" name=""C++ Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__CPP_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__ASM_SRCS.1444028234"" name=""Assembly Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__ASM_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__ASM2_SRCS.950955760"" name=""Assembly Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.compiler.inputType__ASM2_SRCS""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.linkerDebug.821132338"" name=""C6000 Linker"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exe.linkerDebug"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.MAP_FILE.1545416652"" name=""Link information (map) listed into &lt;file&gt; (--map_file, -m)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.MAP_FILE"" value=""${ProjName}.map"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.OUTPUT_FILE.234418165"" name=""Specify output file name (--output_file, -o)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.OUTPUT_FILE"" value=""${ProjName}.out"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.LIBRARY.1535286863"" name=""Include library file or command file as input (--library, -l)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.LIBRARY"" valueType=""libs"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TI_PDK_LIBRARIES}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_LIBRARIES}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""ti.board.ae66""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""libc.a""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.SEARCH_PATH.1553500664"" name=""Add &lt;dir&gt; to library search path (--search_path, -i)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.SEARCH_PATH"" valueType=""libPaths"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TI_PDK_LIBRARY_PATH}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_LIBRARY_PATH}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${CG_TOOL_ROOT}/lib""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TI_PDK_INSTALL_DIR}/packages/ti/board/lib/evmAM572x/c66/release/""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${CG_TOOL_ROOT}/include""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DIAG_WRAP.1966031981"" name=""Wrap diagnostic messages (--diag_wrap)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DIAG_WRAP"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DIAG_WRAP.off"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DISPLAY_ERROR_NUMBER.293106264"" name=""Emit diagnostic identifier numbers (--display_error_number)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.DISPLAY_ERROR_NUMBER"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.XML_LINK_INFO.254468443"" name=""Detailed link information data-base into &lt;file&gt; (--xml_link_info, -xml_link_info)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.linkerID.XML_LINK_INFO"" value=""${ProjName}_linkInfo.xml"" valueType=""string""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__CMD_SRCS.671942195"" name=""Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__CMD_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__CMD2_SRCS.38374272"" name=""Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__CMD2_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__GEN_CMDS.1535584540"" name=""Generated Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.exeLinker.inputType__GEN_CMDS""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool commandLinePattern=""${command} ${flags} &quot;..\..\..\labfiles\SYSBIOShex\out2bootbin_AM5729.cmd&quot; ${output_flag} ${output} ${inputs}"" id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex.1213625584"" name=""C6000 Hex Utility"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex.TOOL_ENABLE.897498474"" name=""Enable tool"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.3.hex.TOOL_ENABLE"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.1229259727"" name=""XDCtools"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool"">")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.XDC_PATH.1730181539"" name=""Package repositories (--xdcpath)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.XDC_PATH"" valueType=""stringList"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_CG_ROOT}/packages""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TI_PDK_INSTALL_DIR}/packages""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.TARGET.517430821"" name=""Target (-t)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.TARGET"" value=""ti.targets.elf.C66"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM.1631230907"" name=""Platform (-p)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM"" value=""ti.platforms.evmAM572X"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM_RAW.1648825993"" name=""Platform (-p)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM_RAW"" value=""ti.platforms.evmAM572X"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.BUILD_PROFILE.291621374"" name=""Build-profile (-r)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.BUILD_PROFILE"" value=""release"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.CODEGEN_TOOL_DIR.1214115932"" name=""Compiler tools directory (-c)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.CODEGEN_TOOL_DIR"" value=""${CG_TOOL_ROOT}"" valueType=""string""/>")
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
        PrintLine(1, "		<cconfiguration id=""com.ti.ccstudio.buildDefinitions.C6000.Release.1782917885"">")
        PrintLine(1, "			<storageModule buildSystemId=""org.eclipse.cdt.managedbuilder.core.configurationDataProvider"" id=""com.ti.ccstudio.buildDefinitions.C6000.Release.1782917885"" moduleId=""org.eclipse.cdt.core.settings"" name=""Release"">")
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
        PrintLine(1, "				<configuration artifactExtension=""out"" artifactName=""${ProjName}"" buildProperties="""" cleanCommand=""${CG_CLEAN_CMD}"" description="""" errorParsers=""org.eclipse.rtsc.xdctools.parsers.ErrorParser;org.eclipse.cdt.core.GmakeErrorParser;com.ti.ccstudio.errorparser.CoffErrorParser;com.ti.ccstudio.errorparser.AsmErrorParser;com.ti.ccstudio.errorparser.LinkErrorParser"" id=""com.ti.ccstudio.buildDefinitions.C6000.Release.1782917885"" name=""Release"" parent=""com.ti.ccstudio.buildDefinitions.C6000.Release"">")
        PrintLine(1, "					<folderInfo id=""com.ti.ccstudio.buildDefinitions.C6000.Release.1782917885."" name=""/"" resourcePath="""">")
        PrintLine(1, "						<toolChain id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exe.ReleaseToolchain.1898043821"" name=""TI Build Tools"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exe.ReleaseToolchain"" targetTool=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exe.linkerRelease.698021637"">")
        PrintLine(1, "							<option id=""com.ti.ccstudio.buildDefinitions.core.OPT_TAGS.293091988"" superClass=""com.ti.ccstudio.buildDefinitions.core.OPT_TAGS"" valueType=""stringList"">")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""DEVICE_CONFIGURATION_ID=TMS320C66XX.AM5728_RevA""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""DEVICE_ENDIANNESS=little""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""OUTPUT_FORMAT=ELF""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""CCS_MBS_VERSION=6.1.3""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""RUNTIME_SUPPORT_LIBRARY=libc.a""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""RTSC_MBS_VERSION=7.0.0""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""XDC_VERSION=3.51.1.18_core""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""OUTPUT_TYPE=rtscApplication:executable""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""PRODUCTS=com.ti.rtsc.SYSBIOS:6.75.2.00;com.ti.pdk.am57xx:1.0.14;""/>")
        PrintLine(1, "								<listOptionValue builtIn=""false"" value=""PRODUCT_MACRO_IMPORTS={&quot;com.ti.rtsc.SYSBIOS&quot;:[&quot;${BIOS_INCLUDE_PATH}&quot;,&quot;${BIOS_LIBRARY_PATH}&quot;,&quot;${BIOS_LIBRARIES}&quot;,&quot;${BIOS_SYMBOLS}&quot;,&quot;${BIOS_SYSCONFIG_MANIFEST}&quot;],&quot;com.ti.pdk.am57xx&quot;:[&quot;${TI_PDK_INCLUDE_PATH}&quot;,&quot;${TI_PDK_LIBRARY_PATH}&quot;,&quot;${TI_PDK_LIBRARIES}&quot;,&quot;${TI_PDK_SYMBOLS}&quot;,&quot;${TI_PDK_SYSCONFIG_MANIFEST}&quot;]}""/>")
        PrintLine(1, "							</option>")
        PrintLine(1, "							<option id=""com.ti.ccstudio.buildDefinitions.core.OPT_CODEGEN_VERSION.1399462541"" name=""Compiler version"" superClass=""com.ti.ccstudio.buildDefinitions.core.OPT_CODEGEN_VERSION"" value=""8.2.5"" valueType=""string""/>")
        PrintLine(1, "							<targetPlatform id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exe.targetPlatformRelease.1746438571"" name=""Platform"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exe.targetPlatformRelease""/>")
        PrintLine(1, "							<builder buildPath=""${BuildDirectory}"" id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exe.builderRelease.779208003"" keepEnvironmentInBuildfile=""false"" name=""GNU Make"" parallelBuildOn=""true"" parallelizationNumber=""optimal"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exe.builderRelease""/>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exe.compilerRelease.229916047"" name=""C6000 Compiler"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exe.compilerRelease"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.DEFINE.1297547752"" name=""Pre-define NAME (--define, -D)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.DEFINE"" valueType=""definedSymbols"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TI_PDK_SYMBOLS}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_SYMBOLS}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""am5728""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""core1""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""C66X""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""SOC_AM572x""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""evmAM572x""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""ti_targets_arm_elf_M4""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.SILICON_VERSION.2081407355"" name=""Target processor version (--silicon_version, -mv)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.SILICON_VERSION"" useByScannerDiscovery=""false"" value=""6600"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.DIAG_WARNING.1149184871"" name=""Treat diagnostic &lt;id&gt; as warning (--diag_warning, -pdsw)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.DIAG_WARNING"" useByScannerDiscovery=""false"" valueType=""stringList"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""225""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.DISPLAY_ERROR_NUMBER.373257279"" name=""Emit diagnostic identifier numbers (--display_error_number, -pden)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.DISPLAY_ERROR_NUMBER"" useByScannerDiscovery=""false"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.DIAG_WRAP.114211741"" name=""Wrap diagnostic messages (--diag_wrap)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.DIAG_WRAP"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.DIAG_WRAP.off"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.INCLUDE_PATH.2039057911"" name=""Add dir to #include search path (--include_path, -I)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.INCLUDE_PATH"" valueType=""includePath"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TI_PDK_INCLUDE_PATH}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_INCLUDE_PATH}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${PROJECT_ROOT}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${CG_TOOL_ROOT}/include""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.DEBUGGING_MODEL.516249670"" name=""Debugging model"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.DEBUGGING_MODEL"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compilerID.DEBUGGING_MODEL.SYMDEBUG__DWARF"" valueType=""enumerated""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compiler.inputType__C_SRCS.527723299"" name=""C Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compiler.inputType__C_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compiler.inputType__CPP_SRCS.71147388"" name=""C++ Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compiler.inputType__CPP_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compiler.inputType__ASM_SRCS.1286856049"" name=""Assembly Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compiler.inputType__ASM_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compiler.inputType__ASM2_SRCS.360415387"" name=""Assembly Sources"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.compiler.inputType__ASM2_SRCS""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exe.linkerRelease.698021637"" name=""C6000 Linker"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exe.linkerRelease"">")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.DEFINE.1766657105"" name=""Pre-define preprocessor macro _name_ to _value_ (--define)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.DEFINE"" valueType=""definedSymbols"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""CORE1=1""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.STACK_SIZE.1545636720"" name=""Set C system stack size (--stack_size, -stack)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.STACK_SIZE"" useByScannerDiscovery=""false"" value=""0x800"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.HEAP_SIZE.1671534778"" name=""Heap size for C/C++ dynamic memory allocation (--heap_size, -heap)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.HEAP_SIZE"" useByScannerDiscovery=""false"" value=""0x800"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.OUTPUT_FILE.1930006518"" name=""Specify output file name (--output_file, -o)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.OUTPUT_FILE"" useByScannerDiscovery=""false"" value=""${ProjName}.out"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.MAP_FILE.380346358"" name=""Link information (map) listed into &lt;file&gt; (--map_file, -m)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.MAP_FILE"" useByScannerDiscovery=""false"" value=""${ProjName}.map"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.XML_LINK_INFO.1395620250"" name=""Detailed link information data-base into &lt;file&gt; (--xml_link_info, -xml_link_info)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.XML_LINK_INFO"" useByScannerDiscovery=""false"" value=""${ProjName}_linkInfo.xml"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.DISPLAY_ERROR_NUMBER.219355363"" name=""Emit diagnostic identifier numbers (--display_error_number)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.DISPLAY_ERROR_NUMBER"" useByScannerDiscovery=""false"" value=""true"" valueType=""boolean""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.DIAG_WRAP.750726005"" name=""Wrap diagnostic messages (--diag_wrap)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.DIAG_WRAP"" useByScannerDiscovery=""false"" value=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.DIAG_WRAP.off"" valueType=""enumerated""/>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.SEARCH_PATH.1112725697"" name=""Add &lt;dir&gt; to library search path (--search_path, -i)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.SEARCH_PATH"" valueType=""libPaths"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TI_PDK_LIBRARY_PATH}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_LIBRARY_PATH}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${CG_TOOL_ROOT}/lib""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TI_PDK_INSTALL_DIR}/packages/ti/board/lib/evmAM572x/c66/release/""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${CG_TOOL_ROOT}/include""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<option id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.LIBRARY.556600088"" name=""Include library file or command file as input (--library, -l)"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.linkerID.LIBRARY"" useByScannerDiscovery=""false"" valueType=""libs"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TI_PDK_LIBRARIES}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_LIBRARIES}""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""ti.board.ae66""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""libc.a""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exeLinker.inputType__CMD_SRCS.1513599615"" name=""Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exeLinker.inputType__CMD_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exeLinker.inputType__CMD2_SRCS.1247341084"" name=""Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exeLinker.inputType__CMD2_SRCS""/>")
        PrintLine(1, "								<inputType id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exeLinker.inputType__GEN_CMDS.923972730"" name=""Generated Linker Command Files"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.exeLinker.inputType__GEN_CMDS""/>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "							<tool id=""com.ti.ccstudio.buildDefinitions.C6000_8.2.hex.1780649869"" name=""C6000 Hex Utility"" superClass=""com.ti.ccstudio.buildDefinitions.C6000_8.2.hex""/>")
        PrintLine(1, "							<tool id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.1218953852"" name=""XDCtools"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool"">")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.CODEGEN_TOOL_DIR.1957230131"" name=""Compiler tools directory (-c)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.CODEGEN_TOOL_DIR"" value=""${CG_TOOL_ROOT}"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.TARGET.541225672"" name=""Target (-t)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.TARGET"" value=""ti.targets.elf.C66"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM.641225041"" name=""Platform (-p)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM"" value=""ti.platforms.evmAM572X"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM_RAW.164458901"" name=""Platform (-p)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.PLATFORM_RAW"" value=""ti.platforms.evmAM572X"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.BUILD_PROFILE.1071892972"" name=""Build-profile (-r)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.BUILD_PROFILE"" value=""release"" valueType=""string""/>")
        PrintLine(1, "								<option id=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.XDC_PATH.241506500"" name=""Package repositories (--xdcpath)"" superClass=""com.ti.rtsc.buildDefinitions.XDC_3.16.tool.XDC_PATH"" valueType=""stringList"">")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${BIOS_CG_ROOT}/packages""/>")
        PrintLine(1, "									<listOptionValue builtIn=""false"" value=""${TI_PDK_INSTALL_DIR}/packages""/>")
        PrintLine(1, "								</option>")
        PrintLine(1, "							</tool>")
        PrintLine(1, "						</toolChain>")
        PrintLine(1, "					</folderInfo>")
        PrintLine(1, "					<sourceEntries>")
        PrintLine(1, "						<entry excluding=""src|app.h"" flags=""VALUE_WORKSPACE_PATH|RESOLVED"" kind=""sourcePath"" name=""""/>")
        PrintLine(1, "					</sourceEntries>")
        PrintLine(1, "				</configuration>")
        PrintLine(1, "			</storageModule>")
        PrintLine(1, "			<storageModule moduleId=""org.eclipse.cdt.core.externalSettings""/>")
        PrintLine(1, "		</cconfiguration>")
        PrintLine(1, "	</storageModule>")
        PrintLine(1, "	<storageModule moduleId=""org.eclipse.cdt.core.LanguageSettingsProviders""/>")
        PrintLine(1, "	<storageModule moduleId=""cdtBuildSystem"" version=""4.0.0"">")
        PrintLine(1, "		<project id=""" & ProjectName & ".com.ti.ccstudio.buildDefinitions.C6000.ProjectType.67028689"" name=""C6000"" projectType=""com.ti.ccstudio.buildDefinitions.C6000.ProjectType""/>")
        PrintLine(1, "	</storageModule>")
        PrintLine(1, "	<storageModule moduleId=""scannerConfiguration""/>")
        PrintLine(1, "	<storageModule moduleId=""org.eclipse.cdt.make.core.buildtargets""/>")
        PrintLine(1, "</cproject>")

        FileClose(1)

        FileOpen(1, Project_ccsproject_fileFullPath, OpenMode.Output)

        PrintLine(1, "<?xml version=""1.0"" encoding=""UTF-8"" ?>")
        PrintLine(1, "<?ccsproject version=""1.0""?>")
        PrintLine(1, "<projectOptions>")
        PrintLine(1, "	<ccsVersion value=""8.3.0""/>")
        PrintLine(1, "	<deviceVariant value=""TMS320C66XX.AM5728_RevA""/>")
        PrintLine(1, "	<deviceFamily value=""C6000""/>")
        PrintLine(1, "	<deviceEndianness value=""little""/>")
        PrintLine(1, "	<codegenToolVersion value=""8.2.5""/>")
        PrintLine(1, "	<isElfFormat value=""true""/>")
        PrintLine(1, "	<connection value=""common/targetdb/connections/TIXDS2XXUSB_Connection.xml""/>")
        PrintLine(1, "	<rts value=""libc.a""/>")
        PrintLine(1, "	<createSlaveProjects value=""""/>")
        PrintLine(1, "	<templateProperties value=""id=" & ProjectName & "_evmAM572X.projectspec." & ProjectName & ",xdcToolsVersion=3_51_01_18_core,products=com.ti.rtsc.SYSBIOS:6.75.02.00;com.ti.pdk.am57xx:1.0.14,type=rtsc,target=ti.targets.elf.C66,platform=ti.platforms.evmAM572X,buildProfile=release,isHybrid=true""/>")
        PrintLine(1, "	<origin value=""C:\CCStudio8\processor_sdk_rtos_am57xx_5_03_00_07\demos\rtos_template_app\am572x\evmAM572X\C66\template_app\rtos_template_app_am572x_c66_evmAM572X.projectspec""/>")
        PrintLine(1, "	<filesToOpen value=""""/>")
        PrintLine(1, "	<isTargetManual value=""true""/>")
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
        'PrintLine(1, "echo hex6x.exe %PROJECT_ROOT%\..\out2bootbin_AM5729.cmd -o %PROJECT_ROOT%\..\" & ProjectName & ".bin %PROJECT_ROOT%\debug\" & ProjectName & ".out >> temp_postBuildStep_Debug.bat")
        'PrintLine(1, "")
        'PrintLine(1, "call temp_postBuildStep_Debug.bat")
        'PrintLine(1, "del temp_postBuildStep_Debug.bat")
        'PrintLine(1, "")
        'PrintLine(1, "endlocal")
        'PrintLine(1, "popd")
        'PrintLine(1, " ")

        'FileClose(1)

        FileOpen(1, Project_projectinclude_fileFullPath, OpenMode.Output)

        PrintLine(1, "#include """ & ProjectName & "_pe66.h""")
        PrintLine(1, "")
        PrintLine(1, " ")

        FileClose(1)

        FileOpen(1, Project_copybat_fileFullPath, OpenMode.Output)


        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2020C6672ProjCreatorFiles\project\main.cfg " & Project_SYSBIOS_Dir & ProjectName & ".cfg")
        'PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2020C6672ProjCreatorFiles\include\*.* " & Project_include_Dir)
        'PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2020C6672ProjCreatorFiles\PRUcode\*.* " & Project_PRUcode_Dir)
        'PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2020C6672ProjCreatorFiles\source\*.* " & Project_source_Dir)
        'PrintLine(1, "move " & Project_source_Dir & "user_PROJECTNAME.c " & Project_source_Dir & "user_" & ProjectName & ".c")
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2020C6672ProjCreatorFiles\project\main.c " & ProjectDirectory & ProjectName & ".c")
        'PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2020C6672ProjCreatorFiles\project\*.ccxml " & ProjectSubDirectory)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2020C6672ProjCreatorFiles\project\.settings\*.* " & ProjectSub_settings_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2020C6672ProjCreatorFiles\project\.launches\*.* " & ProjectSub_launches_Dir)
        PrintLine(1, "copy " & ProjectDirectory & "..\..\LabFiles\Sp2020C6672ProjCreatorFiles\project\targetConfigs\*.* " & ProjectSub_targetConfigs_Dir)
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
