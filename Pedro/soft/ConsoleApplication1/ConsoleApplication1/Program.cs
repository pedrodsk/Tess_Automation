using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Qual o seu nome: ");
            string nomePessoa;
            nomePessoa = Console.ReadLine();
            Console.Write("Ola " + nomePessoa + ", o que deseja?");
            Console.ReadLine();
            
            Console.ReadKey();
            // Console.Write("oii, hello world");
           // Console.ReadKey();
            
        }
    }
}
