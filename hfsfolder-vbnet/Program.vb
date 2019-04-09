'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 08/04/2019
' * Time: 12:20
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 
Imports HfsFolder
	
	
Module Program
	''' <summary>
	''' Program entry point.
	''' </summary>
	<STAThread> _
	Sub Main(args As String())
		Dim folder As String = ""
			Dim tojson As Boolean = False, tofile As Boolean = False, toinsert As Boolean = False, tocvs As Boolean = False

			If args.Length > 0 Then

				For Each opt As String In args
					If Not opt.Contains("--") Then
						folder = opt
					End If
					If opt.Contains("--version") Then
						Console.WriteLine("hfsfolder 1.0")
					End If
					If opt.Contains("--tojson") Then
						tojson = True
					End If
					If opt.Contains("--tofile") Then
						tofile = True
					End If
					If opt.Contains("--toinsert") Then
						toinsert = True
					End If
					If opt.Contains("--tocvs") Then
						tocvs = True
					End If
				Next

				If folder.Length > 0 Then
					Dim data As String = "", outFile As String = "hfsfolder"
					If tojson Then
						outFile += ".json"
						data = ProcessFolders.processFoldersToJson(folder)
					End If
					If toinsert Then
						Console.Write("Inform tab number: ")
						Dim naba As Integer = Convert.ToInt32(Console.ReadLine())
						outFile += "-insert.sql"
						data = ProcessFolders.processFoldersToInsert(folder, naba)
					End If
					If tocvs Then
						outFile += ".csv"
						data = ProcessFolders.processFoldersToCSV(folder)
					End If

					If tofile AndAlso data.Length > 0 Then
						ProcessFolders.processFoldersToFile(data, outFile)
						Console.WriteLine("Finish process folders!")
					ElseIf data.Length > 0 Then
						Console.WriteLine(data)
					End If

					If Not tojson AndAlso Not toinsert AndAlso Not tocvs AndAlso Not tofile Then
						Console.WriteLine("Inform option!")
					End If
				Else
					If tojson OrElse toinsert OrElse tocvs OrElse tofile Then
						Console.WriteLine("Inform folder!")
					End If
				End If
			Else
				Console.WriteLine("HFSFolder " & vbLf & "Usage:" & vbLf & "    dotnet run /folder" & vbLf & vbLf & 
					"Options:" & vbLf & "    --version" & vbLf & "    --tojson" & vbLf & "    --toinsert" & vbLf & 
					"    --tocvs" & vbLf & "    --tofile" & vbLf & vbLf & "Example:" & vbLf & 
					"    dotnet run /folder --tojson --tofile --version" & vbLf)
			End If

		End Sub
End Module
