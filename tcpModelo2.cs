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
namespace tcpModelo
{
    public partial class Form1 : Form
    {
        private TcpClient client;
        public StreamReader STR;
        public StreamWriter STW;
        public string receive;
        public String text_to_send;

        public Form1()
        {
            InitializeComponent();
            IPAddress[] localIP = Dns.GetHostAddresses(Dns.GetHostName());
            foreach (IPAddress address in localIP)
            {
                if (address.AddressFamily == AddressFamily.InterNetwork)
                {
                    textBox3.Text = address.ToString();
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //TcpListener listener = new TcpListener(IPAddress.Any, 502);
            TcpListener listener = new TcpListener(IPAddress.Any, 502);
            listener.Start();
            client = listener.AcceptTcpClient();

            //STW.AutoFlush = true;

            backgroundWorker1.RunWorkerAsync(); //começar receber dado.
            backgroundWorker2.WorkerSupportsCancellation = true; // cancelar thread.  
        }

        private void button3_Click(object sender, EventArgs e)
        {
            client = new TcpClient();
            IPEndPoint IP_END = new IPEndPoint(IPAddress.Parse(textBox5.Text), int.Parse(textBox6.Text));
            try
            {
                client.Connect(IP_END);
                if(client.Connected)
                {
                    textBox2.AppendText("Connect to server" + "\n");
                    STW = new StreamWriter(client.GetStream());
                    STR = new StreamReader(client.GetStream());
                    STW.AutoFlush = true;

                    backgroundWorker1.RunWorkerAsync(); //começar receber dado.
                    backgroundWorker2.WorkerSupportsCancellation = true; // cancelar thread.

                }
            }
            catch(Exception x)
            {
                MessageBox.Show(x.Message.ToString());
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(textBox1.Text != "")
            {
                text_to_send = textBox1.Text;
                backgroundWorker2.RunWorkerAsync();
            }
            textBox1.Text = "";
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            if(client.Connected)
            {
                try
                {
                    TcpListener listener = new TcpListener(IPAddress.Any, 502);
                    listener.Start();
                    client = listener.AcceptTcpClient();
                    Socket s = listener.AcceptSocket();
                    byte[] b = new byte[100];
                    int k = s.Receive(b);
                    Console.WriteLine("Recieved...");
                    for (int i = 0; i < k; i++)
                        Console.Write(b[i]);
                    //Convert.

                    ASCIIEncoding asen = new ASCIIEncoding();
                    s.Send(asen.GetBytes("The string was recieved by the server."));
                    Console.WriteLine("\nSent Acknowledgement");
                    // clean up 
                    s.Close();
                    listener.Stop();
                    receive = STR.ReadLine();
                    this.textBox2.Invoke(new MethodInvoker(delegate () { textBox2.AppendText(b + "\n"); }));
                    receive = "";

                }
                catch(Exception x)
                {
                    MessageBox.Show(x.Message.ToString());
                }
            }
        }

        private void backgroundWorker2_DoWork(object sender, DoWorkEventArgs e)
        {
            if (client.Connected)
            {
                STW.WriteLine(text_to_send);
                this.textBox2.Invoke(new MethodInvoker(delegate () { textBox2.AppendText("Me: " + text_to_send + "\n"); }));

            }
            else
            {
                MessageBox.Show("Send Failed");
            }

            backgroundWorker2.CancelAsync();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
           
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            
        }
    }
}
