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

namespace uppaal2c
{
    class Template
    {
        // add paramters later
        public Template(string name, Declarations declarations, StateNode initial, StateNode[] nodes, StateTransition[] transitions)
        {
            Name = name;
            Declarations = declarations;
            Initial = initial;
            Nodes = nodes;
            Transitions = transitions;

           
        }

        public string Name { get; private set; }
        public Declarations Declarations { get; private set; }
        public StateNode Initial { get; private set;  }
        public StateNode[] Nodes { get; private set; }
        public StateTransition[] Transitions { get; private set; }

    }
}
