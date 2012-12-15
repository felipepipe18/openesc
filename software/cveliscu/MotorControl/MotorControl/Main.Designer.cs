namespace MotorControl
{
    partial class Main
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
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
            this.cmbPort = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel2 = new System.Windows.Forms.ToolStripLabel();
            this.cmbSpeed = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel3 = new System.Windows.Forms.ToolStripLabel();
            this.cmbBits = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel4 = new System.Windows.Forms.ToolStripLabel();
            this.cmbParity = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel5 = new System.Windows.Forms.ToolStripLabel();
            this.cmbStopBits = new System.Windows.Forms.ToolStripComboBox();
            this.logBox = new System.Windows.Forms.RichTextBox();
            this.btnConnect = new System.Windows.Forms.ToolStripButton();
            this.btnDisconnect = new System.Windows.Forms.ToolStripButton();
            this.lblConnected = new System.Windows.Forms.ToolStripLabel();
            this.btnControlVelocityRS = new System.Windows.Forms.Button();
            this.txtInput = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.toolStripLabel7 = new System.Windows.Forms.ToolStripLabel();
            this.txtSlaveAddress = new System.Windows.Forms.ToolStripTextBox();
            this.grpCommands = new System.Windows.Forms.GroupBox();
            this.btnCommCommand = new System.Windows.Forms.Button();
            this.btnReadBackEMF = new System.Windows.Forms.Button();
            this.btnControlONOFF = new System.Windows.Forms.Button();
            this.btnReadR1R2R3 = new System.Windows.Forms.Button();
            this.btnReadAccTab = new System.Windows.Forms.Button();
            this.btnWriteAccTab = new System.Windows.Forms.Button();
            this.btnReadReqDefaultParam = new System.Windows.Forms.Button();
            this.btnSetReqWriteParam = new System.Windows.Forms.Button();
            this.btnReadParam = new System.Windows.Forms.Button();
            this.btnSetParam = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.cmbParameter = new System.Windows.Forms.ComboBox();
            this.grpParameters = new System.Windows.Forms.GroupBox();
            this.toolStripSeparator5 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel6 = new System.Windows.Forms.ToolStripLabel();
            this.txtTimeout = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripSeparator6 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripSeparator7 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripLabel8 = new System.Windows.Forms.ToolStripLabel();
            this.cmbHandshake = new System.Windows.Forms.ToolStripComboBox();
            this.toolStrip1.SuspendLayout();
            this.grpCommands.SuspendLayout();
            this.grpParameters.SuspendLayout();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripLabel1,
            this.cmbPort,
            this.toolStripSeparator1,
            this.toolStripLabel2,
            this.cmbSpeed,
            this.toolStripSeparator2,
            this.toolStripLabel3,
            this.cmbBits,
            this.toolStripSeparator3,
            this.toolStripLabel4,
            this.cmbParity,
            this.toolStripSeparator4,
            this.toolStripLabel5,
            this.cmbStopBits,
            this.toolStripSeparator5,
            this.toolStripLabel8,
            this.cmbHandshake,
            this.toolStripSeparator7,
            this.toolStripLabel6,
            this.txtTimeout,
            this.toolStripSeparator6,
            this.btnConnect,
            this.btnDisconnect,
            this.lblConnected,
            this.txtSlaveAddress,
            this.toolStripLabel7});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(1264, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // toolStripLabel1
            // 
            this.toolStripLabel1.Name = "toolStripLabel1";
            this.toolStripLabel1.Size = new System.Drawing.Size(32, 22);
            this.toolStripLabel1.Text = "Port:";
            // 
            // cmbPort
            // 
            this.cmbPort.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbPort.Name = "cmbPort";
            this.cmbPort.Size = new System.Drawing.Size(81, 25);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripLabel2
            // 
            this.toolStripLabel2.Name = "toolStripLabel2";
            this.toolStripLabel2.Size = new System.Drawing.Size(42, 22);
            this.toolStripLabel2.Text = "Speed:";
            // 
            // cmbSpeed
            // 
            this.cmbSpeed.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbSpeed.Name = "cmbSpeed";
            this.cmbSpeed.Size = new System.Drawing.Size(81, 25);
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripLabel3
            // 
            this.toolStripLabel3.Name = "toolStripLabel3";
            this.toolStripLabel3.Size = new System.Drawing.Size(29, 22);
            this.toolStripLabel3.Text = "Bits:";
            // 
            // cmbBits
            // 
            this.cmbBits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbBits.Name = "cmbBits";
            this.cmbBits.Size = new System.Drawing.Size(75, 25);
            // 
            // toolStripSeparator3
            // 
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripLabel4
            // 
            this.toolStripLabel4.Name = "toolStripLabel4";
            this.toolStripLabel4.Size = new System.Drawing.Size(40, 22);
            this.toolStripLabel4.Text = "Parity:";
            // 
            // cmbParity
            // 
            this.cmbParity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbParity.Name = "cmbParity";
            this.cmbParity.Size = new System.Drawing.Size(75, 25);
            // 
            // toolStripSeparator4
            // 
            this.toolStripSeparator4.Name = "toolStripSeparator4";
            this.toolStripSeparator4.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripLabel5
            // 
            this.toolStripLabel5.Name = "toolStripLabel5";
            this.toolStripLabel5.Size = new System.Drawing.Size(56, 22);
            this.toolStripLabel5.Text = "Stop Bits:";
            // 
            // cmbStopBits
            // 
            this.cmbStopBits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbStopBits.Name = "cmbStopBits";
            this.cmbStopBits.Size = new System.Drawing.Size(75, 25);
            // 
            // logBox
            // 
            this.logBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.logBox.Location = new System.Drawing.Point(0, 161);
            this.logBox.Name = "logBox";
            this.logBox.ReadOnly = true;
            this.logBox.Size = new System.Drawing.Size(1264, 354);
            this.logBox.TabIndex = 1;
            this.logBox.Text = "";
            // 
            // btnConnect
            // 
            this.btnConnect.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.btnConnect.Image = global::MotorControl.Properties.Resources.Ok;
            this.btnConnect.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnConnect.Name = "btnConnect";
            this.btnConnect.Size = new System.Drawing.Size(23, 22);
            this.btnConnect.Text = "Connect";
            this.btnConnect.Click += new System.EventHandler(this.btnConnect_Click);
            // 
            // btnDisconnect
            // 
            this.btnDisconnect.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.btnDisconnect.Image = global::MotorControl.Properties.Resources.Close_2;
            this.btnDisconnect.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.btnDisconnect.Name = "btnDisconnect";
            this.btnDisconnect.Size = new System.Drawing.Size(23, 22);
            this.btnDisconnect.Text = "Disconnect";
            this.btnDisconnect.Click += new System.EventHandler(this.btnDisconnect_Click);
            // 
            // lblConnected
            // 
            this.lblConnected.Name = "lblConnected";
            this.lblConnected.Size = new System.Drawing.Size(86, 22);
            this.lblConnected.Text = "Not connected";
            // 
            // btnControlVelocityRS
            // 
            this.btnControlVelocityRS.Location = new System.Drawing.Point(158, 74);
            this.btnControlVelocityRS.Name = "btnControlVelocityRS";
            this.btnControlVelocityRS.Size = new System.Drawing.Size(140, 23);
            this.btnControlVelocityRS.TabIndex = 8;
            this.btnControlVelocityRS.Text = "Control Velocity RS";
            this.btnControlVelocityRS.UseVisualStyleBackColor = true;
            this.btnControlVelocityRS.Click += new System.EventHandler(this.btnControlVelocityRS_Click);
            // 
            // txtInput
            // 
            this.txtInput.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtInput.Location = new System.Drawing.Point(45, 19);
            this.txtInput.Name = "txtInput";
            this.txtInput.Size = new System.Drawing.Size(1199, 20);
            this.txtInput.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(33, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Data:";
            // 
            // toolStripLabel7
            // 
            this.toolStripLabel7.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.toolStripLabel7.Name = "toolStripLabel7";
            this.toolStripLabel7.Size = new System.Drawing.Size(82, 22);
            this.toolStripLabel7.Text = "Slave Address:";
            // 
            // txtSlaveAddress
            // 
            this.txtSlaveAddress.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
            this.txtSlaveAddress.Name = "txtSlaveAddress";
            this.txtSlaveAddress.Size = new System.Drawing.Size(50, 25);
            // 
            // grpCommands
            // 
            this.grpCommands.Controls.Add(this.grpParameters);
            this.grpCommands.Controls.Add(this.btnSetReqWriteParam);
            this.grpCommands.Controls.Add(this.btnReadReqDefaultParam);
            this.grpCommands.Controls.Add(this.btnWriteAccTab);
            this.grpCommands.Controls.Add(this.btnReadAccTab);
            this.grpCommands.Controls.Add(this.btnReadR1R2R3);
            this.grpCommands.Controls.Add(this.btnControlONOFF);
            this.grpCommands.Controls.Add(this.btnReadBackEMF);
            this.grpCommands.Controls.Add(this.btnCommCommand);
            this.grpCommands.Controls.Add(this.btnControlVelocityRS);
            this.grpCommands.Controls.Add(this.label1);
            this.grpCommands.Controls.Add(this.txtInput);
            this.grpCommands.Dock = System.Windows.Forms.DockStyle.Top;
            this.grpCommands.Location = new System.Drawing.Point(0, 25);
            this.grpCommands.Name = "grpCommands";
            this.grpCommands.Size = new System.Drawing.Size(1264, 136);
            this.grpCommands.TabIndex = 6;
            this.grpCommands.TabStop = false;
            this.grpCommands.Text = "Commands";
            // 
            // btnCommCommand
            // 
            this.btnCommCommand.Location = new System.Drawing.Point(12, 45);
            this.btnCommCommand.Name = "btnCommCommand";
            this.btnCommCommand.Size = new System.Drawing.Size(140, 23);
            this.btnCommCommand.TabIndex = 4;
            this.btnCommCommand.Text = "Comm Command";
            this.btnCommCommand.UseVisualStyleBackColor = true;
            this.btnCommCommand.Click += new System.EventHandler(this.btnCommCommand_Click);
            // 
            // btnReadBackEMF
            // 
            this.btnReadBackEMF.Location = new System.Drawing.Point(12, 74);
            this.btnReadBackEMF.Name = "btnReadBackEMF";
            this.btnReadBackEMF.Size = new System.Drawing.Size(140, 23);
            this.btnReadBackEMF.TabIndex = 5;
            this.btnReadBackEMF.Text = "Read BackEMF";
            this.btnReadBackEMF.UseVisualStyleBackColor = true;
            this.btnReadBackEMF.Click += new System.EventHandler(this.btnReadBackEMF_Click);
            // 
            // btnControlONOFF
            // 
            this.btnControlONOFF.Location = new System.Drawing.Point(12, 103);
            this.btnControlONOFF.Name = "btnControlONOFF";
            this.btnControlONOFF.Size = new System.Drawing.Size(140, 23);
            this.btnControlONOFF.TabIndex = 6;
            this.btnControlONOFF.Text = "Control ON/OFF";
            this.btnControlONOFF.UseVisualStyleBackColor = true;
            this.btnControlONOFF.Click += new System.EventHandler(this.btnControlONOFF_Click);
            // 
            // btnReadR1R2R3
            // 
            this.btnReadR1R2R3.Location = new System.Drawing.Point(158, 45);
            this.btnReadR1R2R3.Name = "btnReadR1R2R3";
            this.btnReadR1R2R3.Size = new System.Drawing.Size(140, 23);
            this.btnReadR1R2R3.TabIndex = 7;
            this.btnReadR1R2R3.Text = "Read R1,R2,R3";
            this.btnReadR1R2R3.UseVisualStyleBackColor = true;
            this.btnReadR1R2R3.Click += new System.EventHandler(this.btnReadR1R2R3_Click);
            // 
            // btnReadAccTab
            // 
            this.btnReadAccTab.Location = new System.Drawing.Point(304, 45);
            this.btnReadAccTab.Name = "btnReadAccTab";
            this.btnReadAccTab.Size = new System.Drawing.Size(140, 23);
            this.btnReadAccTab.TabIndex = 9;
            this.btnReadAccTab.Text = "Read Acc Tab";
            this.btnReadAccTab.UseVisualStyleBackColor = true;
            this.btnReadAccTab.Click += new System.EventHandler(this.btnReadAccTab_Click);
            // 
            // btnWriteAccTab
            // 
            this.btnWriteAccTab.Location = new System.Drawing.Point(304, 74);
            this.btnWriteAccTab.Name = "btnWriteAccTab";
            this.btnWriteAccTab.Size = new System.Drawing.Size(140, 23);
            this.btnWriteAccTab.TabIndex = 10;
            this.btnWriteAccTab.Text = "Write Acc Tab";
            this.btnWriteAccTab.UseVisualStyleBackColor = true;
            this.btnWriteAccTab.Click += new System.EventHandler(this.btnWriteAccTab_Click);
            // 
            // btnReadReqDefaultParam
            // 
            this.btnReadReqDefaultParam.Location = new System.Drawing.Point(450, 45);
            this.btnReadReqDefaultParam.Name = "btnReadReqDefaultParam";
            this.btnReadReqDefaultParam.Size = new System.Drawing.Size(140, 23);
            this.btnReadReqDefaultParam.TabIndex = 11;
            this.btnReadReqDefaultParam.Text = "Read Req Default Param";
            this.btnReadReqDefaultParam.UseVisualStyleBackColor = true;
            this.btnReadReqDefaultParam.Click += new System.EventHandler(this.btnReadReqDefaultParam_Click);
            // 
            // btnSetReqWriteParam
            // 
            this.btnSetReqWriteParam.Location = new System.Drawing.Point(450, 74);
            this.btnSetReqWriteParam.Name = "btnSetReqWriteParam";
            this.btnSetReqWriteParam.Size = new System.Drawing.Size(140, 23);
            this.btnSetReqWriteParam.TabIndex = 12;
            this.btnSetReqWriteParam.Text = "Set Req Write Param";
            this.btnSetReqWriteParam.UseVisualStyleBackColor = true;
            this.btnSetReqWriteParam.Click += new System.EventHandler(this.btnSetReqWriteParam_Click);
            // 
            // btnReadParam
            // 
            this.btnReadParam.Location = new System.Drawing.Point(203, 15);
            this.btnReadParam.Name = "btnReadParam";
            this.btnReadParam.Size = new System.Drawing.Size(140, 23);
            this.btnReadParam.TabIndex = 13;
            this.btnReadParam.Text = "Read Param";
            this.btnReadParam.UseVisualStyleBackColor = true;
            this.btnReadParam.Click += new System.EventHandler(this.btnReadParam_Click);
            // 
            // btnSetParam
            // 
            this.btnSetParam.Location = new System.Drawing.Point(203, 44);
            this.btnSetParam.Name = "btnSetParam";
            this.btnSetParam.Size = new System.Drawing.Size(140, 23);
            this.btnSetParam.TabIndex = 14;
            this.btnSetParam.Text = "Set Param";
            this.btnSetParam.UseVisualStyleBackColor = true;
            this.btnSetParam.Click += new System.EventHandler(this.btnSetParam_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(15, 25);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 13);
            this.label2.TabIndex = 15;
            this.label2.Text = "Parameter:";
            // 
            // cmbParameter
            // 
            this.cmbParameter.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbParameter.FormattingEnabled = true;
            this.cmbParameter.Location = new System.Drawing.Point(18, 45);
            this.cmbParameter.Name = "cmbParameter";
            this.cmbParameter.Size = new System.Drawing.Size(179, 21);
            this.cmbParameter.TabIndex = 16;
            // 
            // grpParameters
            // 
            this.grpParameters.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.grpParameters.Controls.Add(this.btnReadParam);
            this.grpParameters.Controls.Add(this.cmbParameter);
            this.grpParameters.Controls.Add(this.btnSetParam);
            this.grpParameters.Controls.Add(this.label2);
            this.grpParameters.Location = new System.Drawing.Point(895, 45);
            this.grpParameters.Name = "grpParameters";
            this.grpParameters.Size = new System.Drawing.Size(349, 81);
            this.grpParameters.TabIndex = 17;
            this.grpParameters.TabStop = false;
            this.grpParameters.Text = "Read / Set Parameter";
            // 
            // toolStripSeparator5
            // 
            this.toolStripSeparator5.Name = "toolStripSeparator5";
            this.toolStripSeparator5.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripLabel6
            // 
            this.toolStripLabel6.Name = "toolStripLabel6";
            this.toolStripLabel6.Size = new System.Drawing.Size(82, 22);
            this.toolStripLabel6.Text = "Timeout (ms):";
            // 
            // txtTimeout
            // 
            this.txtTimeout.Name = "txtTimeout";
            this.txtTimeout.Size = new System.Drawing.Size(50, 25);
            this.txtTimeout.Text = "500";
            // 
            // toolStripSeparator6
            // 
            this.toolStripSeparator6.Name = "toolStripSeparator6";
            this.toolStripSeparator6.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripSeparator7
            // 
            this.toolStripSeparator7.Name = "toolStripSeparator7";
            this.toolStripSeparator7.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripLabel8
            // 
            this.toolStripLabel8.Name = "toolStripLabel8";
            this.toolStripLabel8.Size = new System.Drawing.Size(69, 22);
            this.toolStripLabel8.Text = "Handshake:";
            // 
            // cmbHandshake
            // 
            this.cmbHandshake.Name = "cmbHandshake";
            this.cmbHandshake.Size = new System.Drawing.Size(75, 25);
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1264, 515);
            this.Controls.Add(this.logBox);
            this.Controls.Add(this.grpCommands);
            this.Controls.Add(this.toolStrip1);
            this.Name = "Main";
            this.Text = "Motor Control Serial Interface";
            this.Load += new System.EventHandler(this.Main_Load);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.grpCommands.ResumeLayout(false);
            this.grpCommands.PerformLayout();
            this.grpParameters.ResumeLayout(false);
            this.grpParameters.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripLabel toolStripLabel1;
        private System.Windows.Forms.ToolStripComboBox cmbPort;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripLabel toolStripLabel2;
        private System.Windows.Forms.ToolStripComboBox cmbSpeed;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ToolStripLabel toolStripLabel3;
        private System.Windows.Forms.ToolStripComboBox cmbBits;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
        private System.Windows.Forms.ToolStripLabel toolStripLabel4;
        private System.Windows.Forms.ToolStripComboBox cmbParity;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
        private System.Windows.Forms.ToolStripLabel toolStripLabel5;
        private System.Windows.Forms.ToolStripComboBox cmbStopBits;
        private System.Windows.Forms.ToolStripButton btnConnect;
        private System.Windows.Forms.ToolStripButton btnDisconnect;
        private System.Windows.Forms.ToolStripLabel lblConnected;
        private System.Windows.Forms.RichTextBox logBox;
        private System.Windows.Forms.Button btnControlVelocityRS;
        private System.Windows.Forms.TextBox txtInput;
        private System.Windows.Forms.ToolStripTextBox txtSlaveAddress;
        private System.Windows.Forms.ToolStripLabel toolStripLabel7;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox grpCommands;
        private System.Windows.Forms.Button btnSetParam;
        private System.Windows.Forms.Button btnReadParam;
        private System.Windows.Forms.Button btnSetReqWriteParam;
        private System.Windows.Forms.Button btnReadReqDefaultParam;
        private System.Windows.Forms.Button btnWriteAccTab;
        private System.Windows.Forms.Button btnReadAccTab;
        private System.Windows.Forms.Button btnReadR1R2R3;
        private System.Windows.Forms.Button btnControlONOFF;
        private System.Windows.Forms.Button btnReadBackEMF;
        private System.Windows.Forms.Button btnCommCommand;
        private System.Windows.Forms.ComboBox cmbParameter;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox grpParameters;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator5;
        private System.Windows.Forms.ToolStripLabel toolStripLabel6;
        private System.Windows.Forms.ToolStripTextBox txtTimeout;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator6;
        private System.Windows.Forms.ToolStripLabel toolStripLabel8;
        private System.Windows.Forms.ToolStripComboBox cmbHandshake;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator7;
    }
}

