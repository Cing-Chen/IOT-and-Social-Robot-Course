using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Linq;

namespace Exercise3
{
    class Program
    {
        static void Main(string[] args)
        {
            jsonFormat json = new jsonFormat();

            json.fruit = new List<string>
            {
                "apple",
                "banana",
                "grape"
            };

            json.color = new Dictionary<string, string>()
            {
                {"apple", "red"},
                {"banana", "yellow"},
                {"grape", "purple"}
            };

            json.restaurant = new Dictionary<string, Dictionary<string, string>>()
            {
                {"apple", new Dictionary<string, string> {{"left", "5"}, {"price", "10"}}},
                {"banana", new Dictionary<string, string> {{"left", "10"}, {"price", "15"}}},
                {"grape", new Dictionary<string, string> {{"left", "12"}, {"price", "20"}}}
            };

            json.info = new List<Dictionary<string, string>>()
            {
                new Dictionary<string, string> {{"food", "apple"}, {"left", "5"}, {"price", "10"}},
                new Dictionary<string, string> {{"food", "banana"}, {"left", "10"}, {"price", "15"}},
                new Dictionary<string, string> {{"food", "grape"}, {"left", "12"}, {"price", "20"}}
            };

            string jsonString = JsonConvert.SerializeObject(json);

            JObject jsonObject = JObject.Parse(jsonString);

            foreach(var item in jsonObject["restaurant"])
            {
                Console.WriteLine(item.ToString());
            }
        }
    }

    public class jsonFormat
    {
        public List<string> fruit;
        public Dictionary<string, string> color;
        public Dictionary<string, Dictionary<string, string>> restaurant;
        public List<Dictionary<string, string>> info;
    }
}