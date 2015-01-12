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
using System.Globalization;
using System.Linq;
using System.Linq.Expressions;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace uppaal2c
{
    public class Expression
    {
        public enum ExpType
        {
            ConstInt,
            ConstBool,
            Var,
            Func,
        };

        public enum Funcs
        {
            [FU(FM.Binary, "{0}+{1}")] BinPlus,
            [FU(FM.Binary, "{0}-{1}")]BinMinus,
            [FU(FM.Unary, "+{0}")] UniPlus,
            [FU(FM.Unary, "-{0}")] UniMinus,
            [FU(FM.Unary, "++{0}")] UniPlusPlusPre,
            [FU(FM.Unary, "--{0}")] UniMinusMinusPre,
            [FU(FM.Unary, "{0}++")] UniPlusPlusPost,
            [FU(FM.Unary, "{0}++")] UniMinusMinusPost,
            [FU(FM.Binary, "{0}*{1}")] Multi,
            [FU(FM.Binary, "{0}/{1}")] Divide,
            [FU(FM.Binary, "{0}%{1}")] Modulus,
            [FU(FM.Binary, "{0}<<{1}")] LeftBitShift,
            [FU(FM.Binary, "{0}>>{1}")] RightBitShift,
            [FU(FM.Binary, "{0}&{1}")] BitAnd,
            [FU(FM.Binary, "{0}|{1}")] BitOr,
            [FU(FM.Binary, "{0}^{1}")] BitXor,
            [FU(FM.Binary, "{0}>{1}")] Larger,
            [FU(FM.Binary, "{0}>={1}")] LargerEqual,
            [FU(FM.Binary, "{0}<{1}")] Smaller,
            [FU(FM.Binary, "{0}<={1}")] SmallEqual,
            [FU(FM.Binary, "{0}=={1}")] Equal,
            [FU(FM.Binary, "{0}!={1}")] NotEqual,
            [FU(FM.Binary, "_min({0},{1})")] Min,
            [FU(FM.Binary, "_max({0},{1})")] Max,
            [FU(FM.Unary, "!{0}")] LogicalNot,
            [FU(FM.Binary, "{0}&&{1}")] LogicalAnd,
            [FU(FM.Binary, "{0}||{1}")] LogicalOr,
            [FU(FM.Trenary, "{0}?{1}:{2}")] IfThenElse,
            [FU(FM.Binary, "{0}[{1}]")] ArrayIndex,
        };

        public Expression(int value)
        {
            Type = ExpType.ConstInt;
            Value = value;
        }

        public Expression(bool value)
        {
            Type = ExpType.ConstBool;
            Value = value ? 1 : 0;
        }

        public Expression(string var)
        {
            Type = ExpType.Var;
            Var = var;
        }


        public Expression(Funcs func, Expression first, Expression second = null, Expression third = null)
        {
            Type = ExpType.Func;
            Func = func;
            First = first;
            Second = second;
            Third = third;
        }

        public static Expression CreateCustomFunc(Expression expr, List<Expression> args)
        {
            if (expr == null)
                throw new ParseException("Function name cannot be null.");

            if(expr.Type != ExpType.Var)
                throw new ParseException("Function name must be a string.");

            switch(expr.Var)
            {
                case "min": 
                    if(args.Count != 2)
                        throw new ParseException("min() must have two arguments.");
                    return new Expression(Funcs.Min, args[0], args[1]);

                case "max":
                    if (args.Count != 2)
                        throw new ParseException("max() must have two arguments.");
                    return new Expression(Funcs.Max, args[0], args[1]);

                // add other functions later if necessary
            }

            // custom user function
            // Easy to add if needed later
            throw new ParseException("Custom user functions not required!");
        }

        public ExpType Type { get; private set; }
        public Expression First { get; private set; }
        public Expression Second { get; private set; }
        public Expression Third { get; private set; }
        public int Value { get; private set; }
        public string Var { get; private set; }
        public Funcs Func { get; private set; }

        public TypeDecl GetType(Declarations symtab)
        {
            switch (Type)
            {
                case ExpType.ConstInt:
                    return new TypeDecl() { Type = VarType.Int };
                case ExpType.ConstBool:
                    return new TypeDecl() { Type = VarType.Int };

                case ExpType.Var:
                    VarDecl v = symtab.getVar(Var);
                    if (v == null)
                        throw new ParseException(String.Format("Unknown variable {0}", Var));
                    return v.Type;

                case ExpType.Func:
                    // this should be improved later
                    return new TypeDecl() { Type = VarType.Int };

                default:
                    throw new ParseException("Internal error 1");
            }
        }

        public void fold(Declarations symtab)
        {
            switch (Type)
            {
                case ExpType.ConstInt:
                    break;
                case ExpType.ConstBool:
                    break;

                case ExpType.Var:
                    int val = 0;
                    if (symtab.getVarValue(Var, out val))
                    {
                        Value = val;
                        Type = ExpType.ConstInt;
                    }
                    break;

                case ExpType.Func:
                    while (foldFunc(symtab))
                    { }

                    break;
            }
        }

        static bool getFoldedValue(Expression e, Declarations symtab, out int val)
        {
            val = 0;
            if (e == null)
                return false;

            e.fold(symtab);

            if (e.Type != ExpType.ConstInt && e.Type != ExpType.ConstBool)
                return false;

            val = e.Value;
            return true;
        }
        static bool getFoldedBoolValue(Expression e, Declarations symtab, out bool val)
        {
            val = false;
            if (e == null)
                return false;

            e.fold(symtab);

            if (e.Type != ExpType.ConstBool)
                return false;

            val = e.Value != 0;
            return true;
        }

        private bool foldFunc(Declarations symtab)
        {
            bool gotfirst, gotsecond;
            int first, second, third;
            bool firstb, secondb;

            switch(Func)
            {
            case Funcs.BinPlus:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstInt;
                        Value = first + second;
                        return false;
                    }

                    if(gotfirst && first == 0)
                    {
                        copyFrom(Second);
                        return false;
                    }
                    if (gotsecond && second == 0)
                    {
                        copyFrom(First);
                        return false;
                    }

                    break;

            case Funcs.BinMinus:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstInt;
                        Value = first - second;
                        return false;
                    }

                    if (gotsecond && second == 0)
                    {
                        copyFrom(First);
                        return false;
                    }

                    break;

            case Funcs.UniPlus:
                    copyFrom(First);
                    return false;

            case Funcs.UniMinus:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    if (gotfirst)
                    {
                        Type = ExpType.ConstInt;
                        Value = -first;
                        return false;
                    }
                    if (First.Type == ExpType.Func && First.Func == Funcs.UniMinus)
                    {
                        copyFrom(First.First);
                        return false;
                    }

                    break;

            case Funcs.UniPlusPlusPre:
                    break;

            case Funcs.UniMinusMinusPre:
                    break;

            case Funcs.UniPlusPlusPost:
                    break;

            case Funcs.UniMinusMinusPost:
                    break;

            case Funcs.Multi:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstInt;
                        Value = first * second;
                        return false;
                    }
                    if(gotfirst && first == 0)
                    {
                        Type = ExpType.ConstInt;
                        Value = 0;
                        return false;
                    }

                    if (gotsecond && second == 0)
                    {
                        Type = ExpType.ConstInt;
                        Value = 0;
                        return false;
                    }


                    if (gotfirst && first == 1)
                    {
                        copyFrom(Second);
                        return false;
                    }
                    if (gotsecond && second == 1)
                    {
                        copyFrom(First);
                        return false;
                    }

                    if(first == -1)
                    {
                        First = Second;
                        Second = null;
                        Func = Funcs.UniMinus;
                        return true;
                    }
                    if (second == -1)
                    {
                        Second = null;
                        Func = Funcs.UniMinus;
                        return true;
                    }
                    break;

            case Funcs.Divide:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstInt;
                        Value = first / second;
                        return false;
                    }
                    if(gotfirst && first == 0)
                    {
                        Type = ExpType.ConstInt;
                        Value = 0;
                        return false;
                    }

                    if (gotsecond && second == 0)
                    {
                        throw new ParseException("Divide by Zero!");
                    }

                    if (gotsecond && second == 1)
                    {
                        copyFrom(First);
                        return false;
                    }

                    if(first == -1)
                    {
                        First = Second;
                        Second = null;
                        Func = Funcs.UniMinus;
                        return true;
                    }
                    if (second == -1)
                    {
                        Second = null;
                        Func = Funcs.UniMinus;
                        return true;
                    }
                    break;


            case Funcs.Modulus:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstInt;
                        Value = first % second;
                        return false;
                    }
                    if(gotfirst && first == 0)
                    {
                        Type = ExpType.ConstInt;
                        Value = 0;
                        return false;
                    }

                    if (gotsecond && second == 0)
                    {
                        throw new ParseException("Divide by Zero!");
                    }

                    if (gotsecond && second == 1)
                    {
                        Type = ExpType.ConstInt;
                        Value = 0;
                        return false;
                    }
                    break;

            case Funcs.Max:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstInt;
                        Value = (first > second) ? first : second;
                        return false;
                    }
                    break;

            case Funcs.Min:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstInt;
                        Value = (first > second) ? second : first;
                        return false;
                    }
                    break;

            case Funcs.LeftBitShift:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstInt;
                        Value = first << second;
                        return false;
                    }

                    if (gotsecond && second == 0)
                    {
                        copyFrom(Second);
                        return false;
                    }
                    break;

            case Funcs.RightBitShift:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstInt;
                        Value = first >> second;
                        return false;
                    }

                    if (gotsecond && second == 0)
                    {
                        copyFrom(Second);
                        return false;
                    }
                    break;

            case Funcs.BitAnd:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstInt;
                        Value = first & second;
                        return false;
                    }

                    if (gotfirst && first == 0)
                    {
                        Type = ExpType.ConstInt;
                        Value = 0;
                        return false;
                    }

                    if (gotsecond && second == 0)
                    {
                        Type = ExpType.ConstInt;
                        Value = 0;
                        return false;
                    }

                    break;

            case Funcs.BitOr:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstInt;
                        Value = first | second;
                        return false;
                    }

                    if (gotfirst && first == 0)
                    {
                        copyFrom(Second);
                        return false;
                    }

                    if (gotsecond && second == 0)
                    {
                        copyFrom(First);
                        return false;
                    }

                    break;

            case Funcs.BitXor:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstInt;
                        Value = first ^ second;
                        return false;
                    }

                    break;

            case Funcs.Larger:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstInt;
                        Value = (first > second) ? 1 : 0;
                        return false;
                    }
                    break;

            case Funcs.LargerEqual:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstBool;
                        Value = (first >= second) ? 1 : 0;
                        return false;
                    }
                    break;

            case Funcs.Smaller:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstBool;
                        Value = (first < second) ? 1 : 0;
                        return false;
                    }
                    break;

            case Funcs.SmallEqual:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstBool;
                        Value = (first <= second) ? 1 : 0;
                        return false;
                    }
                    break;

            case Funcs.Equal:
                    gotfirst = getFoldedBoolValue(First, symtab, out firstb);
                    gotsecond = getFoldedBoolValue(Second, symtab, out secondb);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstBool;
                        Value = (firstb == secondb) ? 1 : 0;
                        return false;
                    }
                    if(gotfirst)
                    {
                        if (firstb)
                            copyFrom(Second);
                        else
                        {
                            Func = Funcs.LogicalNot;
                            First = Second;
                            Second = null;
                        }
                        return true;
                    }
                    if(gotsecond)
                    {
                        if (secondb)
                            copyFrom(First);
                        else
                        {
                            Func = Funcs.LogicalNot;
                            Second = null;
                        }
                        return true;
                    }
                    
                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstBool;
                        Value = (first == second) ? 1 : 0;
                        return false;
                    }
                    break;
            case Funcs.NotEqual:
                    gotfirst = getFoldedBoolValue(First, symtab, out firstb);
                    gotsecond = getFoldedBoolValue(Second, symtab, out secondb);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstBool;
                        Value = (firstb != secondb) ? 1 : 0;
                        return false;
                    }
                    if(gotfirst)
                    {
                        if (!firstb)
                            copyFrom(Second);
                        else
                        {
                            Func = Funcs.LogicalNot;
                            First = Second;
                            Second = null;
                        }
                        return true;
                    }
                    if(gotsecond)
                    {
                        if (!secondb)
                            copyFrom(First);
                        else
                        {
                            Func = Funcs.LogicalNot;
                            Second = null;
                        }
                        return true;
                    }

                    gotfirst = getFoldedValue(First, symtab, out first);
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstBool;
                        Value = (first != second) ? 1 : 0;
                        return false;
                    }
                    break;
            case Funcs.LogicalNot:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    if (gotfirst)
                    {
                        Type = ExpType.ConstBool;
                        Value = (first != 0) ? 0 : 1;
                        return false;
                    }
                    break;

            case Funcs.LogicalAnd:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    if(gotfirst && first == 0)
                    {
                        Type = ExpType.ConstBool;
                        Value = 0;
                        return false;
                    }
                        
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotsecond && second == 0)
                    {
                        Type = ExpType.ConstBool;
                        Value = 0;
                        return false;
                    }

                    if(gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstBool;
                        Value = (first != 0 && second != 0) ? 1 : 0;
                        return false;
                    }
                    break;

            case Funcs.LogicalOr:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    if(gotfirst && first == 1)
                    {
                        Type = ExpType.ConstBool;
                        Value = 1;
                        return false;
                    }
                        
                    gotsecond = getFoldedValue(Second, symtab, out second);
                    if (gotsecond && second == 1)
                    {
                        Type = ExpType.ConstBool;
                        Value = 1;
                        return false;
                    }

                    if(gotfirst && gotsecond)
                    {
                        Type = ExpType.ConstBool;
                        Value = (first != 0 || second != 0) ? 1 : 0;
                        return false;
                    }
                    break;


            case Funcs.IfThenElse:
                    gotfirst = getFoldedValue(First, symtab, out first);
                    if(gotfirst)
                    {
                        if (first != 0)
                            copyFrom(Second);
                        else
                            copyFrom(Third);
                        return false;
                    }
                    getFoldedValue(Second, symtab, out second);
                    getFoldedValue(Third, symtab, out third);

                    return false;

                case Funcs.ArrayIndex:
                    if (First == null || Second == null)
                        throw new ParseException("Array indexer applied to null or is null!");

                    First.fold(symtab);

                    if (First.Type != ExpType.Var)
                        throw new ParseException("Array indexer applied to something that is not a var!");

                    First.fold(symtab);
                    Second.fold(symtab);

                    /* add init support later, if needed */

                    return false;
            }
            return false;
        }

        public string getCodeString(Func<string, string> vargen = null,
                                    Action<Expression> validator = null)
        {
            if (validator != null)
                validator(this);

            string data = "";
            switch (Type)
            {
                case ExpType.ConstInt:
                    data =  Value.ToString();
                    break;
                case ExpType.ConstBool:
                    data = (Value != 0) ? "B_TRUE" : "B_FALSE";
                    break;

                case ExpType.Var:
                    if (vargen == null)
                        data = Var;
                    else
                        data = vargen(Var);
                    break;

                case ExpType.Func:
                    FUAttribute fu = Func.getFU();
                    switch(fu.fm)
                    {
                        case FM.Unary:
                            data = string.Format(fu.format, First.getCodeString(vargen, validator));
                            break;
                        case FM.Binary:
                            data = string.Format(fu.format, First.getCodeString(vargen, validator), Second.getCodeString(vargen, validator));
                            break;
                        case FM.Trenary:
                            data = string.Format(fu.format, First.getCodeString(vargen, validator), Second.getCodeString(vargen, validator), Third.getCodeString(vargen, validator));
                            break;
                    }
                    break;
            }
            return String.Format("({0})", data);
        }

        private void copyFrom(Expression other)
        {
            Type = other.Type;
            First = other.First;
            Second = other.Second;
            Value = other.Value;
            Var = other.Var;
            Func = other.Func;
        }

        public  enum FM { Unary, Binary, Trenary };
        [System.AttributeUsage(System.AttributeTargets.Field)]
        public class FUAttribute :  System.Attribute
        {
            public string format;
            public FM fm;

            public FUAttribute(FM fm, string format)
            {
                this.fm = fm;
                this.format = format;
            }
        }
    }

    public static class FUHelper
    {
        public static Expression.FUAttribute getFU(this Enum enumVal)
        {
            var type = enumVal.GetType();
            var memInfo = type.GetMember(enumVal.ToString());
            var attributes = memInfo[0].GetCustomAttributes(typeof(Expression.FUAttribute), false);
            return (attributes.Length > 0) ? (Expression.FUAttribute)attributes[0] : null;
        }
    }
}
