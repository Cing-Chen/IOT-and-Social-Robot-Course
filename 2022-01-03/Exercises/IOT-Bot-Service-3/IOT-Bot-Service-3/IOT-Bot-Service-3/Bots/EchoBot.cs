// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
//
// Generated with Bot Builder V4 SDK Template for Visual Studio EchoBot v4.15.0

using Microsoft.Bot.Builder;
using Microsoft.Bot.Schema;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;

namespace IOT_Bot_Service_3.Bots
{
    public class EchoBot : ActivityHandler
    {
        protected override async Task OnMessageActivityAsync(ITurnContext<IMessageActivity> turnContext, CancellationToken cancellationToken)
        {
            var replyText = $"Echo: {turnContext.Activity.Text}";
            await turnContext.SendActivityAsync(MessageFactory.Text(replyText, replyText), cancellationToken);

            var recognizerResult = await _botServices.Dispatch.RecognizeAsync(turnContext, cancellationToken);
            var topIntent = recognizerResult.GetTopScoringIntent();
            await DispatchToTopIntentAsync(turnContext, topIntent.intent, recognizerResult, cancellationToken);
        }

        protected override async Task OnMembersAddedAsync(IList<ChannelAccount> membersAdded, ITurnContext<IConversationUpdateActivity> turnContext, CancellationToken cancellationToken)
        {
            var welcomeText = "Hello and welcome!";
            foreach (var member in membersAdded)
            {
                if (member.Id != turnContext.Activity.Recipient.Id)
                {
                    await turnContext.SendActivityAsync(MessageFactory.Text(welcomeText, welcomeText), cancellationToken);
                }
            }
        }

        private async Task DispatchToTopIntentAsync(ITurnContext<IMessageActivity> turnContext, string intent, RecognizerResult recognizerResult, CancellationToken cancellationToken)
        {
            switch (intent)
            {
                case "Book_Meal":
                    await turnContext.SendActivityAsync(MessageFactory.Text($"收到您的訂單囉peko"), cancellationToken);
                    break;
                case "Good_Opinion":
                    await turnContext.SendActivityAsync(MessageFactory.Text($"謝謝您喜歡我們peko"), cancellationToken);
                    break;
                case "Bad_Opinion":
                    await turnContext.SendActivityAsync(MessageFactory.Text($"不爽不要吃peko"), cancellationToken);
                    break;
                case "Suggestion":
                    await turnContext.SendActivityAsync(MessageFactory.Text($"謝謝您的建議，我們會更peko的"), cancellationToken);
                    break;
                default:
                    await turnContext.SendActivityAsync(MessageFactory.Text($"分類錯誤"), cancellationToken);
                    //await turnContext.SendActivityAsync(MessageFactory.Text(intent), cancellationToken);
                    break;
            }
        }

        private IBotServices _botServices;

        public EchoBot(IBotServices botServices)
        {
            this._botServices = botServices;
        }
    }
}
