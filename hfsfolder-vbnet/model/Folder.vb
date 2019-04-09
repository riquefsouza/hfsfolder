'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 08/04/2019
' * Time: 14:04
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Namespace HfsFolder.Model
	''' <summary>
	''' Description of Folder.
	''' </summary>
	Public Class Folder
		Inherits PreFile
		Implements IComparable
		
		Private code As Integer

		Private order As Integer

		Private parentCodFolder As Integer

		Private folderType As Char

		Private path As String

		Private parentName As String

		Private parentPath As String

		Public Sub New(preFile As PreFile)
			MyBase.New(preFile.getName(), preFile.getSize(), preFile.getModified(), preFile.getAttributes(), preFile.getFormatedSize(), preFile.getFormatedModified())
		End Sub

		Public Function getCode() As Integer
			Return code
		End Function

		Public Sub setCode(code As Integer)
			Me.code = code
		End Sub

		Public Function getOrder() As Integer
			Return order
		End Function

		Public Sub setOrder(order As Integer)
			Me.order = order
		End Sub

		Public Function getParentCodFolder() As Integer
			Return parentCodFolder
		End Function

		Public Sub setParentCodFolder(parentCodFolder As Integer)
			Me.parentCodFolder = parentCodFolder
		End Sub

		Public Function getFolderType() As Char
			Return folderType
		End Function

		Public Sub setFolderType(folderType As Char)
			Me.folderType = folderType
		End Sub

		Public Function getPath() As String
			Return path
		End Function

		Public Sub setPath(path As String)
			Me.path = path
		End Sub

		Public Function getParentName() As String
			Return parentName
		End Function

		Public Sub setParentName(parentName As String)
			Me.parentName = parentName
		End Sub

		Public Function getParentPath() As String
			Return parentPath
		End Function

		Public Sub setParentPath(parentPath As String)
			Me.parentPath = parentPath
		End Sub

		Public Overrides Sub limparDados()
			MyBase.limparDados()
			Me.code = 0
			Me.order = 0
			Me.parentCodFolder = 0
			Me.folderType = "A"C
			Me.path = ""
			Me.parentName = ""
			Me.parentPath = ""
		End Sub

		Public Overrides Function ToString() As String
			Return "Folder [codigo=" & code & ", ordem=" & order & ", codDirPai=" & parentCodFolder & ", tipo=" & folderType & ", caminho=" & path & ", nomePai=" & parentName & ", caminhoPai=" & parentPath & "]"
		End Function

		Public Overloads Function ToInsert(naba As Integer) As String
			Return "INSERT INTO Diretorios(aba, cod, ordem, nome, tam, tipo, modificado, atributos, coddirpai, caminho) VALUES(" & naba.ToString() & "," & code & "," & order & ",'" & getName() & "'," & getSize() & ",'" & folderType & "','" & getFormatedModified() & "','" & getAttributes() & "'," & parentCodFolder & ",'" & getPath() & "');"
		End Function

		Public Overrides Function ToCVS() As String
			Return code & ";" & order & ";" & getName() & ";" & getSize() & ";" & folderType & ";" & getFormatedModified() & ";" & getAttributes() & ";" & parentCodFolder & ";" & getPath()
		End Function

		Public Function ToJSON() As [String]
			Return "{" & vbLf & "  ""name"" : """ & getName() & """," & vbLf & "  ""size"" : " & getSize() & "," & vbLf & "  ""modified"" : " & getModified() & "," & vbLf & "  ""attributes"" : """ & getAttributes() & """," & vbLf & "  ""formatedSize"" : """ & getFormatedSize() & """," & vbLf & "  ""formatedModified"" : """ & getFormatedModified() & """," & vbLf & "  ""code"" : " & code & "," & vbLf & "  ""order"" : " & order & "," & vbLf & "  ""parentCodFolder"" : " & parentCodFolder & "," & vbLf & "  ""folderType"" : """ & folderType & """," & vbLf & "  ""path"" : """ & path & """," & vbLf & "  ""parentName"" : """ & parentName & """," & vbLf & "  ""parentPath"" : """ & parentPath & """," & vbLf & "  ""originalPath"" : """ & getOriginalPath() & """" & vbLf & "}"
		End Function

		Public Function CompareTo(obj As Object) As Integer Implements IComparable.CompareTo
			Dim otherFolder As Folder = TryCast(obj, Folder)

			If otherFolder Is Nothing Then
				Return -1
			End If

			Return path.CompareTo(otherFolder.getPath())
		End Function

	End Class
End Namespace
