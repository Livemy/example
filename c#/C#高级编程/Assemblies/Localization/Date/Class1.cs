using System;
using System.Globalization;
using System.Threading;

namespace Wrox.ProCSharp.Assemblies.LocalDateExample
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class Class1
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			DateTime d = new DateTime(2002, 2, 13);

			// current culture

			System.Console.WriteLine(d.ToLongDateString());

			// use IFormatProvider

			System.Console.WriteLine(d.ToString("D", 
				new CultureInfo("fr-fr")));

			// use culture of thread

			CultureInfo ci = Thread.CurrentThread.CurrentCulture;
			Console.WriteLine(ci.ToString() + ": " + d.ToString("D"));
			ci = new CultureInfo("de-de");
			Thread.CurrentThread.CurrentCulture = ci;
			Console.WriteLine(ci.ToString() + ": " + d.ToString("D"));
			Console.ReadLine();

		}
	}
}
