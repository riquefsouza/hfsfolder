program hfsfolder_pascal;

{$mode objfpc}{$H+}

uses
  {$IFDEF UNIX}{$IFDEF UseCThreads}
  cthreads,
  {$ENDIF}{$ENDIF}
  Classes, SysUtils, CustApp, FolderOrder, PreFile, Folder, VisitFoldersUtil,
  PreFileList, ProcessFolders, FolderList, StrUtils;

type

  { THFSFolder }

  THFSFolder = class(TCustomApplication)
  private
    processFolders: TProcessFolders;
    sfolder: string;
    tojson, tofile, toinsert, tocsv: boolean;
  protected
    procedure DoRun; override;
  public
    constructor Create(TheOwner: TComponent); override;
    destructor Destroy; override;
  end;

{ THFSFolder }

procedure THFSFolder.DoRun;
var i: integer;
  opt, sdata, soutFile: string;
  naba: integer;
  saba: string[3];
begin

  if ParamCount > 1 then
  begin
     for i := 1 to ParamCount do
     begin
       opt:=ParamStr(i);

       if not AnsiContainsStr(opt, '--') then
       begin
         sfolder:=opt;
       end;
       if AnsiContainsStr(opt, '--version') then
       begin
         WriteLn('hfsfolder 1.0');
       end;
       if AnsiContainsStr(opt, '--tojson') then
       begin
         tojson:=true;
       end;
       if AnsiContainsStr(opt, '--tofile') then
       begin
         tofile:=true;
       end;
       if AnsiContainsStr(opt, '--toinsert') then
       begin
         toinsert:=true;
       end;
       if AnsiContainsStr(opt, '--tocvs') then
       begin
         tocsv:=true;
       end;
     end;

     if sfolder.Length > 0 then
     begin
       sdata:='';
       soutFile:='hfsfolder';
       if tojson then
       begin
         soutFile := soutFile + '.json';
         sdata := processFolders.processFoldersToJson(sfolder);
       end;
       if toinsert then
       begin
         write('Inform tab number: ');
         Readln(saba);
         naba:=StrToInt(saba);
         soutFile := soutFile + '-insert.sql';
         sdata := processFolders.processFoldersToInsert(sfolder, naba);
       end;
       if tocsv then
       begin
         soutFile := soutFile + '.csv';
         sdata := processFolders.processFoldersToCSV(sfolder);
       end;
       if (tofile) and (sdata.Length > 0) then
       begin
         processFolders.processFoldersToFile(sdata, soutFile);
         WriteLn('Finish process folders!');
       end
       else if sdata.Length > 0 then
       begin
         WriteLn(sdata);
       end;
       if (not tojson) and (not toinsert) and (not tocsv) and (not tofile) then
       begin
         WriteLn('Inform option!');
       end;
     end
     else
     begin
       if (tojson) and (toinsert) and (tocsv) and (tofile) then
       begin
         WriteLn('Inform folder!');
       end;
     end;
  end
  else
  begin
    WriteLn('HFSFolder ' + LineEnding
    + 'Usage:' + LineEnding
    + '    hfsfolder_pascal /folder\n' + LineEnding
    + 'Options:' + LineEnding
    + '    --version' + LineEnding
    + '    --tojson' + LineEnding
    + '    --toinsert' + LineEnding
    + '    --tocvs' + LineEnding
    + '    --tofile\n' + LineEnding
    + 'Example:' + LineEnding
    + '    hfsfolder_pascal /folder --tojson --tofile --version');
  end;

  // stop program loop
  Terminate;
end;

constructor THFSFolder.Create(TheOwner: TComponent);
begin
  inherited Create(TheOwner);
  StopOnException:=True;
  processFolders:=TProcessFolders.Create;
  tojson := false;
  tofile := false;
  toinsert := false;
  tocsv := false;
end;

destructor THFSFolder.Destroy;
begin
  inherited Destroy;
  processFolders.Free;
end;

var
  Application: THFSFolder;
begin
  Application:=THFSFolder.Create(nil);
  Application.Title:='HFS Folder';
  Application.Run;
  Application.Free;
end.

