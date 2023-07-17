namespace WindowsFormsApp1
{
    partial class Form1
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.setModelName = new System.Windows.Forms.TextBox();
            this.setModePath = new System.Windows.Forms.TextBox();
            this.setPicPath = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.setDeviceName = new System.Windows.Forms.ComboBox();
            this.predict = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.labelindex = new System.Windows.Forms.TextBox();
            this.label = new System.Windows.Forms.TextBox();
            this.socre = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.x0 = new System.Windows.Forms.TextBox();
            this.y0 = new System.Windows.Forms.TextBox();
            this.y1 = new System.Windows.Forms.TextBox();
            this.x1 = new System.Windows.Forms.TextBox();
            this.directorySearcher1 = new System.DirectoryServices.DirectorySearcher();
            this.borwseModelPath = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // setModelName
            // 
            this.setModelName.Font = new System.Drawing.Font("SimSun", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.setModelName.Location = new System.Drawing.Point(288, 72);
            this.setModelName.Name = "setModelName";
            this.setModelName.Size = new System.Drawing.Size(406, 29);
            this.setModelName.TabIndex = 4;
            this.setModelName.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            this.setModelName.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.onModeName);
            // 
            // setModePath
            // 
            this.setModePath.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.setModePath.Location = new System.Drawing.Point(288, 125);
            this.setModePath.Name = "setModePath";
            this.setModePath.Size = new System.Drawing.Size(406, 33);
            this.setModePath.TabIndex = 5;
            this.setModePath.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.onModelPath);
            // 
            // setPicPath
            // 
            this.setPicPath.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.setPicPath.Location = new System.Drawing.Point(288, 181);
            this.setPicPath.Name = "setPicPath";
            this.setPicPath.Size = new System.Drawing.Size(406, 33);
            this.setPicPath.TabIndex = 6;
            this.setPicPath.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.onPicPath);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(121, 80);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(86, 21);
            this.label1.TabIndex = 9;
            this.label1.Text = "模型名称";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(121, 137);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(86, 21);
            this.label2.TabIndex = 10;
            this.label2.Text = "模型路径";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(121, 193);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(86, 21);
            this.label3.TabIndex = 11;
            this.label3.Text = "图片路径";
            this.label3.Click += new System.EventHandler(this.label3_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(121, 245);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(86, 21);
            this.label4.TabIndex = 12;
            this.label4.Text = "设备名称";
            this.label4.Click += new System.EventHandler(this.label4_Click);
            // 
            // setDeviceName
            // 
            this.setDeviceName.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.setDeviceName.FormattingEnabled = true;
            this.setDeviceName.Items.AddRange(new object[] {
            "cuda",
            "cpu"});
            this.setDeviceName.Location = new System.Drawing.Point(288, 242);
            this.setDeviceName.Name = "setDeviceName";
            this.setDeviceName.Size = new System.Drawing.Size(406, 29);
            this.setDeviceName.TabIndex = 13;
            this.setDeviceName.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged_1);
            this.setDeviceName.Click += new System.EventHandler(this.onDeviceName);
            // 
            // predict
            // 
            this.predict.Font = new System.Drawing.Font("STZhongsong", 21.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.predict.Location = new System.Drawing.Point(288, 328);
            this.predict.Name = "predict";
            this.predict.Size = new System.Drawing.Size(199, 48);
            this.predict.TabIndex = 14;
            this.predict.Text = "开始预测";
            this.predict.UseVisualStyleBackColor = true;
            this.predict.Click += new System.EventHandler(this.makePrediction);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.Location = new System.Drawing.Point(121, 581);
            this.label5.Name = "label5";
            this.label5.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.label5.Size = new System.Drawing.Size(86, 21);
            this.label5.TabIndex = 15;
            this.label5.Text = "置信分数";
            this.label5.Click += new System.EventHandler(this.label5_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label6.Location = new System.Drawing.Point(121, 457);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(86, 21);
            this.label6.TabIndex = 16;
            this.label6.Text = "类别名称";
            this.label6.Click += new System.EventHandler(this.label6_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label8.Location = new System.Drawing.Point(121, 517);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(86, 21);
            this.label8.TabIndex = 18;
            this.label8.Text = "标签索引";
            this.label8.Click += new System.EventHandler(this.label8_Click);
            // 
            // labelindex
            // 
            this.labelindex.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelindex.Location = new System.Drawing.Point(288, 505);
            this.labelindex.Name = "labelindex";
            this.labelindex.Size = new System.Drawing.Size(406, 33);
            this.labelindex.TabIndex = 20;
            // 
            // label
            // 
            this.label.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label.Location = new System.Drawing.Point(288, 445);
            this.label.Name = "label";
            this.label.Size = new System.Drawing.Size(406, 33);
            this.label.TabIndex = 21;
            // 
            // socre
            // 
            this.socre.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.socre.Location = new System.Drawing.Point(288, 569);
            this.socre.Name = "socre";
            this.socre.Size = new System.Drawing.Size(406, 33);
            this.socre.TabIndex = 22;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label9.Location = new System.Drawing.Point(121, 642);
            this.label9.Name = "label9";
            this.label9.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.label9.Size = new System.Drawing.Size(86, 21);
            this.label9.TabIndex = 23;
            this.label9.Text = "矩阵坐标";
            this.label9.Click += new System.EventHandler(this.label9_Click);
            // 
            // x0
            // 
            this.x0.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.x0.Location = new System.Drawing.Point(288, 630);
            this.x0.Name = "x0";
            this.x0.Size = new System.Drawing.Size(76, 33);
            this.x0.TabIndex = 24;
            // 
            // y0
            // 
            this.y0.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.y0.Location = new System.Drawing.Point(398, 630);
            this.y0.Name = "y0";
            this.y0.Size = new System.Drawing.Size(76, 33);
            this.y0.TabIndex = 25;
            // 
            // y1
            // 
            this.y1.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.y1.Location = new System.Drawing.Point(618, 630);
            this.y1.Name = "y1";
            this.y1.Size = new System.Drawing.Size(76, 33);
            this.y1.TabIndex = 26;
            // 
            // x1
            // 
            this.x1.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.x1.Location = new System.Drawing.Point(508, 630);
            this.x1.Name = "x1";
            this.x1.Size = new System.Drawing.Size(76, 33);
            this.x1.TabIndex = 27;
            // 
            // directorySearcher1
            // 
            this.directorySearcher1.ClientTimeout = System.TimeSpan.Parse("-00:00:01");
            this.directorySearcher1.ServerPageTimeLimit = System.TimeSpan.Parse("-00:00:01");
            this.directorySearcher1.ServerTimeLimit = System.TimeSpan.Parse("-00:00:01");
            // 
            // borwseModelPath
            // 
            this.borwseModelPath.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.borwseModelPath.Location = new System.Drawing.Point(717, 125);
            this.borwseModelPath.Name = "borwseModelPath";
            this.borwseModelPath.Size = new System.Drawing.Size(75, 33);
            this.borwseModelPath.TabIndex = 28;
            this.borwseModelPath.Text = "浏览";
            this.borwseModelPath.UseVisualStyleBackColor = true;
            this.borwseModelPath.Click += new System.EventHandler(this.browseModelPath);
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("STZhongsong", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button1.Location = new System.Drawing.Point(717, 181);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 33);
            this.button1.TabIndex = 29;
            this.button1.Text = "浏览";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.browsePicPath);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Control;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.ClientSize = new System.Drawing.Size(814, 761);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.borwseModelPath);
            this.Controls.Add(this.x1);
            this.Controls.Add(this.y1);
            this.Controls.Add(this.y0);
            this.Controls.Add(this.x0);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.socre);
            this.Controls.Add(this.label);
            this.Controls.Add(this.labelindex);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.predict);
            this.Controls.Add(this.setDeviceName);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.setPicPath);
            this.Controls.Add(this.setModePath);
            this.Controls.Add(this.setModelName);
            this.DoubleBuffered = true;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "NeuroBot";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.closing);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox setModelName;
        private System.Windows.Forms.TextBox setModePath;
        private System.Windows.Forms.TextBox setPicPath;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox setDeviceName;
        private System.Windows.Forms.Button predict;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox labelindex;
        private System.Windows.Forms.TextBox label;
        private System.Windows.Forms.TextBox socre;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox x0;
        private System.Windows.Forms.TextBox y0;
        private System.Windows.Forms.TextBox y1;
        private System.Windows.Forms.TextBox x1;
        private System.DirectoryServices.DirectorySearcher directorySearcher1;
        private System.Windows.Forms.Button borwseModelPath;
        private System.Windows.Forms.Button button1;
    }
}

