namespace DemoPlugin
{
    partial class TagEditorForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.lTitle = new System.Windows.Forms.Label();
            this.lArtist = new System.Windows.Forms.Label();
            this.lAlbum = new System.Windows.Forms.Label();
            this.lGenre = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.lYear = new System.Windows.Forms.Label();
            this.cover = new System.Windows.Forms.PictureBox();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.cover)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(747, 412);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.cover);
            this.tabPage1.Controls.Add(this.lYear);
            this.tabPage1.Controls.Add(this.label5);
            this.tabPage1.Controls.Add(this.lGenre);
            this.tabPage1.Controls.Add(this.lAlbum);
            this.tabPage1.Controls.Add(this.lArtist);
            this.tabPage1.Controls.Add(this.lTitle);
            this.tabPage1.Controls.Add(this.label4);
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Controls.Add(this.label2);
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(739, 386);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Common";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(27, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Title";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 41);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Artist";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 64);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Album";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 89);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(36, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Genre";
            // 
            // lTitle
            // 
            this.lTitle.AutoSize = true;
            this.lTitle.Location = new System.Drawing.Point(76, 19);
            this.lTitle.Name = "lTitle";
            this.lTitle.Size = new System.Drawing.Size(35, 13);
            this.lTitle.TabIndex = 4;
            this.lTitle.Text = "label5";
            // 
            // lArtist
            // 
            this.lArtist.AutoSize = true;
            this.lArtist.Location = new System.Drawing.Point(76, 41);
            this.lArtist.Name = "lArtist";
            this.lArtist.Size = new System.Drawing.Size(35, 13);
            this.lArtist.TabIndex = 5;
            this.lArtist.Text = "label6";
            // 
            // lAlbum
            // 
            this.lAlbum.AutoSize = true;
            this.lAlbum.Location = new System.Drawing.Point(76, 64);
            this.lAlbum.Name = "lAlbum";
            this.lAlbum.Size = new System.Drawing.Size(35, 13);
            this.lAlbum.TabIndex = 6;
            this.lAlbum.Text = "label7";
            // 
            // lGenre
            // 
            this.lGenre.AutoSize = true;
            this.lGenre.Location = new System.Drawing.Point(76, 89);
            this.lGenre.Name = "lGenre";
            this.lGenre.Size = new System.Drawing.Size(35, 13);
            this.lGenre.TabIndex = 7;
            this.lGenre.Text = "label8";
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.button1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panel1.Location = new System.Drawing.Point(0, 412);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(747, 38);
            this.panel1.TabIndex = 1;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(660, 6);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "Close";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(13, 115);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(29, 13);
            this.label5.TabIndex = 8;
            this.label5.Text = "Year";
            // 
            // lYear
            // 
            this.lYear.AutoSize = true;
            this.lYear.Location = new System.Drawing.Point(76, 115);
            this.lYear.Name = "lYear";
            this.lYear.Size = new System.Drawing.Size(35, 13);
            this.lYear.TabIndex = 9;
            this.lYear.Text = "label6";
            // 
            // cover
            // 
            this.cover.Location = new System.Drawing.Point(344, 6);
            this.cover.Name = "cover";
            this.cover.Size = new System.Drawing.Size(387, 374);
            this.cover.TabIndex = 10;
            this.cover.TabStop = false;
            // 
            // TagEditorForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(747, 450);
            this.ControlBox = false;
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "TagEditorForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "TagEditorForm";
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.cover)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label lGenre;
        private System.Windows.Forms.Label lAlbum;
        private System.Windows.Forms.Label lArtist;
        private System.Windows.Forms.Label lTitle;
        private System.Windows.Forms.Label lYear;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.PictureBox cover;
    }
}