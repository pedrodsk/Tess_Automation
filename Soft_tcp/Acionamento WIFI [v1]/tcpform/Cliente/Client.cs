using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.IO;
using System.Net.Sockets;

namespace Cliente
{
    public class Client
    {
        // Atributos
        private TcpClient tcpclnt;
        private string IP = "10.0.0.14";
        private int port = 502;

        private byte[] Lampada1;
        private byte[] Lampada2;
        private byte[] Lampada3;

        private byte[] ArCondicionado_OFF;
        private byte[] ArCondicionado_17;
        private byte[] ArCondicionado_23;

        private byte[] Estado;

        //Construtor

        public Client()
        {
            this.tcpclnt = null;

            this.Lampada1 = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x01, 0x01 };
            this.Lampada2 = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x01, 0x02 };
            this.Lampada3 = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x01, 0x04 };

            this.ArCondicionado_OFF = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x02, 0x04 };
            this.ArCondicionado_17 = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x02, 0x01 };
            this.ArCondicionado_23 = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x02, 0x03 };

            this.Estado = new byte[] { 0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x00 };
        }

        //Metodos

        public void Conexao(string ip, byte[] dado)
        {
            this.tcpclnt = new TcpClient();
            tcpclnt.Connect(ip, port);

            System.Threading.Thread.Sleep(60);

            Stream stm = tcpclnt.GetStream();
            byte[] dados = dado;
            stm.Write(dados, 0, dados.Length);

            System.Threading.Thread.Sleep(60);

            this.CloseTCPclient();
        }

        public void CloseTCPclient()
        {
            this.tcpclnt.Close();
        }

        public void Lig_Deslig_Lampada1()
        {
            this.Conexao(IP, Lampada1);
        }

        public void Lig_Deslig_Lampada2()
        {
            this.Conexao(IP, Lampada2);
        }

        public void Lig_Deslig_Lampada3()
        {
            this.Conexao(IP, Lampada3);
        }

        public void Desligar_Arcondicionado()
        {
            this.Conexao(IP, ArCondicionado_OFF);
        }

        public void Ligar_Arcondicionado_17()
        {
            this.Conexao(IP, ArCondicionado_17);
        }

        public void Ligar_Arcondicionado_23()
        {
            this.Conexao(IP, ArCondicionado_23);
        }

        public void LerEstado()
        {
            this.Conexao(IP, Estado);
        }
    }
}

