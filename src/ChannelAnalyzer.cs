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
    class ChannelAnalyzer
    {
        public ChannelAnalyzer(Model model, GetNameDelegate namer)
        {
            _model = model;
            _namer = namer;
        }

        public IEnumerable<string> getDirOnlyChannels(SyncRule.Direction direction)
        {
            var result = new List<string>();
            foreach (Template t in _model.Templates)
            {
                foreach (var r in t.Transitions
                    .SelectMany(tr => tr.Rules)
                    .Select(s => s as SyncRule)
                    .Where(s => (s != null && s.Dir == direction)))
                {
                    VarDecl vd;
                    switch (r.Expr.Type)
                    {
                        case Expression.ExpType.Func:
                            // might be array/range
                            int idx;
                            if (r.Expr.Func == Expression.Funcs.ArrayIndex
                                && r.Expr.First.Type == Expression.ExpType.Var
                                && t.Declarations.getExprValue(r.Expr.Second, out idx))
                            {
                                vd = t.Declarations.getVar(r.Expr.First.Var);
                                if (vd != null && vd.Type.Type == VarType.Channel)
                                    for (int i = 0; i < vd.ArrLength; ++i)
                                        result.Add(String.Format("{0}_{1}", _namer(vd), vd.ArrLow + i));
                            }
                            break;

                        case Expression.ExpType.Var:
                            vd = t.Declarations.getVar(r.Expr.Var);
                            if (vd != null && vd.Type.Type == VarType.Channel)
                                result.Add(_namer(vd));
                            break;
                    }
                }
            }
            return result.Distinct().OrderBy(x => x);
        }

        private Model _model;
        private GetNameDelegate _namer;
    }
}
