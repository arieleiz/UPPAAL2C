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
    class ReferenceOptimizer
    {
        public static void cleanup(Model m)
        {
            ReferenceOptimizer r = new ReferenceOptimizer(m);
            r.markUnreferenced();
            r.markReferences();
            r.discardUnreferenced();
        }

        private ReferenceOptimizer(Model m)
        {
            _model = m;
        }

        private void markUnreferenced()
        {
            markUnreferenced(_model.Declarations);
            foreach(var t in _model.Templates)
                markUnreferenced(t.Declarations);
        }

        private void markUnreferenced(Declarations d)
        {
            foreach (VarDecl vd in d.getAllVars())
                vd.Referenced = false;
        }

        private void markReferences()
        {
            foreach (var t in _model.Templates)
                markReferences(t);
        }

        private void markReferences(Template t)
        {
            foreach (var s in t.Nodes)
                markReferences(t, s.Rules);
            foreach (var tr in t.Transitions)
                markReferences(t, tr.Rules);
        }

        private void markReferences(Template t, IEnumerable<Rule> rules)
        {
            foreach (var r in rules)
            {
                if (r.Expr != null)
                {
                    if(r is UpdateRule)
                    {
                        markReferencesForVar(t.Declarations, ((UpdateRule)r).VarName);
                    }
                    markReferences(t.Declarations, r.Expr);
                }
            }
        }

        private void markReferences(Declarations d, Expression e)
        {
            switch (e.Type)
            {
                case Expression.ExpType.ConstInt:
                    return;
                case Expression.ExpType.ConstBool:
                    return;

                case Expression.ExpType.Var:
                    markReferencesForVar(d, e.Var);
                    return;

                case Expression.ExpType.Func:
                    if (e.First != null)
                        markReferences(d, e.First);
                    if (e.Second != null)
                        markReferences(d, e.Second);
                    if (e.Third != null)
                        markReferences(d, e.Third);
                    return;
            }
        }

        private void markReferencesForVar(Declarations d, string var)
        {
            var data = d.getVarWithScope(var);
            if (data == null)
                throw new Exception(String.Format("Could not find variable: {0}", var));
            if (data.var.Referenced)
                return;

            data.var.Referenced = true;
            if (data.var.HasExpr)
                markReferences(data.decl, data.var.Expr);
        }

        private void discardUnreferenced()
        {
            discardUnreferenced(_model.Declarations);
            foreach (var t in _model.Templates)
                discardUnreferenced(t.Declarations);
        }

        private void discardUnreferenced(Declarations d)
        {
            VarDecl[] vds = d.getAllVars().ToArray();
            foreach(VarDecl vd in vds)
            {
                if (!vd.Referenced)
                    d.removeVar(vd);
            }
        }

        private Model _model;
    }
}
