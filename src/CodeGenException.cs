using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace uppaal2c
{
    public class CodeGenException : Exception
    {
        public CodeGenException(string msg)
            : base(msg)
        {
        }
    }
}
