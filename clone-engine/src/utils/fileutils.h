#pragma once

#include <string>
#pragma once

#include <fstream>
#include <iostream>

namespace clone {

	std::string read_file(const std::string& filename)
	{
		std::ifstream file;
		file.open(filename.c_str());

		std::string output;
		std::string line;

		if (file.is_open())
		{
			while (file.good())
			{
				std::getline(file, line);
				output.append(line + "\n");
			}
		}
		else
		{
			std::cerr << "Unable to open file: " << filename << std::endl;
		}
		return output;
	}
}