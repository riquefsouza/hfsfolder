# 
# * Created by SharpDevelop.
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 13:52
# *
# * To change this template use Tools | Options | Coding | Edit Standard Headers.
# 
require "mscorlib"
require "System, Version=2.0.0.0, Culture=neutral, PublicKeyToken=b03f5f7f11d50a3a"

module hfsfolder.model
	# <summary>
	# Description of FolderOrder.
	# </summary>
	class FolderOrder
		def initialize(folderOrder)
			self.@codFolder = folderOrder.getCodFolder()
			self.@order = folderOrder.getOrder()
		end

		def initialize(folderOrder)
			self.@codFolder = folderOrder.getCodFolder()
			self.@order = folderOrder.getOrder()
		end

		def getCodFolder()
			return @codFolder
		end

		def setCodFolder(codFolder)
			self.@codFolder = codFolder
		end

		def getOrder()
			return @order
		end

		def setOrder(order)
			self.@order = order
		end
	end
end