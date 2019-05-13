unit VisitFoldersUtil;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, StrUtils, FileUtil, PreFile, PreFileList;

type
  TVisitFoldersUtil = class
  private
    listPreFile: TPreFileList;
    separatorFile: char;

    function mountBigSize(nTam: Int64): String;
    function mountSize(nTam: Extended): String;
    function ToAttributes(npAtributos: integer): String;
    function ToPreFile(sfile: string; SearchRec: TSearchRec): TPreFile;
  public
    constructor Create;
    destructor Destroy; override;
    function getListFromFiles(sdir: String): TPreFileList;
  end;

implementation

constructor TVisitFoldersUtil.Create;
begin
  inherited Create;
  separatorFile := DirectorySeparator;
  listPreFile:=TPreFileList.Create;
end;

destructor TVisitFoldersUtil.Destroy;
begin
  listPreFile.Free;

  inherited Destroy;
end;

function TVisitFoldersUtil.mountBigSize(nTam: Int64): String;
begin
  if nTam > 0 then begin
    result:=mountSize(nTam);
  end else
    result:='';
end;

function TVisitFoldersUtil.mountSize(nTam: Extended): String;
var
  nUmKilo, nUmMega, nUmGiga, nUmTera, nUmPeta: Extended;
begin
  nUmKilo := 1024;
  nUmMega := nUmKilo * 1024;
  nUmGiga := nUmMega * 1024;
  nUmTera := nUmGiga * 1024;
  nUmPeta := nUmTera * 1024;

  if (nTam < nUmKilo) then
  begin
    Result := FormatFloat('#,##0.00', nTam) + ' Byte(s)';
  end
  else if (nTam > nUmKilo) and (nTam < nUmMega) then
  begin
    nTam:=nTam / nUmKilo;
    Result := FormatFloat('#,##0.00', nTam) + ' KByte(s)';
  end
  else if (nTam > nUmMega) and (nTam < nUmGiga) then
  begin
    nTam:=nTam / nUmMega;
    Result := FormatFloat('#,##0.00', nTam) + ' MByte(s)';
  end
  else if (nTam > nUmGiga) and (nTam < nUmTera) then
  begin
    nTam:=nTam / nUmGiga;
    Result := FormatFloat('#,##0.00', nTam) + ' GByte(s)';
  end
  else if (nTam > nUmTera) and (nTam < nUmPeta) then
  begin
    nTam := nTam / nUmTera;
    Result := FormatFloat('#,##0.00', nTam) + ' TByte(s)';
  end
  else
  begin
    nTam := nTam / nUmPeta;
    Result := FormatFloat('#,##0.00', nTam) + ' PByte(s)';
  end;
end;

function TVisitFoldersUtil.ToAttributes(npAtributos: integer): String;
var sAtributos: string;
begin
  sAtributos:='';
  if (npAtributos and SysUtils.faReadOnly > 0) then sAtributos:=sAtributos+'[ROL]';
  if (npAtributos and SysUtils.faHidden > 0) then sAtributos:=sAtributos+'[HID]';
  if (npAtributos and SysUtils.faSysFile > 0) then sAtributos:=sAtributos+'[SYS]';
  //if (npAtributos and SysUtils.faVolumeID > 0) then sAtributos:=sAtributos+'[VOL]';
  if (npAtributos and SysUtils.faDirectory > 0) then sAtributos:=sAtributos+'[DIR]';
  if (npAtributos and SysUtils.faArchive > 0) then sAtributos:=sAtributos+'[ARQ]';
  //if (npAtributos and SysUtils.faAnyFile > 0) then sAtributos:=sAtributos+'[Q]';
  result:=sAtributos;
end;

function TVisitFoldersUtil.ToPreFile(sfile: string; SearchRec: TSearchRec): TPreFile;
var
  prefile: TPreFile;
  sname: string;
begin
  prefile:=TPreFile.Create;
  sname:=ReplaceStr(SearchRec.Name, '''', '''''');
  prefile.setName(sname);
  prefile.setSize(SearchRec.Size);
  prefile.setModified(FileDateToDateTime(SearchRec.Time));
  prefile.setAttributes(ToAttributes(SearchRec.Attr));
  prefile.setOriginalPath(sfile);
  prefile.setFormatedSize(self.mountBigSize(prefile.getSize()));
  prefile.setFormatedModified(FormatDateTime('dd/mm/yyyy hh:nn:ss', prefile.getModified()));

  if FileExists(sfile) then
  begin
    prefile.directory:=false;
  end else if DirectoryExists(sfile) then
  begin
    prefile.directory:=true;
  end;

  result:=prefile;
end;

function TVisitFoldersUtil.getListFromFiles(sdir: String): TPreFileList;
var SearchRec : TSearchRec;
  sfile: string;
  prefile: TPreFile;
begin
  sfile:=sdir+DirectorySeparator+'*.*';
  if FindFirst(sfile, faAnyFile, SearchRec) = 0 then
  begin

    if (SearchRec.Name<>'.') and (SearchRec.Name<>'..') then
    begin
      sfile:=sdir+DirectorySeparator+SearchRec.Name;
      prefile:=self.ToPreFile(sfile, SearchRec);
      listPreFile.Add(prefile);
    end;

    while FindNext(SearchRec) = 0 do
    begin

      if (SearchRec.Name<>'.') and (SearchRec.Name<>'..') then
      begin
        sfile:=sdir+DirectorySeparator+SearchRec.Name;
        prefile:=self.ToPreFile(sfile, SearchRec);
        listPreFile.Add(prefile);

        if DirectoryExists(sfile) then
        begin
          self.getListFromFiles(sfile);
        end;
      end;

    end;
  end;
  FindClose(SearchRec);

  result:=listPreFile;
end;

end.

