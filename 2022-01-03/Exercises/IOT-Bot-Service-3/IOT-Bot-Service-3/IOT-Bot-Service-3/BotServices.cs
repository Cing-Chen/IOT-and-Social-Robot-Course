using Microsoft.Bot.Builder.AI.Luis;
using Microsoft.Extensions.Configuration;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace IOT_Bot_Service_3
{
    public class BotServices : IBotServices
    {
        public BotServices(IConfiguration configuration)
        {
            Dispatch = new LuisRecognizer(new LuisApplication(
                configuration["LuisAppId"],
                configuration["LuisAPIKey"],
                $"https://{configuration["LuisAPIHostName"]}"),
                new LuisPredictionOptions { IncludeAllIntents = true, IncludeInstanceData = true },
                true);
        }
        public LuisRecognizer Dispatch { get; private set; }
    }

}