using System;

namespace tests
{
    class Program
    {
        static void Main(string[] args)
        {

            string test = "hal$lo$!ha¨l!lo";
            string[] splitter = test.Split("$!");

            Console.WriteLine("string 1 = " + splitter[0] + "\n" + "string 2 = "+splitter[1]);
        }
    }
}
