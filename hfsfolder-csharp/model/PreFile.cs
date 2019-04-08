/*
 * Created by SharpDevelop.
 * User: henrique.souza
 * Date: 08/04/2019
 * Time: 14:00
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
using System;

namespace hfsfolder.model
{
	/// <summary>
	/// Description of PreFile.
	/// </summary>
	public class PreFile
	{
		private string name;
	
		private long size;
	
		private DateTime modified;
	
		private string attributes;
	
		private string formatedSize;
	
		private string formatedModified;
		
		private string originalPath;
		
		private bool directory;
		
		public char separatorChar;
	
		public PreFile() {
		}
		
		public PreFile(string name, long size, DateTime modified, string attributes, string formatSize,
				string formatModified) {
			this.name = name;
			this.size = size;
			this.modified = modified;
			this.attributes = attributes;
			this.formatedSize = formatSize;
			this.formatedModified = formatModified;
		}
	
		public string getName() {
			return name;
		}
	
		public void setName(string name) {
			this.name = name;
		}
	
		public long getSize() {
			return size;
		}
	
		public void setSize(long size) {
			this.size = size;
		}
	
		public DateTime getModified() {
			return modified;
		}
	
		public void setModified(DateTime modified) {
			this.modified = modified;
		}
	
		public string getAttributes() {
			return attributes;
		}
	
		public void setAttributes(string attributes) {
			this.attributes = attributes;
		}
	
		public string getFormatedSize() {
			return formatedSize;
		}
	
		public void setFormatedSize(string formatedSize) {
			this.formatedSize = formatedSize;
		}
	
		public string getFormatedModified() {
			return formatedModified;
		}
	
		public void setFormatedModified(string formatedModified) {
			this.formatedModified = formatedModified;
		}
	
		public string getOriginalPath() {
			return originalPath;
		}
	
		public void setOriginalPath(string originalPath) {
			this.originalPath = originalPath;
		}
		
		public bool isDirectory(){
			return directory;
		}
		
		public void setDirectory(bool directory){
			this.directory = directory;
		}
			
		public virtual void limparDados() {
			this.name = "";
			this.size = 0;
			this.modified = DateTime.Now;
			this.attributes = "";
			this.formatedSize = "";
			this.formatedModified = "";
			this.originalPath = "";
			this.directory = false;
		}
	
		public override string ToString() {
			return "PreFile [name=" + name + ", size=" + size + ", modified=" + modified + ", attributes=" + attributes
					+ ", formatSize=" + formatedSize + ", formatModified=" + formatedModified + "]";
		}
	
		public string ToInsert() {
			return "'" + getName() + "'," + size + ",'" + formatedModified + "','" + attributes + "'";
		}
	
		public virtual string ToCVS() {
			return getName() + ";" + size + ";" + formatedModified + ";" + attributes;
		}
			
	}
}
