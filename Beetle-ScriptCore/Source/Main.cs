using System;

namespace Beetle
{
    public class Main
    {
        public float FloatVar { get; set; }
        public Main()
        {
            Console.WriteLine("Main Constructor");
        }

        public void PrintMessage()
        {
            Console.WriteLine("This is a message from the Main class.");
        }

        public void PrintInt(int value)
        {
            Console.WriteLine($"C# Integer: {value}");
        }

        public void PrintInts(int value1, int value2)
        {
            Console.WriteLine($"C# Integers: {value1}, {value2}");
        }

        public void PrintCustomMessage(string message)
        {
            Console.WriteLine($"C# Message: {message}");
        }
    }
}