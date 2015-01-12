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
    public class Declarations
    {
        public Declarations(Declarations parent = null)
        {
            Parent = parent;
        }

        public Declarations Parent { get; set; }

        public void Add(VarDecl vdecl)
        {
            verifyCleanName(vdecl.Name);

            _vdefs.Add(vdecl);
        }

        public void Add(TypedefDecl tdecl)
        {
            verifyCleanName(tdecl.Name);

            _tdefs.Add(tdecl.Name, tdecl);

        }

        public VarDecl getFirstDecl()
        {
            return _vdefs[0];
        }

        public IEnumerable<VarDecl> getAllVars()
        {
            return _vdefs;
        }

        public VarDecl[] getVarsByType(VarType t)
        {
            return _vdefs.Where(v => v.Type.Type == t).ToArray();
        }
            
        protected void verifyCleanName(string name)
        {
            if (getTypeDef(name) != null || getVar(name) != null)
                throw new ParseException(String.Format("Duplicate name '{0}'!", name));
        }

        public bool getExprValue(Expression expr, out int val)
        {
            val = 0;

            expr.fold(this);
            if (expr.Type != Expression.ExpType.ConstInt && expr.Type != Expression.ExpType.ConstBool)
                return false;
            val = expr.Value;
            return true;
        }

        public bool getArrSizeValue(Expression expr, out int low, out int length)
        {
            low = length = 0;

            if(expr.Type == Expression.ExpType.Var)
            {
                // see if its a typedef
                TypedefDecl tdef = getTypeDef(expr.Var);
                if(tdef != null)
                {
                    if(tdef.Type.HaveRange)
                    {
                        low = tdef.Type.RangeLow;
                        length = tdef.Type.RangeHigh - tdef.Type.RangeLow + 1;
                        return true;
                    }
                    throw new ParseException(String.Format("Typedef {0} is not a range specifier.", expr.Var));
                }
            }
            int val;
            if (!getExprValue(expr, out val))
                return false;
            low = 0;
            length = val;
            return true;
        }

        
        public bool getVarValue(string varname, out int val)
        {
            val = 0;
            VarDecl res = getVar(varname);
            if(res == null)
                throw new ParseException(String.Format("Value '{0}': unknown!", varname));
            if (res.IsArray)
                throw new ParseException(String.Format("Value '{0}': Indexers not yet support on consts!", varname));

            if (res.Type.Type != VarType.Int)
                return false;

            if (!res.HasExpr)
                throw new ParseException(String.Format("Value '{0}': not initialized!", varname));

            if (!res.Type.Const)
                return false;

            return getExprValue(res.Expr, out val);
        }

        public TypeDecl normalizeType(TypeDecl decl, string name)
        {
            TypedefDecl exists = getTypeDef(name);
            if (exists == null)
                throw new ParseException("Invalid type " + name);

            decl.merge(exists.Type);

            return decl;

        }

        public TypedefDecl getTypeDef(string name)
        {
            TypedefDecl tdef = null;

            if (_tdefs.TryGetValue(name, out tdef))
                return tdef;
            if (Parent != null)
                return Parent.getTypeDef(name);
            return null;
        }

        public VarDecl getVar(string name)
        {
            VarDecl vdef = _vdefs.SingleOrDefault(var => var.Name == name);

            if (vdef != null)
                return vdef;
            if (Parent != null)
                return Parent.getVar(name);
            return null;
        }

        public void removeVar(VarDecl vd)
        {
            _vdefs.Remove(vd);
        }

        public class VarWithScope
        {
            public VarDecl var;
            public Declarations decl;
        }

        public VarWithScope getVarWithScope(string name)
        {
            VarDecl vdef = _vdefs.SingleOrDefault(var => var.Name == name);

            if (vdef != null)
                return new VarWithScope() { var = vdef, decl = this };
            if (Parent != null)
                return Parent.getVarWithScope(name);
            return null;
        }

        public void setChannelPriority(uppaal2c.Expression e) 
        {
            _channel_priorities[e.getCodeString()] = curChannelPriority;
        }

        public void setChannelDefaultPriority()
        {
            defaultChannelPriority = curChannelPriority;
        }

        public void nextChannelPriority()
        {
            curChannelPriority += 1;
        }

        public int getChannelPriority(Expression e)
        {
            int p;
            if(_channel_priorities.TryGetValue(e.getCodeString(), out p))
                return p;
            if(Parent != null)
                return Parent.getChannelPriority(e);
            return defaultChannelPriority;
        }

        private int curChannelPriority = 0;
        private int defaultChannelPriority = 0;


        private List<VarDecl> _vdefs = new List<VarDecl>(); // sorted
        private Dictionary<string, TypedefDecl> _tdefs = new Dictionary<string, TypedefDecl>();

        private Dictionary<string, int> _channel_priorities = new Dictionary<string, int>();
    }
}
