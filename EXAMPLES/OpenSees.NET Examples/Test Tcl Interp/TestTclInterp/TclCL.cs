using OpenSees.Tcl;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestTclInterp
{
    public enum TclExecutionStatus : int
    {
        Success = 1,
        Failed = 2,
        Partial = 3,
    }

    public struct ExecutionResult
    {
        public TclExecutionStatus ExecutionStatus { get; set; }
        public Object Result { get; set; }
        public String ErrorMessage { get; set; }
    }

    public class TclCommandLine
    {
        private string _cmd;
        private TclWrapper _tcl;
        private TextWriter _tw;
        public TclCommandLine(OpenSees.Tcl.TclWrapper tcl, TextWriter textWriter)
        {
            _tcl = tcl;
            _tw = textWriter;
        }

        
    }
}
