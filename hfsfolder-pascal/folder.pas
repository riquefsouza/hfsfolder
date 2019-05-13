unit Folder;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, PreFile;

type
  TFolder = class(TPreFile)
  private
    code: integer;
    order: integer;
    parentCodFolder: integer;
    folderType: char;
    path: string;
    parentName: string;
    parentPath: string;
  public
    separatorFile: char;

    constructor Create(prefile: TPreFile);
    destructor Destroy; override;

    function getCode(): integer;
    procedure setCode(ncode: integer);
    function getOrder(): integer;
    procedure setOrder(norder: integer);
    function getParentCodFolder(): integer;
    procedure setParentCodFolder(nparentCodFolder: integer);
    function getFolderType(): char;
    procedure setFolderType(sfolderType: char);
    function getPath(): String;
    procedure setPath(spath: String);
    function getParentName(): String;
    procedure setParentName(sparentName: String);
    function getParentPath(): String;
    procedure setParentPath(sparentPath: String);

    procedure limparDados;
    function ToString: ansistring; override;
    function ToInsert(naba: integer): string;
    function ToCVS: string;
    function ToJSON: string;
  end;

implementation

constructor TFolder.Create(prefile: TPreFile);
begin
  inherited Create;
  self.setName(preFile.getName());
  self.setSize(preFile.getSize());
  self.setModified(preFile.getModified());
  self.setAttributes(preFile.getAttributes());
  self.setFormatedSize(preFile.getFormatedSize());
  self.setFormatedModified(preFile.getFormatedModified());
  self.setOriginalPath(prefile.getOriginalPath());
  self.directory:=prefile.directory;
end;

destructor TFolder.Destroy;
begin
  inherited Destroy;
end;

function TFolder.getCode(): integer;
begin
  result:=self.code;
end;

procedure TFolder.setCode(ncode: integer);
begin
  self.code:=ncode;
end;

function TFolder.getOrder(): integer;
begin
   result:=self.order;
end;

procedure TFolder.setOrder(norder: integer);
begin
  self.order:=norder;
end;

function TFolder.getParentCodFolder(): integer;
begin
   result:=self.parentCodFolder;
end;

procedure TFolder.setParentCodFolder(nparentCodFolder: integer);
begin
  self.parentCodFolder:=nparentCodFolder;
end;

function TFolder.getFolderType(): char;
begin
   result:=self.folderType;
end;

procedure TFolder.setFolderType(sfolderType: char);
begin
  self.folderType:=sfolderType;
end;

function TFolder.getPath(): String;
begin
   result:=self.path;
end;

procedure TFolder.setPath(spath: String);
begin
   self.path:=spath;
end;

function TFolder.getParentName(): String;
begin
   result:=self.parentName;
end;

procedure TFolder.setParentName(sparentName: String);
begin
  self.parentName:=sparentName;
end;

function TFolder.getParentPath(): String;
begin
   result:=self.parentPath;
end;

procedure TFolder.setParentPath(sparentPath: String);
begin
  self.parentPath:=sparentPath;
end;


procedure TFolder.limparDados;
begin
  self.limparDados();
  self.code := 0;
  self.order := 0;
  self.parentCodFolder := 0;
  self.folderType := 'A';
  self.path := '';
  self.parentName := '';
  self.parentPath := '';
end;

function TFolder.ToString: ansistring;
begin
  inherited ToString;

  result:='Folder [codigo=' + IntToStr(code) + ', ordem=' + IntToStr(order) +
  ', codDirPai=' + IntToStr(parentCodFolder) + ', tipo=' + folderType +
  ', caminho=' + path + ', nomePai=' + parentName +
  ', caminhoPai=' + parentPath + ']';
end;

function TFolder.ToInsert(naba: integer): string;
begin
  result:='INSERT INTO Diretorios(aba, cod, ordem, nome, '+
  'tam, tipo, modificado, atributos, coddirpai, caminho) VALUES('
  + IntToStr(naba) + ',' + IntToStr(code) + ',' + IntToStr(order) + ',' +
  QuotedStr(getName()) + ',' + IntToStr(getSize()) + ',' +
  QuotedStr(folderType) + ',' + QuotedStr(getFormatedModified()) + ',' +
  QuotedStr(getAttributes()) + ',' + IntToStr(parentCodFolder) + ',' +
  QuotedStr(getPath()) + ');';
end;

function TFolder.ToCVS: string;
begin
  result:=IntToStr(code) + ';' + IntToStr(order) + ';' + getName() + ';' +
  IntToStr(getSize()) + ';' + folderType + ';' + getFormatedModified() + ';' +
  getAttributes() + ';' + IntToStr(parentCodFolder) + ';' + getPath();
end;

function TFolder.ToJSON: string;
begin
  result:= '{'+ LineEnding + '"name" : "' + self.getName() + '",' +
LineEnding + '  "size" : ' + IntToStr(getSize()) + ',' +
LineEnding + '  "modified" : ' + DateTimeToStr(self.getModified()) + ',' +
LineEnding + '  "attributes" : "' + self.getAttributes() + '",' +
LineEnding + '  "formatedSize" : "' + self.getFormatedSize() + '",' +
LineEnding + '  "formatedModified" : "' + self.getFormatedModified() + '",' +
LineEnding + '  "code" : ' + IntToStr(code) + ',' +
LineEnding + '  "order" : ' + IntToStr(order) + ',' +
LineEnding + '  "parentCodFolder" : ' + IntToStr(parentCodFolder) + ',' +
LineEnding + '  "folderType" : "' + self.folderType + '",' +
LineEnding + '  "path" : "' + self.path + '",' +
LineEnding + '  "parentName" : "' + self.parentName + '",' +
LineEnding + '  "parentPath" : "' + self.parentPath + '",' +
LineEnding + '  "originalPath" : "' + self.getOriginalPath() + '"\n}';
end;

end.

