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
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace uppaal2c
{
    class StateTransition
    {
        public StateTransition(string tmplname, StateNode src, StateNode tgt, String name = null)
        {
            int id = 0;
            string names = String.Format("{0}__{1}", src.BaseName, tgt.BaseName);

            string fullname = tmplname + "_" + names;
            _idCounter.TryGetValue(fullname, out id);
            _idCounter[fullname] = id + 1;

            if (name != null)
                BaseName = name;
            else
                BaseName = String.Format("{0}", id);

            Name = String.Format("{0}__{1}", names, BaseName);
            Source = src;
            Target = tgt;
        }

        static Dictionary<string, int> _idCounter = new Dictionary<string, int>();

        public string Name { get; private set;  }
        public string BaseName { get; set; }
        public StateNode Source { get; private set; }
        public StateNode Target { get; private set; }
        public Rule[] Rules { get; set; }
    }
}
