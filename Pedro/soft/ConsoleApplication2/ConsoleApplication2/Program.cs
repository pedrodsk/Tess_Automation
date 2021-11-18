using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EasyModbus;

namespace ConsoleApplication2
{
    class Program
    {
        //private string ip = "192.168.1.80";
        private string ip2;
        private int porta = 502;
        private ushort inicio = 0;
        private ushort quantidade = 2;
        private ModbusClient Modbus;
        public Program()
        {
           // string ip2;
            Console.WriteLine("digite o ip:");
            ip2 = Console.ReadLine();
            Modbus = new ModbusClient(ip2, porta);
            Modbus.Connect();
            int[] response = Modbus.ReadHoldingRegisters(inicio, quantidade);
            Modbus.Disconnect();
            Console.WriteLine("valor das entradas"+ response[0].ToString());
            Console.WriteLine("valor das entradas" + response[1].ToString());
        }
        static void Main(string[] args)
        {
            Program _program = new Program();
            Console.ReadKey();
        }
    }
}
