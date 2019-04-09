'
' * Created by SharpDevelop.
' * User: henrique.souza
' * Date: 08/04/2019
' * Time: 13:52
' * 
' * To change this template use Tools | Options | Coding | Edit Standard Headers.
' 

Namespace HfsFolder.Model
	''' <summary>
	''' Description of FolderOrder.
	''' </summary>
	Public Class FolderOrder
		
		Private codFolder As Integer

		Private order As Integer

		Public Sub New(codFolder As Integer, order As Integer)
			Me.codFolder = codFolder
			Me.order = order
		End Sub

		Public Sub New(folderOrder1 As FolderOrder)
			Me.codFolder = folderOrder1.getCodFolder()
			Me.order = folderOrder1.getOrder()
		End Sub

		Public Function getCodFolder() As Integer
			Return codFolder
		End Function

		Public Sub setCodFolder(codFolder As Integer)
			Me.codFolder = codFolder
		End Sub

		Public Function getOrder() As Integer
			Return order
		End Function

		Public Sub setOrder(order As Integer)
			Me.order = order
		End Sub

	End Class
End Namespace
