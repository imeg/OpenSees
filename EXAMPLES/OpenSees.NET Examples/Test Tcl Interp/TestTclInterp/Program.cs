using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Remoting;
using System.Text;
using System.Threading.Tasks;
using System.IO.Pipes;
using System.Runtime.InteropServices;
using System.ComponentModel;
using OpenSees.Tcl;

namespace TestTclInterp
{


    class Writer : TextWriter
    {
        public string Code { get; set; }
        public override Encoding Encoding => System.Text.Encoding.ASCII;

        public Writer(string code)
        {
            Code = code;
        }

        public override void Write(double value)
        {
            Console.Write($"T{Code} {value}");
        }

        public override void Write(string value)
        {
            if (value == "\n")
            {
                Console.Write($"{value}");
                return;
            }
            Console.Write($"T{Code} {value}");
        }

        public override void WriteLine(string value)
        {
            Console.WriteLine($"T{Code} {value}");
        }

        public void SetFontColor(ConsoleColor color)
        {
            Console.ForegroundColor = color;
        }
    }
    class Program
    {


        static void Main(string[] args)
        {
            var wr1 = new Writer("1");
            var opsStream1 = new OpenSees.Handlers.RedirectStreamWrapper(wr1);
            var tclInterp1 = new OpenSees.Tcl.TclWrapper(opsStream1);
            tclInterp1.Init();
            var domain = tclInterp1.GetActiveDomain();
            //var ret = tclInterp1.Execute($"cd {"C:\\Git Projects\\OpenSees.NET - old2\\OpenSees\\Win64\\bin\\".Replace("\\","/")}");
            var ret = tclInterp1.Execute("source exam.tcl");
            var recorders = domain.GetRecorders();
            foreach (var recorder in recorders)
            {
                var retClose = recorder.CloseOutputStreamHandler();
                var header = recorder.GetStreamHeader();
                var filename = recorder.GetFilename();
            }

            tclInterp1.Execute("wipe");
            return;











            //var domain = tclInterp1.GetActiveDomain();
            //domain.AddNodeEventHandler += Domain_AddNodeEventHandler;
            //TclExecutionResult result = new TclExecutionResult()
            //{
            //    ExecutionStatus = (int)OpenSees.Tcl.TclExecutionStatus.Init,
            //};
            //while (true)
            //{
            //    if (result.ExecutionStatus != (int)OpenSees.Tcl.TclExecutionStatus.Partial)
            //        Console.Write("opensees > ");
            //    var cmd = Console.ReadLine();
            //    if (cmd == "exit") break;
            //    result = tclInterp1.Execute(cmd);
            //    var node1 = domain.GetNode(1);
            //    var ele1 = domain.GetElement(1);
            //    if (result.ExecutionStatus == (int)OpenSees.Tcl.TclExecutionStatus.Success)
            //    {
            //        wr1.WriteLine(result.Result);
            //    }
            //    else if (result.ExecutionStatus == (int)OpenSees.Tcl.TclExecutionStatus.Failed)
            //    {

            //        wr1.WriteLine(result.ErrorMessage);
            //    }
            //}
            Console.ReadKey();
        }

        private static void Domain_AddNodeEventHandler(object sender, OpenSees.Components.DomainAddNodeEventArgs e)
        {
            Console.WriteLine($"Node {e.Node.GetTag()} add");
        }
    }

}
