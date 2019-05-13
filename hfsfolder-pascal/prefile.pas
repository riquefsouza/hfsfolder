unit PreFile;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils;

type
  TPreFile = class
  private
    name: string;
    size: int64;
    modified: tdatetime;
    attributes: String;
    formatedSize: String;
    formatedModified: String;
    originalPath: string;
  public
    directory: boolean;

    constructor Create;
    destructor Destroy; override;

    function getName(): String;
    procedure setName(sname: String);
    function getSize(): int64;
    procedure setSize(nsize: int64);
    function getModified(): tdatetime;
    procedure setModified(dmodified: tdatetime);
    function getAttributes(): String;
    procedure setAttributes(sattributes: String);
    function getFormatedSize(): String;
    procedure setFormatedSize(sformatedSize: String);
    function getFormatedModified(): String;
    procedure setFormatedModified(sformatedModified: String);
    function getOriginalPath(): String;
    procedure setOriginalPath(soriginalPath: String);

    procedure limparDados;
    function ToString: ansistring; override;
    function ToInsert: string;
    function ToCVS: string;
  end;

implementation

constructor TPreFile.Create;
begin
  inherited Create;
end;

destructor TPreFile.Destroy;
begin
  inherited Destroy;
end;

function TPreFile.getName(): String;
begin
  result:=self.name;
end;

procedure TPreFile.setName(sname: String);
begin
self.name := sname;
end;

function TPreFile.getSize(): int64;
begin
  result:=self.size;
end;

procedure TPreFile.setSize(nsize: int64);
begin
self.size:=nsize;
end;

function TPreFile.getModified(): tdatetime;
begin
  result:=self.modified;
end;

procedure TPreFile.setModified(dmodified: tdatetime);
begin
  self.modified:=dmodified;
end;

function TPreFile.getAttributes(): String;
begin
  result:=self.attributes;
end;

procedure TPreFile.setAttributes(sattributes: String);
begin
self.attributes:=sattributes;
end;

function TPreFile.getFormatedSize(): String;
begin
  result:=self.formatedSize;
end;

procedure TPreFile.setFormatedSize(sformatedSize: String);
begin
self.formatedSize:=sformatedSize;
end;

function TPreFile.getFormatedModified(): String;
begin
  result:=self.formatedModified;
end;

procedure TPreFile.setFormatedModified(sformatedModified: String);
begin
  self.formatedModified:=sformatedModified;
end;

function TPreFile.getOriginalPath(): String;
begin
   result:=self.originalPath;
end;

procedure TPreFile.setOriginalPath(soriginalPath: String);
begin
 self.originalPath:=soriginalPath;
end;

procedure TPreFile.limparDados;
begin
  self.name := '';
  self.size := 0;
  self.modified := Now;
  self.attributes := '';
  self.formatedSize := '';
  self.formatedModified := '';
  self.originalPath := '';
end;

function TPreFile.ToString: ansistring;
begin
  inherited ToString;

  result:='PreFile [name=' + name + ', size=' + IntToStr(size) +
  ', modified=' + DateToStr(modified) + ', attributes=' + attributes +
  ', formatSize=' + formatedSize +
  ', formatModified=' + formatedModified + ']';

end;

function TPreFile.ToInsert: string;
begin
  result:=QuotedStr(name) + ',' + IntToStr(size) + ',' +
  QuotedStr(formatedModified) + ',' + QuotedStr(attributes);
end;

function TPreFile.ToCVS: string;
begin
  result:=name + ';' + IntToStr(size) + ';' +
  formatedModified + ';' + attributes;
end;

end.

