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
using System.Security.Authentication.ExtendedProtection;
using System.Text;
using System.Threading.Tasks;
using uppaal2c;

namespace uppaal2c
{
    public enum VarType
    {
        Int,
        Clock,
        Channel
    }

    public class TypeDecl
    {
        public TypeDecl()
        {
            HaveRange = false;
        }

        public bool Const { get; set; }
        public bool Urgent { get; set; }
        public bool Broadcast { get; set; }
        public bool HaveRange { get; set; }
        public int RangeLow { get; set; }
        public int RangeHigh{ get; set; }
        public void SetRange(int low, int high)
        {
            if (Type != VarType.Int)
                throw new ParseException("Type can only be an int");

            RangeLow = low;
            RangeHigh = high;
            HaveRange = true;
        }
        public VarType Type
        {
            get { return _type;  }
            set {

                _type = value;
                sanitizeFlags();
            }
        }

        public void merge(TypeDecl typedef)
        {
            Type = typedef.Type;
            if (typedef.Const)
                Const = true;
            if (typedef.Urgent)
                Urgent = true;
            if (typedef.Broadcast)
                Broadcast = true;

            sanitizeFlags();

        }

        public void sanitizeFlags()
        {
                switch(_type)
                {
                    case VarType.Int:
                        if (Urgent || Broadcast) throw new ParseException("Int cannot be urgent or broadcast.");
                        break;
                    case VarType.Clock:
                        if (Const || Urgent || Broadcast) throw new ParseException("Clock cannot be const or urgent or broadcast.");
                        break;
                    case VarType.Channel:
                        if(Const) throw new ParseException("Channel cannot be const.");
                        break;
                }
        }

        public string NiceName()
        {
            StringBuilder b = new StringBuilder();
            if (Const)
                b.Append("const ");
            if (Urgent)
                b.Append("urgent ");
            if (Broadcast)
                b.Append("brodcast ");
            switch(_type)
            {
                case VarType.Int: b.Append("int"); break;
                case VarType.Clock: b.Append("clock"); break;
                case VarType.Channel: b.Append("chan"); break;
                default:
                    throw new Exception("Type not implemented yet.");
            }
            if(HaveRange)
                b.AppendFormat("[{0},{1}]", RangeLow, RangeHigh);
            return b.ToString();
        }

        private VarType _type;
    }
}
