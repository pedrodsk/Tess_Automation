
//
/*   Server Program    */
 /*
using System;
using System.Text;
using System.Net;
using System.Net.Sockets;

public class serv
{
    public static void Main()
    {
        try
        {
            IPAddress ipAd = IPAddress.Parse("10.0.0.13");
            // use local m/c IP address, and 
            // use the same in the client

            // Initializes the Listener 
TcpListener myList = new TcpListener(ipAd, 502);

            // Start Listeneting at the specified port 
            myList.Start();

            Console.WriteLine("The server is running at port 502...");
            Console.WriteLine("The local End point is  :" +
                              myList.LocalEndpoint);
            Console.WriteLine("Waiting for a connection.....");

            Socket s = myList.AcceptSocket();
            Console.WriteLine("Connection accepted from " + s.RemoteEndPoint);

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
            myList.Stop();
            Console.Read();
        }
        catch (Exception e)
        {
            Console.WriteLine("Error..... " + e.StackTrace);
        }
    }

}
  //  */
/*       Client Program      */

using System;
using System.IO;
using System.Net;
using System.Text;
using System.Net.Sockets;


public class clnt
{

    public static void Main()
    {
        TcpClient tcpclnt = new TcpClient();
        try
        {
           // TcpClient tcpclnt = new TcpClient();
            tcpclnt.Connect("10.0.0.14", 502);
            Stream stm = tcpclnt.GetStream();
            //Console.Read();
            byte[] dado = new byte[] {0x0A, 0x2E, 0x00, 0x2E, 0x00, 0x2E, 0x0D, 0x01, 0x01};
            stm.Write(dado, 0, dado.Length);
            tcpclnt.Close();

        }

        catch (Exception e)
        {
            Console.WriteLine("Error..... " + e.StackTrace);
            tcpclnt.Close();
            Console.Read();
        }
    }

}
//*/
//