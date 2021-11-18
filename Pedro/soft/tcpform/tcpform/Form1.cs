using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.IO;
using System.Net.Sockets;


namespace tcpform
{
    public partial class Form1 : Form
    {
        //TcpClient tcpclnt = new TcpClient();
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //TcpClient tcpclnt = new TcpClient();
            //try
            //{

            //    tcpclnt.Connect("10.0.0.14", 502);
            //    System.Threading.Thread.Sleep(500);
            //    Stream stm = tcpclnt.GetStream();
            //    //Console.Read();
            //    byte[] dado = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x01, 0x01 };
            //    stm.Write(dado, 0, dado.Length);
            //    System.Threading.Thread.Sleep(500);
            //    tcpclnt.Close();

            //}

            //catch (Exception f)
            //{
            //    Console.WriteLine("Error..... " + f.StackTrace);
            //    tcpclnt.Close();
            //    Console.Read();
            //}
            byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x01, 0x01 };
            Conexao("10.0.0.14", x);

        }

        public void Conexao( String ip, byte[] dado )
        {
            TcpClient tcpclnt = new TcpClient();
            try
            {

                tcpclnt.Connect( ip, 502);
                System.Threading.Thread.Sleep(500);
                Stream stm = tcpclnt.GetStream();
                //Console.Read();
                byte[] dados = dado;
                stm.Write(dados, 0, dados.Length);
                System.Threading.Thread.Sleep(500);
                tcpclnt.Close();

            }

            catch (Exception f)
            {
                Console.WriteLine("Error..... " + f.StackTrace);
                tcpclnt.Close();
                Console.Read();
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x01, 0x01 };
            Conexao("10.0.0.14", x);

        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x01, 0x04 };
            Conexao("10.0.0.15", x);

        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x01, 0x02 };
            Conexao("10.0.0.15", x);
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x02, 0x04 };
            Conexao("10.0.0.14", x);

        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x02, 0x02 };
            Conexao("10.0.0.14", x);
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x03, 0x03 };
            Conexao("10.0.0.14", x);
        }
    }
    }

