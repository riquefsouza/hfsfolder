unit PreFileList;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, PreFile;

Type
  TPreFileList = class
  private
    { private declarations }
    FPreFileList : TList;
  protected
    { protected declarations }
  public
    { public declarations }
    constructor Create;
    procedure Add(pPreFile: TPreFile);
    procedure Delete(Index: Integer);
    function Count: Integer;
    function Items(index: integer): TPreFile;
    procedure Free;
    procedure Clear;
  published
    { published declarations }
  end;

implementation

constructor TPreFileList.Create;
begin
  inherited Create;
  FPreFileList := TList.Create;
end;

function TPreFileList.Count: Integer;
begin
  Result := FPreFileList.Count;
end;

procedure TPreFileList.Add(pPreFile: TPreFile);
begin
  FPreFileList.Add(pPreFile);
end;

procedure TPreFileList.Delete(Index: Integer);
begin
  FPreFileList.Delete(Index)
end;

function TPreFileList.Items(index: integer): TPreFile;
begin
  result:=TPreFile(FPreFileList.Items[index]);
end;

procedure TPreFileList.Free;
begin
  FPreFileList.Free;
end;

procedure TPreFileList.Clear;
begin
  FPreFileList.Clear;
end;

end.

