using BearBuildTool.Projects;
using System.IO;
using System;
public class bear_ui : Project
{
	public bear_ui(string ProjectPath)
	{
		PCHFile=Path.Combine(ProjectPath,"source", "BearUI.cpp");
		PCHIncludeFile= "BearUI.hpp";
		AddSourceFiles(Path.Combine(ProjectPath,"source"),true);
		Include.Public.Add(Path.Combine(ProjectPath,"include"));
        Projects.Public.Add("bear_core");
        Projects.Public.Add("bear_graphics");
        Projects.Private.Add("freetype");
		if(BearBuildTool.Config.Global.Platform == BearBuildTool.Config.Platform.Win64
		||BearBuildTool.Config.Global.Platform == BearBuildTool.Config.Platform.Win32)
		{
			LibrariesStatic.Private.Add("freetype26.lib");
		}

    }
} 