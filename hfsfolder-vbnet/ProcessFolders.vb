'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 08/04/2019
' * Time: 14:52
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.IO
Imports System.Text
Imports System.Text.RegularExpressions
Imports System.Collections.Generic
Imports HfsFolder.Model
Imports HfsFolder.Util

Namespace HfsFolder
	''' <summary>
	''' Description of ProcessFolders.
	''' </summary>
	Public Class ProcessFolders

		Private Shared Function createFolder(pf As PreFile, folderOrder As FolderOrder) As Folder
			Dim folder As New Folder(pf)

			If pf.isDirectory() Then
				folder.setFolderType("D"C)
			Else
				folder.setFolderType("A"C)
			End If

			Dim sPath As String = pf.getOriginalPath()

			If Regex.IsMatch(sPath, "[a-zA-Z]:\\") Then
				sPath = sPath.Substring(3)
				folder.separatorChar = "\"C
			End If

			If Regex.IsMatch(sPath, "[a-zA-Z]:/") Then
				sPath = sPath.Substring(3)
				folder.separatorChar = "/"C
			End If

			If sPath.StartsWith("/") Then
				sPath = sPath.Substring(1)
				folder.separatorChar = "/"C
			End If

			folder.setPath(sPath.Replace("'", "''").Replace("\", "/"))
			folder.setOriginalPath(pf.getOriginalPath())

			If Not folder.getPath().Contains("/") Then
				folderOrder.setCodFolder(folderOrder.getCodFolder() + 1)
				folderOrder.setOrder(1)
			Else
				folderOrder.setOrder(folderOrder.getOrder() + 1)
			End If

			folder.setCode(folderOrder.getCodFolder())
			folder.setOrder(folderOrder.getOrder())

			Return folder
		End Function

		Private Shared Function process(folder As String) As List(Of Folder)
			Dim listaFolders As New List(Of Folder)()
			Dim dir As Folder
			Dim folderOrder As New FolderOrder(-1, 0)

			Console.WriteLine("Processing folders!")

			Dim listaPrefiles As List(Of PreFile) = VisitFoldersUtil.getListFromFiles(folder)

			For Each pf As PreFile In listaPrefiles
				dir = ProcessFolders.createFolder(pf, folderOrder)
				listaFolders.Add(dir)
			Next

			For Each item As Folder In listaFolders

				Dim pathChild As String = item.getOriginalPath().Substring(0, item.getOriginalPath().LastIndexOf(item.separatorChar))

				Dim pathFather As Folder = listaFolders.Find(Function(f) f.getOriginalPath().Equals(pathChild))

				If pathFather IsNot Nothing Then
					item.setParentCodFolder(pathFather.getOrder())
					item.setParentName(pathFather.getName())
					item.setParentPath(pathFather.getPath())
				End If
			Next

			listaFolders.Sort()

			Return listaFolders
		End Function

		Public Shared Function processFoldersToJson(folder As String) As String
			Dim lista As List(Of Folder) = process(folder)
			Dim item As Folder
			Dim result As String = "[ "

			For i As Integer = 0 To lista.Count - 1
				item = lista(i)

				If i = 0 Then
					result += item.ToJSON()
				Else
					result += ", " & item.ToJSON()
				End If
			Next

			Return result & " ]"

		End Function

		Public Shared Sub processFoldersToFile(data As String, sfile As String)
			Dim fileStream As FileStream = Nothing
			Try
				fileStream = New FileStream(sfile, FileMode.OpenOrCreate, FileAccess.Write)
				fileStream.Write(Encoding.[Default].GetBytes(data), 0, data.Length)
				fileStream.Flush()
			Catch ioEx As FileNotFoundException
				Console.WriteLine(ioEx.Message)
			Finally
				If fileStream IsNot Nothing Then
					fileStream.Close()
				End If
			End Try
		End Sub

		Public Shared Function processFoldersToInsert(folder As String, naba As Integer) As [String]
			Dim lista As List(Of Folder) = process(folder)
			Dim result As String = ""

			For Each item As Folder In lista
				result += item.ToInsert(naba) & vbLf
			Next

			Return result
		End Function

		Public Shared Function processFoldersToCSV(folder As String) As String
			Dim lista As List(Of Folder) = process(folder)
			Dim result As String = "Code;Order;Name;Size;""Folder Type"";""Formated Modified"";Attributes;""Parent Code Folder"";Path" & vbLf

			For Each item As Folder In lista
				result += item.ToCVS() & vbLf
			Next

			Return result
		End Function


	End Class
End Namespace
