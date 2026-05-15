using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Beetle;

namespace Sandbox
{
    public class Player : Entity
    {
        void OnCreate()
        {
            Console.WriteLine("OnCreate");
        }

        void OnUpate(float ts)
        {
            Console.WriteLine("OnUpdate: " + ts);
        }

    }
}
