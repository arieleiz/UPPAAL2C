﻿/*
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
    class Model
    {
        public Model(Declarations decls, Template[] templates)
        {
            Declarations = decls;
            Templates = templates;
        }

        public Declarations Declarations { get; private set; }
        public Template[] Templates { get; private set; }
    }

}