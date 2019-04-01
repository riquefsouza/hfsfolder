##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=hfsfolder-c
ConfigurationName      :=Debug
WorkspacePath          :=C:/ambiente/workspace-codelite
ProjectPath            :=C:/ambiente/workspace-codelite/hfsfolder-c
IntermediateDirectory  :=./obj/Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Administrador
Date                   :=31/03/2019
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/msys64/mingw64/bin/g++.exe
SharedObjectLinkerName :=C:/msys64/mingw64/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=./bin/Debug/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="hfsfolder-c.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/msys64/mingw64/bin/windres.exe
LinkOptions            :=  
IncludePath            := $(IncludeSwitch)C:/msys64/mingw64/include  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)C:/msys64/mingw64/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)gnurx $(LibrarySwitch)regex 
ArLibs                 :=  "gnurx" "regex" 
LibPath                :=$(LibraryPathSwitch)C:/msys64/mingw64/lib  $(LibraryPathSwitch). $(LibraryPathSwitch)C:/msys64/mingw64/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/msys64/mingw64/bin/ar.exe rcu
CXX      := C:/msys64/mingw64/bin/g++.exe
CC       := C:/msys64/mingw64/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/msys64/mingw64/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/DateTime.c$(ObjectSuffix) $(IntermediateDirectory)/stdafx.c$(ObjectSuffix) $(IntermediateDirectory)/StringUtil.c$(ObjectSuffix) $(IntermediateDirectory)/ProcessFolders.c$(ObjectSuffix) $(IntermediateDirectory)/PreFile.c$(ObjectSuffix) $(IntermediateDirectory)/Folder.c$(ObjectSuffix) $(IntermediateDirectory)/FolderList.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./obj/Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./obj/Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-c/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/DateTime.c$(ObjectSuffix): DateTime.c $(IntermediateDirectory)/DateTime.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-c/DateTime.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DateTime.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DateTime.c$(DependSuffix): DateTime.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DateTime.c$(ObjectSuffix) -MF$(IntermediateDirectory)/DateTime.c$(DependSuffix) -MM DateTime.c

$(IntermediateDirectory)/DateTime.c$(PreprocessSuffix): DateTime.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DateTime.c$(PreprocessSuffix) DateTime.c

$(IntermediateDirectory)/stdafx.c$(ObjectSuffix): stdafx.c $(IntermediateDirectory)/stdafx.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-c/stdafx.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/stdafx.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/stdafx.c$(DependSuffix): stdafx.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/stdafx.c$(ObjectSuffix) -MF$(IntermediateDirectory)/stdafx.c$(DependSuffix) -MM stdafx.c

$(IntermediateDirectory)/stdafx.c$(PreprocessSuffix): stdafx.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/stdafx.c$(PreprocessSuffix) stdafx.c

$(IntermediateDirectory)/StringUtil.c$(ObjectSuffix): StringUtil.c $(IntermediateDirectory)/StringUtil.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-c/StringUtil.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StringUtil.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StringUtil.c$(DependSuffix): StringUtil.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StringUtil.c$(ObjectSuffix) -MF$(IntermediateDirectory)/StringUtil.c$(DependSuffix) -MM StringUtil.c

$(IntermediateDirectory)/StringUtil.c$(PreprocessSuffix): StringUtil.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StringUtil.c$(PreprocessSuffix) StringUtil.c

$(IntermediateDirectory)/ProcessFolders.c$(ObjectSuffix): ProcessFolders.c $(IntermediateDirectory)/ProcessFolders.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-c/ProcessFolders.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ProcessFolders.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ProcessFolders.c$(DependSuffix): ProcessFolders.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ProcessFolders.c$(ObjectSuffix) -MF$(IntermediateDirectory)/ProcessFolders.c$(DependSuffix) -MM ProcessFolders.c

$(IntermediateDirectory)/ProcessFolders.c$(PreprocessSuffix): ProcessFolders.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ProcessFolders.c$(PreprocessSuffix) ProcessFolders.c

$(IntermediateDirectory)/PreFile.c$(ObjectSuffix): PreFile.c $(IntermediateDirectory)/PreFile.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-c/PreFile.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PreFile.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PreFile.c$(DependSuffix): PreFile.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PreFile.c$(ObjectSuffix) -MF$(IntermediateDirectory)/PreFile.c$(DependSuffix) -MM PreFile.c

$(IntermediateDirectory)/PreFile.c$(PreprocessSuffix): PreFile.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PreFile.c$(PreprocessSuffix) PreFile.c

$(IntermediateDirectory)/Folder.c$(ObjectSuffix): Folder.c $(IntermediateDirectory)/Folder.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-c/Folder.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Folder.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Folder.c$(DependSuffix): Folder.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Folder.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Folder.c$(DependSuffix) -MM Folder.c

$(IntermediateDirectory)/Folder.c$(PreprocessSuffix): Folder.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Folder.c$(PreprocessSuffix) Folder.c

$(IntermediateDirectory)/FolderList.c$(ObjectSuffix): FolderList.c $(IntermediateDirectory)/FolderList.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-c/FolderList.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FolderList.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FolderList.c$(DependSuffix): FolderList.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FolderList.c$(ObjectSuffix) -MF$(IntermediateDirectory)/FolderList.c$(DependSuffix) -MM FolderList.c

$(IntermediateDirectory)/FolderList.c$(PreprocessSuffix): FolderList.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FolderList.c$(PreprocessSuffix) FolderList.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./obj/Debug/


