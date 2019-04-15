#
# * User: henrique.souza
# * Date: 08/04/2019
# * Time: 13:52

class FolderOrder

  def initialize(codFolder, order)
    @codFolder = codFolder
    @order = order
  end

  def getCodFolder
    @codFolder
  end

  def setCodFolder(codFolder)
    @codFolder = codFolder
  end

  def getOrder
    @order
  end

  def setOrder(order)
    @order = order
  end
end
