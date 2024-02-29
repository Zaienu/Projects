using System;
using System.IO;
using Newtonsoft.Json;

namespace Helper
{
    public static class JSON_Helper
    {
        public static void SaveToJSON<T>(T _data, string _filePath)
        {
            string json = JsonConvert.SerializeObject(_data, Formatting.Indented);
            File.WriteAllText(_filePath, json);
        }

        public static T? LoadFromJSON<T>(string _filePath, bool _canReturnNull = false) where T : new()
        {
            if (!File.Exists(_filePath))
            {
                throw new Exception("JSON_Helper ERROR : the filePath specified is invalid");
            }

            string json = File.ReadAllText(_filePath);

            if (string.IsNullOrWhiteSpace(json))
            {
                return _canReturnNull ? default : new T();
            }

            try
            {
                T? deserializedData = JsonConvert.DeserializeObject<T?>(json);
                return deserializedData ?? (_canReturnNull ? default : new T());
            }
            catch (JsonException)
            {
                return _canReturnNull ? default : new T();
            }
        }
    }
}