'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 08/04/2019
' * Time: 14:09
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Imports System.IO
Imports System.Collections.Generic
Imports HfsFolder.Model

Namespace HfsFolder.Util
	''' <summary>
	''' Description of VisitFoldersUtil.
	''' </summary>
	Public Class VisitFoldersUtil
		Public Shared Function getListFromFiles(folder As [String]) As List(Of PreFile)
			Dim lst As New List(Of PreFile)()
			Dim dir As New DirectoryInfo(folder)
			lst.Add(attributesToPreFile(dir))
			TraverseDirs(lst, dir)
			Return lst
		End Function

		Private Shared Function FormatDecimal(valor As Decimal) As String
			Return valor.ToString("#,##0.00")
		End Function

		Private Shared Function MountBigSize(nTam As Decimal) As String
			Dim nUmKilo As Decimal, nUmMega As Decimal, nUmGiga As Decimal, nUmTera As Decimal, nUmPeta As Decimal
			Dim nTamLocal As Decimal

			nUmKilo = 1024
			nUmMega = nUmKilo * 1024
			nUmGiga = nUmMega * 1024
			nUmTera = nUmGiga * 1024
			nUmPeta = nUmTera * 1024

			If nTam.CompareTo(nUmKilo) = -1 Then
				nTamLocal = nTam
				Return FormatDecimal(nTamLocal) & " Byte(s)"
			ElseIf nTam.CompareTo(nUmKilo) = 1 AndAlso nTam.CompareTo(nUmMega) = -1 Then
				nTamLocal = nTam / nUmKilo
				Return FormatDecimal(nTamLocal) & " KByte(s)"
			ElseIf nTam.CompareTo(nUmMega) = 1 AndAlso nTam.CompareTo(nUmGiga) = -1 Then
				nTamLocal = nTam / nUmMega
				Return FormatDecimal(nTamLocal) & " MByte(s)"
			ElseIf nTam.CompareTo(nUmGiga) = 1 AndAlso nTam.CompareTo(nUmTera) = -1 Then
				nTamLocal = nTam / nUmGiga
				Return FormatDecimal(nTamLocal) & " GByte(s)"
			ElseIf nTam.CompareTo(nUmTera) = 1 AndAlso nTam.CompareTo(nUmPeta) = -1 Then
				nTamLocal = nTam / nUmTera
				Return FormatDecimal(nTamLocal) & " TByte(s)"
			Else
				nTamLocal = nTam / nUmPeta
				Return FormatDecimal(nTamLocal) & " PByte(s)"
			End If
		End Function

		Private Shared Function attributesToPreFile(dir As DirectoryInfo) As PreFile
			Dim pf As New PreFile()
			Dim sAtributos As String = ""
			Dim sName As String = dir.Name.Replace("'", "''")
			pf.setName(sName)
			pf.setSize(0)
			pf.setModified(dir.LastWriteTime)

			sAtributos += "[DIR]"

			If dir.Attributes = FileAttributes.Hidden Then
				sAtributos += "[HID]"
			End If
			If dir.Attributes = FileAttributes.System Then
				sAtributos += "[SYS]"
			End If

			pf.setAttributes(sAtributos)
			pf.setOriginalPath(dir.FullName)
			pf.setDirectory(True)
			pf.setFormatedSize(MountBigSize(pf.getSize()))
			pf.setFormatedModified(pf.getModified().ToString("dd/MM/yyyy hh:mm:ss"))

			Return pf
		End Function

		Private Shared Function attributesToPreFile(file As FileInfo) As PreFile
			Dim pf As New PreFile()
			Dim sAtributos As String = ""
			Dim sName As String = file.Name.Replace("'", "''")
			pf.setName(sName)
			pf.setSize(file.Length)
			pf.setModified(file.LastWriteTime)

			sAtributos += "[ARQ]"

			If file.IsReadOnly Then
				sAtributos += "[ROL]"
			End If
			If file.Attributes = FileAttributes.Hidden Then
				sAtributos += "[HID]"
			End If
			If file.Attributes = FileAttributes.System Then
				sAtributos += "[SYS]"
			End If

			pf.setAttributes(sAtributos)
			pf.setOriginalPath(file.FullName)
			pf.setDirectory(False)
			pf.setFormatedSize(MountBigSize(pf.getSize()))
			pf.setFormatedModified(pf.getModified().ToString("dd/MM/yyyy hh:mm:ss"))

			Return pf
		End Function

		Private Shared Sub TraverseDirs(lst As List(Of PreFile), dir As DirectoryInfo)
			Try
				For Each iInfo As DirectoryInfo In dir.GetDirectories()
					'if (iInfo.Name.EndsWith(fileSufix)){
					lst.Add(attributesToPreFile(iInfo))
					'}
					TraverseDirs(lst, iInfo)
				Next
			Catch generatedExceptionName As Exception
			End Try

			Try
				For Each iInfo As FileInfo In dir.GetFiles()
					'if (iInfo.Name.EndsWith(fileSufix)){
						'}
					lst.Add(attributesToPreFile(iInfo))
				Next
			Catch generatedExceptionName As Exception
			End Try
		End Sub
	End Class
End Namespace
