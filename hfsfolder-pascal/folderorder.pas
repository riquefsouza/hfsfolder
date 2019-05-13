unit FolderOrder;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils;

type
  TFolderOrder = class
  private
    codFolder: integer;
    order: integer;
  public
    constructor Create(ncodFolder: integer; norder: integer);
    constructor Create(folderOrder: TFolderOrder);
    destructor Destroy; override;

    function getCodFolder(): integer;
    procedure setCodFolder(ncodFolder: integer);
    function getOrder(): integer;
    procedure setOrder(norder: integer);
  end;

implementation

constructor TFolderOrder.Create(ncodFolder: integer; norder: integer);
begin
  inherited Create;
  self.codFolder:=ncodFolder;
  self.order:=norder;
end;

constructor TFolderOrder.Create(folderOrder: TFolderOrder);
begin
  inherited Create;
  self.codFolder:=folderOrder.getCodFolder();
  self.order:=folderOrder.getOrder();
end;

destructor TFolderOrder.Destroy;
begin
  inherited Destroy;
end;

function TFolderOrder.getCodFolder(): integer;
begin
    result:=self.codFolder;
end;

procedure TFolderOrder.setCodFolder(ncodFolder: integer);
begin
   self.codFolder := ncodFolder;
end;

function TFolderOrder.getOrder(): integer;
begin
  result:=self.order;
end;

procedure TFolderOrder.setOrder(norder: integer);
begin
  self.order := norder;
end;


end.

