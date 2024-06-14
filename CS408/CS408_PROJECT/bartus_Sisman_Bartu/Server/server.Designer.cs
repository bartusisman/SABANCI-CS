
namespace Server
{
    partial class server
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
            this.listen_button = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.port_box = new System.Windows.Forms.TextBox();
            this.server_actions = new System.Windows.Forms.RichTextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.sps101_subscribers = new System.Windows.Forms.RichTextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.if100_subscribers = new System.Windows.Forms.RichTextBox();
            this.connected_clients = new System.Windows.Forms.RichTextBox();
            this.SuspendLayout();
            // 
            // listen_button
            // 
            this.listen_button.Location = new System.Drawing.Point(186, 16);
            this.listen_button.Name = "listen_button";
            this.listen_button.Size = new System.Drawing.Size(75, 23);
            this.listen_button.TabIndex = 0;
            this.listen_button.Text = "Listen";
            this.listen_button.UseVisualStyleBackColor = true;
            this.listen_button.Click += new System.EventHandler(this.listen_button_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label1.Location = new System.Drawing.Point(12, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 20);
            this.label1.TabIndex = 1;
            this.label1.Text = "Port:";
            // 
            // port_box
            // 
            this.port_box.Location = new System.Drawing.Point(65, 16);
            this.port_box.Name = "port_box";
            this.port_box.Size = new System.Drawing.Size(100, 20);
            this.port_box.TabIndex = 2;
            // 
            // server_actions
            // 
            this.server_actions.Location = new System.Drawing.Point(16, 102);
            this.server_actions.Name = "server_actions";
            this.server_actions.Size = new System.Drawing.Size(245, 495);
            this.server_actions.TabIndex = 3;
            this.server_actions.Text = "";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label2.Location = new System.Drawing.Point(12, 79);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(126, 20);
            this.label2.TabIndex = 4;
            this.label2.Text = "Server Actions";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label3.Location = new System.Drawing.Point(309, 79);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(156, 20);
            this.label3.TabIndex = 6;
            this.label3.Text = "Connected Clients";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label4.Location = new System.Drawing.Point(515, 79);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(156, 20);
            this.label4.TabIndex = 8;
            this.label4.Text = "IF100 Subscribers";
            // 
            // sps101_subscribers
            // 
            this.sps101_subscribers.Location = new System.Drawing.Point(741, 102);
            this.sps101_subscribers.Name = "sps101_subscribers";
            this.sps101_subscribers.Size = new System.Drawing.Size(116, 495);
            this.sps101_subscribers.TabIndex = 9;
            this.sps101_subscribers.Text = "";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(162)));
            this.label5.Location = new System.Drawing.Point(705, 79);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(174, 20);
            this.label5.TabIndex = 10;
            this.label5.Text = "SPS101 Subscribers";
            // 
            // if100_subscribers
            // 
            this.if100_subscribers.Location = new System.Drawing.Point(536, 102);
            this.if100_subscribers.Name = "if100_subscribers";
            this.if100_subscribers.Size = new System.Drawing.Size(116, 495);
            this.if100_subscribers.TabIndex = 11;
            this.if100_subscribers.Text = "";
            // 
            // connected_clients
            // 
            this.connected_clients.Location = new System.Drawing.Point(330, 102);
            this.connected_clients.Name = "connected_clients";
            this.connected_clients.Size = new System.Drawing.Size(116, 495);
            this.connected_clients.TabIndex = 12;
            this.connected_clients.Text = "";
            // 
            // server
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.AppWorkspace;
            this.ClientSize = new System.Drawing.Size(899, 613);
            this.Controls.Add(this.connected_clients);
            this.Controls.Add(this.if100_subscribers);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.sps101_subscribers);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.server_actions);
            this.Controls.Add(this.port_box);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.listen_button);
            this.Name = "server";
            this.Text = "Server";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button listen_button;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox port_box;
        private System.Windows.Forms.RichTextBox server_actions;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.RichTextBox sps101_subscribers;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.RichTextBox if100_subscribers;
        private System.Windows.Forms.RichTextBox connected_clients;
    }
}

