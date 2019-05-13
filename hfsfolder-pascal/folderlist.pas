unit FolderList;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, Folder;

Type
  TFolderList = class
  private
    { private declarations }
    FFolderList : TList;
  protected
    { protected declarations }
  public
    { public declarations }
    constructor Create;
    procedure Add(pFolder: TFolder);
    procedure Delete(Index: Integer);
    function Count: Integer;
    function Items(index: integer): TFolder;
    procedure Free;
    procedure Clear;
  published
    { published declarations }
  end;

implementation

constructor TFolderList.Create;
begin
  inherited Create;
  FFolderList := TList.Create;
end;

function TFolderList.Count: Integer;
begin
  Result := FFolderList.Count;
end;

procedure TFolderList.Add(pFolder: TFolder);
begin
  FFolderList.Add(pFolder);
end;

procedure TFolderList.Delete(Index: Integer);
begin
  FFolderList.Delete(Index)
end;

function TFolderList.Items(index: integer): TFolder;
begin
  result:=TFolder(FFolderList.Items[index]);
end;

procedure TFolderList.Free;
begin
  FFolderList.Free;
end;

procedure TFolderList.Clear;
begin
  FFolderList.Clear;
end;

end.

