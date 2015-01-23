/*
*  UPPAAAL2C (c) 2014 Ariel Eizenberg - arieleiz@seas.upenn.edu.
*
*    This file is part of UPPAAAL2C. You can redistribute it and/or modify
*    it under the terms of the Academic Free License 3.0
*	  (http://opensource.org/licenses/AFL-3.0).
*
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace uppaal2c
{
    class Program
    {
        const string GENLIST = "genlist:";

        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                System.Console.WriteLine("Syntax: uppaal2c <a.xml> <outdir> [template1 [template2 ...]]");
                System.Console.WriteLine("Syntax: uppaal2c <a.xml> <outdir> <@template.lst>");
                System.Console.WriteLine("To create a template.lst file with all availble templates in UPPAAL XML file:");
                System.Console.WriteLine("   uppaal2c <a.xml> genlist:<templates.lst>");
                return;
            }

            try
            {
                bool gencode = true;
                if (args[1].ToLower().StartsWith(GENLIST))
                    gencode = false;

                List<string> templates = new List<string>();

                if (gencode)
                {
                    for (int i = 2; i < args.Length; ++i)
                    {
                        if (args[i].StartsWith("@"))
                            templates.AddRange(File.ReadAllLines(args[i].Substring(1)).Where(s => !string.IsNullOrWhiteSpace(s)));
                        else
                            templates.Add(args[i]);
                    }
                }

                Model m = UPAALParser.Parse(args[0], templates);
                if (gencode)
                {
                    ReferenceOptimizer.cleanup(m);
                    Generator g = new Generator(m);
                    gensubdirs(args[1]);
                    g.generate(args[1]);
                    TemplateExtractor.extract(args[1]);
                }
                else
                {
                    string fname = args[1].Substring(GENLIST.Length);
                    if(fname.Equals(args[0], StringComparison.InvariantCultureIgnoreCase))
                        throw new ApplicationException("List file name equal to XML name!");

                    File.WriteAllLines(fname, m.Templates.Select(t => t.Name));
                    Console.WriteLine("Generated: " + fname);
                }
            }
            catch (Exception e)
            {
                System.Console.WriteLine("Error: " + e.Message);
                System.Console.WriteLine("At:");
                System.Console.WriteLine(e.StackTrace);
            }
        }

        static void gensubdirs(string path)
        {
            try
            {
                Directory.CreateDirectory(Path.GetDirectoryName(path));
            }
            catch
            {
            }
        }
    }
}
