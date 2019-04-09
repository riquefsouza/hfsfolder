'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 08/04/2019
' * Time: 14:00
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Namespace HfsFolder.Model
	''' <summary>
	''' Description of PreFile.
	''' </summary>
	Public Class PreFile
		Private name As String

		Private size As Long

		Private modified As DateTime

		Private attributes As String

		Private formatedSize As String

		Private formatedModified As String

		Private originalPath As String

		Private directory As Boolean

		Public separatorChar As Char

		Public Sub New()
		End Sub

		Public Sub New(name As String, size As Long, modified As DateTime, attributes As String, formatSize As String, formatModified As String)
			Me.name = name
			Me.size = size
			Me.modified = modified
			Me.attributes = attributes
			Me.formatedSize = formatSize
			Me.formatedModified = formatModified
		End Sub

		Public Function getName() As String
			Return name
		End Function

		Public Sub setName(name As String)
			Me.name = name
		End Sub

		Public Function getSize() As Long
			Return size
		End Function

		Public Sub setSize(size As Long)
			Me.size = size
		End Sub

		Public Function getModified() As DateTime
			Return modified
		End Function

		Public Sub setModified(modified As DateTime)
			Me.modified = modified
		End Sub

		Public Function getAttributes() As String
			Return attributes
		End Function

		Public Sub setAttributes(attributes As String)
			Me.attributes = attributes
		End Sub

		Public Function getFormatedSize() As String
			Return formatedSize
		End Function

		Public Sub setFormatedSize(formatedSize As String)
			Me.formatedSize = formatedSize
		End Sub

		Public Function getFormatedModified() As String
			Return formatedModified
		End Function

		Public Sub setFormatedModified(formatedModified As String)
			Me.formatedModified = formatedModified
		End Sub

		Public Function getOriginalPath() As String
			Return originalPath
		End Function

		Public Sub setOriginalPath(originalPath As String)
			Me.originalPath = originalPath
		End Sub

		Public Function isDirectory() As Boolean
			Return directory
		End Function

		Public Sub setDirectory(directory As Boolean)
			Me.directory = directory
		End Sub

		Public Overridable Sub limparDados()
			Me.name = ""
			Me.size = 0
			Me.modified = DateTime.Now
			Me.attributes = ""
			Me.formatedSize = ""
			Me.formatedModified = ""
			Me.originalPath = ""
			Me.directory = False
		End Sub

		Public Overrides Function ToString() As String
			Return "PreFile [name=" & name & ", size=" & size & ", modified=" & modified & ", attributes=" & attributes & ", formatSize=" & formatedSize & ", formatModified=" & formatedModified & "]"
		End Function

		Public Function ToInsert() As String
			Return "'" & getName() & "'," & size & ",'" & formatedModified & "','" & attributes & "'"
		End Function

		Public Overridable Function ToCVS() As String
			Return getName() & ";" & size & ";" & formatedModified & ";" & attributes
		End Function

	End Class
End Namespace
