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
using System.Data.SqlClient;
//ANTIGO
//ANTIGO
//ANTIGO
//ANTIGO
//ANTIGO
//ANTIGO
//ANTIGO
//ANTIGO
//ANTIGO

namespace tcpform
{   

    public partial class Form1_V1 : Form
    {
        //variaveis globais

        const int porta = 502;
        private TcpClient client;
        public StreamReader STR;
       // public StreamWriter STW;
        public string receive;
        public String text_to_send;
        TcpListener listener;
        public Boolean estado = false;
        public Boolean ativado = false;


        public Form1_V1()

        {
            InitializeComponent();


            IPAddress[] localIP = Dns.GetHostAddresses(Dns.GetHostName());
            foreach (IPAddress ipAd in localIP)
            {
                if (ipAd.AddressFamily == AddressFamily.InterNetwork)
                {
                    textBox_IP.Text = ipAd.ToString();
                    textBox_Porta.Text = porta.ToString();
                    listener = new TcpListener(ipAd, porta);

                }
            }
        }
            
        private void Form1_Load(object sender, EventArgs e)
        {
            listener.Start();
            estado = true;

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            
            if (listener.Pending())
            {
                client = listener.AcceptTcpClient();
                backgroundWorker1.RunWorkerAsync();
                // textBox_InfoConexao.AppendText("Cliente conectado\n");
            }
            if (estado == true)
            {
                //  this.Enabled = false;
                System.Threading.Thread.Sleep(100);
                byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x00 };
                Conexao("10.0.0.14", x);
                estado = false;


            }
        }

        //    string connectionString = @"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=C:\USERS\OPERACAO\DESKTOP\TCPFORM[V2]\TCPFORM\TCPFORM\ACIONAMENTOWIFIDB.MDF;Integrated Security=True;Connect Timeout=30";

        //   SqlConnection sqlconnection = new SqlConnection(connectionString);

        //   sqlconnection.Open();
    

       

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            
            byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x01, 0x01 };
            Conexao("10.0.0.14", x);
         

        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x01, 0x02 };
            Conexao("10.0.0.14", x);

        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x01, 0x04 };
            Conexao("10.0.0.14", x);
        }

        private void radioButton1_MouseClick(object sender, MouseEventArgs e)
        {
            byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x02, 0x04 };
            Conexao("10.0.0.14", x);
        }

        private void radioButton2_MouseClick(object sender, MouseEventArgs e)
        {
            byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x02, 0x01 };
            Conexao("10.0.0.14", x);
        }

        private void radioButton3_MouseClick(object sender, MouseEventArgs e)
        {
            byte[] x = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x02, 0x03 };
            Conexao("10.0.0.14", x);
        }





        public void Conexao(String ip, byte[] dado)
        {
            TcpClient tcpclnt = new TcpClient();
            try
            {
                enable(false);
                tcpclnt.Connect(ip, 502);
                System.Threading.Thread.Sleep(60);
                Stream stm = tcpclnt.GetStream();
                //Console.Read();
                byte[] dados = dado;
                stm.Write(dados, 0, dados.Length);
                System.Threading.Thread.Sleep(60);
                //tcpclnt.EndConnect();
                tcpclnt.Close();
                enable(true);

            }

            catch (Exception f)
            {
                
                tcpclnt.Close();
                MessageBox.Show(f.StackTrace);
                //Console.Read();
            }
        }

           private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            if (client.Connected)
                {
                    STR = new StreamReader(client.GetStream());
                    //System.Threading.Thread.Sleep(50);

                    receive = STR.ReadLine();

                    EscreveMensagem(receive);
                  //  enable(true);
                    //this.Enabled = true;
                    // ativado = true;

                    System.Threading.Thread.Sleep(150);
                    client.Close();
                }
                
                        
        }
        private string[] QuebraMensagem(string str)
        {
            // Formato da Mensagem : IP + Estado + Dado

            string Dado = str.Last().ToString();
            str = str.Remove(str.Length - 1, 1);
            string Funcao = str.Last().ToString();
            str = str.Remove(str.Length - 1, 1);
            string IP = str;

            string[] MensagemQuebrada = { IP, Funcao, Dado };
            return MensagemQuebrada;
        }

        private void EscreveMensagem(string mensagem)
        {
            this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.Clear(); }));
            switch ( mensagem)
            {
                case "A.0.0.E10":
                    
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.AppendText("Lâmpadas Desligadas" + "  Hora: " + DateTime.Now.Hour.ToString() + ":" + DateTime.Now.Minute.ToString() + "\n"); }));
                    this.checkBox1.Invoke(new MethodInvoker(delegate () { checkBox1.Checked = false; }));
                    this.checkBox2.Invoke(new MethodInvoker(delegate () { checkBox2.Checked = false; }));
                    this.checkBox3.Invoke(new MethodInvoker(delegate () { checkBox3.Checked = false; }));
                    break;
                case "A.0.0.E11":
                   // this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.AppendText(""); }));
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.AppendText("Lâmpada 1 Acesa" +  "  Hora: " + DateTime.Now.Hour.ToString() + ":" + DateTime.Now.Minute.ToString() + "\n" ); } )  );
                    this.checkBox1.Invoke(new MethodInvoker(delegate () { checkBox1.Checked = true; }));
                    this.checkBox2.Invoke(new MethodInvoker(delegate () { checkBox2.Checked = false; }));
                    this.checkBox3.Invoke(new MethodInvoker(delegate () { checkBox3.Checked = false; }));
                    break;

                case "A.0.0.E12":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.AppendText("Lâmpada 2 Acesa" + "  Hora: " + DateTime.Now.Hour.ToString() + ":" + DateTime.Now.Minute.ToString() + "\n"); }));
                    this.checkBox1.Invoke(new MethodInvoker(delegate () { checkBox1.Checked = false; }));
                    this.checkBox2.Invoke(new MethodInvoker(delegate () { checkBox2.Checked = true; }));
                    this.checkBox3.Invoke(new MethodInvoker(delegate () { checkBox3.Checked = false; }));
                    break;
                case "A.0.0.E13":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.AppendText("Lâmpadas 1 e 2 Acesas" + "  Hora: " + DateTime.Now.Hour.ToString() + ":" + DateTime.Now.Minute.ToString() + "\n"); }));
                    this.checkBox1.Invoke(new MethodInvoker(delegate () { checkBox1.Checked = true; }));
                    this.checkBox2.Invoke(new MethodInvoker(delegate () { checkBox2.Checked = true; }));
                    this.checkBox3.Invoke(new MethodInvoker(delegate () { checkBox3.Checked = false; }));
                    break;

                case "A.0.0.E14":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.AppendText("Lâmpada 3 Acesa" + "  Hora: " + DateTime.Now.Hour.ToString() + ":" + DateTime.Now.Minute.ToString() + "\n"); }));
                    this.checkBox1.Invoke(new MethodInvoker(delegate () { checkBox1.Checked = false; }));
                    this.checkBox2.Invoke(new MethodInvoker(delegate () { checkBox2.Checked = false; }));
                    this.checkBox3.Invoke(new MethodInvoker(delegate () { checkBox3.Checked = true; }));
                    break;
                case "A.0.0.E15":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.AppendText("Lâmpada 1 e 3 Acesas" + "  Hora: " + DateTime.Now.Hour.ToString() + ":" + DateTime.Now.Minute.ToString() + "\n"); }));
                    this.checkBox1.Invoke(new MethodInvoker(delegate () { checkBox1.Checked = true; }));
                    this.checkBox2.Invoke(new MethodInvoker(delegate () { checkBox2.Checked = false; }));
                    this.checkBox3.Invoke(new MethodInvoker(delegate () { checkBox3.Checked = true; }));
                    break;
                case "A.0.0.E16":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.AppendText("Lâmpada 2 e 3 Acesas" + "  Hora: " + DateTime.Now.Hour.ToString() + ":" + DateTime.Now.Minute.ToString() + "\n"); }));
                    this.checkBox1.Invoke(new MethodInvoker(delegate () { checkBox1.Checked = false; }));
                    this.checkBox2.Invoke(new MethodInvoker(delegate () { checkBox2.Checked = true; }));
                    this.checkBox3.Invoke(new MethodInvoker(delegate () { checkBox3.Checked = true; }));
                    break;
                case "A.0.0.E17":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.AppendText("Lâmpadas Acesas" + "  Hora: " + DateTime.Now.Hour.ToString() + ":" + DateTime.Now.Minute.ToString() + "\n"); }));
                    this.checkBox1.Invoke(new MethodInvoker(delegate () { checkBox1.Checked = true; }));
                    this.checkBox2.Invoke(new MethodInvoker(delegate () { checkBox2.Checked = true; }));
                    this.checkBox3.Invoke(new MethodInvoker(delegate () { checkBox3.Checked = true; }));
                    break;
            }
           
            
        }
        private void enable(Boolean ativado)
        {
            if(ativado ==true)
            {
                this.Invoke(new MethodInvoker(delegate () { this.Enabled = true; }));
                //this.checkBox1.Invoke(new MethodInvoker(delegate () { checkBox1.Enabled = true; }));
                //this.checkBox2.Invoke(new MethodInvoker(delegate () { checkBox2.Enabled = true; }));
                //this.checkBox3.Invoke(new MethodInvoker(delegate () { checkBox3.Enabled = true; }));
               // this.radioButton1.Invoke(new MethodInvoker(delegate () { radioButton1.Enabled = true; }));
               // this.radioButton1.Invoke(new MethodInvoker(delegate () { radioButton1.AutoCheck = true; }));
                //this.radioButton2.Invoke(new MethodInvoker(delegate () { radioButton2.Enabled = true; }));
               // this.radioButton3.Invoke(new MethodInvoker(delegate () { radioButton3.Enabled = true; }));
               // this.radioButton2.Invoke(new MethodInvoker(delegate () { radioButton2.AutoCheck = true; }));
               // this.radioButton3.Invoke(new MethodInvoker(delegate () { radioButton3.AutoCheck = true; }));
            }
            else
            {
                this.Invoke(new MethodInvoker(delegate () { this.Enabled = false; }));
                //this.checkBox1.Invoke(new MethodInvoker(delegate () { checkBox1.Enabled = false; }));
                //this.checkBox2.Invoke(new MethodInvoker(delegate () { checkBox2.Enabled = false; }));
                //this.checkBox3.Invoke(new MethodInvoker(delegate () { checkBox3.Enabled = false; }));
                //    this.radioButton1.Invoke(new MethodInvoker(delegate () { radioButton1.Enabled = false; }));
                //    this.radioButton1.Invoke(new MethodInvoker(delegate () { radioButton1.AutoCheck = false; }));
                //    this.radioButton2.Invoke(new MethodInvoker(delegate () { radioButton2.Enabled = false; }));
                //    this.radioButton3.Invoke(new MethodInvoker(delegate () { radioButton3.Enabled = false; }));
                //    this.radioButton2.Invoke(new MethodInvoker(delegate () { radioButton2.AutoCheck = false; }));
                //    this.radioButton3.Invoke(new MethodInvoker(delegate () { radioButton3.AutoCheck = false; }));
            }
                        // return ativado;

        }

        private void backgroundWorker2_DoWork(object sender, DoWorkEventArgs e)
        {
           // backgroundWorker1.RunWorkerAsync();
           // backgroundWorker2.WorkerSupportsCancellation = true;

            // System.Threading.Thread.Sleep(1000);

            // backgroundWorker2.WorkerSupportsCancellation = true;
        }

       

        //backgroundWorker1.WorkerSupportsCancellation = true;
        //server();
        //IPAddress ipAd = IPAddress.Parse("10.0.0.13");
        //TcpListener myList = new TcpListener(ipAd, 502);
        //Socket s = myList.AcceptSocket();
        //CaixaTexto.Text += ("Connection accepted from " + s.RemoteEndPoint);

        //byte[] b = new byte[100];
        //int k = s.Receive(b);
        //Console.WriteLine("Recieved...");
        //for (int i = 0; i < k; i++)
        //Console.Write(b[i]);
        //CaixaTexto.Text = "teste";
        //////Convert.

        //ASCIIEncoding asen = new ASCIIEncoding();
        //s.Send(asen.GetBytes("The string was recieved by the server."));
        //Console.WriteLine("\nSent Acknowledgement");
        ////// clean up 
        //System.Threading.Thread.Sleep(1000);
        //s.Close();
        ////myList.Stop();
    }





    //  private void button1_Click_1(object sender, EventArgs e)
    //  {
    //    try
    //    {
    //        IPAddress ipAd = IPAddress.Parse("10.0.0.13");
    //        // use local m/c IP address, and 
    //        // use the same in the client

    //        // Initializes the Listener 
    //        TcpListener myList = new TcpListener(ipAd, 502);

    //        // Start Listeneting at the specified port 
    //        myList.Start();

    //        Console.WriteLine("The server is running at port 502...");
    //        Console.WriteLine("The local End point is  :" +
    //                          myList.LocalEndpoint);
    //        Console.WriteLine("Waiting for a connection.....");

    //        Socket s = myList.AcceptSocket();
    //        Console.WriteLine("Connection accepted from " + s.RemoteEndPoint);

    //        byte[] b = new byte[100];
    //        int k = s.Receive(b);
    //        Console.WriteLine("Recieved...");
    //        for (int i = 0; i < k; i++)
    //            Console.Write(b[i]);
    //        //Convert.

    //        ASCIIEncoding asen = new ASCIIEncoding();
    //        s.Send(asen.GetBytes("The string was recieved by the server."));
    //        Console.WriteLine("\nSent Acknowledgement");
    //        // clean up 
    //        s.Close();
    //        myList.Stop();
    //        Console.Read();
    //    }
    //    catch (Exception g)
    //    {
    //        Console.WriteLine("Error..... " + g.StackTrace);
    //    }
    //}
    // receive = "";
    //  listener.Stop();
    //

    // backgroundWorker2.RunWorkerAsync();
    // backgroundWorker1.WorkerSupportsCancellation = true; // cancelar thread.
    // System.Threading.Thread.Sleep(500);

    //  backgroundWorker1.WorkerSupportsCancellation = true;
}




