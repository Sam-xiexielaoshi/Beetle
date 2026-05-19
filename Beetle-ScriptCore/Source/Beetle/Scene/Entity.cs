using System;
using System.Runtime.CompilerServices;

namespace Beetle
{
	public class Entity
	{
		protected Entity() { ID = 0; }
		internal Entity(ulong id)
		{
			ID = id;
		}

		public readonly ulong ID;

		public Vector3 Translation
		{
			get
			{
				return GetComponent<TransformComponent>().Translation;
            }

			set
			{
				InternalCalls.TransformComponent_SetTranslation(ID, ref value);
			}
		}

		public T GetComponent<T>() where T : Component, new()
		{

		}
	}
}