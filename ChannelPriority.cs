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
    class ChannelPriority
    {
        public static IEnumerable<StateTransition> getSortedTransitions(Declarations d, IEnumerable<StateTransition> ts)
        {
            StateTransition[] transitions = ts.ToArray();
            Array.Sort(transitions, (new ChannelPriority(d)).compareByChannelPriority);
            return transitions;
        }

        private ChannelPriority(Declarations d)
        {
            _decls = d;
        }

        int compareByChannelPriority(StateTransition x, StateTransition y)
        {
            SyncRule xr = (SyncRule)x.Rules.SingleOrDefault(r => r is SyncRule);
            SyncRule yr = (SyncRule)y.Rules.SingleOrDefault(r => r is SyncRule);

            // no sync rules are last
            if (xr == null && yr == null)
                return x.Name.CompareTo(y.Name);
            if (xr == null)
                return -1;
            if (yr == null)
                return 1;

            // both have sync rules
            int xp = _decls.getChannelPriority(xr.Expr);
            int yp = _decls.getChannelPriority(yr.Expr);
            return xp.CompareTo(yp);
        }

        private Declarations _decls;
    }
}
