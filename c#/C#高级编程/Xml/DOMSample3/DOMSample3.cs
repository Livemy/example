using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Xml;

namespace Wrox.ProCSharp.Xml.DOMSample3
{
	

	/// <summary>
	///		Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.ListBox listBox1;
		private System.Windows.Forms.Button button1;
		/// <summary>
		///		Required designer variable.
		/// </summary>
		private System.ComponentModel.Container components=null;
		private XmlDocument doc=new XmlDocument();

		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		///		Clean up any resources being used.
		/// </summary>
		
		protected override void Dispose( bool disposing )
				{
					if( disposing )
					{
						if (components != null) 
						{
							components.Dispose();
						}
					}
					base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		///		Required method for Designer support - do not modify
		///		the contents of this method with the code editor.
		/// </summary>
    private void InitializeComponent()
    {
      this.listBox1 = new System.Windows.Forms.ListBox();
      this.button1 = new System.Windows.Forms.Button();
      this.listBox1.Anchor = ((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
        | System.Windows.Forms.AnchorStyles.Right);
      this.listBox1.Size = new System.Drawing.Size(336, 238);
      this.listBox1.TabIndex = 0;
      this.listBox1.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
      this.button1.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
      this.button1.Location = new System.Drawing.Point(136, 264);
      this.button1.TabIndex = 1;
      this.button1.Text = "Load XML";
      this.button1.Click += new System.EventHandler(this.button1_Click);
      this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
      this.ClientSize = new System.Drawing.Size(339, 320);
      this.Controls.AddRange(new System.Windows.Forms.Control[] {this.button1,
                                                                  this.listBox1});
      this.Text = "Form1";

    }
		#endregion

		/// <summary>
		/// 	The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}
    // DOMSample3/form1.cs
    private void button1_Click(object sender, System.EventArgs e)
    {
      //change path to match your structure
      doc.Load("..\\books.xml");
      //create a new 'book' element
      XmlElement newBook=doc.CreateElement("book");
      //set some attributes
      newBook.SetAttribute("genre","Mystery");
      newBook.SetAttribute("publicationdate","2001");
      newBook.SetAttribute("ISBN","123456789");
      //create a new 'title' element
      XmlElement newTitle=doc.CreateElement("title");
      newTitle.InnerText="Case of the Missing Cookie";
      newBook.AppendChild(newTitle);
      //create new author element
      XmlElement newAuthor=doc.CreateElement("author");
      newBook.AppendChild(newAuthor);
      //create new name element
      XmlElement newName=doc.CreateElement("name");
      newName.InnerText="Cookie Monster";
      newAuthor.AppendChild(newName);
      //create new price element
      XmlElement newPrice=doc.CreateElement("price");
      newPrice.InnerText="9.95";
      newBook.AppendChild(newPrice);
      //add to the current document
      doc.DocumentElement.AppendChild(newBook);
      //write out the doc to disk
      XmlTextWriter tr=new XmlTextWriter("..\\booksEdit.xml",null);
      tr.Formatting=Formatting.Indented;
      doc.WriteContentTo(tr);
     
      tr.Close();
      //load listBox1 with all of the titles, including new one
      XmlNodeList nodeLst=doc.GetElementsByTagName("title");
      
      foreach(XmlNode node in nodeLst)
        listBox1.Items.Add(node.InnerText);
      
    }
    
    private void listBox1_SelectedIndexChanged(object sender, System.EventArgs e)
    {
      string srch="bookstore/book[title='" + listBox1.SelectedItem.ToString() + "']";
      XmlNode foundNode=doc.SelectSingleNode(srch);
      if(foundNode!=null)
        MessageBox.Show(foundNode.InnerText);
      else
        MessageBox.Show("Not found");
      
    }

	}
}
