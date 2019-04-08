/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 08/04/2019
 * Time: 14:04
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;

namespace hfsfolder.model
{
	/// <summary>
	/// Description of Folder.
	/// </summary>
	public class Folder : PreFile, IComparable
	{
		private int code;
	
		private int order;
	
		private int parentCodFolder;
	
		private char folderType;
	
		private string path;
	
		private string parentName;
	
		private string parentPath;
			
		public Folder(PreFile preFile) : 
			base(preFile.getName(), preFile.getSize(), preFile.getModified(), preFile.getAttributes(),
		         preFile.getFormatedSize(), preFile.getFormatedModified()) {
		}
	
		public int getCode() {
			return code;
		}
	
		public void setCode(int code) {
			this.code = code;
		}
	
		public int getOrder() {
			return order;
		}
	
		public void setOrder(int order) {
			this.order = order;
		}
	
		public int getParentCodFolder() {
			return parentCodFolder;
		}
	
		public void setParentCodFolder(int parentCodFolder) {
			this.parentCodFolder = parentCodFolder;
		}
	
		public char getFolderType() {
			return folderType;
		}
	
		public void setFolderType(char folderType) {
			this.folderType = folderType;
		}
	
		public string getPath() {
			return path;
		}
	
		public void setPath(string path) {
			this.path = path;
		}
	
		public string getParentName() {
			return parentName;
		}
	
		public void setParentName(string parentName) {
			this.parentName = parentName;
		}
	
		public string getParentPath() {
			return parentPath;
		}
	
		public void setParentPath(string parentPath) {
			this.parentPath = parentPath;
		}
	
		public override void limparDados() {
			base.limparDados();
			this.code = 0;
			this.order = 0;
			this.parentCodFolder = 0;
			this.folderType = 'A';
			this.path = "";
			this.parentName = "";
			this.parentPath = "";			
		}
	
		public override string ToString() {
			return "Folder [codigo=" + code + ", ordem=" + order + ", codDirPai=" + parentCodFolder + ", tipo=" + folderType
					+ ", caminho=" + path + ", nomePai=" + parentName + ", caminhoPai=" + parentPath + "]";
		}
	
		public string ToInsert(int naba) {
			return "INSERT INTO Diretorios(aba, cod, ordem, nome, tam, tipo, modificado, atributos, coddirpai, caminho) VALUES("
				+ naba.ToString() + "," + code + "," + order + ",'" + getName() + "'," + getSize() + ",'" + folderType + "','"
					+ getFormatedModified() + "','" + getAttributes() + "'," + parentCodFolder + ",'" + getPath()
					+ "');";
		}
	
		public override string ToCVS() {
			return code + ";" + order + ";" + getName() + ";" + getSize() + ";" + folderType + ";" 
					+ getFormatedModified() + ";" + getAttributes() + ";" + parentCodFolder + ";" + getPath(); 
		}

		public String ToJSON() {
			return "{\n  \"name\" : \"" + getName() + "\"," +
				  "\n  \"size\" : " + getSize() + "," +
				  "\n  \"modified\" : " + getModified() + "," +
				  "\n  \"attributes\" : \"" + getAttributes() + "\"," +
				  "\n  \"formatedSize\" : \"" + getFormatedSize() + "\"," +
				  "\n  \"formatedModified\" : \"" + getFormatedModified() + "\"," +
				  "\n  \"code\" : " + code + "," +
				  "\n  \"order\" : " + order + "," +
				  "\n  \"parentCodFolder\" : " + parentCodFolder + "," +
				  "\n  \"folderType\" : \"" + folderType + "\"," +
				  "\n  \"path\" : \"" + path + "\"," +
				  "\n  \"parentName\" : \"" + parentName + "\"," +
				  "\n  \"parentPath\" : \"" + parentPath + "\"," +
				  "\n  \"originalPath\" : \"" + getOriginalPath() + "\"\n}";
		}
		
        public int CompareTo(object obj)
        {
            var otherFolder = obj as Folder;

            if(otherFolder == null)
            {
                return -1;
            }

            return path.CompareTo(otherFolder.getPath());
        }
		
	}
}
