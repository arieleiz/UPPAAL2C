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
    public enum NodeMode
    {
        Regular,
        Commited,
        Urgent
    };

    class StateNode
    {
        public static int count = 0;

        public StateNode(string name, string nodeid, NodeMode mode)
        {
            Id = count++;
            if (string.IsNullOrEmpty(name))
                BaseName = String.Format("Unnamed{0}", Id);
            else
                BaseName = name;
            Name = BaseName;
            NodeId = nodeid;
            Mode = mode;
        }

        public int Id { get;private set; }
        public string Name { get; private set; }
        public string BaseName { get; private set; }
        public string NodeId { get; private set; }
        public Rule[] Rules { get; set; }
        public bool Commited { get; private set; }
        public NodeMode Mode { get; private set; }


    }
}
