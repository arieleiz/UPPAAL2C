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
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace uppaal2c
{
    class UPAALParser
    {
        public static Model Parse(string path, IEnumerable<string> templates)
        {
            UPAALParser parser = new UPAALParser(templates);
            return parser.run(path);
        }

        private UPAALParser(IEnumerable<string> templates)
        {
            foreach(string s in templates)
                _templates.Add(s);
        }

        private Model run(string path)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(path);

            XmlNode declsnode = doc.SelectSingleNode("/nta/declaration");
            Declarations decls = new Declarations();
            if (declsnode != null && getElementText(declsnode) != null)
            {
                decls = parseDeclarations(getElementText(declsnode), null);
            }

            XmlNodeList templates = doc.SelectNodes("/nta/template");
            if (templates == null)
                throw new ParseException("No templates found!");

            Template[] tmpllist = (from XmlNode node in templates select parseTemplate((XmlElement) node, decls)).Where(n => n != null).ToArray();

            return new Model(decls, tmpllist);
        }

        private Template parseTemplate(XmlElement node, Declarations globaldecls)
        {
            try
            {
                Console.WriteLine("  Parsing template ...");
                TemplateState state = new TemplateState();
                XmlNodeList subnodes;

                XmlNode namenode = node.SelectSingleNode("./name");
                if (namenode == null || string.IsNullOrEmpty(getElementText(namenode)))
                    throw new ParseException("No name node!");
                state._name = getElementText(namenode);
                if(_templates.Count > 0 && !_templates.Contains(state._name))
                    return null;

                XmlNode decnode = node.SelectSingleNode("./declaration");
                if (decnode != null)
                    state._declarations = parseDeclarations(getElementText(decnode), globaldecls);
                else
                    state._declarations = new Declarations() { Parent = globaldecls };

                Console.WriteLine("     Name: " + state._name);

                subnodes = node.SelectNodes("./location");
                if (subnodes != null)
                {
                    foreach (XmlNode subnode in subnodes)
                    {
                        StateNode sn = parseNode((XmlElement)subnode, state._declarations);
                        state._nodes.Add(sn);
                    }
                }
                subnodes = node.SelectNodes("./transition");
                if (subnodes != null)
                {
                    foreach (XmlNode subnode in subnodes)
                    {
                        StateTransition st = parseTransition((XmlElement)subnode, state);
                        state._transitions.Add(st);
                    }

                }

                XmlNode initnode = node.SelectSingleNode("./init");
                if (initnode == null || string.IsNullOrEmpty(((XmlElement)initnode).GetAttribute("ref")))
                    throw new ParseException("No init node!");

                state._init = findNode(((XmlElement)initnode).GetAttribute("ref"), state);
                if (state._init == null)
                    throw new ParseException("Init node not found");

                XmlNode parameter = node.SelectSingleNode("./parameter");
                if (parameter != null)
                    throw new ParseException("template parameters not yet supported, easy to add if needed!");

                return new Template(state._name, state._declarations, state._init, state._nodes.ToArray(), state._transitions.ToArray());
            }
            catch (SelectNotSupportException)
            {
                return null; // for now
            }
        }

        private string getElementText(XmlNode node)
        {
            if (node == null)
                return null;
            if(node is XmlElement)
            {
                foreach(XmlNode n in node.ChildNodes)
                {
                    if (n is XmlText)
                        return n.Value;
                }
            }
            return node.Value;
        }
        private StateTransition parseTransition(XmlElement node, TemplateState state)
        {
            Console.WriteLine("    Parsing transition ...");

            string id = node.GetAttribute("id");
            if (id == null)
                throw new ParseException("Expected id in <location>");

            XmlNode source = node.SelectSingleNode("./source");
            if (source == null)
                throw new ParseException("Expected source in <location>");
            XmlNode target = node.SelectSingleNode("./target");
            if (target == null)
                throw new ParseException("Expected source in <location>");
            string srcid = ((XmlElement) source).GetAttribute("ref");
            if(string.IsNullOrEmpty(srcid) )
                throw new ParseException("No source id for transition");
            string tgtid = ((XmlElement)target).GetAttribute("ref");
            if (string.IsNullOrEmpty(tgtid))
                throw new ParseException("No target id for transition");

            StateNode tgtnode = findNode(tgtid, state);
            if (tgtnode == null)
                throw new ParseException("Target node not found for transition");

            StateNode srcnode = findNode(srcid, state);
            if (srcnode == null)
                throw new ParseException("Source node not found for transition");

            string name = null;
            XmlNodeList namenodes = node.SelectNodes("./label[@kind='comments']");
            if (namenodes != null)
            {
                XmlNode namenode = (from XmlNode n in namenodes select n).SingleOrDefault(n => getElementText(n).Contains("{name="));
                if(namenode != null)
                {
                    string txt = getElementText(namenode);
                    int pos = txt.IndexOf("{name=");
                    txt = txt.Substring(pos + 6);
                    pos = txt.IndexOf("}");
                    if (pos > 0)
                        name = txt.Substring(0, pos);
                }
            }
            StateTransition st = new StateTransition(state._name, srcnode, tgtnode, name);

            st.Rules = parseRules(node, st.Name, state._declarations);
            return st;
        }

        private StateNode findNode(string nodeid, TemplateState state)
        {
            return state._nodes.Find(node => node.NodeId == nodeid);
        }

        private StateNode parseNode(XmlElement node, Declarations decls)
        {
            Console.WriteLine("    Parsing node ...");

            string id = node.GetAttribute("id");
            if(id == null)
                throw new ParseException("Expected id in <location>");

            XmlNode namenode = node.SelectSingleNode("./name");
            string name = string.IsNullOrEmpty(getElementText(namenode))
                ? String.Format("Unnamed{0}", _noname ++)
                : getElementText(namenode);

            NodeMode mode = NodeMode.Regular;
            if(node.SelectSingleNode("./commited") != null)
                mode = NodeMode.Commited;
            else
                if (node.SelectSingleNode("./urgent") != null)
                    mode = NodeMode.Commited;

            StateNode sn = new StateNode(name, id, mode);
            sn.Rules = parseRules(node, sn.Name, decls);
            return sn;
        }

        private Rule[] parseRules(XmlElement node, string pname, Declarations decls)
        {
            Console.WriteLine("    Parsing rules ...");

            XmlNodeList nodes = node.SelectNodes("./label");
            List<Rule> rules = new List<Rule>();
            foreach(XmlNode subnode in nodes)
            {
                XmlElement elem = (XmlElement)subnode;
                string kind = elem.GetAttribute("kind");
                string values_str = getElementText(elem);
                switch (kind)
                {
                    case "comments":
                        break;
                    case "synchronisation":
                        rules.Add(parseSyncRule(pname, values_str.Trim(), decls));
                        break;
                    case "invariant":
                        rules.Add(parseGuardRule(pname, values_str.Trim(), decls));
                        break;
                    case "guard":
                        rules.Add(parseGuardRule(pname, values_str.Trim(), decls));
                        break;
                    case "assignment":
                        string[] values = values_str.Split(new char[] {','});
                        rules.AddRange(values.Select(value => parseUpdateRule(pname, value.Trim(), decls)));
                        break;
                    case "select":
                        Console.WriteLine("WARNING: transaction select not yet supported!");
                        throw new SelectNotSupportException();
                        //throw new ParseException("transaction select not yet supported!");
                        //break;
                    default:
                        throw new ParseException(String.Format("label of kind {0} not supported!", kind));
                }
            }
            return rules.ToArray();

        }

        private Rule parseSyncRule(string pname, string rule, Declarations decls)
        {
            SyncRule.Direction dir;

            if (rule.EndsWith("?"))
                dir = SyncRule.Direction.Receive;
            else 
            if (rule.EndsWith("!"))
                dir = SyncRule.Direction.Send;
            else 
                throw new ParseException(String.Format("Synchronization rule '{0}' must end with '!' or '?'!"));

            rule = rule.TrimEnd(new char[] { '?', '!' });
            string expr = String.Format("chan _CHANNEL_ = {0};", rule);
            Declarations newdecls = parseDeclarations(expr, decls);
            Expression e = newdecls.getVar("_CHANNEL_").Expr;
            e.fold(newdecls);
            return new SyncRule(e, dir);
        }

        private Rule parseGuardRule(string pname, string rule, Declarations decls)
        {
            string expr = String.Format("bool _GUARD_ = {0};", rule);
            Declarations newdecls = parseDeclarations(expr, decls);
            Expression e = newdecls.getVar("_GUARD_").Expr;
            e.fold(newdecls);
            return new GuardRule(e);
        }

        private Rule parseUpdateRule(string pname, string rule, Declarations decls)
        {
            int len = 1;
            int equal = rule.IndexOf(":=");
            if (equal < 0)
                equal = rule.IndexOf('=');
            else
                len = 2;
            if(equal < 0)
                throw new ParseException(String.Format("Invalid update rule '{0}'!", rule));

            string varname = rule.Substring(0, equal).Trim();
            string upexpr = rule.Substring(equal + len).Trim();

            VarDecl vd = decls.getVar(varname);
            if(vd == null)
                throw new ParseException(String.Format("Unknown variable {0}!", varname));

            string expr = String.Format("int _UPDATE_{0} = {1};", varname, upexpr);
            Declarations newdecls = parseDeclarations(expr, decls);
            Expression e = newdecls.getFirstDecl().Expr;
            e.fold(newdecls);
            return new UpdateRule(varname, e);
        }

        private Declarations parseDeclarations(string s, Declarations parent)
        {
            Console.WriteLine("     Parsing declarations ...");
            Scanner scanner = new Scanner(genStreamFromString(s));
            Parser parser = new Parser(scanner);
            parser.decls.Parent = parent;
            parser.Parse();
            if(parser.errors.count > 0 )
            {
                throw new ParseException(String.Format("{0} error(s).", parser.errors.count));
            }
            return parser.decls;
        }

        private Stream genStreamFromString(string p)
        {
            return new MemoryStream(_ascii.GetBytes(p));
        }

        private ASCIIEncoding _ascii = new ASCIIEncoding();

        private class TemplateState
        {
            public Declarations _declarations = new Declarations();
            public List<StateNode> _nodes = new List<StateNode>();
            public List<StateTransition> _transitions = new List<StateTransition>();
            public StateNode _init;
            public string _name;
        }

        class SelectNotSupportException : Exception { }

        private int _noname = 0;
        private HashSet<string> _templates = new HashSet<string>();
    }
}
