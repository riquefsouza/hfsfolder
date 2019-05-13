unit ProcessFolders;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, StrUtils, PreFile, Folder, VisitFoldersUtil,
  FolderOrder, FolderList, RegExpr, PreFileList;

type
  TProcessFolders = class
  private
    function createFolder(pf: TPreFile; folderOrder: TFolderOrder): TFolder;
    function filterFindFirst(listFolders: TFolderList; sfolder: string): TFolder;
    function process(sfolder: string): TFolderList;
  public
    constructor Create;
    destructor Destroy; override;

    function processFoldersToJson(sfolder: string): string;
    procedure processFoldersToFile(sdata: string; sfile: string);
    function processFoldersToInsert(sfolder: string; naba: integer): string;
    function processFoldersToCSV(sfolder: string): string;
  end;

implementation

constructor TProcessFolders.Create;
begin
  inherited Create;
end;

destructor TProcessFolders.Destroy;
begin
  inherited Destroy;
end;

function TProcessFolders.createFolder(
  pf: TPreFile; folderOrder: TFolderOrder): TFolder;
var folder: TFolder;
  sPath, sPart: string;
  regex: TRegExpr;
begin
  folder:=TFolder.Create(pf);

  if pf.directory then
      folder.setFolderType('D')
  else
      folder.setFolderType('A');

  sPath := pf.getOriginalPath();

  regex := TRegExpr.Create('[a-zA-Z]:\\');
  if regex.Exec(sPath) then
  begin
    sPath := copy(sPath, 4, Length(sPath));
    folder.separatorFile:='\';
  end;
  regex.Free;

  regex := TRegExpr.Create('[a-zA-Z]:/');
  if regex.Exec(sPath) then
  begin
    sPath := copy(sPath, 3, Length(sPath));
    folder.separatorFile:='/';
  end;
  regex.Free;

  if sPath.StartsWith('/') then
  begin
    sPath := copy(sPath, 1, Length(sPath));
    folder.separatorFile:='/';
  end;

  sPart:=ReplaceStr(sPath, '''', '''''');
  sPart:=ReplaceStr(sPart, '\\', '\');

  folder.setPath(sPart);
  folder.setOriginalPath(pf.getOriginalPath());

  if (not AnsiContainsStr(folder.getPath(), '/')) then
  begin
    folderOrder.setCodFolder(folderOrder.getCodFolder()+1);
    folderOrder.setOrder(1);
  end
  else
  begin
     folderOrder.setOrder(folderOrder.getOrder()+1);
  end;

  folder.setCode(folderOrder.getCodFolder());
  folder.setOrder(folderOrder.getOrder());

  result:=folder;
end;

function TProcessFolders.filterFindFirst(
  listFolders: TFolderList; sfolder: string): TFolder;
var folder: TFolder;
  i: integer;
begin
  for i := 0 to listFolders.Count - 1 do begin
     folder := listFolders.Items(i);

     if (sfolder = folder.getOriginalPath()) then
     begin
       result:=folder;
     end;
  end;
  result:=nil;
end;

function TProcessFolders.process(sfolder: string): TFolderList;
var listFolders: TFolderList;
  folderOrder: TFolderOrder;
  vfu: TVisitFoldersUtil;
  listPreFile: TPreFileList;
  pf: TPreFile;
  folder, item, pathFather: TFolder;
  i, nlastIndex: integer;
  pathChild: string;
begin
  listFolders := TFolderList.Create;
  folderOrder := TFolderOrder.Create(-1, 0);
  WriteLn('Processing folders!\n');
  vfu := TVisitFoldersUtil.Create;
  listPreFile := vfu.getListFromFiles(sfolder);

  for i := 0 to listPreFile.Count - 1 do begin
     pf := listPreFile.Items(i);

     folder := self.createFolder(pf, folderOrder);
     listFolders.Add(folder);
  end;

  for i := 0 to listFolders.Count - 1 do begin
     item := listFolders.Items(i);

     nlastIndex := item.getOriginalPath().LastIndexOf(item.separatorFile);
     pathChild := copy(item.getOriginalPath(), 0, nlastIndex);

     pathFather := self.filterFindFirst(listFolders, pathChild);

     if (pathFather <> nil) then
     begin
	item.setParentCodFolder(pathFather.getOrder());
	item.setParentName(pathFather.getName());
	item.setParentPath(pathFather.getPath());
     end
     else
     begin
	item.setParentCodFolder(0);
	item.setParentName('');
	item.setParentPath('');
     end;

  end;

  result:=listFolders;
end;

function TProcessFolders.processFoldersToJson(sfolder: string): string;
var listFolders: TFolderList;
  folder: TFolder;
  i: integer;
  sres: string;
begin
  listFolders := self.process(sfolder);
  sres := '[ ';

  for i := 0 to listFolders.Count - 1 do begin
     folder := listFolders.Items(i);

     if i = 0 then
       sres := sres + folder.ToJSON
     else
       sres := sres + ', ' + folder.ToJSON;
  end;

  result:=sres;
end;

procedure TProcessFolders.processFoldersToFile(sdata: string; sfile: string);
var mFile: TextFile;
begin
  AssignFile(mFile, sfile);

  try
    append(mFile);
    write(mFile, sdata);
  finally
    CloseFile(mFile)
  end
end;

function TProcessFolders.processFoldersToInsert(
  sfolder: string; naba: integer): string;
var listFolders: TFolderList;
  folder: TFolder;
  i: integer;
  sres: string;
begin
  listFolders := self.process(sfolder);
  sres := '';

  for i := 0 to listFolders.Count - 1 do begin
     folder := listFolders.Items(i);

     sres := sres + folder.ToInsert(naba) + LineEnding;
  end;

  result:=sres
end;

function TProcessFolders.processFoldersToCSV(sfolder: string): string;
var listFolders: TFolderList;
  folder: TFolder;
  i: integer;
  sres: string;
begin
  listFolders := self.process(sfolder);
  sres := 'Code;Order;Name;Size;"Folder Type";"Formated Modified";Attributes;"Parent Code Folder";Path'
  + LineEnding;

  for i := 0 to listFolders.Count - 1 do begin
     folder := listFolders.Items(i);

     sres := sres + folder.ToCVS + LineEnding;
  end;

  result:=sres
end;

end.

