using System.Net;
using System.IO;
using System.Net.Sockets;

namespace Servidor
{
    public class Server
    {
        //Atributos
        private const int buffer = 1024;
        public int Buffer { get { return buffer; } }
        private const int port = 502;
        public int Port { get { return port; } }

        private TcpListener listener;

        private IPAddress[] localIP;
        private IPAddress IPlocal;
        public IPAddress IPLocal { get { return IPlocal; } }

        private TcpClient client;
        private StreamReader stream;

        private string receive;
        public string Receive { get { return receive; } }

        //Construtor
        public Server()
        {
            this.localIP = Dns.GetHostAddresses(Dns.GetHostName());
            foreach (IPAddress ipAd in localIP)
            {
                if (ipAd.AddressFamily == AddressFamily.InterNetwork)
                {
                    this.IPlocal = ipAd;
                    this.listener = new TcpListener(ipAd, port);
                }
            }
            this.receive = null;

        }

        //Metodos
        public void StartListener()
        {
            this.listener.Start(); 
        }

        public bool Listener_Pending()
        {
            return this.listener.Pending();
        }

        public void AcceptClient()
        {     
            this.client = listener.AcceptTcpClient();
        }

        public void StartReceive()
        {
            this.stream = new StreamReader(client.GetStream());
            this.receive = stream.ReadLine();
        }

        public bool Client_IsConnected()
        {
            return this.client.Connected;
        }

        public void CloseConnection()
        {
            this.stream.Close();
            this.client.Close();
        }

    }
}
