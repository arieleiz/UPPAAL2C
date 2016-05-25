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
    public enum RuleType {  Select, Guard, Sync, Update };

    public class Rule
    {
        protected Rule(RuleType type, Expression e)
        {
            Type = type;
            Expr = e;
        }

        public RuleType Type { get; private set; }
        public Expression Expr { get; private set; }
    }

    class GuardRule : Rule
    {
        public GuardRule(Expression e) : base(RuleType.Guard, e)
        {
        }

    }
    class SyncRule : Rule
    {
        public enum Direction { Send, Receive };

        public SyncRule(Expression e, Direction d)
            : base(RuleType.Sync, e)
        {
            Dir = d;
        }

        public Direction Dir { get; private set; }
    }

    class UpdateRule : Rule
    {
        public UpdateRule(string vname, Expression e)
            : base(RuleType.Update, e)
        {
            VarName = vname;
        }

        public string VarName { get; private set; }
    }
}
