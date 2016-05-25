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
    public delegate string GetNameDelegate(object o);

    class ExpressionGenerator
    {
        public ExpressionGenerator(GetNameDelegate namer, Declarations decls, string stateStructName)
        {
            _stateStructName = stateStructName;
            _decls = decls;
            _namer = namer;
        }

        public string generate(GuardRule gr)
        {
            return String.Format("return ({0});",
                    generate(gr.Expr));
        }

        public string generate(UpdateRule ur)
        {
            VarDecl vd = _decls.getVar(ur.VarName);
            if(vd == null)
                throw new CodeGenException(String.Format("Unknown variable {0}!", ur.VarName));

            string vname;
            if(vd.IsArray)
            {
                if(ur.Expr.Type != Expression.ExpType.Func
                    || ur.Expr.Func != Expression.Funcs.ArrayIndex
                    || ur.Expr.First.Type != Expression.ExpType.Var)
                {
                    throw new CodeGenException(String.Format("Array variable {0} not accessed by index!", vd.Name));
                }
                vd = _decls.getVar(ur.Expr.First.Var);
                vname = String.Format("{0}[{1}]", _namer(vd), generate(ur.Expr.Second));
            }
            else 
            {
                vname = _namer(vd);
            }

            return String.Format("{0}({1}.{2}, ({3}));",
                    getSetter(vd),
                    _stateStructName,
                    vname,
                    generate(ur.Expr));
        }

        public string generate(Expression e)
        {
            // XXX mutex!
            return e.getCodeString((str) => String.Format("{0}({1}.{2})", 
                                        getGetter(_decls.getVar(str)),
                                        _stateStructName, 
                                        _namer(_decls.getVar(str)) 
                                        ),
                                    validateOnGenerate);
        }

        private string getGetter(VarDecl vd)
        {
            switch(vd.Type.Type)
            {
                case VarType.Channel:
                    throw new CodeGenException("Channels cannot be used as variables!");
                case VarType.Clock:
                    return "_U2C_GET_CLK";
                case VarType.Int:
                    return "_U2C_GET_INT";
                default:
                    throw new CodeGenException("Unknown variable type!");
            }
        }

        private string getSetter(VarDecl vd)
        {
            switch (vd.Type.Type)
            {
                case VarType.Channel:
                    throw new CodeGenException("Channels cannot be used as variables!");
                case VarType.Clock:
                    return "_U2C_SET_CLK";
                case VarType.Int:
                    return "_U2C_SET_INT";
                default:
                    throw new CodeGenException("Unknown variable type!");
            }
        }

        private void validateOnGenerate(Expression e)
        {
            if (e.Type != Expression.ExpType.Func)
                return;

            switch (e.Func)
            {
                case Expression.Funcs.UniPlusPlusPre:
                    if (e.First.Type != Expression.ExpType.Var)
                        throw new CodeGenException("'++' operator can only be applied to a variable.");
                    break;
                case Expression.Funcs.UniMinusMinusPre:
                    if (e.First.Type != Expression.ExpType.Var)
                        throw new CodeGenException("'--' operator can only be applied to a variable.");
                    break;
                case Expression.Funcs.UniPlusPlusPost:
                    if (e.First.Type != Expression.ExpType.Var)
                        throw new CodeGenException("'++' operator can only be applied to a variable.");
                    break;
                case Expression.Funcs.UniMinusMinusPost:
                    if (e.First.Type != Expression.ExpType.Var)
                        throw new CodeGenException("'--' operator can only be applied to a variable.");
                    break;
            }
        }

        private string _stateStructName;
        private Declarations _decls;
        private GetNameDelegate _namer;
    }
}
