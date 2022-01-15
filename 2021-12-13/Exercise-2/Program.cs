using System;
using System.Net.Http.Headers;
using System.Text;
using System.Net.Http;
using System.Web;

namespace CSHttpClientSample
{
    static class Program
    {
        static void Main(string[] args)
        {
            MakeRequest();
            Console.WriteLine("Hit ENTER to exit...");
            Console.ReadLine();
        }

        static async void MakeRequest()
        {
            var client = new HttpClient();
            var queryString = HttpUtility.ParseQueryString(string.Empty);

            // Request headers
            client.DefaultRequestHeaders.Add("Ocp-Apim-Subscription-Key", "7aa30a7a22bd43c1a75968d34f65bb06");

            // Request parameters
            queryString["returnFaceId"] = "true";
            queryString["returnFaceLandmarks"] = "false";
            queryString["returnFaceAttributes"] = "gender,age,emotion";
            queryString["recognitionModel"] = "recognition_03";
            queryString["returnRecognitionModel"] = "false";
            queryString["detectionModel"] = "detection_01";
            queryString["faceIdTimeToLive"] = "86400";
            var uri = "https://eastasia.api.cognitive.microsoft.com/face/v1.0/detect?" + queryString;

            HttpResponseMessage response;

            // Request body
            byte[] byteData = Encoding.UTF8.GetBytes("{\"url\": \"https://upload.wikimedia.org/wikipedia/commons/thumb/e/e8/Mao_Zedong_portrait.jpg/220px-Mao_Zedong_portrait.jpg\"}");

            string result;

            using (var content = new ByteArrayContent(byteData))
            {
                content.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                response = await client.PostAsync(uri, content);
                result = await response.Content.ReadAsStringAsync();
            }

            Console.WriteLine(result);
        }
    }
}