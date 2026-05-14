using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Sandbox
{
    public class Player
    {
        void OnCreate()
        {
            Console.WriteLine("OnCreate");
        }

        void OnUpate(float ts)
        {
            Console.WriteLine("OnUpdate: " + ts);
        }

        void OnDestroy()
        {
            Console.WriteLine("OnDestroy");
        }
    }
}
