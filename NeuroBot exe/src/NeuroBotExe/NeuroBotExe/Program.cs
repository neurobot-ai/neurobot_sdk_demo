using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            //mysdk demo = new mysdk();
            //demo.modelName = "modelname";
            //demo.deviceName = "cpu";
            //demo.modelPath = "c:\\users\\neurobot\\desktop\\disney\\cpu_kuaisu_model";
            //demo.imageFolderPath = "c:\\users\\neurobot\\desktop\\disney\\cpu_kuaisu_pic";
            //demo.sdkMain();
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
            
        }
    }
}
