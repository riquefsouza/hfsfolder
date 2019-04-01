##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=hfsfolder-cpp
ConfigurationName      :=Debug
WorkspacePath          :=C:/ambiente/workspace-codelite
ProjectPath            :=C:/ambiente/workspace-codelite/hfsfolder-cpp
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
ObjectsFileList        :="hfsfolder-cpp.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/msys64/mingw64/bin/windres.exe
LinkOptions            :=  
IncludePath            := $(IncludeSwitch)C:/msys64/mingw64/include  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)C:/msys64/mingw64/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)boost_filesystem-mt $(LibrarySwitch)boost_regex-mt $(LibrarySwitch)boost_date_time-mt 
ArLibs                 :=  "boost_filesystem-mt" "boost_regex-mt" "boost_date_time-mt" 
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
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/Folder.cpp$(ObjectSuffix) $(IntermediateDirectory)/StringUtil.cpp$(ObjectSuffix) $(IntermediateDirectory)/FolderOrder.cpp$(ObjectSuffix) $(IntermediateDirectory)/ProcessFolders.cpp$(ObjectSuffix) $(IntermediateDirectory)/PreFile.cpp$(ObjectSuffix) $(IntermediateDirectory)/VisitFoldersUtil.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-cpp/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/Folder.cpp$(ObjectSuffix): Folder.cpp $(IntermediateDirectory)/Folder.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-cpp/Folder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Folder.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Folder.cpp$(DependSuffix): Folder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Folder.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Folder.cpp$(DependSuffix) -MM Folder.cpp

$(IntermediateDirectory)/Folder.cpp$(PreprocessSuffix): Folder.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Folder.cpp$(PreprocessSuffix) Folder.cpp

$(IntermediateDirectory)/StringUtil.cpp$(ObjectSuffix): StringUtil.cpp $(IntermediateDirectory)/StringUtil.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-cpp/StringUtil.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/StringUtil.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/StringUtil.cpp$(DependSuffix): StringUtil.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/StringUtil.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/StringUtil.cpp$(DependSuffix) -MM StringUtil.cpp

$(IntermediateDirectory)/StringUtil.cpp$(PreprocessSuffix): StringUtil.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/StringUtil.cpp$(PreprocessSuffix) StringUtil.cpp

$(IntermediateDirectory)/FolderOrder.cpp$(ObjectSuffix): FolderOrder.cpp $(IntermediateDirectory)/FolderOrder.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-cpp/FolderOrder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/FolderOrder.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/FolderOrder.cpp$(DependSuffix): FolderOrder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/FolderOrder.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/FolderOrder.cpp$(DependSuffix) -MM FolderOrder.cpp

$(IntermediateDirectory)/FolderOrder.cpp$(PreprocessSuffix): FolderOrder.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/FolderOrder.cpp$(PreprocessSuffix) FolderOrder.cpp

$(IntermediateDirectory)/ProcessFolders.cpp$(ObjectSuffix): ProcessFolders.cpp $(IntermediateDirectory)/ProcessFolders.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-cpp/ProcessFolders.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ProcessFolders.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ProcessFolders.cpp$(DependSuffix): ProcessFolders.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/ProcessFolders.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/ProcessFolders.cpp$(DependSuffix) -MM ProcessFolders.cpp

$(IntermediateDirectory)/ProcessFolders.cpp$(PreprocessSuffix): ProcessFolders.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ProcessFolders.cpp$(PreprocessSuffix) ProcessFolders.cpp

$(IntermediateDirectory)/PreFile.cpp$(ObjectSuffix): PreFile.cpp $(IntermediateDirectory)/PreFile.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-cpp/PreFile.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PreFile.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PreFile.cpp$(DependSuffix): PreFile.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PreFile.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PreFile.cpp$(DependSuffix) -MM PreFile.cpp

$(IntermediateDirectory)/PreFile.cpp$(PreprocessSuffix): PreFile.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PreFile.cpp$(PreprocessSuffix) PreFile.cpp

$(IntermediateDirectory)/VisitFoldersUtil.cpp$(ObjectSuffix): VisitFoldersUtil.cpp $(IntermediateDirectory)/VisitFoldersUtil.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/ambiente/workspace-codelite/hfsfolder-cpp/VisitFoldersUtil.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/VisitFoldersUtil.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/VisitFoldersUtil.cpp$(DependSuffix): VisitFoldersUtil.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/VisitFoldersUtil.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/VisitFoldersUtil.cpp$(DependSuffix) -MM VisitFoldersUtil.cpp

$(IntermediateDirectory)/VisitFoldersUtil.cpp$(PreprocessSuffix): VisitFoldersUtil.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/VisitFoldersUtil.cpp$(PreprocessSuffix) VisitFoldersUtil.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./obj/Debug/


