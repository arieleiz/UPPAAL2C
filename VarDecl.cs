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
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

namespace uppaal2c
{
    public class VarDecl 
    {
        public VarDecl(string name, TypeDecl type)
        {
            Name = name;
            Type = type;
            IsArray = false;
            ArrLow = 0;
            ArrLength = 0;
            HasExpr = false;
            Expr = null;
        }

        public string Name { get; set; }
        public TypeDecl Type { get; set; }
        public bool IsArray { get; set; }
        public int ArrLow { get; set; }
        public int ArrLength { get; set; }
        public bool HasExpr { get; set; }
        public Expression Expr { get; set;  }
        public bool Referenced { get; set; }

        public string NiceName()
        {
            String nice = String.Format("{0} {1}", Type.NiceName(), Name);
            if(IsArray)
                nice += String.Format("[{0},{1}]", ArrLow, ArrLow + ArrLength - 1);

            return nice;
        }
    }
}
