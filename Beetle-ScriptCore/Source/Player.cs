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
            Console.WriteLine("Player.OnCreate");
        }

        void OnUpdate(float ts)
        {
            Console.WriteLine($"OnUpdate: {ts}");

            Vector3 translation = Translation;
            translation.X += speed;
            Translation = translation;
        }

    }
}
