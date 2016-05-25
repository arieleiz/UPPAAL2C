using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace uppaal2c
{
    class TemplateExtractor
    {
        public static void extract(string outdir)
        {
            var rs = templates.Templates.ResourceManager.GetResourceSet(new System.Globalization.CultureInfo(""), true, true);
            string s = templates.Templates.uppaal2c___c;
            foreach(var r in rs)
            {
                var de = (System.Collections.DictionaryEntry)r;
                string name = de.Key.ToString().Replace("___", ".");
                string contents = de.Value.ToString();

                string path = Path.Combine(outdir, name);
                int mine = getStreamVersion(new StringReader(contents));
                int existing = -1;
                if (File.Exists(path))
                {
                    existing = getStreamVersion(new StreamReader(path));
                }
                if(mine <= existing)
                {
                    Console.WriteLine("File {0} already exists (same or newer version).", name);
                    continue;
                }
                if(mine > existing)
                {
                    if (existing >= 0)
                        Console.WriteLine("Replacing file {0} (older version).", name);
                    else
                        Console.WriteLine("Extracting {0}.", name);
                }
                File.WriteAllText(path, contents);
            }

        }

        const string VERSION_PREFIX = "// VERSION: ";

        private static int getStreamVersion(TextReader s)
        {
            string line = s.ReadLine();
            if (!line.StartsWith(VERSION_PREFIX))
                return int.MaxValue;
            int ver;
            if (!int.TryParse(line.Substring(VERSION_PREFIX.Length), out ver))
                return int.MaxValue;
            return ver;
        }
    }
}
