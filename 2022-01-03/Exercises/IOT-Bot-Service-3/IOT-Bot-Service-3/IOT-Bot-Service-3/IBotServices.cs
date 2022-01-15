using Microsoft.Bot.Builder.AI.Luis;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace IOT_Bot_Service_3
{
	public interface IBotServices
	{
		LuisRecognizer Dispatch { get; }
	}
}