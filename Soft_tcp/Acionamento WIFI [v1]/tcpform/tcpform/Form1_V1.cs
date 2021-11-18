using System;
using System.ComponentModel;
using System.Linq;
using System.Windows.Forms;

using Cliente;
using Servidor;

namespace tcpform
{
    public partial class Form1_V1 : Form
    {
        #region Atributos
        Client client = new Client();
        Server server = new Server();
        public Boolean estado = false;
        public Boolean ativado = false;

        #endregion

        public Form1_V1()

        {
            InitializeComponent();

            textBox_IP.Text = server.IPLocal.ToString();
            textBox_Porta.Text = server.Port.ToString();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                //this.Enable(false);
                server.StartListener();
            }
            catch (Exception s)
            {        
                MessageBox.Show("Error: Listernet.Start()" + s.Message);
            }
            estado = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {

            if (server.Listener_Pending())
            {
                server.AcceptClient();
                this.backgroundWorker1.RunWorkerAsync();
            }

            if (estado == true)
            {
                System.Threading.Thread.Sleep(100);
                try
                {
                    client.LerEstado();
                }
                catch (Exception s)
                {
                    client.CloseTCPclient();
                    MessageBox.Show("Error: LerEstado()" + s.Message );
                }
                estado = false;
            }
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            try
            {
                if (server.Client_IsConnected())
                {
                    server.StartReceive();
                    this.AtualizaEstado(server.Receive);  
                }
            }
            catch (Exception s)
            {
                MessageBox.Show("Error: Client Connected" + s.Message);
            }
            finally
            {
                this.Enable(true);
                System.Threading.Thread.Sleep(150);
                server.CloseConnection();
            }
        }

        
        #region Eventos checkbox e radiobutton

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            try
            {
                this.Enable(false);
                client.Lig_Deslig_Lampada1();
            }
            catch (Exception s)
            {
                client.CloseTCPclient();
                MessageBox.Show("Error: Lampada1()" + s.Message);
            }
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            try
            {
                this.Enable(false);
                client.Lig_Deslig_Lampada2();
            }
            catch (Exception s)
            {
                client.CloseTCPclient();
                MessageBox.Show("Error: Lampada2()" + s.Message);
            }     
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            try
            {
                this.Enable(false);
                client.Lig_Deslig_Lampada3();
            }
            catch (Exception s)
            {
                client.CloseTCPclient();
                MessageBox.Show("Error: Lampada3()" + s.Message);
            }
        }

        private void radioButton1_MouseClick(object sender, MouseEventArgs e)
        {
            try
            {
                client.Desligar_Arcondicionado();
            }
            catch (Exception s)
            {
                client.CloseTCPclient();
                MessageBox.Show("Error: DesligarAr()" + s.Message);
            }
        }

        private void radioButton2_MouseClick(object sender, MouseEventArgs e)
        {
            try
            {
                client.Ligar_Arcondicionado_17();
            }
            catch (Exception s)
            {
                client.CloseTCPclient();
                MessageBox.Show("Error: Ar17()" + s.Message);
            }
        }

        private void radioButton3_MouseClick(object sender, MouseEventArgs e)
        {
            try
            {
                client.Ligar_Arcondicionado_23();
            }
            catch (Exception s)
            {
                client.CloseTCPclient();
                MessageBox.Show("Error: Ar23()" + s.Message);
            }
        }

        #endregion


        private void AtualizaEstado(string receive)
        {
            //Informa a hora da requisição
            this.textBox_Hora.Invoke(new MethodInvoker(delegate () { this.textBox_Hora.Text = DateTime.Now.ToString("HH:mm"); }));

            //Informa o novo estado das lampadas
            #region Switch
            switch (receive)
            {
                case "A.0.0.E10":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.Text = "Lâmpadas Desligadas"; }));
                    this.MudaCheckbox(false, false, false); 
                    break;

                case "A.0.0.E11":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.Text = "Lâmpada 1 Ligada"; }));
                    this.MudaCheckbox(true, false, false);
                    break;

                case "A.0.0.E12":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate (){ textBox_InfoConexao.Text = "Lâmpada 2 Ligada"; }));
                    this.MudaCheckbox(false, true, false);
                    break;

                case "A.0.0.E13":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate (){ textBox_InfoConexao.Text= "Lâmpadas 1 e 2 Ligadas"; }));
                    this.MudaCheckbox(true, true, false);
                    break;

                case "A.0.0.E14":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.Text = "Lâmpada 3 Ligada"; }));
                    this.MudaCheckbox(false, false, true);
                    break;

                case "A.0.0.E15":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate () { textBox_InfoConexao.Text= "Lâmpada 1 e 3 Ligadas"; }));
                    this.MudaCheckbox(true, false, true);
                    break;
                case "A.0.0.E16":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate (){ textBox_InfoConexao.Text= "Lâmpada 2 e 3 Ligadas"; }));
                    this.MudaCheckbox(false, true, true);
                    break;

                case "A.0.0.E17":
                    this.textBox_InfoConexao.Invoke(new MethodInvoker(delegate (){ textBox_InfoConexao.Text = "Lâmpadas Ligadas"; }));
                    this.MudaCheckbox(true,true,true); 
                    break;
            }
            #endregion

        }//Fim função AtualizaEstado

        private void MudaCheckbox(bool c1, bool c2, bool c3)
        {
            this.checkBox1.Invoke(new MethodInvoker(delegate () { checkBox1.Checked = c1; }));
            this.checkBox2.Invoke(new MethodInvoker(delegate () { checkBox2.Checked = c2; }));
            this.checkBox3.Invoke(new MethodInvoker(delegate () { checkBox3.Checked = c3; }));
        }

        private void Enable(Boolean ativado)
        {
            if (ativado == true)
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

        }//Fim função enable

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

    }//fim classe Form1_v1

}//Fim Namespace

















//    string connectionString = @"Data Source=(LocalDB)\MSSQLLocalDB;AttachDbFilename=C:\USERS\OPERACAO\DESKTOP\TCPFORM[V2]\TCPFORM\TCPFORM\ACIONAMENTOWIFIDB.MDF;Integrated Security=True;Connect Timeout=30";
//   SqlConnection sqlconnection = new SqlConnection(connectionString);
//   sqlconnection.Open();








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


