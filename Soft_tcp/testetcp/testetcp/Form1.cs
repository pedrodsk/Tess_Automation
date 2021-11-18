using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
//using System;
using System.IO;
using System.Net;
//using System.Text;
using System.Net.Sockets;

namespace testetcp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            TcpClient tcpclnt = new TcpClient();
            try
            {
                // TcpClient tcpclnt = new TcpClient();
                tcpclnt.Connect("10.0.0.14", 502);
                Stream stm = tcpclnt.GetStream();
                //Console.Read();
                byte[] dado = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x01, 0x01 };
                stm.Write(dado, 0, dado.Length);
                tcpclnt.Close();

            }

            catch (Exception f)
            {
                Console.WriteLine("Error..... " + f.StackTrace);
                tcpclnt.Close();
                Console.Read();
            }

        }
    }
}
